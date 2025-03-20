// AUTOGENERATED FILE
#pragma once

#include "../columns.hpp"
#include "barretenberg/relations/generic_lookup/generic_lookup_relation.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace bb::avm2 {

/////////////////// lookup_instr_fetching_instr_abs_diff_positive ///////////////////

class lookup_instr_fetching_instr_abs_diff_positive_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_INSTR_FETCHING_INSTR_ABS_DIFF_POSITIVE";
    static constexpr std::string_view RELATION_NAME = "instr_fetching";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 1;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::instr_fetching_sel;
    static constexpr Column DST_SELECTOR = Column::precomputed_sel_range_8;
    static constexpr Column COUNTS = Column::lookup_instr_fetching_instr_abs_diff_positive_counts;
    static constexpr Column INVERSES = Column::lookup_instr_fetching_instr_abs_diff_positive_inv;
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        ColumnAndShifts::instr_fetching_instr_abs_diff
    };
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> DST_COLUMNS = { ColumnAndShifts::precomputed_clk };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._instr_fetching_sel() == 1 || in._precomputed_sel_range_8() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._instr_fetching_sel());
        const auto is_table_entry = View(in._precomputed_sel_range_8());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_instr_fetching_instr_abs_diff_positive_inv(),
                                     in._lookup_instr_fetching_instr_abs_diff_positive_counts(),
                                     in._instr_fetching_sel(),
                                     in._precomputed_sel_range_8(),
                                     in._instr_fetching_instr_abs_diff(),
                                     in._precomputed_clk());
    }
};

template <typename FF_>
class lookup_instr_fetching_instr_abs_diff_positive_relation
    : public GenericLookupRelation<lookup_instr_fetching_instr_abs_diff_positive_settings, FF_> {
  public:
    using Settings = lookup_instr_fetching_instr_abs_diff_positive_settings;
    static constexpr std::string_view NAME = lookup_instr_fetching_instr_abs_diff_positive_settings::NAME;
    static constexpr std::string_view RELATION_NAME =
        lookup_instr_fetching_instr_abs_diff_positive_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_instr_fetching_instr_abs_diff_positive_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

/////////////////// lookup_instr_fetching_pc_abs_diff_positive ///////////////////

class lookup_instr_fetching_pc_abs_diff_positive_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_INSTR_FETCHING_PC_ABS_DIFF_POSITIVE";
    static constexpr std::string_view RELATION_NAME = "instr_fetching";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 2;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::instr_fetching_sel;
    static constexpr Column DST_SELECTOR = Column::range_check_sel;
    static constexpr Column COUNTS = Column::lookup_instr_fetching_pc_abs_diff_positive_counts;
    static constexpr Column INVERSES = Column::lookup_instr_fetching_pc_abs_diff_positive_inv;
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        ColumnAndShifts::instr_fetching_pc_abs_diff, ColumnAndShifts::instr_fetching_thirty_two
    };
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> DST_COLUMNS = {
        ColumnAndShifts::range_check_value, ColumnAndShifts::range_check_rng_chk_bits
    };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._instr_fetching_sel() == 1 || in._range_check_sel() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._instr_fetching_sel());
        const auto is_table_entry = View(in._range_check_sel());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_instr_fetching_pc_abs_diff_positive_inv(),
                                     in._lookup_instr_fetching_pc_abs_diff_positive_counts(),
                                     in._instr_fetching_sel(),
                                     in._range_check_sel(),
                                     in._instr_fetching_pc_abs_diff(),
                                     in._instr_fetching_thirty_two(),
                                     in._range_check_value(),
                                     in._range_check_rng_chk_bits());
    }
};

