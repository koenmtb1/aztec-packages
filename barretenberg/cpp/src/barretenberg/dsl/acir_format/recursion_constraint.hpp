#pragma once
#include "barretenberg/plonk/proof_system/constants.hpp"
#include "barretenberg/plonk/proof_system/verification_key/verification_key.hpp"
#include "barretenberg/plonk/transcript/transcript_wrappers.hpp"
#include <vector>

namespace acir_format {

// Used to specify the type of recursive verifier via the proof_type specified by the RecursiveAggregation opcode from
// ACIR
// Keep this enum values in sync with their noir counterpart constants defined in
// noir-protocol-circuits/crates/types/src/constants.nr
enum PROOF_TYPE { PLONK, HONK, OINK, PG, AVM, ROLLUP_HONK, ROLLUP_ROOT_HONK };

using namespace bb::plonk;
using Builder = bb::UltraCircuitBuilder;

/**
 * @brief RecursionConstraint struct contains information required to recursively verify a proof!
 *
 * @details The recursive verifier algorithm produces an 'aggregation object' representing 2 G1 points, expressed as 16
 * witness values. The smart contract Verifier must be aware of this aggregation object in order to complete the full
 * recursive verification. If the circuit verifies more than 1 proof, the recursion algorithm will update a pre-existing
 * aggregation object (`input_aggregation_object`).
 *
 * @details We currently require that the inner circuit being verified only has a single public input. If more are
 * required, the outer circuit can hash them down to 1 input.
 *
 * @param verification_key_data The inner circuit vkey. Is converted into circuit witness values (internal to the
 * backend)
 * @param proof The plonk proof. Is converted into circuit witness values (internal to the backend)
 * @param is_aggregation_object_nonzero A flag to tell us whether the circuit has already recursively verified proofs
 * (and therefore an aggregation object is present)
 * @param public_input The index of the single public input
 * @param input_aggregation_object Witness indices of pre-existing aggregation object (if it exists)
 * @param output_aggregation_object Witness indices of the aggregation object produced by recursive verification
 * @param nested_aggregation_object Public input indices of an aggregation object inside the proof.
 *
 * @note If input_aggregation_object witness indices are all zero, we interpret this to mean that the inner proof does
 * NOT contain a previously recursively verified proof
 * @note nested_aggregation_object is used for cases where the proof being verified contains an aggregation object in
 * its public inputs! If this is the case, we record the public input locations in `nested_aggregation_object`. If the
 * inner proof is of a circuit that does not have a nested aggregation object, these values are all zero.
 *
 * To outline the interaction between the input_aggergation_object and the nested_aggregation_object take the following
 * example: If we have a circuit that verifies 2 proofs A and B, the recursion constraint for B will have an
 * input_aggregation_object that points to the aggregation output produced by verifying A. If circuit B also verifies a
 * proof, in the above example the recursion constraint for verifying B will have a nested object that describes the
 * aggregation object in B’s public inputs as well as an input aggregation object that points to the object produced by
 * the previous recursion constraint in the circuit (the one that verifies A)
 *
 * TODO(https://github.com/AztecProtocol/barretenberg/issues/996): Create similar comments for Honk.
 */
struct RecursionConstraint {
    // An aggregation state is represented by two G1 affine elements. Each G1 point has
    // two field element coordinates (x, y). Thus, four field elements
    static constexpr size_t NUM_AGGREGATION_ELEMENTS = 4;
    std::vector<uint32_t> key;
    std::vector<uint32_t> proof;
    std::vector<uint32_t> public_inputs;
    uint32_t key_hash;
    uint32_t proof_type;

    friend bool operator==(RecursionConstraint const& lhs, RecursionConstraint const& rhs) = default;
};

bb::PairingPointAccumulatorIndices create_recursion_constraints(
    Builder& builder,
    const RecursionConstraint& input,
    const bb::PairingPointAccumulatorIndices& input_aggregation_object,
    const bb::PairingPointAccumulatorIndices& nested_aggregation_object,
    bool has_valid_witness_assignments = false);

std::vector<bb::fr> export_key_in_recursion_format(std::shared_ptr<verification_key> const& vkey);
std::vector<bb::fr> export_dummy_key_in_recursion_format(const PolynomialManifest& polynomial_manifest,
                                                         bool contains_pairing_point_accumulator = 0);

std::vector<bb::fr> export_transcript_in_recursion_format(const transcript::StandardTranscript& transcript);
std::vector<bb::fr> export_dummy_transcript_in_recursion_format(const transcript::Manifest& manifest,
                                                                const bool contains_pairing_point_accumulator);
size_t recursion_proof_size_without_public_inputs();

// In order to interact with a recursive aggregation state inside of a circuit, we need to represent its internal G1
// elements as field elements. This happens in multiple locations when creating a recursion constraint. The struct and
// method below export a g1 affine element as fields to use as part of the recursive circuit.
struct G1AsFields {
    bb::fr x_lo;
    bb::fr x_hi;
    bb::fr y_lo;
    bb::fr y_hi;
};
G1AsFields export_g1_affine_element_as_fields(const bb::g1::affine_element& group_element);

template <typename B> inline void read(B& buf, RecursionConstraint& constraint)
{
    using serialize::read;
    read(buf, constraint.key);
    read(buf, constraint.proof);
    read(buf, constraint.public_inputs);
    read(buf, constraint.key_hash);
}

template <typename B> inline void write(B& buf, RecursionConstraint const& constraint)
{
    using serialize::write;
    write(buf, constraint.key);
    write(buf, constraint.proof);
    write(buf, constraint.public_inputs);
    write(buf, constraint.key_hash);
}

} // namespace acir_format
