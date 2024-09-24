#include "barretenberg/commitment_schemes/shplonk/shplemini.hpp"
#include "barretenberg/circuit_checker/circuit_checker.hpp"
#include "barretenberg/commitment_schemes/commitment_key.test.hpp"
#include "barretenberg/commitment_schemes/gemini/gemini.hpp"
#include "barretenberg/commitment_schemes/ipa/ipa.hpp"
#include "barretenberg/commitment_schemes/kzg/kzg.hpp"
#include "barretenberg/commitment_schemes/shplonk/shplonk.hpp"
#include "barretenberg/srs/global_crs.hpp"
#include "barretenberg/stdlib/primitives/curves/bn254.hpp"
#include "barretenberg/stdlib/primitives/curves/grumpkin.hpp"
#include "barretenberg/stdlib/transcript/transcript.hpp"
#include "barretenberg/stdlib_circuit_builders/ultra_circuit_builder.hpp"
#include <gtest/gtest.h>

using namespace bb;

template <class PCS> class ShpleminiRecursionTest : public CommitmentTest<typename PCS::Curve::NativeCurve> {};

numeric::RNG& shplemini_engine = numeric::get_debug_randomness();

/**
 * @brief Test Recursive Verification for 2 multilinear polynomials and a shift of one of them
 *
 */
TEST(ShpleminiRecursionTest, ProveAndVerifySingle)
{
    // Define some useful type aliases
    using Builder = UltraCircuitBuilder;
    using Curve = typename stdlib::bn254<Builder>;
    using NativeCurve = typename Curve::NativeCurve;
    using Commitment = typename Curve::AffineElement;
    using NativeCommitment = typename Curve::AffineElementNative;
    using NativeCurve = typename Curve::NativeCurve;
    using NativePCS = std::conditional_t<std::same_as<NativeCurve, curve::BN254>, KZG<NativeCurve>, IPA<NativeCurve>>;
    using CommitmentKey = typename NativePCS::CK;
    using ShpleminiProver = ShpleminiProver_<NativeCurve>;
    using ShpleminiVerifier = ShpleminiVerifier_<Curve>;
    using Fr = typename Curve::ScalarField;
    using NativeFr = typename Curve::NativeCurve::ScalarField;
    using Polynomial = bb::Polynomial<NativeFr>;
    using Transcript = bb::BaseTranscript<bb::stdlib::recursion::honk::StdlibTranscriptParams<Builder>>;

    constexpr size_t N = 16;
    constexpr size_t log_circuit_size = 4;
    constexpr size_t NUM_UNSHIFTED = 2;
    constexpr size_t NUM_SHIFTED = 1;

    srs::init_crs_factory("../srs_db/ignition");

    std::vector<NativeFr> u_challenge(log_circuit_size);
    for (size_t idx = 0; idx < log_circuit_size; ++idx) {
        u_challenge[idx] = NativeFr::random_element(&shplemini_engine);
    };
    // Construct some random multilinear polynomials f_i and their evaluations v_i = f_i(u)
    std::vector<Polynomial> f_polynomials; // unshifted polynomials
    std::vector<NativeFr> v_evaluations;
    for (size_t i = 0; i < NUM_UNSHIFTED; ++i) {
        f_polynomials.emplace_back(Polynomial::random(N, /*shiftable*/ 1));
        v_evaluations.emplace_back(f_polynomials[i].evaluate_mle(u_challenge));
    }

    // Construct some "shifted" multilinear polynomials h_i as the left-shift-by-1 of f_i
    std::vector<Polynomial> g_polynomials; // to-be-shifted polynomials
    std::vector<Polynomial> h_polynomials; // shifts of the to-be-shifted polynomials
    std::vector<NativeFr> w_evaluations;
    if constexpr (NUM_SHIFTED > 0) {
        for (size_t i = 0; i < NUM_SHIFTED; ++i) {
            g_polynomials.emplace_back(f_polynomials[i]);
            h_polynomials.emplace_back(g_polynomials[i].shifted());
            w_evaluations.emplace_back(f_polynomials[i].evaluate_mle(u_challenge, true));
        }
    }

    // Compute commitments [f_i]
    std::vector<NativeCommitment> f_commitments;
    auto commitment_key = std::make_shared<CommitmentKey>(4096);
    for (size_t i = 0; i < NUM_UNSHIFTED; ++i) {
        f_commitments.emplace_back(commitment_key->commit(f_polynomials[i]));
    }
    // Construct container of commitments of the "to-be-shifted" polynomials [g_i] (= [f_i])
    std::vector<NativeCommitment> g_commitments;
    for (size_t i = 0; i < NUM_SHIFTED; ++i) {
        g_commitments.emplace_back(f_commitments[i]);
    }

    // Initialize an empty NativeTranscript
    auto prover_transcript = NativeTranscript::prover_init_empty();
    auto prover_opening_claims = ShpleminiProver::prove(
        N, RefVector(f_polynomials), RefVector(g_polynomials), u_challenge, commitment_key, prover_transcript);

    Builder builder;
    StdlibProof<Builder> stdlib_proof = bb::convert_proof_to_witness(&builder, prover_transcript->proof_data);
    auto stdlib_verifier_transcript = std::make_shared<Transcript>(stdlib_proof);
    [[maybe_unused]] auto _ = stdlib_verifier_transcript->template receive_from_prover<Fr>("Init");

    // Execute Verifier protocol without the need for vk prior the final check
    const auto commitments_to_witnesses = [&builder](const auto& commitments) {
        std::vector<Commitment> commitments_in_biggroup(commitments.size());
        std::transform(commitments.begin(),
                       commitments.end(),
                       commitments_in_biggroup.begin(),
                       [&builder](const auto& native_commitment) {
                           return Commitment::from_witness(&builder, native_commitment);
                       });
        return commitments_in_biggroup;
    };
    const auto elements_to_witness = [&](const auto& elements) {
        std::vector<Fr> elements_in_circuit(elements.size());
        std::transform(elements.begin(),
                       elements.end(),
                       elements_in_circuit.begin(),
                       [&builder](const auto& native_element) { return Fr::from_witness(&builder, native_element); });
        return elements_in_circuit;
    };
    auto stdlib_f_commitments = commitments_to_witnesses(f_commitments);
    auto stdlib_g_commitments = commitments_to_witnesses(g_commitments);
    auto stdlib_v_evaluations = elements_to_witness(v_evaluations);
    auto stdlib_w_evaluations = elements_to_witness(w_evaluations);

    std::vector<Fr> u_challenge_in_circuit = elements_to_witness(u_challenge);

    [[maybe_unused]] auto opening_claim =
        ShpleminiVerifier::compute_batch_opening_claim(Fr::from_witness(&builder, N),
                                                       RefVector(stdlib_f_commitments),
                                                       RefVector(stdlib_g_commitments),
                                                       RefVector(stdlib_v_evaluations),
                                                       RefVector(stdlib_w_evaluations),
                                                       u_challenge_in_circuit,
                                                       Commitment::one(&builder),
                                                       stdlib_verifier_transcript);

    EXPECT_TRUE(CircuitChecker::check(builder));
}
