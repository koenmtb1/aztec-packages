#include "sumcheck.hpp"
#include "barretenberg/ecc/curves/bn254/fr.hpp"
#include "barretenberg/polynomials/polynomial.hpp"
#include "barretenberg/relations/auxiliary_relation.hpp"
#include "barretenberg/relations/delta_range_constraint_relation.hpp"
#include "barretenberg/relations/elliptic_relation.hpp"
#include "barretenberg/relations/permutation_relation.hpp"
#include "barretenberg/relations/ultra_arithmetic_relation.hpp"
#include "barretenberg/stdlib_circuit_builders/mega_zk_flavor.hpp"
#include "barretenberg/stdlib_circuit_builders/plookup_tables/fixed_base/fixed_base.hpp"
#include "barretenberg/stdlib_circuit_builders/ultra_flavor.hpp"
#include "barretenberg/stdlib_circuit_builders/ultra_zk_flavor.hpp"
#include "barretenberg/transcript/transcript.hpp"
#include <gtest/gtest.h>

using namespace bb;

namespace {
template <typename Flavor> class SumcheckTests : public ::testing::Test {
  public:
    using FF = typename Flavor::FF;
    using ProverPolynomials = typename Flavor::ProverPolynomials;
    using RelationSeparator = Flavor::RelationSeparator;
    const size_t NUM_POLYNOMIALS = Flavor::NUM_ALL_ENTITIES;
    static void SetUpTestSuite() { bb::srs::init_crs_factory("../srs_db/ignition"); }

    Polynomial<FF> random_poly(size_t size)
    {
        auto poly = bb::Polynomial<FF>(size);
        for (auto& coeff : poly.coeffs()) {
            coeff = FF::random_element();
        }
        return poly;
    }

    ProverPolynomials construct_ultra_full_polynomials(auto& input_polynomials)
    {
        ProverPolynomials full_polynomials;
        for (auto [full_poly, input_poly] : zip_view(full_polynomials.get_all(), input_polynomials)) {
            full_poly = input_poly.share();
        }
        return full_polynomials;
    }

    void test_polynomial_normalization()
    {
        // TODO(#225)(Cody): We should not use real constants like this in the tests, at least not in so many of them.
        const size_t multivariate_d(3);
        const size_t multivariate_n(1 << multivariate_d);

        // Randomly construct the prover polynomials that are input to Sumcheck.
        // Note: ProverPolynomials are defined as spans so the polynomials they point to need to exist in memory.
        std::vector<bb::Polynomial<FF>> random_polynomials(NUM_POLYNOMIALS);
        for (auto& poly : random_polynomials) {
            poly = random_poly(multivariate_n);
        }
        auto full_polynomials = construct_ultra_full_polynomials(random_polynomials);

        auto transcript = Flavor::Transcript::prover_init_empty();

        auto sumcheck = SumcheckProver<Flavor>(multivariate_n, transcript);
        RelationSeparator alpha;
        for (size_t idx = 0; idx < alpha.size(); idx++) {
            alpha[idx] = transcript->template get_challenge<FF>("Sumcheck:alpha_" + std::to_string(idx));
        }

        std::vector<FF> gate_challenges(multivariate_d);
        for (size_t idx = 0; idx < multivariate_d; idx++) {
            gate_challenges[idx] =
                transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
        }
        auto output = sumcheck.prove(full_polynomials, {}, alpha, gate_challenges);

        FF u_0 = output.challenge[0];
        FF u_1 = output.challenge[1];
        FF u_2 = output.challenge[2];

        /* sumcheck.prove() terminates with sumcheck.multivariates.folded_polynoimals as an array such that
         * sumcheck.multivariates.folded_polynoimals[i][0] is the evaluatioin of the i'th multivariate at the vector of
         challenges u_i. What does this mean?

         Here we show that if the multivariate is F(X0, X1, X2) defined as above, then what we get is F(u0, u1, u2) and
         not, say F(u2, u1, u0). This is in accordance with Adrian's thesis (cf page 9).
          */

        // Get the values of the Lagrange basis polys L_i defined
        // by: L_i(v) = 1 if i = v, 0 otherwise, for v from 0 to 7.
        FF one{ 1 };
        // clang-format off
        FF l_0 = (one - u_0) * (one - u_1) * (one - u_2);
        FF l_1 = (u_0) * (one - u_1) * (one - u_2);
        FF l_2 = (one - u_0) * (u_1) * (one - u_2);
        FF l_3 = (u_0) * (u_1) * (one - u_2);
        FF l_4 = (one - u_0) * (one - u_1) * (u_2);
        FF l_5 = (u_0) * (one - u_1) * (u_2);
        FF l_6 = (one - u_0) * (u_1) * (u_2);
        FF l_7 = (u_0) * (u_1) * (u_2);
        // clang-format on
        FF hand_computed_value;
        for (auto [full_poly, partial_eval_poly] :
             zip_view(full_polynomials.get_all(), sumcheck.partially_evaluated_polynomials.get_all())) {
            // full_polynomials[0][0] = w_l[0], full_polynomials[1][1] = w_r[1], and so on.
            hand_computed_value = l_0 * full_poly[0] + l_1 * full_poly[1] + l_2 * full_poly[2] + l_3 * full_poly[3] +
                                  l_4 * full_poly[4] + l_5 * full_poly[5] + l_6 * full_poly[6] + l_7 * full_poly[7];
            EXPECT_EQ(hand_computed_value, partial_eval_poly[0]);
        }

        // We can also check the correctness of the multilinear evaluations produced by Sumcheck by directly evaluating
        // the full polynomials at challenge u via the evaluate_mle() function
        std::vector<FF> u_challenge = { u_0, u_1, u_2 };
        for (auto [full_poly, claimed_eval] :
             zip_view(full_polynomials.get_all(), output.claimed_evaluations.get_all())) {
            Polynomial<FF> poly(full_poly);
            auto v_expected = poly.evaluate_mle(u_challenge);
            EXPECT_EQ(v_expected, claimed_eval);
        }
    }

    void test_prover()
    {
        const size_t multivariate_d(2);
        const size_t multivariate_n(1 << multivariate_d);

        // Randomly construct the prover polynomials that are input to Sumcheck.
        // Note: ProverPolynomials are defined as spans so the polynomials they point to need to exist in memory.
        std::vector<Polynomial<FF>> random_polynomials(NUM_POLYNOMIALS);
        for (auto& poly : random_polynomials) {
            poly = random_poly(multivariate_n);
        }
        auto full_polynomials = construct_ultra_full_polynomials(random_polynomials);

        auto transcript = Flavor::Transcript::prover_init_empty();

        auto sumcheck = SumcheckProver<Flavor>(multivariate_n, transcript);

        RelationSeparator alpha;
        for (size_t idx = 0; idx < alpha.size(); idx++) {
            alpha[idx] = transcript->template get_challenge<FF>("Sumcheck:alpha_" + std::to_string(idx));
        }

        std::vector<FF> gate_challenges(multivariate_d);
        for (size_t idx = 0; idx < gate_challenges.size(); idx++) {
            gate_challenges[idx] =
                transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
        }
        SumcheckOutput<Flavor> output;

        if constexpr (Flavor::HasZK) {
            ZKSumcheckData<Flavor> zk_sumcheck_data(multivariate_d, transcript);
            output = sumcheck.prove(full_polynomials, {}, alpha, gate_challenges, zk_sumcheck_data);
        } else {
            output = sumcheck.prove(full_polynomials, {}, alpha, gate_challenges);
        }
        FF u_0 = output.challenge[0];
        FF u_1 = output.challenge[1];
        std::vector<FF> expected_values;
        for (auto& polynomial_ptr : full_polynomials.get_all()) {
            auto& polynomial = polynomial_ptr;
            // using knowledge of inputs here to derive the evaluation
            FF expected_lo = polynomial[0] * (FF(1) - u_0) + polynomial[1] * u_0;
            expected_lo *= (FF(1) - u_1);
            FF expected_hi = polynomial[2] * (FF(1) - u_0) + polynomial[3] * u_0;
            expected_hi *= u_1;
            expected_values.emplace_back(expected_lo + expected_hi);
        }

        for (auto [eval, expected] : zip_view(output.claimed_evaluations.get_all(), expected_values)) {
            eval = expected;
        }
    }

    // TODO(#225): make the inputs to this test more interesting, e.g. non-trivial permutations
    void test_prover_verifier_flow()
    {
        const size_t multivariate_d(2);
        const size_t multivariate_n(1 << multivariate_d);

        // Construct prover polynomials where each is the zero polynomial.
        // Note: ProverPolynomials are defined as spans so the polynomials they point to need to exist in memory.
        std::vector<Polynomial<FF>> zero_polynomials(NUM_POLYNOMIALS);
        for (auto& poly : zero_polynomials) {
            poly = bb::Polynomial<FF>(multivariate_n);
        }
        auto full_polynomials = construct_ultra_full_polynomials(zero_polynomials);

        // Add some non-trivial values to certain polynomials so that the arithmetic relation will have non-trivial
        // contribution. Note: since all other polynomials are set to 0, all other relations are trivially
        // satisfied.
        std::array<FF, multivariate_n> w_l;
        w_l = { 0, 1, 2, 0 };
        std::array<FF, multivariate_n> w_r = { 0, 1, 2, 0 };
        std::array<FF, multivariate_n> w_o = { 0, 2, 4, 0 };
        std::array<FF, multivariate_n> w_4 = { 0, 0, 0, 0 };
        std::array<FF, multivariate_n> q_m = { 0, 0, 1, 0 };
        std::array<FF, multivariate_n> q_l = { 0, 1, 0, 0 };
        std::array<FF, multivariate_n> q_r = { 0, 1, 0, 0 };
        std::array<FF, multivariate_n> q_o = { 0, -1, -1, 0 };
        std::array<FF, multivariate_n> q_c = { 0, 0, 0, 0 };
        std::array<FF, multivariate_n> q_arith = { 0, 1, 1, 0 };
        // Setting all of these to 0 ensures the GrandProductRelation is satisfied

        full_polynomials.w_l = bb::Polynomial<FF>(w_l);
        full_polynomials.w_r = bb::Polynomial<FF>(w_r);
        full_polynomials.w_o = bb::Polynomial<FF>(w_o);
        full_polynomials.w_4 = bb::Polynomial<FF>(w_4);
        full_polynomials.q_m = bb::Polynomial<FF>(q_m);
        full_polynomials.q_l = bb::Polynomial<FF>(q_l);
        full_polynomials.q_r = bb::Polynomial<FF>(q_r);
        full_polynomials.q_o = bb::Polynomial<FF>(q_o);
        full_polynomials.q_c = bb::Polynomial<FF>(q_c);
        full_polynomials.q_arith = bb::Polynomial<FF>(q_arith);

        // Set aribitrary random relation parameters
        RelationParameters<FF> relation_parameters{
            .beta = FF::random_element(),
            .gamma = FF::random_element(),
            .public_input_delta = FF::one(),
        };
        auto prover_transcript = Flavor::Transcript::prover_init_empty();
        auto sumcheck_prover = SumcheckProver<Flavor>(multivariate_n, prover_transcript);

        RelationSeparator prover_alpha;
        for (size_t idx = 0; idx < prover_alpha.size(); idx++) {
            prover_alpha[idx] = prover_transcript->template get_challenge<FF>("Sumcheck:alpha_" + std::to_string(idx));
        }
        std::vector<FF> prover_gate_challenges(multivariate_d);
        for (size_t idx = 0; idx < multivariate_d; idx++) {
            prover_gate_challenges[idx] =
                prover_transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
        }
        SumcheckOutput<Flavor> output;
        if constexpr (Flavor::HasZK) {
            ZKSumcheckData<Flavor> zk_sumcheck_data(multivariate_d, prover_transcript);
            output = sumcheck_prover.prove(
                full_polynomials, relation_parameters, prover_alpha, prover_gate_challenges, zk_sumcheck_data);
        } else {
            output = sumcheck_prover.prove(full_polynomials, relation_parameters, prover_alpha, prover_gate_challenges);
        }

        auto verifier_transcript = Flavor::Transcript::verifier_init_empty(prover_transcript);

        auto sumcheck_verifier = SumcheckVerifier<Flavor>(multivariate_d, verifier_transcript);
        RelationSeparator verifier_alpha;
        for (size_t idx = 0; idx < verifier_alpha.size(); idx++) {
            verifier_alpha[idx] =
                verifier_transcript->template get_challenge<FF>("Sumcheck:alpha_" + std::to_string(idx));
        }
        std::vector<FF> verifier_gate_challenges(multivariate_d);
        for (size_t idx = 0; idx < multivariate_d; idx++) {
            verifier_gate_challenges[idx] =
                verifier_transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
        }
        auto verifier_output = sumcheck_verifier.verify(relation_parameters, verifier_alpha, verifier_gate_challenges);

        auto verified = verifier_output.verified.value();

        EXPECT_EQ(verified, true);
    };

    void test_failure_prover_verifier_flow()
    {
        const size_t multivariate_d(2);
        const size_t multivariate_n(1 << multivariate_d);

        // Construct prover polynomials where each is the zero polynomial.
        // Note: ProverPolynomials are defined as spans so the polynomials they point to need to exist in memory.
        std::vector<Polynomial<FF>> zero_polynomials(NUM_POLYNOMIALS);
        for (auto& poly : zero_polynomials) {
            poly = bb::Polynomial<FF>(multivariate_n);
        }
        auto full_polynomials = construct_ultra_full_polynomials(zero_polynomials);

        // Add some non-trivial values to certain polynomials so that the arithmetic relation will have non-trivial
        // contribution. Note: since all other polynomials are set to 0, all other relations are trivially
        // satisfied.
        std::array<FF, multivariate_n> w_l;
        w_l = { 0, 0, 2, 0 }; // this witness value makes the circuit from previous test invalid
        std::array<FF, multivariate_n> w_r = { 0, 1, 2, 0 };
        std::array<FF, multivariate_n> w_o = { 0, 2, 4, 0 };
        std::array<FF, multivariate_n> w_4 = { 0, 0, 0, 0 };
        std::array<FF, multivariate_n> q_m = { 0, 0, 1, 0 };
        std::array<FF, multivariate_n> q_l = { 0, 1, 0, 0 };
        std::array<FF, multivariate_n> q_r = { 0, 1, 0, 0 };
        std::array<FF, multivariate_n> q_o = { 0, -1, -1, 0 };
        std::array<FF, multivariate_n> q_c = { 0, 0, 0, 0 };
        std::array<FF, multivariate_n> q_arith = { 0, 1, 1, 0 };
        // Setting all of these to 0 ensures the GrandProductRelation is satisfied

        full_polynomials.w_l = bb::Polynomial<FF>(w_l);
        full_polynomials.w_r = bb::Polynomial<FF>(w_r);
        full_polynomials.w_o = bb::Polynomial<FF>(w_o);
        full_polynomials.w_4 = bb::Polynomial<FF>(w_4);
        full_polynomials.q_m = bb::Polynomial<FF>(q_m);
        full_polynomials.q_l = bb::Polynomial<FF>(q_l);
        full_polynomials.q_r = bb::Polynomial<FF>(q_r);
        full_polynomials.q_o = bb::Polynomial<FF>(q_o);
        full_polynomials.q_c = bb::Polynomial<FF>(q_c);
        full_polynomials.q_arith = bb::Polynomial<FF>(q_arith);

        // Set aribitrary random relation parameters
        RelationParameters<FF> relation_parameters{
            .beta = FF::random_element(),
            .gamma = FF::random_element(),
            .public_input_delta = FF::one(),
        };
        auto prover_transcript = Flavor::Transcript::prover_init_empty();
        auto sumcheck_prover = SumcheckProver<Flavor>(multivariate_n, prover_transcript);

        RelationSeparator prover_alpha;
        for (size_t idx = 0; idx < prover_alpha.size(); idx++) {
            prover_alpha[idx] = prover_transcript->template get_challenge<FF>("Sumcheck:alpha_" + std::to_string(idx));
        }
        std::vector<FF> prover_gate_challenges(multivariate_d);
        for (size_t idx = 0; idx < multivariate_d; idx++) {
            prover_gate_challenges[idx] =
                prover_transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
        }
        SumcheckOutput<Flavor> output;
        if constexpr (Flavor::HasZK) {
            // construct libra masking polynomials and compute auxiliary data
            ZKSumcheckData<Flavor> zk_sumcheck_data(multivariate_d, prover_transcript);
            output = sumcheck_prover.prove(
                full_polynomials, relation_parameters, prover_alpha, prover_gate_challenges, zk_sumcheck_data);
        } else {
            output = sumcheck_prover.prove(full_polynomials, relation_parameters, prover_alpha, prover_gate_challenges);
        }

        auto verifier_transcript = Flavor::Transcript::verifier_init_empty(prover_transcript);

        auto sumcheck_verifier = SumcheckVerifier<Flavor>(multivariate_d, verifier_transcript);
        RelationSeparator verifier_alpha;
        for (size_t idx = 0; idx < verifier_alpha.size(); idx++) {
            verifier_alpha[idx] =
                verifier_transcript->template get_challenge<FF>("Sumcheck:alpha_" + std::to_string(idx));
        }
        std::vector<FF> verifier_gate_challenges(multivariate_d);
        for (size_t idx = 0; idx < multivariate_d; idx++) {
            verifier_gate_challenges[idx] =
                verifier_transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
        }
        auto verifier_output = sumcheck_verifier.verify(relation_parameters, verifier_alpha, verifier_gate_challenges);

        auto verified = verifier_output.verified.value();

        EXPECT_EQ(verified, false);
    };
};

// Define the FlavorTypes
using FlavorTypes = testing::Types<UltraFlavor, UltraFlavorWithZK, MegaZKFlavor>;

TYPED_TEST_SUITE(SumcheckTests, FlavorTypes);

#define SKIP_IF_ZK()                                                                                                   \
    if (std::is_same<TypeParam, UltraFlavorWithZK>::value || std::is_same<TypeParam, MegaZKFlavor>::value) {           \
        GTEST_SKIP() << "Skipping test for ZK-enabled flavors";                                                        \
    }

TYPED_TEST(SumcheckTests, PolynomialNormalization)
{
    SKIP_IF_ZK();
    this->test_polynomial_normalization();
}
// Test the prover
TYPED_TEST(SumcheckTests, Prover)
{
    this->test_prover();
}
// Tests the prover-verifier flow
TYPED_TEST(SumcheckTests, ProverAndVerifierSimple)
{
    this->test_prover_verifier_flow();
}
// This tests is fed an invalid circuit and checks that the verifier would output false.
TYPED_TEST(SumcheckTests, ProverAndVerifierSimpleFailure)
{
    this->test_failure_prover_verifier_flow();
}
} // namespace
