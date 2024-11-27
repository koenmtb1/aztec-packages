export type EnvVar =
  | 'ACVM_BINARY_PATH'
  | 'ACVM_WORKING_DIRECTORY'
  | 'GOVERNANCE_CONTRACT_ADDRESS'
  | 'API_KEY'
  | 'API_PREFIX'
  | 'ARCHIVER_MAX_LOGS'
  | 'ARCHIVER_POLLING_INTERVAL_MS'
  | 'ARCHIVER_URL'
  | 'ARCHIVER_VIEM_POLLING_INTERVAL_MS'
  | 'ASSUME_PROVEN_THROUGH_BLOCK_NUMBER'
  | 'AZTEC_NODE_URL'
  | 'AZTEC_PORT'
  | 'BB_BINARY_PATH'
  | 'BB_SKIP_CLEANUP'
  | 'BB_WORKING_DIRECTORY'
  | 'BOOTSTRAP_NODES'
  | 'BOT_DA_GAS_LIMIT'
  | 'BOT_FEE_PAYMENT_METHOD'
  | 'BOT_FLUSH_SETUP_TRANSACTIONS'
  | 'BOT_FOLLOW_CHAIN'
  | 'BOT_L2_GAS_LIMIT'
  | 'BOT_MAX_PENDING_TXS'
  | 'BOT_NO_START'
  | 'BOT_NO_WAIT_FOR_TRANSFERS'
  | 'BOT_PRIVATE_KEY'
  | 'BOT_PRIVATE_TRANSFERS_PER_TX'
  | 'BOT_PUBLIC_TRANSFERS_PER_TX'
  | 'BOT_PXE_URL'
  | 'BOT_RECIPIENT_ENCRYPTION_SECRET'
  | 'BOT_SKIP_PUBLIC_SIMULATION'
  | 'BOT_TOKEN_CONTRACT'
  | 'BOT_TOKEN_SALT'
  | 'BOT_TX_INTERVAL_SECONDS'
  | 'BOT_TX_MINED_WAIT_SECONDS'
  | 'BOT_MAX_CONSECUTIVE_ERRORS'
  | 'BOT_STOP_WHEN_UNHEALTHY'
  | 'COINBASE'
  | 'DATA_DIRECTORY'
  | 'DATA_STORE_MAP_SIZE_KB'
  | 'DEBUG'
  | 'DEPLOY_AZTEC_CONTRACTS_SALT'
  | 'DEPLOY_AZTEC_CONTRACTS'
  | 'ENABLE_GAS'
  | 'ENFORCE_FEES'
  | 'ETHEREUM_HOST'
  | 'FEE_JUICE_CONTRACT_ADDRESS'
  | 'FEE_JUICE_PORTAL_CONTRACT_ADDRESS'
  | 'FEE_RECIPIENT'
  | 'GOVERNANCE_PROPOSER_CONTRACT_ADDRESS'
  | 'GOVERNANCE_PROPOSER_PAYLOAD_ADDRESS'
  | 'INBOX_CONTRACT_ADDRESS'
  | 'L1_CHAIN_ID'
  | 'L1_PRIVATE_KEY'
  | 'L2_QUEUE_SIZE'
  | 'LOG_ELAPSED_TIME'
  | 'LOG_JSON'
  | 'LOG_LEVEL'
  | 'MNEMONIC'
  | 'NETWORK_NAME'
  | 'NETWORK'
  | 'COIN_ISSUER_CONTRACT_ADDRESS'
  | 'OTEL_EXPORTER_OTLP_METRICS_ENDPOINT'
  | 'OTEL_EXPORTER_OTLP_TRACES_ENDPOINT'
  | 'OTEL_EXPORTER_OTLP_LOGS_ENDPOINT'
  | 'OTEL_SERVICE_NAME'
  | 'OTEL_COLLECT_INTERVAL_MS'
  | 'OTEL_EXPORT_TIMEOUT_MS'
  | 'OUTBOX_CONTRACT_ADDRESS'
  | 'P2P_BLOCK_CHECK_INTERVAL_MS'
  | 'P2P_BLOCK_REQUEST_BATCH_SIZE'
  | 'P2P_ENABLED'
  | 'P2P_GOSSIPSUB_D'
  | 'P2P_GOSSIPSUB_DHI'
  | 'P2P_GOSSIPSUB_DLO'
  | 'P2P_GOSSIPSUB_INTERVAL_MS'
  | 'P2P_GOSSIPSUB_MCACHE_GOSSIP'
  | 'P2P_GOSSIPSUB_MCACHE_LENGTH'
  | 'P2P_GOSSIPSUB_TX_INVALID_MESSAGE_DELIVERIES_DECAY'
  | 'P2P_GOSSIPSUB_TX_INVALID_MESSAGE_DELIVERIES_WEIGHT'
  | 'P2P_GOSSIPSUB_TX_TOPIC_WEIGHT'
  | 'P2P_L2_QUEUE_SIZE'
  | 'P2P_MAX_PEERS'
  | 'P2P_MIN_PEERS'
  | 'P2P_PEER_CHECK_INTERVAL_MS'
  | 'P2P_PEER_PENALTY_VALUES'
  | 'P2P_QUERY_FOR_IP'
  | 'P2P_REQRESP_INDIVIDUAL_REQUEST_TIMEOUT_MS'
  | 'P2P_REQRESP_OVERALL_REQUEST_TIMEOUT_MS'
  | 'P2P_SEVERE_PEER_PENALTY_BLOCK_LENGTH'
  | 'P2P_TCP_LISTEN_ADDR'
  | 'P2P_TCP_ANNOUNCE_ADDR'
  | 'P2P_TX_POOL_KEEP_PROVEN_FOR'
  | 'P2P_TX_PROTOCOL'
  | 'P2P_UDP_ANNOUNCE_ADDR'
  | 'P2P_UDP_LISTEN_ADDR'
  | 'PEER_ID_PRIVATE_KEY'
  | 'PROOF_VERIFIER_L1_START_BLOCK'
  | 'PROOF_VERIFIER_POLL_INTERVAL_MS'
  | 'PROVER_AGENT_CONCURRENCY'
  | 'PROVER_AGENT_ENABLED'
  | 'PROVER_AGENT_POLL_INTERVAL_MS'
  | 'PROVER_COORDINATION_NODE_URL'
  | 'PROVER_DISABLED'
  | 'PROVER_ID'
  | 'PROVER_JOB_POLL_INTERVAL_MS'
  | 'PROVER_JOB_TIMEOUT_MS'
  | 'PROVER_JOB_SOURCE_URL'
  | 'PROVER_NODE_POLLING_INTERVAL_MS'
  | 'PROVER_NODE_MAX_PENDING_JOBS'
  | 'PROVER_PUBLISH_RETRY_INTERVAL_MS'
  | 'PROVER_PUBLISHER_PRIVATE_KEY'
  | 'PROVER_REAL_PROOFS'
  | 'PROVER_REQUIRED_CONFIRMATIONS'
  | 'PROVER_TEST_DELAY_MS'
  | 'PXE_BLOCK_POLLING_INTERVAL_MS'
  | 'PXE_L2_STARTING_BLOCK'
  | 'PXE_PROVER_ENABLED'
  | 'QUOTE_PROVIDER_BASIS_POINT_FEE'
  | 'QUOTE_PROVIDER_BOND_AMOUNT'
  | 'QUOTE_PROVIDER_URL'
  | 'PROVER_TARGET_ESCROW_AMOUNT'
  | 'PROVER_MINIMUM_ESCROW_AMOUNT'
  | 'REGISTRY_CONTRACT_ADDRESS'
  | 'ROLLUP_CONTRACT_ADDRESS'
  | 'SEQ_ALLOWED_SETUP_FN'
  | 'SEQ_ALLOWED_TEARDOWN_FN'
  | 'SEQ_MAX_BLOCK_SIZE_IN_BYTES'
  | 'SEQ_MAX_SECONDS_BETWEEN_BLOCKS'
  | 'SEQ_MAX_TX_PER_BLOCK'
  | 'SEQ_MIN_SECONDS_BETWEEN_BLOCKS'
  | 'SEQ_MIN_TX_PER_BLOCK'
  | 'SEQ_PUBLISH_RETRY_INTERVAL_MS'
  | 'SEQ_PUBLISHER_PRIVATE_KEY'
  | 'SEQ_REQUIRED_CONFIRMATIONS'
  | 'SEQ_TX_POLLING_INTERVAL_MS'
  | 'SEQ_ENFORCE_TIME_TABLE'
  | 'REWARD_DISTRIBUTOR_CONTRACT_ADDRESS'
  | 'TELEMETRY'
  | 'TEST_ACCOUNTS'
  | 'TX_GOSSIP_VERSION'
  | 'TXE_PORT'
  | 'VALIDATOR_ATTESTATIONS_POLLING_INTERVAL_MS'
  | 'VALIDATOR_ATTESTATIONS_WAIT_TIMEOUT_MS'
  | 'VALIDATOR_DISABLED'
  | 'VALIDATOR_PRIVATE_KEY'
  | 'VALIDATOR_REEXECUTE'
  | 'VERSION'
  | 'WS_BLOCK_CHECK_INTERVAL_MS'
  | 'WS_PROVEN_BLOCKS_ONLY'
  | 'WS_BLOCK_REQUEST_BATCH_SIZE'
  | 'VERIFIER_VIEM_POLLING_INTERVAL_MS'
  | 'L1_READER_VIEM_POLLING_INTERVAL_MS'
  | 'PROVER_VIEM_POLLING_INTERVAL_MS'
  | 'SEQ_VIEM_POLLING_INTERVAL_MS'
  | 'WS_DB_MAP_SIZE_KB'
  | 'WS_DATA_DIRECTORY'
  | 'WS_NUM_HISTORIC_BLOCKS'
  | 'ETHEREUM_SLOT_DURATION'
  | 'AZTEC_SLOT_DURATION'
  | 'AZTEC_EPOCH_DURATION'
  | 'AZTEC_TARGET_COMMITTEE_SIZE'
  | 'AZTEC_EPOCH_PROOF_CLAIM_WINDOW_IN_L2_SLOTS';