template <typename FF_>
class lookup_instr_fetching_pc_abs_diff_positive_relation
    : public GenericLookupRelation<lookup_instr_fetching_pc_abs_diff_positive_settings, FF_> {
  public:
    using Settings = lookup_instr_fetching_pc_abs_diff_positive_settings;
    static constexpr std::string_view NAME = lookup_instr_fetching_pc_abs_diff_positive_settings::NAME;
    static constexpr std::string_view RELATION_NAME =
        lookup_instr_fetching_pc_abs_diff_positive_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_instr_fetching_pc_abs_diff_positive_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

/////////////////// lookup_instr_fetching_bytecode_size_from_bc_dec ///////////////////

class lookup_instr_fetching_bytecode_size_from_bc_dec_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_INSTR_FETCHING_BYTECODE_SIZE_FROM_BC_DEC";
    static constexpr std::string_view RELATION_NAME = "instr_fetching";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 3;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::instr_fetching_sel;
    static constexpr Column DST_SELECTOR = Column::bc_decomposition_sel;
    static constexpr Column COUNTS = Column::lookup_instr_fetching_bytecode_size_from_bc_dec_counts;
    static constexpr Column INVERSES = Column::lookup_instr_fetching_bytecode_size_from_bc_dec_inv;
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        ColumnAndShifts::instr_fetching_bytecode_id,
        ColumnAndShifts::precomputed_zero,
        ColumnAndShifts::instr_fetching_bytecode_size
    };
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> DST_COLUMNS = {
        ColumnAndShifts::bc_decomposition_id,
        ColumnAndShifts::bc_decomposition_pc,
        ColumnAndShifts::bc_decomposition_bytes_remaining
    };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._instr_fetching_sel() == 1 || in._bc_decomposition_sel() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._instr_fetching_sel());
        const auto is_table_entry = View(in._bc_decomposition_sel());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_instr_fetching_bytecode_size_from_bc_dec_inv(),
                                     in._lookup_instr_fetching_bytecode_size_from_bc_dec_counts(),
                                     in._instr_fetching_sel(),
                                     in._bc_decomposition_sel(),
                                     in._instr_fetching_bytecode_id(),
                                     in._precomputed_zero(),
                                     in._instr_fetching_bytecode_size(),
                                     in._bc_decomposition_id(),
                                     in._bc_decomposition_pc(),
                                     in._bc_decomposition_bytes_remaining());
    }
};

