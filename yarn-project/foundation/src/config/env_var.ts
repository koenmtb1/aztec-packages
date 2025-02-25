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
  | 'ARCHIVER_BATCH_SIZE'
  | 'ASSUME_PROVEN_THROUGH_BLOCK_NUMBER'
  | 'AZTEC_NODE_URL'
  | 'AZTEC_PORT'
  | 'BB_BINARY_PATH'
  | 'BB_SKIP_CLEANUP'
  | 'BB_WORKING_DIRECTORY'
  | 'BOOTSTRAP_NODES'
  | 'BLOB_SINK_PORT'
  | 'BLOB_SINK_URL'
  | 'BOT_DA_GAS_LIMIT'
  | 'BOT_FEE_PAYMENT_METHOD'
  | 'BOT_FLUSH_SETUP_TRANSACTIONS'
  | 'BOT_FOLLOW_CHAIN'
  | 'BOT_L2_GAS_LIMIT'
  | 'BOT_MAX_PENDING_TXS'
  | 'BOT_NO_START'
  | 'BOT_NO_WAIT_FOR_TRANSFERS'
  | 'BOT_L1_MNEMONIC'
  | 'BOT_L1_PRIVATE_KEY'
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
  | 'DEBUG_P2P_DISABLE_COLOCATION_PENALTY'
  | 'DEPLOY_AZTEC_CONTRACTS_SALT'
  | 'DEPLOY_AZTEC_CONTRACTS'
  | 'ETHEREUM_HOST'
  | 'FEE_JUICE_CONTRACT_ADDRESS'
  | 'FEE_JUICE_PORTAL_CONTRACT_ADDRESS'
  | 'FEE_RECIPIENT'
  | 'FORCE_COLOR'
  | 'GOVERNANCE_PROPOSER_CONTRACT_ADDRESS'
  | 'GOVERNANCE_PROPOSER_PAYLOAD_ADDRESS'
  | 'INBOX_CONTRACT_ADDRESS'
  | 'L1_CHAIN_ID'
  | 'L1_CONSENSUS_HOST_URL'
  | 'L1_CONSENSUS_HOST_API_KEY'
  | 'L1_CONSENSUS_HOST_API_KEY_HEADER'
  | 'L1_PRIVATE_KEY'
  | 'L2_QUEUE_SIZE'
  | 'LOG_ELAPSED_TIME'
  | 'LOG_JSON'
  | 'LOG_MULTILINE'
  | 'LOG_LEVEL'
  | 'MNEMONIC'
  | 'NETWORK_NAME'
  | 'NETWORK'
  | 'NO_PXE'
  | 'COIN_ISSUER_CONTRACT_ADDRESS'
  | 'USE_GCLOUD_LOGGING'
  | 'OTEL_EXPORTER_OTLP_METRICS_ENDPOINT'
  | 'OTEL_EXPORTER_OTLP_TRACES_ENDPOINT'
  | 'OTEL_EXPORTER_OTLP_LOGS_ENDPOINT'
  | 'OTEL_SERVICE_NAME'
  | 'OTEL_COLLECT_INTERVAL_MS'
  | 'OTEL_EXCLUDE_METRICS'
  | 'OTEL_EXPORT_TIMEOUT_MS'
  | 'OUTBOX_CONTRACT_ADDRESS'
  | 'P2P_BLOCK_CHECK_INTERVAL_MS'
  | 'P2P_BLOCK_REQUEST_BATCH_SIZE'
  | 'P2P_BOOTSTRAP_NODE_ENR_VERSION_CHECK'
  | 'P2P_ENABLED'
  | 'P2P_GOSSIPSUB_D'
  | 'P2P_GOSSIPSUB_DHI'
  | 'P2P_GOSSIPSUB_DLO'
  | 'P2P_GOSSIPSUB_DLAZY'
  | 'P2P_GOSSIPSUB_FLOOD_PUBLISH'
  | 'P2P_GOSSIPSUB_INTERVAL_MS'
  | 'P2P_GOSSIPSUB_MCACHE_GOSSIP'
  | 'P2P_GOSSIPSUB_MCACHE_LENGTH'
  | 'P2P_GOSSIPSUB_TX_INVALID_MESSAGE_DELIVERIES_DECAY'
  | 'P2P_GOSSIPSUB_TX_INVALID_MESSAGE_DELIVERIES_WEIGHT'
  | 'P2P_GOSSIPSUB_TX_TOPIC_WEIGHT'
  | 'P2P_L2_QUEUE_SIZE'
  | 'P2P_MAX_PEERS'
  | 'P2P_PEER_CHECK_INTERVAL_MS'
  | 'P2P_PEER_PENALTY_VALUES'
  | 'P2P_QUERY_FOR_IP'
  | 'P2P_REQRESP_INDIVIDUAL_REQUEST_TIMEOUT_MS'
  | 'P2P_REQRESP_OVERALL_REQUEST_TIMEOUT_MS'
  | 'P2P_SEVERE_PEER_PENALTY_BLOCK_LENGTH'
  | 'P2P_TCP_LISTEN_ADDR'
  | 'P2P_TCP_ANNOUNCE_ADDR'
  | 'P2P_TX_POOL_KEEP_PROVEN_FOR'
  | 'P2P_ATTESTATION_POOL_KEEP_FOR'
  | 'P2P_TX_PROTOCOL'
  | 'P2P_UDP_ANNOUNCE_ADDR'
  | 'P2P_UDP_LISTEN_ADDR'
  | 'P2P_ARCHIVED_TX_LIMIT'
  | 'PEER_ID_PRIVATE_KEY'
  | 'PROOF_VERIFIER_L1_START_BLOCK'
  | 'PROOF_VERIFIER_POLL_INTERVAL_MS'
  | 'PROVER_AGENT_ENABLED'
  | 'PROVER_AGENT_CONCURRENCY'
  | 'PROVER_AGENT_COUNT'
  | 'PROVER_AGENT_PROOF_TYPES'
  | 'PROVER_AGENT_POLL_INTERVAL_MS'
  | 'PROVER_BROKER_HOST'
  | 'PROVER_BROKER_ENABLED'
  | 'PROVER_BROKER_JOB_TIMEOUT_MS'
  | 'PROVER_BROKER_POLL_INTERVAL_MS'
  | 'PROVER_BROKER_JOB_MAX_RETRIES'
  | 'PROVER_BROKER_BATCH_INTERVAL_MS'
  | 'PROVER_BROKER_BATCH_SIZE'
  | 'PROVER_BROKER_MAX_EPOCHS_TO_KEEP_RESULTS_FOR'
  | 'PROVER_COORDINATION_NODE_URL'
  | 'PROVER_DISABLED'
  | 'PROVER_FAILED_PROOF_STORE'
  | 'PROVER_ID'
  | 'PROVER_JOB_POLL_INTERVAL_MS'
  | 'PROVER_JOB_TIMEOUT_MS'
  | 'PROVER_NODE_POLLING_INTERVAL_MS'
  | 'PROVER_NODE_MAX_PENDING_JOBS'
  | 'PROVER_NODE_MAX_PARALLEL_BLOCKS_PER_EPOCH'
  | 'PROVER_NODE_TX_GATHERING_TIMEOUT_MS'
  | 'PROVER_NODE_TX_GATHERING_INTERVAL_MS'
  | 'PROVER_NODE_TX_GATHERING_MAX_PARALLEL_REQUESTS'
  | 'PROVER_PUBLISH_RETRY_INTERVAL_MS'
  | 'PROVER_PUBLISHER_PRIVATE_KEY'
  | 'PROVER_REAL_PROOFS'
  | 'PROVER_REQUIRED_CONFIRMATIONS'
  | 'PROVER_TEST_DELAY_FACTOR'
  | 'PROVER_TEST_DELAY_MS'
  | 'PROVER_TEST_DELAY_TYPE'
  | 'PXE_L2_STARTING_BLOCK'
  | 'PXE_PROVER_ENABLED'
  | 'PROVER_TARGET_ESCROW_AMOUNT'
  | 'PROVER_MINIMUM_ESCROW_AMOUNT'
  | 'REGISTRY_CONTRACT_ADDRESS'
  | 'ROLLUP_CONTRACT_ADDRESS'
  | 'SEQ_ALLOWED_SETUP_FN'
  | 'SEQ_MAX_BLOCK_SIZE_IN_BYTES'
  | 'SEQ_MAX_TX_PER_BLOCK'
  | 'SEQ_MIN_TX_PER_BLOCK'
  | 'SEQ_MAX_DA_BLOCK_GAS'
  | 'SEQ_MAX_L2_BLOCK_GAS'
  | 'SEQ_PUBLISH_RETRY_INTERVAL_MS'
  | 'SEQ_PUBLISHER_PRIVATE_KEY'
  | 'SEQ_REQUIRED_CONFIRMATIONS'
  | 'SEQ_TX_POLLING_INTERVAL_MS'
  | 'SEQ_ENFORCE_TIME_TABLE'
  | 'SEQ_MAX_L1_TX_INCLUSION_TIME_INTO_SLOT'
  | 'SLASH_FACTORY_CONTRACT_ADDRESS'
  | 'STAKING_ASSET_CONTRACT_ADDRESS'
  | 'REWARD_DISTRIBUTOR_CONTRACT_ADDRESS'
  | 'TELEMETRY'
  | 'TEST_ACCOUNTS'
  | 'TX_GOSSIP_VERSION'
  | 'TXE_PORT'
  | 'VALIDATOR_ATTESTATIONS_POLLING_INTERVAL_MS'
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
  | 'AZTEC_PROOF_SUBMISSION_WINDOW'
  | 'AZTEC_MINIMUM_STAKE'
  | 'AZTEC_SLASHING_QUORUM'
  | 'AZTEC_SLASHING_ROUND_SIZE'
  | 'AZTEC_GOVERNANCE_PROPOSER_QUORUM'
  | 'AZTEC_GOVERNANCE_PROPOSER_ROUND_SIZE'
  | 'L1_GAS_LIMIT_BUFFER_PERCENTAGE'
  | 'L1_GAS_LIMIT_BUFFER_FIXED'
  | 'L1_GAS_PRICE_MIN'
  | 'L1_GAS_PRICE_MAX'
  | 'L1_BLOB_FEE_PER_GAS_MAX'
  | 'L1_PRIORITY_FEE_BUMP_PERCENTAGE'
  | 'L1_PRIORITY_FEE_RETRY_BUMP_PERCENTAGE'
  | 'L1_FIXED_PRIORITY_FEE_PER_GAS'
  | 'L1_TX_MONITOR_MAX_ATTEMPTS'
  | 'L1_TX_MONITOR_CHECK_INTERVAL_MS'
  | 'L1_TX_MONITOR_STALL_TIME_MS'
  | 'L1_TX_MONITOR_TX_TIMEOUT_MS'
  | 'L1_TX_PROPAGATION_MAX_QUERY_ATTEMPTS'
  | 'FAUCET_MNEMONIC_ACCOUNT_INDEX'
  | 'FAUCET_ETH_AMOUNT'
  | 'FAUCET_INTERVAL_MS'
  | 'FAUCET_L1_ASSETS'
  | 'K8S_POD_NAME'
  | 'K8S_POD_UID'
  | 'K8S_NAMESPACE_NAME'
  | 'CUSTOM_FORWARDER_CONTRACT_ADDRESS';
