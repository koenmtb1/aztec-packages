import { ClientIvcProof, Fr, type GasSettings, PrivateLog } from '@aztec/circuits.js';
import { PrivateKernelTailCircuitPublicInputs, type PrivateToPublicAccumulatedData } from '@aztec/circuits.js/kernel';
import { Buffer32 } from '@aztec/foundation/buffer';
import { arraySerializedSizeOfNonEmpty } from '@aztec/foundation/collection';
import { BufferReader, serializeArrayOfBufferableToVector, serializeToBuffer } from '@aztec/foundation/serialize';
import { type FieldsOf } from '@aztec/foundation/types';

import { z } from 'zod';

import { type GetPublicLogsResponse } from '../logs/get_logs_response.js';
import { type L2LogsSource } from '../logs/l2_logs_source.js';
import { ContractClassTxL2Logs } from '../logs/tx_l2_logs.js';
import { Gossipable } from '../p2p/gossipable.js';
import { TopicType, createTopicString } from '../p2p/topic_type.js';
import { PublicExecutionRequest } from '../public_execution_request.js';
import { type TxStats } from '../stats/stats.js';
import { TxHash } from './tx_hash.js';

/**
 * The interface of an L2 transaction.
 */
export class Tx extends Gossipable {
  static override p2pTopic: string;
  // For memoization
  private txHash: TxHash | undefined;

  constructor(
    /**
     * Output of the private kernel circuit for this tx.
     */
    public readonly data: PrivateKernelTailCircuitPublicInputs,
    /**
     * Proof from the private kernel circuit.
     * TODO(#7368): This client IVC object currently contains various VKs that will eventually be more like static data.
     *
     */
    public readonly clientIvcProof: ClientIvcProof,
    /**
     * Contract class logs generated by the tx.
     */
    public contractClassLogs: ContractClassTxL2Logs,
    /**
     * Enqueued public functions from the private circuit to be run by the sequencer.
     */
    public readonly enqueuedPublicFunctionCalls: PublicExecutionRequest[],
    /**
     * Public function call to be run by the sequencer as part of teardown.
     */
    public readonly publicTeardownFunctionCall: PublicExecutionRequest,
  ) {
    super();
  }

  // Gossipable method
  static {
    this.p2pTopic = createTopicString(TopicType.tx);
  }

  // Gossipable method
  override async p2pMessageIdentifier(): Promise<Buffer32> {
    return new Buffer32((await this.getTxHash()).toBuffer());
  }

  hasPublicCalls() {
    return this.data.numberOfPublicCallRequests() > 0;
  }

  getNonRevertiblePublicExecutionRequests(): PublicExecutionRequest[] {
    const numRevertible = this.data.numberOfRevertiblePublicCallRequests();
    return this.enqueuedPublicFunctionCalls.slice(numRevertible);
  }

  getRevertiblePublicExecutionRequests(): PublicExecutionRequest[] {
    const numRevertible = this.data.numberOfRevertiblePublicCallRequests();
    return this.enqueuedPublicFunctionCalls.slice(0, numRevertible);
  }

  getPublicTeardownExecutionRequest(): PublicExecutionRequest | undefined {
    return this.publicTeardownFunctionCall.isEmpty() ? undefined : this.publicTeardownFunctionCall;
  }

  getGasSettings(): GasSettings {
    return this.data.constants.txContext.gasSettings;
  }

  /**
   * Deserializes the Tx object from a Buffer.
   * @param buffer - Buffer or BufferReader object to deserialize.
   * @returns An instance of Tx.
   */
  static fromBuffer(buffer: Buffer | BufferReader): Tx {
    const reader = BufferReader.asReader(buffer);
    return new Tx(
      reader.readObject(PrivateKernelTailCircuitPublicInputs),
      reader.readObject(ClientIvcProof),
      reader.readObject(ContractClassTxL2Logs),
      reader.readVectorUint8Prefix(PublicExecutionRequest),
      reader.readObject(PublicExecutionRequest),
    );
  }

