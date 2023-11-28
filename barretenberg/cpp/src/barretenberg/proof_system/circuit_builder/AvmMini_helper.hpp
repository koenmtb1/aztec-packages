#pragma once

#include "barretenberg/ecc/curves/bn254/fr.hpp"
#include "barretenberg/proof_system/circuit_builder/circuit_builder_base.hpp"

#include "barretenberg/flavor/generated/AvmMini_flavor.hpp"
#include "barretenberg/relations/generated/AvmMini.hpp"

namespace proof_system {

using Flavor = proof_system::honk::flavor::AvmMiniFlavor;
using FF = Flavor::FF;
using Row = proof_system::AvmMini_vm::Row<barretenberg::fr>;

void log_avmMini_trace(std::vector<Row> const& trace, size_t beg, size_t end);

} // namespace proof_system