template <typename FF_>
class lookup_instr_fetching_bytecode_size_from_bc_dec_relation
    : public GenericLookupRelation<lookup_instr_fetching_bytecode_size_from_bc_dec_settings, FF_> {
  public:
    using Settings = lookup_instr_fetching_bytecode_size_from_bc_dec_settings;
    static constexpr std::string_view NAME = lookup_instr_fetching_bytecode_size_from_bc_dec_settings::NAME;
    static constexpr std::string_view RELATION_NAME =
        lookup_instr_fetching_bytecode_size_from_bc_dec_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_instr_fetching_bytecode_size_from_bc_dec_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

/////////////////// lookup_instr_fetching_bytes_from_bc_dec ///////////////////

class lookup_instr_fetching_bytes_from_bc_dec_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_INSTR_FETCHING_BYTES_FROM_BC_DEC";
    static constexpr std::string_view RELATION_NAME = "instr_fetching";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 40;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::instr_fetching_sel_opcode_defined;
    static constexpr Column DST_SELECTOR = Column::bc_decomposition_sel;
    static constexpr Column COUNTS = Column::lookup_instr_fetching_bytes_from_bc_dec_counts;
    static constexpr Column INVERSES = Column::lookup_instr_fetching_bytes_from_bc_dec_inv;
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        ColumnAndShifts::instr_fetching_bytecode_id,   ColumnAndShifts::instr_fetching_pc,
        ColumnAndShifts::instr_fetching_bytes_to_read, ColumnAndShifts::instr_fetching_bd0,
        ColumnAndShifts::instr_fetching_bd1,           ColumnAndShifts::instr_fetching_bd2,
        ColumnAndShifts::instr_fetching_bd3,           ColumnAndShifts::instr_fetching_bd4,
        ColumnAndShifts::instr_fetching_bd5,           ColumnAndShifts::instr_fetching_bd6,
        ColumnAndShifts::instr_fetching_bd7,           ColumnAndShifts::instr_fetching_bd8,
        ColumnAndShifts::instr_fetching_bd9,           ColumnAndShifts::instr_fetching_bd10,
        ColumnAndShifts::instr_fetching_bd11,          ColumnAndShifts::instr_fetching_bd12,
        ColumnAndShifts::instr_fetching_bd13,          ColumnAndShifts::instr_fetching_bd14,
        ColumnAndShifts::instr_fetching_bd15,          ColumnAndShifts::instr_fetching_bd16,
        ColumnAndShifts::instr_fetching_bd17,          ColumnAndShifts::instr_fetching_bd18,
        ColumnAndShifts::instr_fetching_bd19,          ColumnAndShifts::instr_fetching_bd20,
        ColumnAndShifts::instr_fetching_bd21,          ColumnAndShifts::instr_fetching_bd22,
        ColumnAndShifts::instr_fetching_bd23,          ColumnAndShifts::instr_fetching_bd24,
        ColumnAndShifts::instr_fetching_bd25,          ColumnAndShifts::instr_fetching_bd26,
        ColumnAndShifts::instr_fetching_bd27,          ColumnAndShifts::instr_fetching_bd28,
        ColumnAndShifts::instr_fetching_bd29,          ColumnAndShifts::instr_fetching_bd30,
        ColumnAndShifts::instr_fetching_bd31,          ColumnAndShifts::instr_fetching_bd32,
        ColumnAndShifts::instr_fetching_bd33,          ColumnAndShifts::instr_fetching_bd34,
        ColumnAndShifts::instr_fetching_bd35,          ColumnAndShifts::instr_fetching_bd36
    };
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> DST_COLUMNS = {
        ColumnAndShifts::bc_decomposition_id,
        ColumnAndShifts::bc_decomposition_pc,
        ColumnAndShifts::bc_decomposition_bytes_to_read,
        ColumnAndShifts::bc_decomposition_bytes,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_1,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_2,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_3,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_4,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_5,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_6,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_7,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_8,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_9,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_10,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_11,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_12,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_13,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_14,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_15,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_16,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_17,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_18,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_19,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_20,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_21,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_22,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_23,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_24,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_25,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_26,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_27,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_28,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_29,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_30,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_31,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_32,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_33,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_34,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_35,
        ColumnAndShifts::bc_decomposition_bytes_pc_plus_36
    };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._instr_fetching_sel_opcode_defined() == 1 || in._bc_decomposition_sel() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._instr_fetching_sel_opcode_defined());
        const auto is_table_entry = View(in._bc_decomposition_sel());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_instr_fetching_bytes_from_bc_dec_inv(),
                                     in._lookup_instr_fetching_bytes_from_bc_dec_counts(),
                                     in._instr_fetching_sel_opcode_defined(),
                                     in._bc_decomposition_sel(),
                                     in._instr_fetching_bytecode_id(),
                                     in._instr_fetching_pc(),
                                     in._instr_fetching_bytes_to_read(),
                                     in._instr_fetching_bd0(),
                                     in._instr_fetching_bd1(),
                                     in._instr_fetching_bd2(),
                                     in._instr_fetching_bd3(),
                                     in._instr_fetching_bd4(),
                                     in._instr_fetching_bd5(),
                                     in._instr_fetching_bd6(),
                                     in._instr_fetching_bd7(),
                                     in._instr_fetching_bd8(),
                                     in._instr_fetching_bd9(),
                                     in._instr_fetching_bd10(),
                                     in._instr_fetching_bd11(),
                                     in._instr_fetching_bd12(),
                                     in._instr_fetching_bd13(),
                                     in._instr_fetching_bd14(),
                                     in._instr_fetching_bd15(),
                                     in._instr_fetching_bd16(),
                                     in._instr_fetching_bd17(),
                                     in._instr_fetching_bd18(),
                                     in._instr_fetching_bd19(),
                                     in._instr_fetching_bd20(),
                                     in._instr_fetching_bd21(),
                                     in._instr_fetching_bd22(),
                                     in._instr_fetching_bd23(),
                                     in._instr_fetching_bd24(),
                                     in._instr_fetching_bd25(),
                                     in._instr_fetching_bd26(),
                                     in._instr_fetching_bd27(),
                                     in._instr_fetching_bd28(),
                                     in._instr_fetching_bd29(),
                                     in._instr_fetching_bd30(),
                                     in._instr_fetching_bd31(),
                                     in._instr_fetching_bd32(),
                                     in._instr_fetching_bd33(),
                                     in._instr_fetching_bd34(),
                                     in._instr_fetching_bd35(),
                                     in._instr_fetching_bd36(),
                                     in._bc_decomposition_id(),
                                     in._bc_decomposition_pc(),
                                     in._bc_decomposition_bytes_to_read(),
                                     in._bc_decomposition_bytes(),
                                     in._bc_decomposition_bytes_pc_plus_1(),
                                     in._bc_decomposition_bytes_pc_plus_2(),
                                     in._bc_decomposition_bytes_pc_plus_3(),
                                     in._bc_decomposition_bytes_pc_plus_4(),
                                     in._bc_decomposition_bytes_pc_plus_5(),
                                     in._bc_decomposition_bytes_pc_plus_6(),
                                     in._bc_decomposition_bytes_pc_plus_7(),
                                     in._bc_decomposition_bytes_pc_plus_8(),
                                     in._bc_decomposition_bytes_pc_plus_9(),
                                     in._bc_decomposition_bytes_pc_plus_10(),
                                     in._bc_decomposition_bytes_pc_plus_11(),
                                     in._bc_decomposition_bytes_pc_plus_12(),
                                     in._bc_decomposition_bytes_pc_plus_13(),
                                     in._bc_decomposition_bytes_pc_plus_14(),
                                     in._bc_decomposition_bytes_pc_plus_15(),
                                     in._bc_decomposition_bytes_pc_plus_16(),
                                     in._bc_decomposition_bytes_pc_plus_17(),
                                     in._bc_decomposition_bytes_pc_plus_18(),
                                     in._bc_decomposition_bytes_pc_plus_19(),
                                     in._bc_decomposition_bytes_pc_plus_20(),
                                     in._bc_decomposition_bytes_pc_plus_21(),
                                     in._bc_decomposition_bytes_pc_plus_22(),
                                     in._bc_decomposition_bytes_pc_plus_23(),
                                     in._bc_decomposition_bytes_pc_plus_24(),
                                     in._bc_decomposition_bytes_pc_plus_25(),
                                     in._bc_decomposition_bytes_pc_plus_26(),
                                     in._bc_decomposition_bytes_pc_plus_27(),
                                     in._bc_decomposition_bytes_pc_plus_28(),
                                     in._bc_decomposition_bytes_pc_plus_29(),
                                     in._bc_decomposition_bytes_pc_plus_30(),
                                     in._bc_decomposition_bytes_pc_plus_31(),
                                     in._bc_decomposition_bytes_pc_plus_32(),
                                     in._bc_decomposition_bytes_pc_plus_33(),
                                     in._bc_decomposition_bytes_pc_plus_34(),
                                     in._bc_decomposition_bytes_pc_plus_35(),
                                     in._bc_decomposition_bytes_pc_plus_36());
    }
};

