// AUTOGENERATED FILE
#pragma once

#include "barretenberg/relations/relation_parameters.hpp"
#include "barretenberg/relations/relation_types.hpp"

namespace bb::Avm_vm {

template <typename FF_> class memImpl {
  public:
    using FF = FF_;

    static constexpr std::array<size_t, 54> SUBRELATION_PARTIAL_LENGTHS = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
                                                                            3, 4, 3, 4, 3, 3, 2, 3, 3, 4, 4, 4, 4, 4,
                                                                            2, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                                                            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2 };

    template <typename ContainerOverSubrelations, typename AllEntities>
    void static accumulate(ContainerOverSubrelations& evals,
                           const AllEntities& new_term,
                           [[maybe_unused]] const RelationParameters<FF>&,
                           [[maybe_unused]] const FF& scaling_factor)
    {
        const auto constants_MEM_TAG_FF = FF(0);
        const auto constants_MEM_TAG_U32 = FF(4);
        const auto mem_SEL_DIRECT_MEM_OP_A =
            ((new_term.mem_sel_op_a + new_term.mem_sel_op_poseidon_read_a) + new_term.mem_sel_op_poseidon_write_a);
        const auto mem_SEL_DIRECT_MEM_OP_B =
            ((new_term.mem_sel_op_b + new_term.mem_sel_op_poseidon_read_b) + new_term.mem_sel_op_poseidon_write_b);
        const auto mem_SEL_DIRECT_MEM_OP_C =
            ((new_term.mem_sel_op_c + new_term.mem_sel_op_poseidon_read_c) + new_term.mem_sel_op_poseidon_write_c);
        const auto mem_SEL_DIRECT_MEM_OP_D =
            ((new_term.mem_sel_op_d + new_term.mem_sel_op_poseidon_read_d) + new_term.mem_sel_op_poseidon_write_d);
        const auto mem_NUM_SUB_CLK = FF(12);
        const auto mem_IND_OP = (((new_term.mem_sel_resolve_ind_addr_a + new_term.mem_sel_resolve_ind_addr_b) +
                                  new_term.mem_sel_resolve_ind_addr_c) +
                                 new_term.mem_sel_resolve_ind_addr_d);
        const auto mem_SUB_CLK =
            (new_term.mem_sel_mem * ((((new_term.mem_sel_resolve_ind_addr_b + mem_SEL_DIRECT_MEM_OP_B) +
                                       (FF(2) * (new_term.mem_sel_resolve_ind_addr_c + mem_SEL_DIRECT_MEM_OP_C))) +
                                      (FF(3) * (new_term.mem_sel_resolve_ind_addr_d + mem_SEL_DIRECT_MEM_OP_D))) +
                                     (FF(4) * ((FF(1) - mem_IND_OP) + new_term.mem_rw))));

        {
            using Accumulator = typename std::tuple_element_t<0, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_lastAccess * (FF(1) - new_term.mem_lastAccess));
            tmp *= scaling_factor;
            std::get<0>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<1, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_last * (FF(1) - new_term.mem_last));
            tmp *= scaling_factor;
            std::get<1>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<2, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_rw * (FF(1) - new_term.mem_rw));
            tmp *= scaling_factor;
            std::get<2>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<3, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_tag_err * (FF(1) - new_term.mem_tag_err));
            tmp *= scaling_factor;
            std::get<3>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<4, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_a * (FF(1) - new_term.mem_sel_op_a));
            tmp *= scaling_factor;
            std::get<4>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<5, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_b * (FF(1) - new_term.mem_sel_op_b));
            tmp *= scaling_factor;
            std::get<5>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<6, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_c * (FF(1) - new_term.mem_sel_op_c));
            tmp *= scaling_factor;
            std::get<6>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<7, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_d * (FF(1) - new_term.mem_sel_op_d));
            tmp *= scaling_factor;
            std::get<7>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<8, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_slice * (FF(1) - new_term.mem_sel_op_slice));
            tmp *= scaling_factor;
            std::get<8>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<9, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_a * (FF(1) - new_term.mem_sel_resolve_ind_addr_a));
            tmp *= scaling_factor;
            std::get<9>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<10, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_b * (FF(1) - new_term.mem_sel_resolve_ind_addr_b));
            tmp *= scaling_factor;
            std::get<10>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<11, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_c * (FF(1) - new_term.mem_sel_resolve_ind_addr_c));
            tmp *= scaling_factor;
            std::get<11>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<12, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_d * (FF(1) - new_term.mem_sel_resolve_ind_addr_d));
            tmp *= scaling_factor;
            std::get<12>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<13, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_mem -
                        ((((((((mem_SEL_DIRECT_MEM_OP_A + mem_SEL_DIRECT_MEM_OP_B) + mem_SEL_DIRECT_MEM_OP_C) +
                              mem_SEL_DIRECT_MEM_OP_D) +
                             new_term.mem_sel_resolve_ind_addr_a) +
                            new_term.mem_sel_resolve_ind_addr_b) +
                           new_term.mem_sel_resolve_ind_addr_c) +
                          new_term.mem_sel_resolve_ind_addr_d) +
                         new_term.mem_sel_op_slice));
            tmp *= scaling_factor;
            std::get<13>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<14, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_mem * (new_term.mem_sel_mem - FF(1)));
            tmp *= scaling_factor;
            std::get<14>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<15, ContainerOverSubrelations>;
            auto tmp =
                (((FF(1) - new_term.main_sel_first) * new_term.mem_sel_mem_shift) * (FF(1) - new_term.mem_sel_mem));
            tmp *= scaling_factor;
            std::get<15>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<16, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.mem_sel_mem);
            tmp *= scaling_factor;
            std::get<16>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<17, ContainerOverSubrelations>;
            auto tmp = (((FF(1) - new_term.mem_last) * new_term.mem_sel_mem) * (FF(1) - new_term.mem_sel_mem_shift));
            tmp *= scaling_factor;
            std::get<17>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<18, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_rng_chk - (new_term.mem_sel_mem * (FF(1) - new_term.mem_last)));
            tmp *= scaling_factor;
            std::get<18>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<19, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_tsp - ((mem_NUM_SUB_CLK * new_term.mem_clk) + mem_SUB_CLK));
            tmp *= scaling_factor;
            std::get<19>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<20, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_glob_addr - ((new_term.mem_space_id * FF(4294967296UL)) + new_term.mem_addr));
            tmp *= scaling_factor;
            std::get<20>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<21, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * (FF(1) - new_term.mem_lastAccess));
            tmp *= scaling_factor;
            std::get<21>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<22, ContainerOverSubrelations>;
            auto tmp = ((FF(1) - new_term.mem_lastAccess) * (new_term.mem_glob_addr_shift - new_term.mem_glob_addr));
            tmp *= scaling_factor;
            std::get<22>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<23, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_rng_chk *
                        (new_term.mem_diff -
                         ((new_term.mem_lastAccess * (new_term.mem_glob_addr_shift - new_term.mem_glob_addr)) +
                          ((FF(1) - new_term.mem_lastAccess) * (new_term.mem_tsp_shift - new_term.mem_tsp)))));
            tmp *= scaling_factor;
            std::get<23>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<24, ContainerOverSubrelations>;
            auto tmp = (((FF(1) - new_term.mem_lastAccess) * (FF(1) - new_term.mem_rw_shift)) *
                        (new_term.mem_val_shift - new_term.mem_val));
            tmp *= scaling_factor;
            std::get<24>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<25, ContainerOverSubrelations>;
            auto tmp = (((FF(1) - new_term.mem_lastAccess) * (FF(1) - new_term.mem_rw_shift)) *
                        (new_term.mem_tag_shift - new_term.mem_tag));
            tmp *= scaling_factor;
            std::get<25>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<26, ContainerOverSubrelations>;
            auto tmp = ((new_term.mem_lastAccess * (FF(1) - new_term.mem_rw_shift)) * new_term.mem_val_shift);
            tmp *= scaling_factor;
            std::get<26>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<27, ContainerOverSubrelations>;
            auto tmp = ((new_term.mem_lastAccess * (FF(1) - new_term.mem_rw_shift)) *
                        (new_term.mem_tag_shift - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<27>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<28, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_skip_check_tag - new_term.mem_sel_op_slice);
            tmp *= scaling_factor;
            std::get<28>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<29, ContainerOverSubrelations>;
            auto tmp = (((FF(1) - new_term.mem_skip_check_tag) * (FF(1) - new_term.mem_rw)) *
                        (((new_term.mem_r_in_tag - new_term.mem_tag) * (FF(1) - new_term.mem_one_min_inv)) -
                         new_term.mem_tag_err));
            tmp *= scaling_factor;
            std::get<29>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<30, ContainerOverSubrelations>;
            auto tmp = ((FF(1) - new_term.mem_tag_err) * new_term.mem_one_min_inv);
            tmp *= scaling_factor;
            std::get<30>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<31, ContainerOverSubrelations>;
            auto tmp = ((new_term.mem_skip_check_tag + new_term.mem_rw) * new_term.mem_tag_err);
            tmp *= scaling_factor;
            std::get<31>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<32, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_rw * (new_term.mem_w_in_tag - new_term.mem_tag));
            tmp *= scaling_factor;
            std::get<32>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<33, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_rw * new_term.mem_tag_err);
            tmp *= scaling_factor;
            std::get<33>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<34, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_a * (new_term.mem_r_in_tag - constants_MEM_TAG_U32));
            tmp *= scaling_factor;
            std::get<34>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<35, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_b * (new_term.mem_r_in_tag - constants_MEM_TAG_U32));
            tmp *= scaling_factor;
            std::get<35>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<36, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_c * (new_term.mem_r_in_tag - constants_MEM_TAG_U32));
            tmp *= scaling_factor;
            std::get<36>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<37, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_d * (new_term.mem_r_in_tag - constants_MEM_TAG_U32));
            tmp *= scaling_factor;
            std::get<37>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<38, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_a * new_term.mem_rw);
            tmp *= scaling_factor;
            std::get<38>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<39, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_b * new_term.mem_rw);
            tmp *= scaling_factor;
            std::get<39>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<40, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_c * new_term.mem_rw);
            tmp *= scaling_factor;
            std::get<40>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<41, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_resolve_ind_addr_d * new_term.mem_rw);
            tmp *= scaling_factor;
            std::get<41>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<42, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_slice * (new_term.mem_w_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<42>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<43, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_slice * (new_term.mem_r_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<43>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<44, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_read_a * (new_term.mem_w_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<44>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<45, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_read_b * (new_term.mem_w_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<45>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<46, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_read_c * (new_term.mem_w_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<46>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<47, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_read_d * (new_term.mem_w_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<47>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<48, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_write_a * (new_term.mem_r_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<48>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<49, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_write_b * (new_term.mem_r_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<49>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<50, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_write_c * (new_term.mem_r_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<50>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<51, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_sel_op_poseidon_write_d * (new_term.mem_r_in_tag - constants_MEM_TAG_FF));
            tmp *= scaling_factor;
            std::get<51>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<52, ContainerOverSubrelations>;
            auto tmp = ((new_term.mem_sel_mov_ia_to_ic + new_term.mem_sel_mov_ib_to_ic) * new_term.mem_tag_err);
            tmp *= scaling_factor;
            std::get<52>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<53, ContainerOverSubrelations>;
            auto tmp = (new_term.mem_diff - ((new_term.mem_u16_r0 + (new_term.mem_u16_r1 * FF(65536))) +
                                             (new_term.mem_u8_r0 * FF(4294967296UL))));
            tmp *= scaling_factor;
            std::get<53>(evals) += typename Accumulator::View(tmp);
        }
    }
};

template <typename FF> class mem : public Relation<memImpl<FF>> {
  public:
    static constexpr const char* NAME = "mem";

    static std::string get_subrelation_label(size_t index)
    {
        switch (index) {
        case 15:
            return "MEM_CONTIGUOUS";
        case 16:
            return "MEM_FIRST_EMPTY";
        case 17:
            return "MEM_LAST";
        case 19:
            return "TIMESTAMP";
        case 20:
            return "GLOBAL_ADDR";
        case 21:
            return "LAST_ACCESS_FIRST_ROW";
        case 22:
            return "MEM_LAST_ACCESS_DELIMITER";
        case 24:
            return "MEM_READ_WRITE_VAL_CONSISTENCY";
        case 25:
            return "MEM_READ_WRITE_TAG_CONSISTENCY";
        case 26:
            return "MEM_ZERO_INIT";
        case 27:
            return "MEM_ZERO_INIT_TAG_FF";
        case 28:
            return "SKIP_CHECK_TAG";
        case 29:
            return "MEM_IN_TAG_CONSISTENCY_1";
        case 30:
            return "MEM_IN_TAG_CONSISTENCY_2";
        case 31:
            return "NO_TAG_ERR_WRITE_OR_SKIP";
        case 33:
            return "NO_TAG_ERR_WRITE";
        case 52:
            return "MOV_SAME_TAG";
        }
        return std::to_string(index);
    }
};

} // namespace bb::Avm_vm