  static newWithTxData(
    data: PrivateKernelTailCircuitPublicInputs,
    publicTeardownExecutionRequest?: PublicExecutionRequest,
  ) {
    return new Tx(
      data,
      ClientIvcProof.empty(),
      ContractClassTxL2Logs.empty(),
      [],
      publicTeardownExecutionRequest ? publicTeardownExecutionRequest : PublicExecutionRequest.empty(),
    );
  }

  /**
   * Serializes the Tx object into a Buffer.
   * @returns Buffer representation of the Tx object.
   */
  toBuffer() {
    return serializeToBuffer([
      this.data,
      this.clientIvcProof,
      this.contractClassLogs,
      serializeArrayOfBufferableToVector(this.enqueuedPublicFunctionCalls, 1),
      this.publicTeardownFunctionCall,
    ]);
  }

  static get schema() {
    return z
      .object({
        data: PrivateKernelTailCircuitPublicInputs.schema,
        clientIvcProof: ClientIvcProof.schema,
        contractClassLogs: ContractClassTxL2Logs.schema,
        enqueuedPublicFunctionCalls: z.array(PublicExecutionRequest.schema),
        publicTeardownFunctionCall: PublicExecutionRequest.schema,
      })
      .transform(Tx.from);
  }

  static from(fields: FieldsOf<Tx>) {
    return new Tx(
      fields.data,
      fields.clientIvcProof,
      fields.contractClassLogs,
      fields.enqueuedPublicFunctionCalls,
      fields.publicTeardownFunctionCall,
    );
  }

  /**
   * Gets public logs emitted by this tx.
   * @param logsSource - An instance of `L2LogsSource` which can be used to obtain the logs.
   * @returns The requested logs.
   */
  public async getPublicLogs(logsSource: L2LogsSource): Promise<GetPublicLogsResponse> {
    return logsSource.getPublicLogs({ txHash: await this.getTxHash() });
  }

  /**
   * Computes (if necessary) & return transaction hash.
   * @returns The hash of the public inputs of the private kernel tail circuit.
   */
  async getTxHash(forceRecompute = false): Promise<TxHash> {
    if (!this.txHash || forceRecompute) {
      const hash = this.data.forPublic
        ? await this.data.toPrivateToPublicKernelCircuitPublicInputs().hash()
        : await this.data.toPrivateToRollupKernelCircuitPublicInputs().hash();
      this.txHash = new TxHash(hash);
    }
    return this.txHash!;
  }

  /**
   * Allows setting the hash of the Tx.
   * Use this when you want to skip computing it from the original data.
   * Don't set a Tx hash received from an untrusted source.
   * @param hash - The hash to set.
   */
  setTxHash(hash: TxHash) {
    this.txHash = hash;
  }

  /** Returns stats about this tx. */
  async getStats(): Promise<TxStats> {
    return {
      txHash: (await this.getTxHash()).toString(),

      noteHashCount: this.data.getNonEmptyNoteHashes().length,
      nullifierCount: this.data.getNonEmptyNullifiers().length,
      privateLogCount: this.data.getNonEmptyPrivateLogs().length,

      proofSize: this.clientIvcProof.clientIvcProofBuffer.length,
      size: this.toBuffer().length,

      feePaymentMethod:
        // needsSetup? then we pay through a fee payment contract
        this.data.forPublic?.needsSetup
          ? // if the first call is to `approve_public_authwit`, then it's a public payment
            this.data.getNonRevertiblePublicCallRequests().at(-1)!.functionSelector.toField().toBigInt() === 0x43417bb1n
            ? 'fpc_public'
            : 'fpc_private'
          : 'fee_juice',
      classRegisteredCount: this.contractClassLogs.unrollLogs().length,
      contractClassLogSize: this.contractClassLogs.getSerializedLength(),
    };
  }

  getSize() {
    return (
      this.data.getSize() +
      this.clientIvcProof.clientIvcProofBuffer.length +
      this.contractClassLogs.getSerializedLength() +
      arraySerializedSizeOfNonEmpty(this.enqueuedPublicFunctionCalls) +
      arraySerializedSizeOfNonEmpty([this.publicTeardownFunctionCall])
    );
  }

