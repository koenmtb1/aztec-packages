#pragma once
#include "barretenberg/common/mem.hpp"
#include "barretenberg/common/ref_array.hpp"
#include "barretenberg/common/slab_allocator.hpp"
#include <cstddef>

#ifdef CHECK_CIRCUIT_STACKTRACES
#include <backward.hpp>
#endif

namespace bb {

#ifdef CHECK_CIRCUIT_STACKTRACES
struct BbStackTrace : backward::StackTrace {
    BbStackTrace() { load_here(32); }
};
struct StackTraces {
    std::vector<BbStackTrace> stack_traces;
    void populate() { stack_traces.emplace_back(); }
    void print(size_t gate_idx) const { backward::Printer{}.print(stack_traces.at(gate_idx)); }
    // Don't interfere with equality semantics of structs that include this in debug builds
    bool operator==(const StackTraces& other) const
    {
        static_cast<void>(other);
        return true;
    }
};
#endif

// A set of fixed block size conigurations to be used with the structured execution trace. The actual block sizes
// corresponding to these settings are defined in the corresponding arithmetization classes (Ultra/Mega). For efficiency
// it is best to use the smallest possible block sizes to accommodate a given situation.
enum class TraceStructure { NONE, TINY_TEST, SMALL_TEST, CLIENT_IVC_BENCH, E2E_FULL_TEST };

struct TraceSettings {
    TraceStructure structure = TraceStructure::NONE;
    // The size of the overflow block. Specified separately because it is allowed to be determined at runtime in the
    // context of VK computation
    uint32_t overflow_capacity = 0;
};

/**
 * @brief Basic structure for storing gate data in a builder
 *
 * @tparam FF
 * @tparam NUM_WIRES
 * @tparam NUM_SELECTORS
 */
template <typename FF, size_t NUM_WIRES, size_t NUM_SELECTORS> class ExecutionTraceBlock {
  public:
    using SelectorType = SlabVector<FF>;
    using WireType = SlabVector<uint32_t>;
    using Selectors = std::array<SelectorType, NUM_SELECTORS>;
    using Wires = std::array<WireType, NUM_WIRES>;

#ifdef CHECK_CIRCUIT_STACKTRACES
    // If enabled, we keep slow stack traces to be able to correlate gates with code locations where they were added
    StackTraces stack_traces;
#endif
#ifdef TRACY_HACK_GATES_AS_MEMORY
    std::vector<size_t> allocated_gates;
#endif
    void tracy_gate()
    {
#ifdef TRACY_HACK_GATES_AS_MEMORY
        std::unique_lock<std::mutex> lock(GLOBAL_GATE_MUTEX);
        GLOBAL_GATE++;
        TRACY_GATE_ALLOC(GLOBAL_GATE);
        allocated_gates.push_back(GLOBAL_GATE);
#endif
    }

    Wires wires; // vectors of indices into a witness variables array
    Selectors selectors;
    bool has_ram_rom = false;   // does the block contain RAM/ROM gates
    bool is_pub_inputs = false; // is this the public inputs block
    uint32_t trace_offset = 0;  // where this block starts in the trace

    bool operator==(const ExecutionTraceBlock& other) const = default;

    size_t size() const { return std::get<0>(this->wires).size(); }

    void reserve(size_t size_hint)
    {
        for (auto& w : wires) {
            w.reserve(size_hint);
        }
        for (auto& p : selectors) {
            p.reserve(size_hint);
        }
#ifdef CHECK_CIRCUIT_STACKTRACES
        stack_traces.stack_traces.reserve(size_hint);
#endif
    }

    uint32_t get_fixed_size(bool is_structured = true) const
    {
        return is_structured ? fixed_size : static_cast<uint32_t>(size());
    }
    void set_fixed_size(uint32_t size_in) { fixed_size = size_in; }
#ifdef TRACY_HACK_GATES_AS_MEMORY
    ~ExecutionTraceBlock()
    {
        std::unique_lock<std::mutex> lock(GLOBAL_GATE_MUTEX);
        for ([[maybe_unused]] size_t gate : allocated_gates) {
            if (!FREED_GATES.contains(gate)) {
                TRACY_GATE_FREE(gate);
                FREED_GATES.insert(gate);
            }
        }
    }
#endif
  private:
    uint32_t fixed_size = 0; // Fixed size for use in structured trace
};

} // namespace bb