import { AVM_VERIFICATION_KEY_LENGTH_IN_FIELDS } from '@aztec/constants';
import { Fr } from '@aztec/foundation/fields';
import { hashVK } from '@aztec/stdlib/hash';
import { VerificationKeyAsFields, VerificationKeyData } from '@aztec/stdlib/vks';

import { strict as assert } from 'assert';
import { promises as fs } from 'fs';
import * as path from 'path';

import { VK_FIELDS_FILENAME, VK_FILENAME } from '../bb/execute.js';

/**
 * Reads the verification key data stored at the specified location and parses into a VerificationKeyData
 * @param vkDirectoryPath - The directory containing the verification key data files
 * @returns The verification key data
 */
export async function extractVkData(vkDirectoryPath: string): Promise<VerificationKeyData> {
  const [rawFields, rawBinary] = await Promise.all([
    fs.readFile(path.join(vkDirectoryPath, VK_FIELDS_FILENAME), { encoding: 'utf-8' }),
    fs.readFile(path.join(vkDirectoryPath, VK_FILENAME)),
  ]);
  const fieldsJson = JSON.parse(rawFields);
  const fields = fieldsJson.map(Fr.fromHexString);
  // The hash is not included in the BB response
  const vkHash = await hashVK(fields);
  const vkAsFields = new VerificationKeyAsFields(fields, vkHash);
  return new VerificationKeyData(vkAsFields, rawBinary);
}

// TODO: This was adapted from the above function. A refactor might be needed.
export async function extractAvmVkData(vkDirectoryPath: string): Promise<VerificationKeyData> {
  const [rawFields, rawBinary] = await Promise.all([
    fs.readFile(path.join(vkDirectoryPath, VK_FIELDS_FILENAME), { encoding: 'utf-8' }),
    fs.readFile(path.join(vkDirectoryPath, VK_FILENAME)),
  ]);
  const fieldsJson = JSON.parse(rawFields);
  const fields = fieldsJson.map(Fr.fromHexString);
  // The first item is the hash, this is not part of the actual VK
  // TODO: is the above actually the case?
  const vkHash = fields[0];
  assert(fields.length === AVM_VERIFICATION_KEY_LENGTH_IN_FIELDS, 'Invalid AVM verification key length');
  const vkAsFields = new VerificationKeyAsFields(fields, vkHash);
  const vk = new VerificationKeyData(vkAsFields, rawBinary);
  return vk;
}
