// AUTOGENERATED FILE
#pragma once

#include "barretenberg/relations/relation_parameters.hpp"
#include "barretenberg/relations/relation_types.hpp"

namespace bb::Avm_vm {

template <typename FF_> class kernelImpl {
  public:
    using FF = FF_;

    static constexpr std::array<size_t, 42> SUBRELATION_PARTIAL_LENGTHS = { 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                                                                            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3,
                                                                            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

    template <typename ContainerOverSubrelations, typename AllEntities>
    void static accumulate(ContainerOverSubrelations& evals,
                           const AllEntities& new_term,
                           [[maybe_unused]] const RelationParameters<FF>&,
                           [[maybe_unused]] const FF& scaling_factor)
    {
        const auto constants_SENDER_KERNEL_INPUTS_COL_OFFSET = FF(0);
        const auto constants_ADDRESS_KERNEL_INPUTS_COL_OFFSET = FF(1);
        const auto constants_FUNCTION_SELECTOR_KERNEL_INPUTS_COL_OFFSET = FF(2);
        const auto constants_IS_STATIC_CALL_KERNEL_INPUTS_COL_OFFSET = FF(3);
        const auto constants_CHAIN_ID_KERNEL_INPUTS_COL_OFFSET = FF(4);
        const auto constants_VERSION_KERNEL_INPUTS_COL_OFFSET = FF(5);
        const auto constants_BLOCK_NUMBER_KERNEL_INPUTS_COL_OFFSET = FF(6);
        const auto constants_TIMESTAMP_KERNEL_INPUTS_COL_OFFSET = FF(7);
        const auto constants_FEE_PER_DA_GAS_KERNEL_INPUTS_COL_OFFSET = FF(8);
        const auto constants_FEE_PER_L2_GAS_KERNEL_INPUTS_COL_OFFSET = FF(9);
        const auto constants_TRANSACTION_FEE_KERNEL_INPUTS_COL_OFFSET = FF(14);
        const auto constants_START_NOTE_HASH_EXISTS_WRITE_OFFSET = FF(0);
        const auto constants_START_NULLIFIER_EXISTS_OFFSET = FF(16);
        const auto constants_START_NULLIFIER_NON_EXISTS_OFFSET = FF(32);
        const auto constants_START_L1_TO_L2_MSG_EXISTS_WRITE_OFFSET = FF(48);
        const auto constants_START_SSTORE_WRITE_OFFSET = FF(64);
        const auto constants_START_SLOAD_WRITE_OFFSET = FF(128);
        const auto constants_START_EMIT_NOTE_HASH_WRITE_OFFSET = FF(192);
        const auto constants_START_EMIT_NULLIFIER_WRITE_OFFSET = FF(208);
        const auto constants_START_EMIT_L2_TO_L1_MSG_WRITE_OFFSET = FF(224);
        const auto constants_START_EMIT_UNENCRYPTED_LOG_WRITE_OFFSET = FF(226);
        const auto main_KERNEL_INPUT_SELECTORS = ((((((((((new_term.main_sel_op_address + new_term.main_sel_op_sender) +
                                                          new_term.main_sel_op_function_selector) +
                                                         new_term.main_sel_op_transaction_fee) +
                                                        new_term.main_sel_op_chain_id) +
                                                       new_term.main_sel_op_version) +
                                                      new_term.main_sel_op_block_number) +
                                                     new_term.main_sel_op_timestamp) +
                                                    new_term.main_sel_op_fee_per_l2_gas) +
                                                   new_term.main_sel_op_fee_per_da_gas) +
                                                  new_term.main_sel_op_is_static_call);
        const auto main_KERNEL_OUTPUT_SELECTORS =
            ((((((((new_term.main_sel_op_note_hash_exists + new_term.main_sel_op_emit_note_hash) +
                   new_term.main_sel_op_nullifier_exists) +
                  new_term.main_sel_op_emit_nullifier) +
                 new_term.main_sel_op_l1_to_l2_msg_exists) +
                new_term.main_sel_op_emit_unencrypted_log) +
               new_term.main_sel_op_emit_l2_to_l1_msg) +
              new_term.main_sel_op_sload) +
             new_term.main_sel_op_sstore);

        {
            using Accumulator = typename std::tuple_element_t<0, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_execution_row *
                        (new_term.main_note_hash_exist_write_offset_shift -
                         (new_term.main_note_hash_exist_write_offset + new_term.main_sel_op_note_hash_exists)));
            tmp *= scaling_factor;
            std::get<0>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<1, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_execution_row *
                        (new_term.main_emit_note_hash_write_offset_shift -
                         (new_term.main_emit_note_hash_write_offset + new_term.main_sel_op_emit_note_hash)));
            tmp *= scaling_factor;
            std::get<1>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<2, ContainerOverSubrelations>;
            auto tmp =
                (new_term.main_sel_execution_row * (new_term.main_nullifier_exists_write_offset_shift -
                                                    (new_term.main_nullifier_exists_write_offset +
                                                     (new_term.main_sel_op_nullifier_exists * new_term.main_ib))));
            tmp *= scaling_factor;
            std::get<2>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<3, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_execution_row *
                        (new_term.main_nullifier_non_exists_write_offset_shift -
                         (new_term.main_nullifier_non_exists_write_offset +
                          (new_term.main_sel_op_nullifier_exists * (FF(1) - new_term.main_ib)))));
            tmp *= scaling_factor;
            std::get<3>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<4, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_execution_row *
                        (new_term.main_emit_nullifier_write_offset_shift -
                         (new_term.main_emit_nullifier_write_offset + new_term.main_sel_op_emit_nullifier)));
            tmp *= scaling_factor;
            std::get<4>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<5, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_execution_row *
                        (new_term.main_l1_to_l2_msg_exists_write_offset_shift -
                         (new_term.main_l1_to_l2_msg_exists_write_offset + new_term.main_sel_op_l1_to_l2_msg_exists)));
            tmp *= scaling_factor;
            std::get<5>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<6, ContainerOverSubrelations>;
            auto tmp =
                (new_term.main_sel_execution_row *
                 (new_term.main_emit_unencrypted_log_write_offset_shift -
                  (new_term.main_emit_unencrypted_log_write_offset + new_term.main_sel_op_emit_unencrypted_log)));
            tmp *= scaling_factor;
            std::get<6>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<7, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_execution_row *
                        (new_term.main_emit_l2_to_l1_msg_write_offset_shift -
                         (new_term.main_emit_l2_to_l1_msg_write_offset + new_term.main_sel_op_emit_l2_to_l1_msg)));
            tmp *= scaling_factor;
            std::get<7>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<8, ContainerOverSubrelations>;
            auto tmp =
                (new_term.main_sel_execution_row * (new_term.main_sload_write_offset_shift -
                                                    (new_term.main_sload_write_offset + new_term.main_sel_op_sload)));
            tmp *= scaling_factor;
            std::get<8>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<9, ContainerOverSubrelations>;
            auto tmp =
                (new_term.main_sel_execution_row * (new_term.main_sstore_write_offset_shift -
                                                    (new_term.main_sstore_write_offset + new_term.main_sel_op_sstore)));
            tmp *= scaling_factor;
            std::get<9>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<10, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_address *
                        (new_term.main_kernel_in_offset - constants_ADDRESS_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<10>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<11, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_sender *
                        (new_term.main_kernel_in_offset - constants_SENDER_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<11>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<12, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_function_selector *
                        (new_term.main_kernel_in_offset - constants_FUNCTION_SELECTOR_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<12>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<13, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_transaction_fee *
                        (new_term.main_kernel_in_offset - constants_TRANSACTION_FEE_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<13>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<14, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_is_static_call *
                        (new_term.main_kernel_in_offset - constants_IS_STATIC_CALL_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<14>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<15, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_chain_id *
                        (new_term.main_kernel_in_offset - constants_CHAIN_ID_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<15>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<16, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_version *
                        (new_term.main_kernel_in_offset - constants_VERSION_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<16>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<17, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_block_number *
                        (new_term.main_kernel_in_offset - constants_BLOCK_NUMBER_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<17>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<18, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_timestamp *
                        (new_term.main_kernel_in_offset - constants_TIMESTAMP_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<18>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<19, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_fee_per_da_gas *
                        (new_term.main_kernel_in_offset - constants_FEE_PER_DA_GAS_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<19>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<20, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_fee_per_l2_gas *
                        (new_term.main_kernel_in_offset - constants_FEE_PER_L2_GAS_KERNEL_INPUTS_COL_OFFSET));
            tmp *= scaling_factor;
            std::get<20>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<21, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_note_hash_exists *
                        (new_term.main_kernel_out_offset -
                         (constants_START_NOTE_HASH_EXISTS_WRITE_OFFSET + new_term.main_note_hash_exist_write_offset)));
            tmp *= scaling_factor;
            std::get<21>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<22, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_note_hash_exist_write_offset);
            tmp *= scaling_factor;
            std::get<22>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<23, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_emit_note_hash *
                        (new_term.main_kernel_out_offset -
                         (constants_START_EMIT_NOTE_HASH_WRITE_OFFSET + new_term.main_emit_note_hash_write_offset)));
            tmp *= scaling_factor;
            std::get<23>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<24, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_emit_note_hash_write_offset);
            tmp *= scaling_factor;
            std::get<24>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<25, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_nullifier_exists *
                        (new_term.main_kernel_out_offset -
                         ((new_term.main_ib *
                           (constants_START_NULLIFIER_EXISTS_OFFSET + new_term.main_nullifier_exists_write_offset)) +
                          ((FF(1) - new_term.main_ib) * (constants_START_NULLIFIER_NON_EXISTS_OFFSET +
                                                         new_term.main_nullifier_non_exists_write_offset)))));
            tmp *= scaling_factor;
            std::get<25>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<26, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_nullifier_exists_write_offset);
            tmp *= scaling_factor;
            std::get<26>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<27, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_nullifier_non_exists_write_offset);
            tmp *= scaling_factor;
            std::get<27>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<28, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_emit_nullifier *
                        (new_term.main_kernel_out_offset -
                         (constants_START_EMIT_NULLIFIER_WRITE_OFFSET + new_term.main_emit_nullifier_write_offset)));
            tmp *= scaling_factor;
            std::get<28>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<29, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_emit_nullifier_write_offset);
            tmp *= scaling_factor;
            std::get<29>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<30, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_l1_to_l2_msg_exists *
                        (new_term.main_kernel_out_offset - (constants_START_L1_TO_L2_MSG_EXISTS_WRITE_OFFSET +
                                                            new_term.main_l1_to_l2_msg_exists_write_offset)));
            tmp *= scaling_factor;
            std::get<30>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<31, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_l1_to_l2_msg_exists_write_offset);
            tmp *= scaling_factor;
            std::get<31>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<32, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_emit_unencrypted_log *
                        (new_term.main_kernel_out_offset - (constants_START_EMIT_UNENCRYPTED_LOG_WRITE_OFFSET +
                                                            new_term.main_emit_unencrypted_log_write_offset)));
            tmp *= scaling_factor;
            std::get<32>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<33, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_emit_unencrypted_log_write_offset);
            tmp *= scaling_factor;
            std::get<33>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<34, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_op_emit_l2_to_l1_msg *
                        (new_term.main_kernel_out_offset - (constants_START_EMIT_L2_TO_L1_MSG_WRITE_OFFSET +
                                                            new_term.main_emit_l2_to_l1_msg_write_offset)));
            tmp *= scaling_factor;
            std::get<34>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<35, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_emit_l2_to_l1_msg_write_offset);
            tmp *= scaling_factor;
            std::get<35>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<36, ContainerOverSubrelations>;
            auto tmp =
                (new_term.main_sel_op_sload * (new_term.main_kernel_out_offset - (constants_START_SLOAD_WRITE_OFFSET +
                                                                                  new_term.main_sload_write_offset)));
            tmp *= scaling_factor;
            std::get<36>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<37, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_sload_write_offset);
            tmp *= scaling_factor;
            std::get<37>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<38, ContainerOverSubrelations>;
            auto tmp =
                (new_term.main_sel_op_sstore * (new_term.main_kernel_out_offset - (constants_START_SSTORE_WRITE_OFFSET +
                                                                                   new_term.main_sstore_write_offset)));
            tmp *= scaling_factor;
            std::get<38>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<39, ContainerOverSubrelations>;
            auto tmp = (new_term.main_sel_first * new_term.main_sstore_write_offset);
            tmp *= scaling_factor;
            std::get<39>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<40, ContainerOverSubrelations>;
            auto tmp = (main_KERNEL_INPUT_SELECTORS * (FF(1) - new_term.main_sel_q_kernel_lookup));
            tmp *= scaling_factor;
            std::get<40>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<41, ContainerOverSubrelations>;
            auto tmp = (main_KERNEL_OUTPUT_SELECTORS * (FF(1) - new_term.main_sel_q_kernel_output_lookup));
            tmp *= scaling_factor;
            std::get<41>(evals) += typename Accumulator::View(tmp);
        }
    }
};

