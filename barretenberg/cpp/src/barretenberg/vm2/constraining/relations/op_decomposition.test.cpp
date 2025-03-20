#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>

#include "barretenberg/vm2/simulation/lib/serialization.hpp"

/******************************************************************************
       CODE GENERATION OF OPERAND DECOMPOSITION INTO BYTES
*******************************************************************************
This test serves the purpose of code-generate the operand decomposition into bytes
which can be statically derived by the wire format of the opcodes specified in
the map WireOpCode_WIRE_FORMAT (see serialization.hpp).

The artifacts are generated by writing to the standard output:
- Precomputed Selectors Table which must be copied to: WireOpCode_DC_SELECTORS in instruction_spec.cpp
- PIL code with relations copied to: instr_fetching.pil

The precomputed selectors table consists of a row per wire opcode and as many
columns as selector (determined by the algorithm below).
Example row: { WireOpCode::SHR_16, { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }

The pil relations map a fixed size bytecode chunk starting from a wire opcode byte
into the operands of the opcode as defined by WireOpCode_WIRE_FORMAT.
Example: op4 = sel_op_dc_0 * (bd9 * 2**8 + bd10 * 2**0) + sel_op_dc_4 * (bd8 * 2**8 + bd9 * 2**0) + sel_op_dc_7 * (bd8 *
2**0);

We have 8 operands: indirect, op1, op2, op3, op4, op5, op6, op7
Bytes of bytecode are denoted: bd0, bd1, bd2, bd3, ...., bd37 where bd0 is the
opcode and never appears in the above pil relation as it is trivially not an operand.

The goal of the algorithm below is to determine the least number of selectors sel_op_dc_XXX
required to decompose each operand into bytes covering all opcode formats.
Each selector sel_op_dc_XXX determines a subset of opcodes as defined per the table
WireOpCode_DC_SELECTORS. For any given column, select all opcodes for which the
entry bit is toggled.

Below, we denote any of the 8 operands op_idx. An operand layout is a pair (offset, len)
which corresponds to a byte offset of the wire format and len being the length in bytes.

Example CAST_8: { OperandType::INDIRECT8, OperandType::UINT8, OperandType::UINT8, OperandType::TAG }
[{0,1}, {1,1}, {2,1}, {3, 1}]

Example SET_128: { OperandType::INDIRECT8, OperandType::UINT16, OperandType::TAG, OperandType::UINT128 }
[{0,1}, {1,2}, {3,1}, {4,16}]

The algorithm consists in processing WireOpCode_WIRE_FORMAT and map every combination
[op_idx, op_layout] to a subset of opcodes. Continuing example above, SET_128 opcode
would be present in the subsets indexed by the following [op_idx, op_layout] triples:
[indirect, {0,1}]
[op1, {1,2}]
[op2, {3,1}]
[op3, {4,16}]

Each subset is then encoded into a bitmask of opcodes packed as a uint128_t key.
Each unique subset is then mapped to a selector sel_op_dc_XXX.

Assuming in the example above that [op1, {1,2}] maps to selector sel_op_dc_13, the
corresponding PIL relation will be if the form:
op1 = sel_op_dc_13 * (bd2 * 2**8 + bd3 * 2**0) + sel_op_dc_XXX * (...) + sel_op_dc_XXX * () ...
Note that offset is bd2 as bd0 is opcode byte and therefore needs to increase offset by one.
len = 2 meanse that we have two bytes and therefore bd2 and bd3 are the bytes encoding
(in big endian) operand op1.

In addition, we add a naive algorithm to remove a partitioned subset by two other
subsets and aliases the corresponding selector of the partitioned subset as
an addition of the selectors pertaining to the 2 other subsets.
For instance: pol sel_op_dc_18 = sel_op_dc_1 + sel_op_dc_6;
This allows to save some selectors.

******************************************************************************/

