import { type FunctionCall, type Note, type TxExecutionRequest } from '@aztec/circuit-types';
import { type AztecNode, PrivateExecutionResult } from '@aztec/circuit-types/interfaces/client';
import { CallContext } from '@aztec/circuits.js';
import {
  type FunctionArtifact,
  FunctionSelector,
  FunctionType,
  type NoteSelector,
  encodeArguments,
} from '@aztec/circuits.js/abi';
import { AztecAddress } from '@aztec/circuits.js/aztec-address';
import { Fr } from '@aztec/foundation/fields';
import { type Logger, createLogger } from '@aztec/foundation/log';

import { createSimulationError } from '../common/errors.js';
import { HashedValuesCache } from '../common/hashed_values_cache.js';
import { type SimulationProvider } from '../common/simulation_provider.js';
import { ClientExecutionContext } from './client_execution_context.js';
import { type DBOracle } from './db_oracle.js';
import { ExecutionNoteCache } from './execution_note_cache.js';
import { executePrivateFunction, verifyCurrentClassId } from './private_execution.js';
import { executeUnconstrainedFunction } from './unconstrained_execution.js';
import { ViewDataOracle } from './view_data_oracle.js';

/**
 * The ACIR simulator.
 */
export class AcirSimulator {
  private log: Logger;

  constructor(private db: DBOracle, private node: AztecNode, private simulationProvider: SimulationProvider) {
    this.log = createLogger('simulator');
  }

  /**
   * Runs a private function.
   * @param request - The transaction request.
   * @param entryPointArtifact - The artifact of the entry point function.
   * @param contractAddress - The address of the contract (should match request.origin)
   * @param msgSender - The address calling the function. This can be replaced to simulate a call from another contract or a specific account.
   * @param scopes - The accounts whose notes we can access in this call. Currently optional and will default to all.
   * @returns The result of the execution.
   */
  public async run(
    request: TxExecutionRequest,
    contractAddress: AztecAddress,
    selector: FunctionSelector,
    msgSender = AztecAddress.fromField(Fr.MAX_FIELD_VALUE),
    scopes?: AztecAddress[],
  ): Promise<PrivateExecutionResult> {
    const header = await this.db.getBlockHeader();

    await verifyCurrentClassId(
      contractAddress,
      await this.db.getContractInstance(contractAddress),
      this.node,
      header.globalVariables.blockNumber.toNumber(),
    );
    const entryPointArtifact = await this.db.getFunctionArtifact(contractAddress, selector);

    if (entryPointArtifact.functionType !== FunctionType.PRIVATE) {
      throw new Error(`Cannot run ${entryPointArtifact.functionType} function as private`);
    }

    if (request.origin !== contractAddress) {
      this.log.warn(
        `Request origin does not match contract address in simulation. Request origin: ${request.origin}, contract address: ${contractAddress}`,
      );
    }

    // reserve the first side effect for the tx hash (inserted by the private kernel)
    const startSideEffectCounter = 1;

    const callContext = new CallContext(
      msgSender,
      contractAddress,
      await FunctionSelector.fromNameAndParameters(entryPointArtifact.name, entryPointArtifact.parameters),
      entryPointArtifact.isStatic,
    );

    const txRequestHash = await request.toTxRequest().hash();
    const noteCache = new ExecutionNoteCache(txRequestHash);

    const context = new ClientExecutionContext(
      request.firstCallArgsHash,
      request.txContext,
      callContext,
      header,
      request.authWitnesses,
      request.capsules,
      HashedValuesCache.create(request.argsOfCalls),
      noteCache,
      this.db,
      this.node,
      this.simulationProvider,
      startSideEffectCounter,
      undefined,
      scopes,
    );

    try {
      const executionResult = await executePrivateFunction(
        this.simulationProvider,
        context,
        entryPointArtifact,
        contractAddress,
        request.functionSelector,
      );
      const { usedTxRequestHashForNonces } = noteCache.finish();
      const firstNullifierHint = usedTxRequestHashForNonces ? Fr.ZERO : noteCache.getAllNullifiers()[0];
      return new PrivateExecutionResult(executionResult, firstNullifierHint);
    } catch (err) {
      throw createSimulationError(err instanceof Error ? err : new Error('Unknown error during private execution'));
    }
  }

