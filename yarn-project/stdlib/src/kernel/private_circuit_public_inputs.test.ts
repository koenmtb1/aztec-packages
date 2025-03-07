import { PRIVATE_CIRCUIT_PUBLIC_INPUTS_LENGTH } from '@aztec/constants';
import { randomInt } from '@aztec/foundation/crypto';
import { setupCustomSnapshotSerializers } from '@aztec/foundation/testing';

import { makePrivateCircuitPublicInputs } from '../tests/factories.js';
import { PrivateCircuitPublicInputs } from './private_circuit_public_inputs.js';

describe('PrivateCircuitPublicInputs', () => {
  let inputs: PrivateCircuitPublicInputs;

  beforeAll(() => {
    setupCustomSnapshotSerializers(expect);
    inputs = makePrivateCircuitPublicInputs(randomInt(1000));
  });

  it('serializes to buffer and back', () => {
    const buffer = inputs.toBuffer();
    const result = PrivateCircuitPublicInputs.fromBuffer(buffer);
    expect(result).toEqual(inputs);
  });

  it('serializes to fields and back', () => {
    const fields = inputs.toFields();
    const result = PrivateCircuitPublicInputs.fromFields(fields);
    expect(result).toEqual(inputs);
  });

  it(`initializes an empty PrivateCircuitPublicInputs`, () => {
    const target = PrivateCircuitPublicInputs.empty();
    expect(target.isEmpty()).toBe(true);
  });

  it('number of fields matches constant', () => {
    const fields = inputs.toFields();
    expect(fields.length).toBe(PRIVATE_CIRCUIT_PUBLIC_INPUTS_LENGTH);
  });
});
