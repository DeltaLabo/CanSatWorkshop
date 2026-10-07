# PM&SE controlled contract publications

These files are controlled human-readable integration and traceability publications derived from the model baselines. They do **not** supersede the model.

## Authority hierarchy

1. [`PM&SE/MBSE/v1.0/`](../MBSE/v1.0/README.md) owns the cross-subsystem product architecture, interfaces, behavior, and shared constraints.
2. Subsystem `v1.0` baselines refine subsystem-internal implementation and allocation:
   - `ADS/MBSE/v1.0/`
   - `AMS/MBSE/v1.0/`
   - `OBCC/MBSE/v1.0/`
   - `DPS/MBSE/v1.0/`
   - `PDM/MBSE/v1.0/`
3. Modeled verification packages under `*/MBSE/tests/` own test means, oracles, statistics, and fault cases.
4. Markdown contracts in this folder publish the selected model semantics for integration use and traceability; they shall not redefine contradictory values.
5. [`sensor_obcc_freshness_contract.h`](sensor_obcc_freshness_contract.h) and [`../../OBCC/LoRa_Frame.md`](../../OBCC/LoRa_Frame.md) are implementation/encoding realizations traced to the model.

## Controlled publications

| Publication | Kind | Role |
|---|---|---|
| [`sensor_obcc_freshness_contract.md`](sensor_obcc_freshness_contract.md) | Markdown publication | Human-readable publication of the modeled ADS/AMS-to-OBCC freshness, status, and telemetry-packaging semantics. |
| [`sensor_obcc_freshness_contract.h`](sensor_obcc_freshness_contract.h) | C realization header | Reference constants, enum values, envelope metadata type, and predicates realizing the modeled freshness contract. |
| [`obcc_dps_lora_telemetry_contract.md`](obcc_dps_lora_telemetry_contract.md) | Markdown publication | Human-readable publication of the modeled OBCC/DPS telemetry, command, RF, deployment-status, and evidence semantics. |
| [`../../OBCC/LoRa_Frame.md`](../../OBCC/LoRa_Frame.md) | Byte-level realization | Payload field order, types, offsets, and current 100-byte frame basis mapping for `OBCC-LORA-PAYLOAD-v1.0`. |

Related OBCC deployment/fault policy realization: [`../../OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md`](../../OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md).

## Change rule

Any product semantic change starts in the PM&SE system model, then flows into the subsystem baselines and modeled verification packages, and only then into these publications and realization artifacts.