template <typename FF_>
class lookup_instr_fetching_bytes_from_bc_dec_relation
    : public GenericLookupRelation<lookup_instr_fetching_bytes_from_bc_dec_settings, FF_> {
  public:
    using Settings = lookup_instr_fetching_bytes_from_bc_dec_settings;
    static constexpr std::string_view NAME = lookup_instr_fetching_bytes_from_bc_dec_settings::NAME;
    static constexpr std::string_view RELATION_NAME = lookup_instr_fetching_bytes_from_bc_dec_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_instr_fetching_bytes_from_bc_dec_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

/////////////////// lookup_instr_fetching_wire_instruction_info ///////////////////

class lookup_instr_fetching_wire_instruction_info_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_INSTR_FETCHING_WIRE_INSTRUCTION_INFO";
    static constexpr std::string_view RELATION_NAME = "instr_fetching";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 22;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::instr_fetching_sel_opcode_defined;
    static constexpr Column DST_SELECTOR = Column::precomputed_sel_range_8;
    static constexpr Column COUNTS = Column::lookup_instr_fetching_wire_instruction_info_counts;
    static constexpr Column INVERSES = Column::lookup_instr_fetching_wire_instruction_info_inv;
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        ColumnAndShifts::instr_fetching_bd0,          ColumnAndShifts::instr_fetching_opcode_out_of_range,
        ColumnAndShifts::instr_fetching_exec_opcode,  ColumnAndShifts::instr_fetching_instr_size,
        ColumnAndShifts::instr_fetching_sel_op_dc_0,  ColumnAndShifts::instr_fetching_sel_op_dc_1,
        ColumnAndShifts::instr_fetching_sel_op_dc_2,  ColumnAndShifts::instr_fetching_sel_op_dc_3,
        ColumnAndShifts::instr_fetching_sel_op_dc_4,  ColumnAndShifts::instr_fetching_sel_op_dc_5,
        ColumnAndShifts::instr_fetching_sel_op_dc_6,  ColumnAndShifts::instr_fetching_sel_op_dc_7,
        ColumnAndShifts::instr_fetching_sel_op_dc_8,  ColumnAndShifts::instr_fetching_sel_op_dc_9,
        ColumnAndShifts::instr_fetching_sel_op_dc_10, ColumnAndShifts::instr_fetching_sel_op_dc_11,
        ColumnAndShifts::instr_fetching_sel_op_dc_12, ColumnAndShifts::instr_fetching_sel_op_dc_13,
        ColumnAndShifts::instr_fetching_sel_op_dc_14, ColumnAndShifts::instr_fetching_sel_op_dc_15,
        ColumnAndShifts::instr_fetching_sel_op_dc_16, ColumnAndShifts::instr_fetching_sel_op_dc_17
    };
    static constexpr std::array<ColumnAndShifts, LOOKUP_TUPLE_SIZE> DST_COLUMNS = {
        ColumnAndShifts::precomputed_clk,          ColumnAndShifts::precomputed_opcode_out_of_range,
        ColumnAndShifts::precomputed_exec_opcode,  ColumnAndShifts::precomputed_instr_size,
        ColumnAndShifts::precomputed_sel_op_dc_0,  ColumnAndShifts::precomputed_sel_op_dc_1,
        ColumnAndShifts::precomputed_sel_op_dc_2,  ColumnAndShifts::precomputed_sel_op_dc_3,
        ColumnAndShifts::precomputed_sel_op_dc_4,  ColumnAndShifts::precomputed_sel_op_dc_5,
        ColumnAndShifts::precomputed_sel_op_dc_6,  ColumnAndShifts::precomputed_sel_op_dc_7,
        ColumnAndShifts::precomputed_sel_op_dc_8,  ColumnAndShifts::precomputed_sel_op_dc_9,
        ColumnAndShifts::precomputed_sel_op_dc_10, ColumnAndShifts::precomputed_sel_op_dc_11,
        ColumnAndShifts::precomputed_sel_op_dc_12, ColumnAndShifts::precomputed_sel_op_dc_13,
        ColumnAndShifts::precomputed_sel_op_dc_14, ColumnAndShifts::precomputed_sel_op_dc_15,
        ColumnAndShifts::precomputed_sel_op_dc_16, ColumnAndShifts::precomputed_sel_op_dc_17
    };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._instr_fetching_sel_opcode_defined() == 1 || in._precomputed_sel_range_8() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._instr_fetching_sel_opcode_defined());
        const auto is_table_entry = View(in._precomputed_sel_range_8());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_instr_fetching_wire_instruction_info_inv(),
                                     in._lookup_instr_fetching_wire_instruction_info_counts(),
                                     in._instr_fetching_sel_opcode_defined(),
                                     in._precomputed_sel_range_8(),
                                     in._instr_fetching_bd0(),
                                     in._instr_fetching_opcode_out_of_range(),
                                     in._instr_fetching_exec_opcode(),
                                     in._instr_fetching_instr_size(),
                                     in._instr_fetching_sel_op_dc_0(),
                                     in._instr_fetching_sel_op_dc_1(),
                                     in._instr_fetching_sel_op_dc_2(),
                                     in._instr_fetching_sel_op_dc_3(),
                                     in._instr_fetching_sel_op_dc_4(),
                                     in._instr_fetching_sel_op_dc_5(),
                                     in._instr_fetching_sel_op_dc_6(),
                                     in._instr_fetching_sel_op_dc_7(),
                                     in._instr_fetching_sel_op_dc_8(),
                                     in._instr_fetching_sel_op_dc_9(),
                                     in._instr_fetching_sel_op_dc_10(),
                                     in._instr_fetching_sel_op_dc_11(),
                                     in._instr_fetching_sel_op_dc_12(),
                                     in._instr_fetching_sel_op_dc_13(),
                                     in._instr_fetching_sel_op_dc_14(),
                                     in._instr_fetching_sel_op_dc_15(),
                                     in._instr_fetching_sel_op_dc_16(),
                                     in._instr_fetching_sel_op_dc_17(),
                                     in._precomputed_clk(),
                                     in._precomputed_opcode_out_of_range(),
                                     in._precomputed_exec_opcode(),
                                     in._precomputed_instr_size(),
                                     in._precomputed_sel_op_dc_0(),
                                     in._precomputed_sel_op_dc_1(),
                                     in._precomputed_sel_op_dc_2(),
                                     in._precomputed_sel_op_dc_3(),
                                     in._precomputed_sel_op_dc_4(),
                                     in._precomputed_sel_op_dc_5(),
                                     in._precomputed_sel_op_dc_6(),
                                     in._precomputed_sel_op_dc_7(),
                                     in._precomputed_sel_op_dc_8(),
                                     in._precomputed_sel_op_dc_9(),
                                     in._precomputed_sel_op_dc_10(),
                                     in._precomputed_sel_op_dc_11(),
                                     in._precomputed_sel_op_dc_12(),
                                     in._precomputed_sel_op_dc_13(),
                                     in._precomputed_sel_op_dc_14(),
                                     in._precomputed_sel_op_dc_15(),
                                     in._precomputed_sel_op_dc_16(),
                                     in._precomputed_sel_op_dc_17());
    }
};

template <typename FF_>
class lookup_instr_fetching_wire_instruction_info_relation
    : public GenericLookupRelation<lookup_instr_fetching_wire_instruction_info_settings, FF_> {
  public:
    using Settings = lookup_instr_fetching_wire_instruction_info_settings;
    static constexpr std::string_view NAME = lookup_instr_fetching_wire_instruction_info_settings::NAME;
    static constexpr std::string_view RELATION_NAME =
        lookup_instr_fetching_wire_instruction_info_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_instr_fetching_wire_instruction_info_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

} // namespace bb::avm2
