# OBCC-DPS LoRa telemetry, command, RF, and PDR contract

**Contract version:** `PMSE-OBCC-DPS-LORA-TELEMETRY-v1.0`

**Publication owner:** PM&SE configuration control

**Applies to:** OBCC v1.0 LoRa telemetry downlink, DPS v1.0 receive/decode/store/display behavior, OBCC command/uplink evidence, and the current PM&SE system verification packages that exercise those paths.

## 1. Authority and change control

1. [`PM&SE/MBSE/v1.0/`](../MBSE/v1.0/README.md) owns the cross-subsystem telemetry, command, deployment-status, and RF service semantics.
2. Subsystem `v1.0` baselines refine implementation and allocation in `OBCC/MBSE/v1.0/`, `DPS/MBSE/v1.0/`, and `PDM/MBSE/v1.0/`.
3. Modeled verification packages own test means, pass/fail oracles, statistics, and fault cases.
4. This Markdown file is a controlled human-readable publication. It shall not redefine contradictory model values.
5. [`../../OBCC/LoRa_Frame.md`](../../OBCC/LoRa_Frame.md) is the byte-level realization of `OBCC-LORA-PAYLOAD-v1.0`; it is not a competing architecture source.
6. Product semantic changes start in the PM&SE system model, then flow into subsystem baselines and verification packages, and only then into this publication and the byte-level realization.

## 2. Model coverage