template <typename FF> class kernel : public Relation<kernelImpl<FF>> {
  public:
    static constexpr const char* NAME = "kernel";

    static std::string get_subrelation_label(size_t index)
    {
        switch (index) {
        case 0:
            return "NOTE_HASH_EXISTS_INC_CONSISTENCY_CHECK";
        case 1:
            return "EMIT_NOTE_HASH_INC_CONSISTENCY_CHECK";
        case 2:
            return "NULLIFIER_EXISTS_INC_CONSISTENCY_CHECK";
        case 3:
            return "NULLIFIER_NON_EXISTS_INC_CONSISTENCY_CHECK";
        case 4:
            return "EMIT_NULLIFIER_INC_CONSISTENCY_CHECK";
        case 5:
            return "L1_TO_L2_MSG_EXISTS_INC_CONSISTENCY_CHECK";
        case 6:
            return "EMIT_UNENCRYPTED_LOG_INC_CONSISTENCY_CHECK";
        case 7:
            return "EMIT_L2_TO_L1_MSG_INC_CONSISTENCY_CHECK";
        case 8:
            return "SLOAD_INC_CONSISTENCY_CHECK";
        case 9:
            return "SSTORE_INC_CONSISTENCY_CHECK";
        case 10:
            return "ADDRESS_KERNEL";
        case 11:
            return "SENDER_KERNEL";
        case 12:
            return "FUNCTION_SELECTOR_KERNEL";
        case 13:
            return "FEE_TRANSACTION_FEE_KERNEL";
        case 14:
            return "IS_STATIC_CALL_KERNEL";
        case 15:
            return "CHAIN_ID_KERNEL";
        case 16:
            return "VERSION_KERNEL";
        case 17:
            return "BLOCK_NUMBER_KERNEL";
        case 18:
            return "TIMESTAMP_KERNEL";
        case 19:
            return "FEE_DA_GAS_KERNEL";
        case 20:
            return "FEE_L2_GAS_KERNEL";
        case 21:
            return "NOTE_HASH_KERNEL_OUTPUT";
        case 23:
            return "EMIT_NOTE_HASH_KERNEL_OUTPUT";
        case 25:
            return "NULLIFIER_EXISTS_KERNEL_OUTPUT";
        case 28:
            return "EMIT_NULLIFIER_KERNEL_OUTPUT";
        case 30:
            return "L1_TO_L2_MSG_EXISTS_KERNEL_OUTPUT";
        case 32:
            return "EMIT_UNENCRYPTED_LOG_KERNEL_OUTPUT";
        case 34:
            return "EMIT_L2_TO_L1_MSGS_KERNEL_OUTPUT";
        case 36:
            return "SLOAD_KERNEL_OUTPUT";
        case 38:
            return "SSTORE_KERNEL_OUTPUT";
        case 40:
            return "KERNEL_INPUT_ACTIVE_CHECK";
        case 41:
            return "KERNEL_OUTPUT_ACTIVE_CHECK";
        }
        return std::to_string(index);
    }
};

} // namespace bb::Avm_vm