  /**
   * Estimates the tx size based on its private effects. Note that the actual size of the tx
   * after processing will probably be larger, as public execution would generate more data.
   */
  getEstimatedPrivateTxEffectsSize() {
    return (
      this.contractClassLogs.getSerializedLength() +
      this.data.getNonEmptyNoteHashes().length * Fr.SIZE_IN_BYTES +
      this.data.getNonEmptyNullifiers().length * Fr.SIZE_IN_BYTES +
      this.data.getNonEmptyPrivateLogs().length * PrivateLog.SIZE_IN_BYTES
    );
  }

  /**
   * Convenience function to get a hash out of a tx or a tx-like.
   * @param tx - Tx-like object.
   * @returns - The hash.
   */
  static async getHash(tx: Tx | HasHash): Promise<TxHash> {
    return hasHash(tx) ? tx.hash : await tx.getTxHash();
  }

  /**
   * Convenience function to get array of hashes for an array of txs.
   * @param txs - The txs to get the hashes from.
   * @returns The corresponding array of hashes.
   */
  static async getHashes(txs: (Tx | HasHash)[]): Promise<TxHash[]> {
    return await Promise.all(txs.map(Tx.getHash));
  }

  /**
   * Clones a tx, making a deep copy of all fields.
   * @param tx - The transaction to be cloned.
   * @returns The cloned transaction.
   */
  static clone(tx: Tx): Tx {
    const publicInputs = PrivateKernelTailCircuitPublicInputs.fromBuffer(tx.data.toBuffer());
    const clientIvcProof = ClientIvcProof.fromBuffer(tx.clientIvcProof.toBuffer());
    const contractClassLogs = ContractClassTxL2Logs.fromBuffer(tx.contractClassLogs.toBuffer());
    const enqueuedPublicFunctionCalls = tx.enqueuedPublicFunctionCalls.map(x =>
      PublicExecutionRequest.fromBuffer(x.toBuffer()),
    );
    const publicTeardownFunctionCall = PublicExecutionRequest.fromBuffer(tx.publicTeardownFunctionCall.toBuffer());
    const clonedTx = new Tx(
      publicInputs,
      clientIvcProof,
      contractClassLogs,
      enqueuedPublicFunctionCalls,
      publicTeardownFunctionCall,
    );
    if (tx.txHash) {
      clonedTx.setTxHash(TxHash.fromBuffer(tx.txHash.toBuffer()));
    }

    return clonedTx;
  }

  static async random() {
    return new Tx(
      PrivateKernelTailCircuitPublicInputs.emptyWithNullifier(),
      ClientIvcProof.empty(),
      await ContractClassTxL2Logs.random(1, 1),
      [await PublicExecutionRequest.random()],
      await PublicExecutionRequest.random(),
    );
  }

  /**
   * Filters out logs from functions that are not present in the provided kernel output.
   *
   * The purpose of this is to remove logs that got dropped due to a revert,
   * in which case, we only have the kernel's hashes to go on, as opposed to
   * this grouping by function maintained in this class.
   *
   * The logic therefore is to drop all FunctionLogs if any constituent hash
   * does not appear in the provided hashes: it is impossible for part of a
   * function to revert.
   *
   * @param logHashes the individual log hashes we want to keep
   * @param out the output to put passing logs in, to keep this function abstract
   */
  public filterRevertedLogs(privateNonRevertible: PrivateToPublicAccumulatedData) {
    this.contractClassLogs = this.contractClassLogs.filterScoped(
      privateNonRevertible.contractClassLogsHashes,
      ContractClassTxL2Logs.empty(),
    );
  }
}

/** Utility type for an entity that has a hash property for a txhash */
type HasHash = { /** The tx hash */ hash: TxHash };

function hasHash(tx: Tx | HasHash): tx is HasHash {
  return (tx as HasHash).hash !== undefined;
}
