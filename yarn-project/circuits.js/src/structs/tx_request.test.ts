import { TX_REQUEST_LENGTH } from '@aztec/constants';
import { randomInt } from '@aztec/foundation/crypto';
import { Fr } from '@aztec/foundation/fields';
import { setupCustomSnapshotSerializers } from '@aztec/foundation/testing';
import { updateInlineTestData } from '@aztec/foundation/testing/files';

import { FunctionSelector } from '../abi/index.js';
import { AztecAddress } from '../aztec-address/index.js';
import { makeTxRequest } from '../tests/factories.js';
import { FunctionData } from './function_data.js';
import { Gas } from './gas.js';
import { GasFees } from './gas_fees.js';
import { GasSettings } from './gas_settings.js';
import { TxContext } from './tx_context.js';
import { TxRequest } from './tx_request.js';

describe('TxRequest', () => {
  let request: TxRequest;

  beforeAll(() => {
    setupCustomSnapshotSerializers(expect);
    request = makeTxRequest(randomInt(1000));
  });

  it(`serializes to buffer and deserializes it back`, () => {
    const buffer = request.toBuffer();
    const res = TxRequest.fromBuffer(buffer);
    expect(res).toEqual(request);
    expect(res.isEmpty()).toBe(false);
  });

  it('number of fields matches constant', () => {
    const fields = request.toFields();
    expect(fields.length).toBe(TX_REQUEST_LENGTH);
  });

  it('compute hash', async () => {
    const gasSettings = new GasSettings(new Gas(2, 2), new Gas(1, 1), new GasFees(4, 4), new GasFees(3, 3));
    const txRequest = TxRequest.from({
      origin: AztecAddress.fromBigInt(1n),
      functionData: new FunctionData(FunctionSelector.fromField(new Fr(2n)), /*isPrivate=*/ true),
      argsHash: new Fr(3),
      txContext: new TxContext(Fr.ZERO, Fr.ZERO, gasSettings),
    });

    const hash = await txRequest.hash();

    expect(hash.toString()).toMatchSnapshot();

    // Run with AZTEC_GENERATE_TEST_DATA=1 to update noir test data
    updateInlineTestData(
      'noir-projects/noir-protocol-circuits/crates/types/src/transaction/tx_request.nr',
      'test_data_tx_request_hash',
      hash.toString(),
    );
  });
});
