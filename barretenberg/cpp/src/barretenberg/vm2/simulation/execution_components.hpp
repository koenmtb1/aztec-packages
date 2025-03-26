#pragma once

#include <memory>
#include <span>

#include "barretenberg/vm2/common/aztec_types.hpp"
#include "barretenberg/vm2/common/field.hpp"
#include "barretenberg/vm2/simulation/addressing.hpp"
#include "barretenberg/vm2/simulation/bytecode_manager.hpp"
#include "barretenberg/vm2/simulation/context.hpp"
#include "barretenberg/vm2/simulation/events/addressing_event.hpp"
#include "barretenberg/vm2/simulation/events/context_events.hpp"
#include "barretenberg/vm2/simulation/events/event_emitter.hpp"
#include "barretenberg/vm2/simulation/events/memory_event.hpp"
#include "barretenberg/vm2/simulation/memory.hpp"

namespace bb::avm2::simulation {

class ExecutionComponentsProviderInterface {
  public:
    virtual ~ExecutionComponentsProviderInterface() = default;

    // TODO: Update this, these params are temporary
    virtual std::unique_ptr<ContextInterface> make_nested_context(AztecAddress address,
                                                                  AztecAddress msg_sender,
                                                                  std::span<const FF> calldata,
                                                                  bool is_static) = 0;

    virtual std::unique_ptr<ContextInterface> make_enqueued_context(AztecAddress address,
                                                                    AztecAddress msg_sender,
                                                                    std::span<const FF> calldata,
                                                                    bool is_static) = 0;

    virtual std::unique_ptr<AddressingInterface> make_addressing(AddressingEvent& event) = 0;
};

class ExecutionComponentsProvider : public ExecutionComponentsProviderInterface {
  public:
    ExecutionComponentsProvider(TxBytecodeManagerInterface& tx_bytecode_manager,
                                EventEmitterInterface<MemoryEvent>& memory_events,
                                EventEmitterInterface<ContextStackEvent>& ctx_stack_events,
                                const InstructionInfoDBInterface& instruction_info_db)
        : tx_bytecode_manager(tx_bytecode_manager)
        , memory_events(memory_events)
        , ctx_stack_events(ctx_stack_events)
        , instruction_info_db(instruction_info_db)
    {}
    std::unique_ptr<ContextInterface> make_nested_context(AztecAddress address,
                                                          AztecAddress msg_sender,
                                                          std::span<const FF> calldata,
                                                          bool is_static) override;
    std::unique_ptr<ContextInterface> make_enqueued_context(AztecAddress address,
                                                            AztecAddress msg_sender,
                                                            std::span<const FF> calldata,
                                                            bool is_static) override;
    std::unique_ptr<AddressingInterface> make_addressing(AddressingEvent& event) override;

  private:
    uint32_t next_context_id = 0;

    TxBytecodeManagerInterface& tx_bytecode_manager;
    EventEmitterInterface<MemoryEvent>& memory_events;
    EventEmitterInterface<ContextStackEvent>& ctx_stack_events;
    const InstructionInfoDBInterface& instruction_info_db;

    // Sadly someone has to own these.
    // TODO(fcarreiro): We are creating one of these per execution row and only releasing them at
    // the end of the TX. Ideally we'd improve this.
    std::vector<std::unique_ptr<EventEmitterInterface<AddressingEvent>>> addressing_event_emitters;
};

} // namespace bb::avm2::simulation