  /**
   * Runs an unconstrained function.
   * @param request - The transaction request.
   * @param entryPointArtifact - The artifact of the entry point function.
   * @param contractAddress - The address of the contract.
   * @param scopes - The accounts whose notes we can access in this call. Currently optional and will default to all.
   */
  public async runUnconstrained(
    request: FunctionCall,
    contractAddress: AztecAddress,
    selector: FunctionSelector,
    scopes?: AztecAddress[],
  ) {
    await verifyCurrentClassId(
      contractAddress,
      await this.db.getContractInstance(contractAddress),
      this.node,
      await this.node.getBlockNumber(),
    );
    const entryPointArtifact = await this.db.getFunctionArtifact(contractAddress, selector);

    if (entryPointArtifact.functionType !== FunctionType.UNCONSTRAINED) {
      throw new Error(`Cannot run ${entryPointArtifact.functionType} function as unconstrained`);
    }

    const context = new ViewDataOracle(contractAddress, [], [], this.db, this.node, undefined, scopes);

    try {
      return await executeUnconstrainedFunction(
        this.simulationProvider,
        context,
        entryPointArtifact,
        contractAddress,
        request.selector,
        request.args,
      );
    } catch (err) {
      throw createSimulationError(err instanceof Error ? err : new Error('Unknown error during private execution'));
    }
  }

  /**
   * Computes the note hash and inner nullifier of a note.
   * @param contractAddress - The address of the contract.
   * @param nonce - The nonce of the note hash, is not used when calculating the base note hash.
   * @param storageSlot - The storage slot.
   * @param noteTypeId - The note type identifier.
   * @param note - The note.
   * @returns The note hash (and intermediary forms) and inner nullifier.
   */
  public async computeNoteHashAndNullifier(
    contractAddress: AztecAddress,
    nonce: Fr,
    storageSlot: Fr,
    noteTypeId: NoteSelector,
    note: Note,
  ) {
    const artifact: FunctionArtifact | undefined = await this.db.getFunctionArtifactByName(
      contractAddress,
      'compute_note_hash_and_optionally_a_nullifier',
    );
    if (!artifact) {
      throw new Error(
        `Mandatory implementation of "compute_note_hash_and_optionally_a_nullifier" missing in noir contract ${contractAddress.toString()}.`,
      );
    }

    if (artifact.parameters.length != 6) {
      throw new Error(
        `Expected 6 parameters in mandatory implementation of "compute_note_hash_and_optionally_a_nullifier", but found ${
          artifact.parameters.length
        } in noir contract ${contractAddress.toString()}.`,
      );
    }

    // This constant is not exposed anywhere (because it doesn't have to - it's internal to aztec-nr). It's only here as
    // a temporary stopgap until we delete this function fully.
    const MAX_NOTE_PACKED_LEN = 16;
    const maxNoteFields = MAX_NOTE_PACKED_LEN;

    if (maxNoteFields < note.items.length) {
      throw new Error(
        `The note being processed has ${note.items.length} fields, while "compute_note_hash_and_optionally_a_nullifier" can only handle a maximum of ${maxNoteFields} fields. Please reduce the number of fields in your note.`,
      );
    }

    const noteItemsBoundedVec = {
      len: note.items.length,
      storage: note.items.concat(Array(maxNoteFields - note.items.length).fill(Fr.ZERO)),
    };
    const selector = await FunctionSelector.fromNameAndParameters(artifact);
    const execRequest: FunctionCall = {
      name: artifact.name,
      to: contractAddress,
      selector,
      type: FunctionType.UNCONSTRAINED,
      isStatic: artifact.isStatic,
      args: encodeArguments(artifact, [contractAddress, nonce, storageSlot, noteTypeId, true, noteItemsBoundedVec]),
      returnTypes: artifact.returnTypes,
    };

    const [noteHash, uniqueNoteHash, siloedNoteHash, innerNullifier] = (await this.runUnconstrained(
      execRequest,
      contractAddress,
      selector,
      // We can omit scopes here, because "compute_note_hash_and_optionally_a_nullifier" does not need access to any notes.
    )) as bigint[];

    return {
      noteHash: new Fr(noteHash),
      uniqueNoteHash: new Fr(uniqueNoteHash),
      siloedNoteHash: new Fr(siloedNoteHash),
      innerNullifier: new Fr(innerNullifier),
    };
  }
}
