# PM&SE controlled contracts

This directory contains cross-subsystem interface and verification contracts controlled by PM&SE.

| Contract | Purpose |
|---|---|
| [`sensor_obcc_freshness_contract.md`](sensor_obcc_freshness_contract.md) | Shared ADS/AMS sensor-to-OBCC freshness, status, and telemetry-packaging rule for v1.0 internal OBCC consumers and telemetry evidence. |
| [`sensor_obcc_freshness_contract.h`](sensor_obcc_freshness_contract.h) | ESP32/FreeRTOS Arduino-compatible reference constants, status enum, response metadata, and fresh-valid predicate for the shared contract. |

Subsystem-specific API details, such as ADS or AMS pointer ownership/lifetime naming, may be added as supplements, but they shall reference this shared contract and shall not redefine contradictory freshness or status semantics.
