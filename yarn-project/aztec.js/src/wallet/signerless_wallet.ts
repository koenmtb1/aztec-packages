import type { Fr } from '@aztec/foundation/fields';
import { AuthWitness } from '@aztec/stdlib/auth-witness';
import type { CompleteAddress } from '@aztec/stdlib/contract';
import type { PXE } from '@aztec/stdlib/interfaces/client';
import type { TxExecutionRequest } from '@aztec/stdlib/tx';

import { DefaultEntrypoint } from '../entrypoint/default_entrypoint.js';
import type { EntrypointInterface, ExecutionRequestInit } from '../entrypoint/entrypoint.js';
import type { IntentAction, IntentInnerHash } from '../utils/authwit.js';
import { BaseWallet } from './base_wallet.js';

/**
 * Wallet implementation which creates a transaction request directly to the requested contract without any signing.
 */
export class SignerlessWallet extends BaseWallet {
  constructor(pxe: PXE, private entrypoint?: EntrypointInterface) {
    super(pxe);
  }
  async createTxExecutionRequest(execution: ExecutionRequestInit): Promise<TxExecutionRequest> {
    let entrypoint = this.entrypoint;
    if (!entrypoint) {
      const { l1ChainId: chainId, protocolVersion } = await this.pxe.getNodeInfo();
      entrypoint = new DefaultEntrypoint(chainId, protocolVersion);
    }

    return entrypoint.createTxExecutionRequest(execution);
  }

  getChainId(): Fr {
    throw new Error('SignerlessWallet: Method getChainId not implemented.');
  }

  getVersion(): Fr {
    throw new Error('SignerlessWallet: Method getVersion not implemented.');
  }

  getPublicKeysHash(): Fr {
    throw new Error('SignerlessWallet: Method getPublicKeysHash not implemented.');
  }

  getCompleteAddress(): CompleteAddress {
    throw new Error('SignerlessWallet: Method getCompleteAddress not implemented.');
  }

  createAuthWit(_intent: Fr | Buffer | IntentInnerHash | IntentAction): Promise<AuthWitness> {
    throw new Error('SignerlessWallet: Method createAuthWit not implemented.');
  }

  override isL1ToL2MessageSynced(l1ToL2Message: Fr): Promise<boolean> {
    return this.pxe.isL1ToL2MessageSynced(l1ToL2Message);
  }
}
