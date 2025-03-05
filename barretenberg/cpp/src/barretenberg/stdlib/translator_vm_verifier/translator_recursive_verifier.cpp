#include "./translator_recursive_verifier.hpp"
#include "barretenberg/commitment_schemes/shplonk/shplemini.hpp"
#include "barretenberg/common/throw_or_abort.hpp"
#include "barretenberg/relations/translator_vm/translator_decomposition_relation_impl.hpp"
#include "barretenberg/relations/translator_vm/translator_delta_range_constraint_relation_impl.hpp"
#include "barretenberg/relations/translator_vm/translator_extra_relations_impl.hpp"
#include "barretenberg/relations/translator_vm/translator_non_native_field_relation_impl.hpp"
#include "barretenberg/relations/translator_vm/translator_permutation_relation_impl.hpp"
#include "barretenberg/sumcheck/sumcheck.hpp"

namespace bb {

template <typename Flavor>
TranslatorRecursiveVerifier_<Flavor>::TranslatorRecursiveVerifier_(
    Builder* builder,
    const std::shared_ptr<NativeVerificationKey>& native_verifier_key,
    const std::shared_ptr<Transcript>& transcript)
    : key(std::make_shared<VerificationKey>(builder, native_verifier_key))
    , transcript(transcript)
    , builder(builder)
{}

// Relation params used in sumcheck which is done over FF but the received data is from BF
template <typename Flavor>
void TranslatorRecursiveVerifier_<Flavor>::put_translation_data_in_relation_parameters(const BF& evaluation_input_x,
                                                                                       const BF& batching_challenge_v,
                                                                                       const BF& accumulated_result)
{

    const auto compute_four_limbs = [](const BF& in) {
        return std::array<FF, 4>{ FF(in.binary_basis_limbs[0].element),
                                  FF(in.binary_basis_limbs[1].element),
                                  FF(in.binary_basis_limbs[2].element),
                                  FF(in.binary_basis_limbs[3].element) };
    };

    const auto compute_five_limbs = [](const BF& in) {
        return std::array<FF, 5>{ FF(in.binary_basis_limbs[0].element),
                                  FF(in.binary_basis_limbs[1].element),
                                  FF(in.binary_basis_limbs[2].element),
                                  FF(in.binary_basis_limbs[3].element),
                                  FF(in.prime_basis_limb) };
    };

    relation_parameters.evaluation_input_x = compute_five_limbs(evaluation_input_x);

    BF batching_challenge_v_power = batching_challenge_v;
    for (size_t i = 0; i < 4; i++) {
        relation_parameters.batching_challenge_v[i] = compute_five_limbs(batching_challenge_v_power);
        batching_challenge_v_power = batching_challenge_v_power * batching_challenge_v;
    }

    relation_parameters.accumulated_result = compute_four_limbs(accumulated_result);
};

/**
 * @brief This function verifies an TranslatorFlavor Honk proof for given program settings.
 */
template <typename Flavor>
std::array<typename Flavor::GroupElement, 2> TranslatorRecursiveVerifier_<Flavor>::verify_proof(
    const HonkProof& proof, const BF& evaluation_input_x, const BF& batching_challenge_v)
{
    using Sumcheck = ::bb::SumcheckVerifier<Flavor>;
    using PCS = typename Flavor::PCS;
    using Curve = typename Flavor::Curve;
    using Shplemini = ::bb::ShpleminiVerifier_<Curve>;
    using VerifierCommitments = typename Flavor::VerifierCommitments;
    using CommitmentLabels = typename Flavor::CommitmentLabels;
    using ClaimBatcher = ClaimBatcher_<Curve>;
    using ClaimBatch = ClaimBatcher::Batch;
    using InterleavedBatch = ClaimBatcher::InterleavedBatch;

    StdlibProof<Builder> stdlib_proof = bb::convert_native_proof_to_stdlib(builder, proof);
    transcript->load_proof(stdlib_proof);

    VerifierCommitments commitments{ key };
    CommitmentLabels commitment_labels;

    const FF circuit_size = transcript->template receive_from_prover<FF>("circuit_size");
    if (static_cast<uint32_t>(circuit_size.get_value()) != key->circuit_size) {
        throw_or_abort(
            "TranslatorRecursiveVerifier::verify_proof: proof circuit size does not match verification key!");
    }

    const BF accumulated_result = transcript->template receive_from_prover<BF>("accumulated_result");

    put_translation_data_in_relation_parameters(evaluation_input_x, batching_challenge_v, accumulated_result);

    // Get commitments to wires and the ordered range constraints that do not require additional challenges
    for (auto [comm, label] : zip_view(commitments.get_wires_and_ordered_range_constraints(),
                                       commitment_labels.get_wires_and_ordered_range_constraints())) {
        comm = transcript->template receive_from_prover<Commitment>(label);
    }

    // Get permutation challenges
    FF gamma = transcript->template get_challenge<FF>("gamma");

    relation_parameters.beta = 0;
    relation_parameters.gamma = gamma;
    relation_parameters.public_input_delta = 0;
    relation_parameters.lookup_grand_product_delta = 0;

    // Get commitment to permutation and lookup grand products
    commitments.z_perm = transcript->template receive_from_prover<Commitment>(commitment_labels.z_perm);

    // Execute Sumcheck Verifier
    const size_t log_circuit_size = numeric::get_msb(static_cast<uint32_t>(circuit_size.get_value()));
    auto sumcheck = Sumcheck(log_circuit_size, transcript);
    FF alpha = transcript->template get_challenge<FF>("Sumcheck:alpha");
    std::vector<FF> gate_challenges(CONST_PROOF_SIZE_LOG_N);
    for (size_t idx = 0; idx < gate_challenges.size(); idx++) {
        gate_challenges[idx] = transcript->template get_challenge<FF>("Sumcheck:gate_challenge_" + std::to_string(idx));
    }

    std::array<Commitment, NUM_LIBRA_COMMITMENTS> libra_commitments = {};
    libra_commitments[0] = transcript->template receive_from_prover<Commitment>("Libra:concatenation_commitment");

    auto sumcheck_output = sumcheck.verify(relation_parameters, alpha, gate_challenges);

    libra_commitments[1] = transcript->template receive_from_prover<Commitment>("Libra:grand_sum_commitment");
    libra_commitments[2] = transcript->template receive_from_prover<Commitment>("Libra:quotient_commitment");

    // Execute Shplemini
    bool consistency_checked = true;
    ClaimBatcher claim_batcher{
        .unshifted = ClaimBatch{ commitments.get_unshifted_without_interleaved(),
                                 sumcheck_output.claimed_evaluations.get_unshifted_without_interleaved() },
        .shifted = ClaimBatch{ commitments.get_to_be_shifted(), sumcheck_output.claimed_evaluations.get_shifted() },
        .interleaved = InterleavedBatch{ .commitments_groups = commitments.get_groups_to_be_interleaved(),
                                         .evaluations = sumcheck_output.claimed_evaluations.get_interleaved() }
    };
    const BatchOpeningClaim<Curve> opening_claim =
        Shplemini::compute_batch_opening_claim(circuit_size,
                                               claim_batcher,
                                               sumcheck_output.challenge,
                                               Commitment::one(builder),
                                               transcript,
                                               Flavor::REPEATED_COMMITMENTS,
                                               Flavor::HasZK,
                                               &consistency_checked,
                                               libra_commitments,
                                               sumcheck_output.claimed_libra_evaluation);

    const auto pairing_points = PCS::reduce_verify_batch_opening_claim(opening_claim, transcript);

    return pairing_points;
}

template <typename Flavor>
bool TranslatorRecursiveVerifier_<Flavor>::verify_translation(
    const TranslationEvaluations_<
        typename stdlib::bigfield<typename Flavor::CircuitBuilder, typename Flavor::Curve::BaseFieldNative::Params>,
        typename Flavor::FF>& translation_evaluations)
{
    const auto reconstruct_from_array = [&](const auto& arr) {
        return BF::construct_from_limbs(arr[0], arr[1], arr[2], arr[3]);
    };

    const auto& reconstruct_value_from_eccvm_evaluations = [&](const TranslationEvaluations& translation_evaluations,
                                                               auto& relation_parameters) {
        const BF accumulated_result = reconstruct_from_array(relation_parameters.accumulated_result);
        const BF x = reconstruct_from_array(relation_parameters.evaluation_input_x);
        const BF v1 = reconstruct_from_array(relation_parameters.batching_challenge_v[0]);
        const BF v2 = reconstruct_from_array(relation_parameters.batching_challenge_v[1]);
        const BF v3 = reconstruct_from_array(relation_parameters.batching_challenge_v[2]);
        const BF v4 = reconstruct_from_array(relation_parameters.batching_challenge_v[3]);
        const BF& op = translation_evaluations.op;
        const BF& Px = translation_evaluations.Px;
        const BF& Py = translation_evaluations.Py;
        const BF& z1 = translation_evaluations.z1;
        const BF& z2 = translation_evaluations.z2;

        const BF eccvm_opening = (op + (v1 * Px) + (v2 * Py) + (v3 * z1) + (v4 * z2));
        // multiply by x here to deal with shift
        eccvm_opening.assert_equal(x * accumulated_result);
        return (eccvm_opening.get_value() == (x * accumulated_result).get_value());
    };

    bool is_value_reconstructed =
        reconstruct_value_from_eccvm_evaluations(translation_evaluations, relation_parameters);
    return is_value_reconstructed;
}
template class TranslatorRecursiveVerifier_<bb::TranslatorRecursiveFlavor_<UltraCircuitBuilder>>;
template class TranslatorRecursiveVerifier_<bb::TranslatorRecursiveFlavor_<MegaCircuitBuilder>>;
template class TranslatorRecursiveVerifier_<bb::TranslatorRecursiveFlavor_<CircuitSimulatorBN254>>;

} // namespace bb