| Concern | PM&SE system baseline view(s) | Subsystem refinement view(s) | System verification package(s) |
|---|---|---|---|
| Telemetry schema | [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2), [`CANSAT_v1.0_view8_deployment_safety_status_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view8_deployment_safety_status_chain.d2) | OBCC [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2), [`OBCC_v1.0_view3_functional_allocation.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view3_functional_allocation.d2); DPS [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2), [`DPS_v1.0_view3_functional_allocation.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view3_functional_allocation.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |
| Telemetry cadence | [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2), [`CANSAT_v1.0_view9_rf_service_performance_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view9_rf_service_performance_chain.d2) | OBCC [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2); DPS [`DPS_v1.0_view3_functional_allocation.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view3_functional_allocation.d2), [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2) | [`SYS-RF-RANGE-PDR`](../MBSE/tests/SYS-RF-RANGE-PDR/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md), [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md) |
| Telemetry validation | [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2), [`CANSAT_v1.0_view9_rf_service_performance_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view9_rf_service_performance_chain.d2) | DPS [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2), [`DPS_v1.0_view10_invalid_frame_rejection_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view10_invalid_frame_rejection_chain.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-RF-RANGE-PDR`](../MBSE/tests/SYS-RF-RANGE-PDR/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |
| Command uplink and state reflection | [`CANSAT_v1.0_view7_command_uplink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view7_command_uplink_chain.d2), [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2) | OBCC [`OBCC_v1.0_view6_command_state_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view6_command_state_chain.d2); DPS [`DPS_v1.0_view5_command_uplink_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view5_command_uplink_chain.d2) | [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md), [`SYS-FLIGHT-READINESS-CLOSURE`](../MBSE/tests/SYS-FLIGHT-READINESS-CLOSURE/README.md) |
| Deployment-status disclosure | [`CANSAT_v1.0_view8_deployment_safety_status_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view8_deployment_safety_status_chain.d2), [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2) | OBCC [`OBCC_v1.0_view7_deployment_gating_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view7_deployment_gating_chain.d2), [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2); PDM [`PDM_v1.0_view3_functional_allocation.d2`](../../PDM/MBSE/v1.0/PDM_v1.0_view3_functional_allocation.d2), [`PDM_v1.0_view4_imu_triggered_deployment_chain.d2`](../../PDM/MBSE/v1.0/PDM_v1.0_view4_imu_triggered_deployment_chain.d2), [`PDM_v1.0_view5_degraded_fault_status_chain.d2`](../../PDM/MBSE/v1.0/PDM_v1.0_view5_degraded_fault_status_chain.d2); DPS [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2) | [`SYS-DEPLOYMENT-SAFE-LIVE`](../MBSE/tests/SYS-DEPLOYMENT-SAFE-LIVE/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md), [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md) |
| RF service baseline | [`CANSAT_v1.0_view1_physical.d2`](../MBSE/v1.0/CANSAT_v1.0_view1_physical.d2), [`CANSAT_v1.0_view9_rf_service_performance_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view9_rf_service_performance_chain.d2) | OBCC [`OBCC_v1.0_view3_functional_allocation.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view3_functional_allocation.d2), [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2); DPS [`DPS_v1.0_view3_functional_allocation.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view3_functional_allocation.d2), [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2) | [`SYS-RF-RANGE-PDR`](../MBSE/tests/SYS-RF-RANGE-PDR/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |
| Packet-delivery ratio (PDR) | [`CANSAT_v1.0_view9_rf_service_performance_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view9_rf_service_performance_chain.d2) | DPS [`DPS_v1.0_view3_functional_allocation.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view3_functional_allocation.d2), [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2) | [`SYS-RF-RANGE-PDR`](../MBSE/tests/SYS-RF-RANGE-PDR/README.md) |
| Evidence and closure | [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2), [`CANSAT_v1.0_view7_command_uplink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view7_command_uplink_chain.d2), [`CANSAT_v1.0_view8_deployment_safety_status_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view8_deployment_safety_status_chain.d2), [`CANSAT_v1.0_view9_rf_service_performance_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view9_rf_service_performance_chain.d2) | OBCC [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2), [`OBCC_v1.0_view6_command_state_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view6_command_state_chain.d2), [`OBCC_v1.0_view7_deployment_gating_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view7_deployment_gating_chain.d2); DPS [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2), [`DPS_v1.0_view5_command_uplink_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view5_command_uplink_chain.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-RF-RANGE-PDR`](../MBSE/tests/SYS-RF-RANGE-PDR/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md), [`SYS-FLIGHT-READINESS-CLOSURE`](../MBSE/tests/SYS-FLIGHT-READINESS-CLOSURE/README.md) |

## 3. Relationship to other controlled artifacts

- ADS/AMS sample freshness inside telemetry is controlled by [`sensor_obcc_freshness_contract.md`](sensor_obcc_freshness_contract.md). Telemetry shall preserve, or remain losslessly traceable to, the ADS/AMS `status` and `age_ms` evidence required there.
- [`../../OBCC/LoRa_Frame.md`](../../OBCC/LoRa_Frame.md) is the current byte-level realization of `OBCC-LORA-PAYLOAD-v1.0` field order, types, offsets, and the current 100-byte frame basis mapping.
- System and subsystem verification packages own the execution-specific statistics, fault campaigns, and verdict criteria. This document repeats them only as a traceability aid.

## 4. Derived RF realization content retained here

The following RF selections are retained here because the product model intentionally summarizes them and the verification packages need a controlled human-readable publication of the chosen realization.

- Endpoint geometry: horizontal line-of-sight range with `>=500 m` endpoint separation.
- Frequency: `915 MHz`.
- Radio articles: OBCC CanSat and DPS ground-station articles use `RFM96W` LoRa radios or an approved, recorded equivalent.
- Antennas: matching `22 AWG` straight-wire monopoles with `81.4 mm` exposed conductor on the CanSat and ground-station articles.
- Orientation/polarization: both monopoles straight and vertical unless the final installation requires otherwise; record any tilt, shadowing, body orientation, or polarization mismatch.
- Radio parameters for the current **100-byte frame basis**: `SF7`, `125 kHz` bandwidth, coding rate `4/5`, explicit header, payload CRC on, preamble `8`, low-data-rate optimization off.
- Current airtime basis for the **100-byte frame basis**: `174.336 ms`; at a `2 s` cadence this is about `8.72%` raw time-on-air per transmitting node before turnaround/listen margins.
- Legal/site prerequisites: frequency, TX power, antenna gain, EIRP, duty cycle, and site authorization shall be legal and recorded for the test location.

## 5. Derived payload realization content retained here

- Controlled payload schema ID: `OBCC-LORA-PAYLOAD-v1.0`.
- Payload realization source: [`../../OBCC/LoRa_Frame.md`](../../OBCC/LoRa_Frame.md).
- Current variable-table size: `35 bytes` inside the current **100-byte frame basis**, before envelope identities, command/request fields, schema/version, sequence/timestamp, health metadata outside the listed fields, RSSI/SNR evidence, delimiters, or footer bytes.
- Relative humidity is not part of the active v1.0 payload and shall not be inferred, remapped, or displayed as another quantity.
- Required telemetry metadata: source/destination/configuration identity, schema/version, sequence/timestamp, integrity, payload length, units/scale/encoding, ADS/AMS freshness status/age evidence, and `deployment_status`, either in the payload or by lossless synchronized trace.

### `deployment_status` realization

`deployment_status` is a one-byte unsigned enum carried in the existing 100-byte frame basis. In [`../../OBCC/LoRa_Frame.md`](../../OBCC/LoRa_Frame.md) it is the final variable-table field at zero-based variable-table byte offset `34`. The current firmware/DPS packet mapping carries it at payload byte offset `48`, with bytes `49..95` reserved before the footer.

| Code | `deployment_status` symbol | Category | Consumer meaning |
|---|---|---|---|
| 0 | `NOT_COMMANDED` | `not-deployed` | No accepted deployment command/current trigger context. |
| 1 | `INHIBITED_STANDBY` | `not-deployed` | Request suppressed because OBCC is in Standby. |
| 2 | `COMMAND_SENT` | `in-progress` | OBCC sent open command; not success by itself. |
| 3 | `OPEN_IN_PROGRESS` | `in-progress` | Actuator/PDM response underway, not confirmed. |
| 4 | `OPEN_CONFIRMED` | `deployed` | PDM feedback or independent safe-fixture/current/position observer confirms open; only success/deployed state. |
| 5 | `NO_OPEN_CONFIRMED` | `not-deployed` | Observer/feedback confirms no open. |
| 6 | `TIMEOUT` | `fault` | No open confirmation within declared timing window. |
| 7 | `JAM_DETECTED` | `fault` | Current/position/feedback indicates jam/blocked travel. |
| 8 | `PDM_FAULT` | `fault` | PDM reports fault or command path unavailable. |
| 9 | `UNKNOWN` | `unknown` | Cannot prove status; never success. |

Only `OPEN_CONFIRMED` may be treated as deployed/success. `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, or unrecognized statuses remain non-success.

Additional retained realization and traceability rules:

- Every strict telemetry, CSV, dashboard, or end-to-end data report shall identify the payload schema ID/version, field order, units, scale/encoding, payload length, deployment-status code/symbol/category mapping, code/configuration source, parser/decoder version, and any deviations.
- Telemetry shall carry `deployment_status` and shall include, or be losslessly traceable in synchronized logs to, frame sequence, transmit/receive timestamp or slot number, OBCC mode (`Standby` or `On`), command-result state where applicable, runtime health/result codes, and ADS/AMS freshness status/age evidence when those samples are packaged.
- DPS CSV, dashboard, and report consumers shall preserve the `deployment_status` numeric code, symbol, and category and shall treat only `OPEN_CONFIRMED` / `deployed` as deployed.
- If an implementation carries some required metadata only in local trace rather than over RF payload, the report shall retain the correlation method. Missing correlation limits the claim to characterization for the affected field.

## 6. Derived command realization content retained here

- Controlled command schema ID: `OBCC-DPS-CMD-v1.0`.
- Required command classes for strict tests: `DATA`, `ON`, and `STANDBY` / `STAND-BY`.
- Minimum command evidence fields: source ID, destination ID, opcode/command class, replay discriminator or equivalent sequence/timestamp, receive timestamp, integrity result, acceptance/rejection result, and resulting OBCC mode/state telemetry.
- Current envelope realization context: `LORA_HEADER = "CSWS"`, `GS_LORA_ID = "GS"`, CanSat ID such as `"M2"`, `LORA_TX_COMMAND = "DATA"`, and `LORA_FOOTER = "DTLB"`.
- Valid `DATA` requests solicit one telemetry response and shall not cause an On/Standby transition or deployment side effect.
- Valid `ON` and `STANDBY` commands shall be accepted exactly once, produce the modeled state transition, and be reflected in telemetry/trace evidence.
- Invalid, corrupt, unsupported, duplicate, replayed, stale-context, or out-of-context commands shall not change operational state, shall not deploy, and shall be logged or telemetry-visible as rejected/ignored where supported.

## 7. Derived execution context owned by IVV and verification packages

The following execution selections and statistics are owned by [`PM&SE/IVV.md`](../IVV.md) and the modeled verification packages; they are repeated here for traceability:

- Flight telemetry cadence for strict campaigns: `2 s` scheduled telemetry opportunities.
- Formal cadence timing claim: `n = 59` representative intervals with every interval within `2.0 s +/- 0.2 s` unless a stricter verification package declares otherwise.
- Range/PDR campaign: `N = 300` scheduled unique frames over `10 min`.
- PDR acceptance: `k >= 279` successful frames so the one-sided 95% exact-binomial / Clopper-Pearson lower confidence bound is `>=0.90`.
- Strict DPS pipeline claim: p95 RX-to-consumer latency `<1 s`, no crash/deadlock/watchdog reset/unhandled exception, no accepted-frame loss from queue overflow, bounded queue/backlog returning to zero within `10 s` after the final scheduled frame, and bounded memory.

Success classification for a scheduled frame: correct identity/configuration, valid integrity, valid sequence/timestamp, valid payload length/schema, recorded RSSI/SNR, and no duplicate/replay substitution. Missing frame, integrity failure, parse/schema failure, wrong ID, replay, out-of-window frame, duplicate replacing a missing sequence, corrupted payload accepted as valid, or missing required RSSI/SNR/validity evidence is a failure.
- Retransmission rule: no deliberate application-level retransmission of a failed scheduled frame may be counted as the original success. A repeated request after timeout means the original trial failed.
- Abort rule: abort for safety, legal/site approval loss, power/configuration mismatch, evidence logger failure, equipment damage risk, or uncontrolled site conditions. An aborted run gives no strict pass.

## 8. As-tested configuration and evidence records

Before strict execution credit, reports shall record:

- CanSat OBCC article ID, ground-station/DPS radio article ID, antenna build IDs, UUT serial/revision, firmware commits/builds, settings/config files, parser/decoder/dashboard versions, analysis scripts, operator, and evidence archive path.
- Radio settings including frequency, SF, bandwidth, coding rate, preamble, header mode, CRC setting, TX power/EIRP inputs, duty-cycle basis, and legal/site approval.
- Endpoint coordinates/survey marks, endpoint-distance method/uncertainty, antenna feed-point heights, photos showing horizontal line of sight, weather/ambient conditions, observed interference/channel occupancy if available, and safety controls.
- Raw RF frames/bytes where available, sequence/timestamps, RSSI/SNR, validity/reject reasons, decoded payload records, CSV/dashboard evidence, and timebase/correlation method.

## 9. Relevant modeled verification definitions

System packages: [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-RF-RANGE-PDR`](../MBSE/tests/SYS-RF-RANGE-PDR/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md), [`SYS-DEPLOYMENT-SAFE-LIVE`](../MBSE/tests/SYS-DEPLOYMENT-SAFE-LIVE/README.md), [`SYS-FLIGHT-READINESS-CLOSURE`](../MBSE/tests/SYS-FLIGHT-READINESS-CLOSURE/README.md).

Subsystem packages that refine the same concerns include DPS [`DPS-V10-C-001`](../../DPS/MBSE/tests/DPS-V10-C-001/README.md), [`DPS-V10-C-003`](../../DPS/MBSE/tests/DPS-V10-C-003/README.md), [`DPS-V10-T-001`](../../DPS/MBSE/tests/DPS-V10-T-001/README.md), [`DPS-V10-T-002`](../../DPS/MBSE/tests/DPS-V10-T-002/README.md), [`DPS-V10-T-003`](../../DPS/MBSE/tests/DPS-V10-T-003/README.md), and OBCC [`OBCC-V10_Deployment_Fault_Policy.md`](../../OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md).
