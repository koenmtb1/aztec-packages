// AUTOGENERATED FILE
#pragma once

#include <string_view>

#include "barretenberg/relations/relation_parameters.hpp"
#include "barretenberg/relations/relation_types.hpp"

namespace bb::avm2 {

template <typename FF_> class bitwiseImpl {
  public:
    using FF = FF_;

    static constexpr std::array<size_t, 12> SUBRELATION_PARTIAL_LENGTHS = { 3, 3, 3, 4, 4, 5, 3, 3, 3, 3, 3, 3 };

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        const auto& new_term = in;
        return ((new_term.bitwise_sel + new_term.bitwise_last)).is_zero();
    }

    template <typename ContainerOverSubrelations, typename AllEntities>
    void static accumulate(ContainerOverSubrelations& evals,
                           const AllEntities& new_term,
                           [[maybe_unused]] const RelationParameters<FF>&,
                           [[maybe_unused]] const FF& scaling_factor)
    {

        {
            using Accumulator = typename std::tuple_element_t<0, ContainerOverSubrelations>;
            auto tmp = (new_term.bitwise_sel * (FF(1) - new_term.bitwise_sel));
            tmp *= scaling_factor;
            std::get<0>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<1, ContainerOverSubrelations>;
            auto tmp = (new_term.bitwise_last * (FF(1) - new_term.bitwise_last));
            tmp *= scaling_factor;
            std::get<1>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<2, ContainerOverSubrelations>;
            auto tmp = ((new_term.bitwise_op_id_shift - new_term.bitwise_op_id) * (FF(1) - new_term.bitwise_last));
            tmp *= scaling_factor;
            std::get<2>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<3, ContainerOverSubrelations>;
            auto tmp = ((new_term.bitwise_sel * ((new_term.bitwise_ctr_shift - new_term.bitwise_ctr) + FF(1))) *
                        (FF(1) - new_term.bitwise_last));
            tmp *= scaling_factor;
            std::get<3>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<4, ContainerOverSubrelations>;
            auto tmp = ((new_term.bitwise_ctr * (((FF(1) - new_term.bitwise_sel) * (FF(1) - new_term.bitwise_ctr_inv)) +
                                                 new_term.bitwise_ctr_inv)) -
                        new_term.bitwise_sel);
            tmp *= scaling_factor;
            std::get<4>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<5, ContainerOverSubrelations>;
            auto tmp =
                (new_term.bitwise_sel * ((((new_term.bitwise_ctr - FF(1)) *
                                           ((new_term.bitwise_last * (FF(1) - new_term.bitwise_ctr_min_one_inv)) +
                                            new_term.bitwise_ctr_min_one_inv)) +
                                          new_term.bitwise_last) -
                                         FF(1)));
            tmp *= scaling_factor;
            std::get<5>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<6, ContainerOverSubrelations>;
            auto tmp = (new_term.bitwise_last * (new_term.bitwise_acc_ia - new_term.bitwise_ia_byte));
            tmp *= scaling_factor;
            std::get<6>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<7, ContainerOverSubrelations>;
            auto tmp = (new_term.bitwise_last * (new_term.bitwise_acc_ib - new_term.bitwise_ib_byte));
            tmp *= scaling_factor;
            std::get<7>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<8, ContainerOverSubrelations>;
            auto tmp = (new_term.bitwise_last * (new_term.bitwise_acc_ic - new_term.bitwise_ic_byte));
            tmp *= scaling_factor;
            std::get<8>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<9, ContainerOverSubrelations>;
            auto tmp =
                (((new_term.bitwise_acc_ia - new_term.bitwise_ia_byte) - (FF(256) * new_term.bitwise_acc_ia_shift)) *
                 (FF(1) - new_term.bitwise_last));
            tmp *= scaling_factor;
            std::get<9>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<10, ContainerOverSubrelations>;
            auto tmp =
                (((new_term.bitwise_acc_ib - new_term.bitwise_ib_byte) - (FF(256) * new_term.bitwise_acc_ib_shift)) *
                 (FF(1) - new_term.bitwise_last));
            tmp *= scaling_factor;
            std::get<10>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<11, ContainerOverSubrelations>;
            auto tmp =
                (((new_term.bitwise_acc_ic - new_term.bitwise_ic_byte) - (FF(256) * new_term.bitwise_acc_ic_shift)) *
                 (FF(1) - new_term.bitwise_last));
            tmp *= scaling_factor;
            std::get<11>(evals) += typename Accumulator::View(tmp);
        }
    }
};

template <typename FF> class bitwise : public Relation<bitwiseImpl<FF>> {
  public:
    static constexpr const std::string_view NAME = "bitwise";

    static std::string get_subrelation_label(size_t index)
    {
        switch (index) {
        case 2:
            return "BITW_OP_ID_REL";
        case 3:
            return "BITW_CTR_DECREMENT";
        case 4:
            return "BITW_SEL_CTR_NON_ZERO";
        case 5:
            return "BITW_LAST_FOR_CTR_ONE";
        case 6:
            return "BITW_INIT_A";
        case 7:
            return "BITW_INIT_B";
        case 8:
            return "BITW_INIT_C";
        case 9:
            return "BITW_ACC_REL_A";
        case 10:
            return "BITW_ACC_REL_B";
        case 11:
            return "BITW_ACC_REL_C";
        }
        return std::to_string(index);
    }

    // Subrelation indices constants, to be used in tests.
    static constexpr size_t SR_BITW_OP_ID_REL = 2;
    static constexpr size_t SR_BITW_CTR_DECREMENT = 3;
    static constexpr size_t SR_BITW_SEL_CTR_NON_ZERO = 4;
    static constexpr size_t SR_BITW_LAST_FOR_CTR_ONE = 5;
    static constexpr size_t SR_BITW_INIT_A = 6;
    static constexpr size_t SR_BITW_INIT_B = 7;
    static constexpr size_t SR_BITW_INIT_C = 8;
    static constexpr size_t SR_BITW_ACC_REL_A = 9;
    static constexpr size_t SR_BITW_ACC_REL_B = 10;
    static constexpr size_t SR_BITW_ACC_REL_C = 11;
};

} // namespace bb::avm2