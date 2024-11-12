#!/bin/bash
set -eu

SCRIPT_DIR="$(dirname $(realpath -s "${BASH_SOURCE[0]}"))"
cd "$SCRIPT_DIR"

# check if metrics is already installed
if helm ls --namespace metrics | grep -q metrics; then
  echo "metrics is already installed"
  exit 0
fi

helm repo add open-telemetry https://open-telemetry.github.io/opentelemetry-helm-charts
helm repo add grafana https://grafana.github.io/helm-charts
helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
helm dependency update
# need to disable node exporter for GKE autopilot to be happy
helm upgrade metrics "$SCRIPT_DIR" -n metrics --install --create-namespace --atomic --set prometheus.prometheus-node-exporter.enabled=false