// AUTOGENERATED FILE
#pragma once

#include "../columns.hpp"
#include "barretenberg/relations/generic_permutation/generic_permutation_relation.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace bb::avm {

/////////////////// perm_merkle_poseidon2 ///////////////////

class perm_merkle_poseidon2_permutation_settings {
  public:
    // This constant defines how many columns are bundled together to form each set.
    constexpr static size_t COLUMNS_PER_SET = 4;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::merkle_tree_sel_merkle_tree;
    static constexpr Column DST_SELECTOR = Column::poseidon2_full_sel_merkle_tree;
    static constexpr Column INVERSES = Column::perm_merkle_poseidon2_inv;

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._merkle_tree_sel_merkle_tree() == 1 || in._poseidon2_full_sel_merkle_tree() == 1);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return std::forward_as_tuple(in._perm_merkle_poseidon2_inv(),
                                     in._merkle_tree_sel_merkle_tree(),
                                     in._merkle_tree_sel_merkle_tree(),
                                     in._poseidon2_full_sel_merkle_tree(),
                                     in._merkle_tree_clk(),
                                     in._merkle_tree_left_hash(),
                                     in._merkle_tree_right_hash(),
                                     in._merkle_tree_output_hash(),
                                     in._poseidon2_full_clk(),
                                     in._poseidon2_full_input_0(),
                                     in._poseidon2_full_input_1(),
                                     in._poseidon2_full_output());
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return std::forward_as_tuple(in._perm_merkle_poseidon2_inv(),
                                     in._merkle_tree_sel_merkle_tree(),
                                     in._merkle_tree_sel_merkle_tree(),
                                     in._poseidon2_full_sel_merkle_tree(),
                                     in._merkle_tree_clk(),
                                     in._merkle_tree_left_hash(),
                                     in._merkle_tree_right_hash(),
                                     in._merkle_tree_output_hash(),
                                     in._poseidon2_full_clk(),
                                     in._poseidon2_full_input_0(),
                                     in._poseidon2_full_input_1(),
                                     in._poseidon2_full_output());
    }
};

template <typename FF_>
class perm_merkle_poseidon2_relation
    : public GenericPermutationRelation<perm_merkle_poseidon2_permutation_settings, FF_> {
  public:
    static constexpr std::string_view NAME = "PERM_MERKLE_POSEIDON2";
};
template <typename FF_>
using perm_merkle_poseidon2 = GenericPermutation<perm_merkle_poseidon2_permutation_settings, FF_>;

} // namespace bb::avm