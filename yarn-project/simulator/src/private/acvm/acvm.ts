import { createLogger } from '@aztec/foundation/log';
import {
  type ExecutionError,
  type ForeignCallInput,
  type ForeignCallOutput,
  executeCircuitWithReturnWitness,
} from '@aztec/noir-acvm_js';
import type { FunctionDebugMetadata } from '@aztec/stdlib/abi';
import type { NoirCallStack } from '@aztec/stdlib/errors';

import { resolveOpcodeLocations, traverseCauseChain } from '../../common/errors.js';
import type { ACVMWitness } from './acvm_types.js';
import type { ORACLE_NAMES } from './oracle/index.js';

/**
 * The callback interface for the ACIR.
 */
export type ACIRCallback = Record<ORACLE_NAMES, (...args: ForeignCallInput[]) => Promise<ForeignCallOutput[]>>;

/**
 * The result of executing an ACIR.
 */
export interface ACIRExecutionResult {
  /**
   * An execution result contains two witnesses.
   * 1. The partial witness of the execution.
   * 2. The return witness which contains the given public return values within the full witness.
   */
  partialWitness: ACVMWitness;
  returnWitness: ACVMWitness;
}

/**
 * The function call that executes an ACIR.
 */
export async function acvm(
  acir: Buffer,
  initialWitness: ACVMWitness,
  callback: ACIRCallback,
): Promise<ACIRExecutionResult> {
  const logger = createLogger('simulator:acvm');

  const solvedAndReturnWitness = await executeCircuitWithReturnWitness(
    acir,
    initialWitness,
    (name: string, args: ForeignCallInput[]) => {
      try {
        logger.debug(`Oracle callback ${name}`);
        const oracleFunction = callback[name as ORACLE_NAMES];
        if (!oracleFunction) {
          throw new Error(`Oracle callback ${name} not found`);
        }

        return oracleFunction.call(callback, ...args);
      } catch (err) {
        let typedError: Error;
        if (err instanceof Error) {
          typedError = err;
        } else {
          typedError = new Error(`Error in oracle callback ${err}`);
        }
        logger.error(`Error in oracle callback ${name}: ${typedError.message}`);
        throw typedError;
      }
    },
  ).catch((err: Error) => {
    // Wasm callbacks act as a boundary for stack traces, so we capture it here and complete the error if it happens.
    const stack = new Error().stack;

    traverseCauseChain(err, cause => {
      if (cause.stack) {
        cause.stack += stack;
      }
    });

    throw err;
  });

  return { partialWitness: solvedAndReturnWitness.solvedWitness, returnWitness: solvedAndReturnWitness.returnWitness };
}

/**
 * Extracts the call stack from an thrown by the acvm.
 * @param error - The error to extract from.
 * @param debug - The debug metadata of the function called.
 * @returns The call stack, if available.
 */
export function extractCallStack(
  error: Error | ExecutionError,
  debug?: FunctionDebugMetadata,
): NoirCallStack | undefined {
  if (!('callStack' in error) || !error.callStack) {
    return undefined;
  }
  const { callStack, brilligFunctionId } = error;
  if (!debug) {
    return callStack;
  }

  try {
    return resolveOpcodeLocations(callStack, debug, brilligFunctionId);
  } catch (err) {
    return callStack;
  }
}