namespace bb::avm2::constraining {
using simulation::OperandType;
namespace {

constexpr std::string OPERAND_PREFIX = "op";
constexpr std::string BYTE_PREFIX = "bd";
constexpr std::string SELECTOR_PREFIX = "sel_op_dc_";

constexpr size_t NUM_OF_OPERANDS = 8; // Need 8 to cover ECADD

struct OperandLayout {
    uint8_t offset = 0;
    uint8_t len = 0;
};

struct Partition {
    uint128_t subset_1;
    uint128_t subset_2;
    uint128_t union_subset;
};

uint32_t encode_operand_idx_with_layout(uint8_t operand_idx, uint8_t offset, uint8_t len)
{
    uint32_t layout = len;
    layout += (static_cast<uint32_t>(offset) << 8);
    layout += (static_cast<uint32_t>(operand_idx) << 16);
    return layout;
}

uint8_t get_op_idx(uint32_t op_idx_with_layout)
{
    return static_cast<uint8_t>(op_idx_with_layout >> 16);
}

OperandLayout get_op_layout(uint32_t op_idx_with_layout)
{
    uint8_t offset = static_cast<uint8_t>((op_idx_with_layout >> 8) & 0xFF);
    uint8_t len = static_cast<uint8_t>(op_idx_with_layout & 0xFF);
    return OperandLayout{ .offset = offset, .len = len };
}

uint128_t encode_subset_wire_opcodes(const std::unordered_set<WireOpCode>& set)
{
    uint128_t value = 0;
    for (const auto& wire_opcode : set) {
        value += (static_cast<uint128_t>(1) << static_cast<uint8_t>(wire_opcode));
    }

    return value;
}

std::string render_selector_array(WireOpCode wire_opcode, const std::vector<uint128_t>& sel_bitmasks)
{
    size_t num_of_selectors = sel_bitmasks.size();
    std::vector<bool> selectors;
    selectors.reserve(num_of_selectors);

    for (const auto& bitmask : sel_bitmasks) {
        selectors.push_back(((static_cast<uint128_t>(1) << static_cast<uint128_t>(wire_opcode)) & bitmask) != 0);
    }

    std::string output = format("{", selectors[0]);
    for (size_t i = 1; i < num_of_selectors; i++) {
        output += format(", ", selectors[i]);
    }
    output += "}";
    return output;
}

auto add_fold = [](const std::string& a, const std::string& b) { return a + " + " + b; };

// Write pol sel_i = sel_j + sel_k
std::string render_partitions_pil(const std::vector<Partition>& partitions,
                                  const std::unordered_map<uint128_t, size_t>& bitmask_to_sel_idx)
{
    std::string output;
    for (const auto& partition : partitions) {
        output += format("pol ", SELECTOR_PREFIX, bitmask_to_sel_idx.at(partition.union_subset));
        output += format(" = ", SELECTOR_PREFIX, bitmask_to_sel_idx.at(partition.subset_1));
        output += format(" + ", SELECTOR_PREFIX, bitmask_to_sel_idx.at(partition.subset_2), ";\n");
    }
    return output;
}

// Output a string like: bd4 * 2**24 + bd5 * 2**16 + bd6 * 2**8 + bd7 * 2**0
std::string render_operand_layout_pil(OperandLayout layout)
{
    std::vector<std::string> monomials;
    monomials.reserve(layout.len);
    uint8_t byte_offset = layout.offset;
    for (int i = 0; i < layout.len; i++) {
        monomials.push_back(
            format(BYTE_PREFIX, byte_offset + i + 1, " * 2**", 8 * (layout.len - i - 1))); // Big-endian bytes
    }

    return std::accumulate(std::next(monomials.begin()), monomials.end(), monomials[0], add_fold);
}

std::string render_pil(
    const std::array<std::vector<std::pair<size_t, OperandLayout>>, NUM_OF_OPERANDS>& sel_layout_breakdowns)
{
    std::string pil_equations;
    for (uint8_t i = 0; i < NUM_OF_OPERANDS; i++) {
        pil_equations += (i == 0) ? "#[INDIRECT_BYTES_DECOMPOSITION]\n"
                                  : format("#[OP", static_cast<uint32_t>(i), "_BYTES_DECOMPOSITION]\n");
        pil_equations += (i == 0) ? "indirect = " : format(OPERAND_PREFIX, static_cast<uint32_t>(i), " = ");

        pil_equations += "(1 - parsing_err) * ("; // Error gating multiplicative term

        std::vector<std::string> additive_terms;
        for (const auto& sel_layout : sel_layout_breakdowns[i]) {
            additive_terms.push_back(
                format(SELECTOR_PREFIX, sel_layout.first, " * (", render_operand_layout_pil(sel_layout.second), ")"));
        }
        pil_equations +=
            std::accumulate(std::next(additive_terms.begin()), additive_terms.end(), additive_terms[0], add_fold);
        pil_equations += ");\n";
    }
    return pil_equations;
}

std::unordered_map<WireOpCode, std::array<OperandLayout, NUM_OF_OPERANDS>> gen_opcode_to_operands_layout()
{
    std::unordered_map<WireOpCode, std::array<OperandLayout, NUM_OF_OPERANDS>> mapping;

    const auto& operand_type_sizes = simulation::testonly::get_operand_type_sizes();
    const auto& wire_formats = simulation::testonly::get_instruction_wire_formats();

    for (const auto& [opcode, format] : wire_formats) {
        std::array<OperandLayout, 8> operands_layout_array;
        uint8_t op_idx = 1; // We start at index 1 because the index zero is reserved for indirect value.
        uint8_t byte_offset = 0;

        for (const auto& operand : format) {
            const auto operand_len = static_cast<uint8_t>(operand_type_sizes.at(operand));
            const auto op_layout = OperandLayout{ .offset = byte_offset, .len = operand_len };

            if (operand == OperandType::INDIRECT8 || operand == OperandType::INDIRECT16) {
                operands_layout_array[0] = op_layout;
            } else {
                operands_layout_array[op_idx++] = op_layout;
            }
            byte_offset += operand_len;
        }
        mapping.insert(std::make_pair(opcode, operands_layout_array));
    }
    return mapping;
}

std::unordered_map<uint32_t, std::unordered_set<WireOpCode>> gen_op_idx_with_layout_to_opcode_subset(
    const std::unordered_map<WireOpCode, std::array<OperandLayout, NUM_OF_OPERANDS>>& opcode_to_layouts)
{
    std::unordered_map<uint32_t, std::unordered_set<WireOpCode>> op_idx_with_layout_to_subset;

    for (const auto& [wire_opcode, operand_layouts] : opcode_to_layouts) {
        for (uint8_t i = 0; i < NUM_OF_OPERANDS; i++) {
            const auto& layout = operand_layouts[i];
            if (layout.len != 0) {
                const auto key = encode_operand_idx_with_layout(i, layout.offset, layout.len);
                if (op_idx_with_layout_to_subset.contains(key)) {
                    op_idx_with_layout_to_subset[key].insert(wire_opcode);
                } else {
                    op_idx_with_layout_to_subset[key] = { wire_opcode };
                }
            }
        }
    }
    return op_idx_with_layout_to_subset;
}

TEST(DecompositionSelectors, CodeGen)
{
    GTEST_SKIP(); // Comment out in order to code-generate.
    std::unordered_map<WireOpCode, std::array<OperandLayout, NUM_OF_OPERANDS>> opcode_to_layouts =
        gen_opcode_to_operands_layout();

    // Map any given operand idx with layout to a subset of wire opcodes where
    // we encode an operand idx with OperandLayout into a uint32_t as per function encode_operand_idx_with_layout().
    std::unordered_map<uint32_t, std::unordered_set<WireOpCode>> op_idx_with_layout_to_subset =
        gen_op_idx_with_layout_to_opcode_subset(opcode_to_layouts);

    // A bit mask encodes a subset. Whenever an opcode is present in the subset, we toggle the bit
    // at position represented by the opcode. Number of opcodes is smaller than 128 and therefore the bitmask
    // fits in a uint128_t.
    static_assert(static_cast<uint32_t>(WireOpCode::LAST_OPCODE_SENTINEL) < 128);

    std::unordered_set<uint128_t> set_of_bitmasks;
    std::unordered_map<uint32_t, uint128_t> op_idx_with_layout_to_bitmask;

    for (const auto& [op_layout, subset] : op_idx_with_layout_to_subset) {
        const auto encoded = encode_subset_wire_opcodes(subset);
        set_of_bitmasks.insert(encoded);
        op_idx_with_layout_to_bitmask.insert(std::make_pair(op_layout, encoded));
    }

    info("NUMBER OF SUBSETS: ", set_of_bitmasks.size());

    // Is there any union of two disjoint subsets equal to another one?
    bool partition_found = true;
    std::vector<Partition> partitions;

    // We try to remove partitions in a naive way, basically we remove the first encountered
    // partition one after the other. This is by no way an exhaustive algorithm to find a hierarchy
    // of partitions. This does the job as we have only one partition with the current AVM design.
    while (partition_found) {
        for (auto it1 = set_of_bitmasks.begin(); it1 != set_of_bitmasks.end(); it1++) {
            auto it2 = it1;
            for (it2++; it2 != set_of_bitmasks.end(); it2++) {
                uint128_t sub_union = *it1 | *it2;
                if ((*it1 & *it2) == 0 && set_of_bitmasks.contains(sub_union)) {
                    info("PARTITION FOUND! ", *it1, "  ", *it2, "  ", sub_union);
                    partitions.push_back(Partition{ .subset_1 = *it1, .subset_2 = *it2, .union_subset = sub_union });
                    set_of_bitmasks.erase(sub_union);
                    partition_found = true;
                    break;
                }
                partition_found = false;
            }
            if (partition_found) { // Mechanism to exit the outer loop
                break;
            }
        }
    }

    info("NUMBER OF SUBSETS AFTER PARTITION REMOVAL: ", set_of_bitmasks.size());

    std::vector<uint128_t> bitmasks_vector;
    std::copy(set_of_bitmasks.begin(), set_of_bitmasks.end(), std::back_inserter(bitmasks_vector));

    // Ensure a deterministic order
    std::sort(bitmasks_vector.begin(), bitmasks_vector.end(), std::greater<>());

    info("\n#################################");
    info(" Precomputed Selectors Table:");
    info("#################################\n");

    info("constexpr size_t NUM_OP_DC_SELECTORS = 18;\n\n");

    info("const std::unordered_map<WireOpCode, std::array<uint8_t, NUM_OP_DC_SELECTORS>> WireOpCode_DC_SELECTORS = "
         "{");

    const auto& wire_formats = simulation::testonly::get_instruction_wire_formats();
    for (int i = 0; i < static_cast<int>(WireOpCode::LAST_OPCODE_SENTINEL); i++) {
        const auto wire_opcode = static_cast<WireOpCode>(i);
        if (wire_formats.contains(wire_opcode)) {
            info("{WireOpCode::", wire_opcode, ", ", render_selector_array(wire_opcode, bitmasks_vector), "},");
        }
    }
    info("};");

    // Add subsets/bitmasks which were removed as unions at the end.
    for (const auto& partition : partitions) {
        bitmasks_vector.push_back(partition.union_subset);
    }

    std::unordered_map<uint128_t, size_t> bitmask_to_sel_idx;

    for (size_t i = 0; i < bitmasks_vector.size(); i++) {
        bitmask_to_sel_idx.insert(std::make_pair(bitmasks_vector[i], i));
    }

    // For each operand (index of the array), we store a vector of (selector, layout) corresponding to
    // the decomposition of the operand with respect to bytes (bd1, bd2, ...)
    // op_1 = sel_1 * (bd1 + bd2 * 2^8) + sel_4 * (bd5 + bd6 * 2^8)
    std::array<std::vector<std::pair<size_t, OperandLayout>>, NUM_OF_OPERANDS> sel_layout_breakdowns;
    for (const auto& [op_idx_with_layout, bitmask] : op_idx_with_layout_to_bitmask) {
        uint8_t op_idx = get_op_idx(op_idx_with_layout);
        OperandLayout layout = get_op_layout(op_idx_with_layout);
        size_t sel_idx = bitmask_to_sel_idx.at(bitmask);
        sel_layout_breakdowns[op_idx].emplace_back(std::make_pair(sel_idx, layout));
    }

    // For each sel-layout breakdown vector, we sort by increasing selector indices.
    for (uint8_t i = 0; i < NUM_OF_OPERANDS; i++) {
        std::sort(
            sel_layout_breakdowns[i].begin(),
            sel_layout_breakdowns[i].end(),
            [](std::pair<size_t, OperandLayout> a, std::pair<size_t, OperandLayout> b) { return a.first < b.first; });
    }

    info("\n##################");
    info("PIL Relations:");
    info("##################\n");

    info(render_partitions_pil(partitions, bitmask_to_sel_idx));
    info(render_pil(sel_layout_breakdowns));
}

} // namespace
} // namespace bb::avm2::constraining
