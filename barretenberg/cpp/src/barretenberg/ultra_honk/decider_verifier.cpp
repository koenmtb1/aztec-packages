#include "decider_verifier.hpp"
#include "barretenberg/commitment_schemes/shplonk/shplemini.hpp"
#include "barretenberg/numeric/bitop/get_msb.hpp"
#include "barretenberg/sumcheck/sumcheck.hpp"
#include "barretenberg/transcript/transcript.hpp"
#include "barretenberg/ultra_honk/decider_verification_key.hpp"

namespace bb {

template <typename Flavor>
DeciderVerifier_<Flavor>::DeciderVerifier_(const std::shared_ptr<DeciderVerificationKey>& accumulator,
                                           const std::shared_ptr<Transcript>& transcript)
    : accumulator(accumulator)
    , pcs_verification_key(accumulator->verification_key->pcs_verification_key)
    , transcript(transcript)
{}

template <typename Flavor>
DeciderVerifier_<Flavor>::DeciderVerifier_(const std::shared_ptr<DeciderVerificationKey>& accumulator)
    : accumulator(accumulator)
    , pcs_verification_key(accumulator->verification_key->pcs_verification_key)
{}

/**
 * @brief Verify a decider proof relative to a decider verification key (ϕ, \vec{β*}, e*).
 */
template <typename Flavor> bool DeciderVerifier_<Flavor>::verify_proof(const DeciderProof& proof)
{
    transcript = std::make_shared<Transcript>(proof);
    return verify();
}

/**
 * @brief Verify a decider proof that is assumed to be contained in the transcript
 *
 */
template <typename Flavor> bool DeciderVerifier_<Flavor>::verify()
{
    using PCS = typename Flavor::PCS;
    using Curve = typename Flavor::Curve;
    using Shplemini = ShpleminiVerifier_<Curve>;
    using VerifierCommitments = typename Flavor::VerifierCommitments;

    VerifierCommitments commitments{ accumulator->verification_key, accumulator->witness_commitments };

    auto sumcheck = SumcheckVerifier<Flavor>(
        static_cast<size_t>(accumulator->verification_key->log_circuit_size), transcript, accumulator->target_sum);
    // For MegaZKFlavor: receive commitments to Libra masking polynomials
    std::vector<Commitment> libra_commitments = {};
    if constexpr (Flavor::HasZK) {
        for (size_t idx = 0; idx < static_cast<size_t>(accumulator->verification_key->log_circuit_size); idx++) {
            Commitment libra_commitment =
                transcript->template receive_from_prover<Commitment>("Libra:commitment_" + std::to_string(idx));
            libra_commitments.push_back(libra_commitment);
        };
    }

    SumcheckOutput<Flavor> sumcheck_output =
        sumcheck.verify(accumulator->relation_parameters, accumulator->alphas, accumulator->gate_challenges);

    // For MegaZKFlavor: the sumcheck output contains claimed evaluations of the Libra polynomials
    std::vector<FF> libra_evaluations = {};
    if constexpr (Flavor::HasZK) {
        libra_evaluations = std::move(sumcheck_output.claimed_libra_evaluations);
    }

    // If Sumcheck did not verify, return false
    if (sumcheck_output.verified.has_value() && !sumcheck_output.verified.value()) {
        info("Sumcheck verification failed.");
        return false;
    }

    const BatchOpeningClaim<Curve> opening_claim =
        Shplemini::compute_batch_opening_claim(accumulator->verification_key->circuit_size,
                                               commitments.get_unshifted(),
                                               commitments.get_to_be_shifted(),
                                               sumcheck_output.claimed_evaluations.get_unshifted(),
                                               sumcheck_output.claimed_evaluations.get_shifted(),
                                               sumcheck_output.challenge,
                                               Commitment::one(),
                                               transcript,
                                               RefVector(libra_commitments),
                                               libra_evaluations);
    const auto pairing_points = PCS::reduce_verify_batch_opening_claim(opening_claim, transcript);
    bool verified = pcs_verification_key->pairing_check(pairing_points[0], pairing_points[1]);

    return sumcheck_output.verified.value() && verified;
}

template class DeciderVerifier_<UltraFlavor>;
template class DeciderVerifier_<UltraKeccakFlavor>;
template class DeciderVerifier_<MegaFlavor>;
template class DeciderVerifier_<MegaZKFlavor>;

} // namespace bb
