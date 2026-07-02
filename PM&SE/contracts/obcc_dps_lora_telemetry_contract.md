# OBCC-DPS LoRa telemetry, command, RF, and PDR contract

**Contract version:** `PMSE-OBCC-DPS-LORA-TELEMETRY-v1.0`

**Owner:** PM&SE configuration control, with OBCC and DPS execution owners.

**Applies to:** OBCC v1.0 LoRa telemetry downlink, DPS v1.0 receive/decode/store/display evidence, OBCC command/uplink tests, `OBCC-V03-GATE-001`, `OBCC-V04-GATE-001`, `OBCC-V09-GATE-001`, `OBCC-V10-FLIGHT-001`, `DPS-V10-C-001`, `DPS-V10-C-003`, and `SYS-RF-RANGE-PDR` unless a later controlled system definition supersedes it.

This contract freezes definition parameters only. It is not an execution report and does not grant pass/fail credit. Activity READMEs, D2/model views, source/configuration files, reports, and as-tested evidence still have to be updated or executed where applicable.

## 1. Relationship to DPS and sensor contracts

This contract reuses the RF/range/PDR and concurrency selections made for DPS in `DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md` so that OBCC and DPS do not define contradictory radio evidence.

ADS/AMS sample freshness carried by OBCC telemetry is controlled separately by `PM&SE/contracts/sensor_obcc_freshness_contract.md`. OBCC telemetry shall include, or be traceable through preserved logs to, the ADS/AMS `status` and `age_ms` evidence required by that contract.

## 2. RF/range/PDR baseline

Strict OBCC/DPS RF range and PDR evidence shall use this baseline unless superseded by a controlled system-level definition:

- Endpoint geometry: horizontal line-of-sight range with `500 m` endpoint separation. The measured horizontal separation between antenna endpoints, including measurement uncertainty, shall be at least `500 m` for strict credit.
- Frequency: `915 MHz`.
- Radio articles: OBCC CanSat and DPS ground-station articles use `RFM96W` LoRa radios or an approved, recorded equivalent/deviation.
- Antennas: matching `22 AWG` straight-wire monopoles with `81.4 mm` exposed conductor on the CanSat and ground-station articles.
- Orientation/polarization: both monopoles straight and vertical unless the final as-flown installation requires otherwise; both endpoints shall use matching linear polarization. Record any tilt, enclosure shadowing, body orientation, or polarization mismatch.
- Radio parameters for definition-level airtime/PDR planning: `SF7`, `125 kHz` bandwidth, coding rate `4/5`, explicit header, payload CRC on, preamble `8`, low-data-rate optimization off.
- Payload size basis: current worst-case `LORA_PAYLOAD_SIZE = 100 bytes`. Any final payload/envelope change shall trigger a new airtime calculation before strict execution credit.
- Current airtime basis: a 100-byte frame at the selected parameters is `174.336 ms`; at a `2 s` flight cadence this is about `8.72%` raw time-on-air per transmitting node before turnaround/listen margins.
- Legal/site prerequisites: frequency, TX power, antenna gain, EIRP, duty cycle, and site authorization shall be legal and recorded for the test location. Otherwise the run is characterization only.

## 3. Telemetry cadence and PDR acceptance

- Flight telemetry cadence: `2 s` scheduled telemetry opportunities during nominal mission/range evidence.
- Formal cadence timing claim: collect at least `n = 59` representative consecutive received or generated intervals and require every interval to be within `2.0 s +/- 0.2 s` (`1.8 s` to `2.2 s`) unless a later controlled activity definition declares a stricter tolerance.
- Range/PDR campaign: use `N = 300` scheduled unique frames over a `10 min` window at the `2 s` cadence.
- Acceptance rule: require `k >= 279` successful frames out of `N = 300`, yielding a one-sided 95% exact-binomial / Clopper-Pearson lower confidence bound `>=0.90`.
- Success classification: one scheduled unique frame is successful only when received at the DPS ground station within its declared timing window with expected source/destination/configuration identity, valid integrity check, valid sequence/timestamp, valid payload length/schema, recorded RSSI/SNR, and no duplicate/replay substitution.
- Failure classification: missing frame, integrity failure, parse/schema failure, wrong ID, stale replay, out-of-window frame, duplicate replacing a missing sequence, corrupted payload accepted as valid, or missing required RSSI/SNR/validity evidence for a scheduled trial.
- Retransmission rule: no deliberate application-level retransmission of a failed scheduled frame may be counted as the original success. A repeated request after timeout means the original trial failed.
- Abort rule: abort for safety, legal/site approval loss, power/configuration mismatch, evidence logger failure, equipment damage risk, or uncontrolled site conditions. An aborted run gives no strict pass.

## 4. Payload schema traceability baseline

- Controlled payload schema ID for the current OBCC measurement/status table: `OBCC-LORA-PAYLOAD-v1.0`.
- Payload source: `OBCC/LoRa_Frame.md` is the controlled variable table for the active v1.0 OBCC payload unless a later schema document supersedes it.
- Current variable-table size: `35 bytes` before LoRa envelope, IDs, command/request fields, schema/version, sequence/timestamp, health/status metadata outside the listed fields, RSSI/SNR logging fields, delimiters, or other envelope overhead.
- Required in-payload deployment disclosure: `Parachute Deployment Status` / field name `deployment_status` is a one-byte unsigned enum carried in the existing 100-byte OBCC-to-DPS LoRa telemetry frame. Schema traceability: in `OBCC/LoRa_Frame.md` it is the final field at variable-table byte offset `34` (zero-based; 35th byte). The current 100-byte firmware/DPS packet mapping carries it at payload byte offset `48`, after the `CSWS`/sender/receiver envelope and legacy measurement slots, with bytes `49..95` reserved.

| Code | `deployment_status` symbol | Category | Consumer meaning |
|---|---|---|---|
| 0 | `NOT_COMMANDED` | `not-deployed` | No accepted deployment command/current trigger context. |
| 1 | `INHIBITED_STANDBY` | `not-deployed` | Request suppressed because OBCC is in Stand-by. |
| 2 | `COMMAND_SENT` | `in-progress` | OBCC sent open command; not success by itself. |
| 3 | `OPEN_IN_PROGRESS` | `in-progress` | Actuator/PDM response underway, not confirmed. |
| 4 | `OPEN_CONFIRMED` | `deployed` | PDM feedback or independent safe-fixture/current/position observer confirms open; only success/deployed state. |
| 5 | `NO_OPEN_CONFIRMED` | `not-deployed` | Observer/feedback confirms no open. |
| 6 | `TIMEOUT` | `fault` | No open confirmation within declared timing window. |
| 7 | `JAM_DETECTED` | `fault` | Current/position/feedback indicates jam/blocked travel. |
| 8 | `PDM_FAULT` | `fault` | PDM reports fault or command path unavailable. |
| 9 | `UNKNOWN` | `unknown` | Cannot prove status; never success. |

- Deployment-status source/semantics: OBCC shall populate `deployment_status` from PDM/actuator confirmation evidence exposed to OBCC or from OBCC-owned deployment/fault-policy interpretation. `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, or unrecognized statuses shall not be interpreted as deployed; only `OPEN_CONFIRMED` may be treated as deployed/success.
- Relative humidity is not part of the active v1.0 OBCC payload. A frame or dashboard column shall not silently map any obsolete RH field to another quantity.
- Required traceability: every strict telemetry, CSV, dashboard, or end-to-end data report shall identify the payload schema ID/version, field order, units, scale/encoding, payload length, deployment-status enum code/symbol/category mapping, code/configuration source, parser/decoder version, and any deviations.
- Health/status metadata and deployment disclosure: telemetry shall carry `deployment_status` and shall include, or be losslessly traceable in synchronized logs to, frame sequence, transmit/receive timestamp or slot number, OBCC mode (`Stand-by` or `On`), command-result state where applicable, runtime health/result codes, and ADS/AMS freshness status/age evidence when those samples are packaged.
- DPS CSV, dashboard, and report consumers shall preserve the `deployment_status` numeric code, symbol, and category and shall treat only `OPEN_CONFIRMED` / `deployed` as deployed. Fault, inhibited, timeout, unknown, missing, unrecognized, no-open, in-progress, and command-sent states shall remain distinguishable and non-success.
- If an implementation carries some required metadata only in local trace rather than over the RF payload, the report must retain the correlation method. Missing correlation limits the claim to characterization for the affected field.

## 5. Command schema traceability baseline

- Controlled command schema ID for OBCC/DPS verification: `OBCC-DPS-CMD-v1.0`.
- Required command classes for strict tests: `DATA` request, `ON`, and `STANDBY` / `STAND-BY` state command. Exact opcode spelling may vary only if the execution report provides a one-to-one controlled mapping.
- Minimum command evidence fields: source ID, destination ID, opcode/command class, sequence/trial ID or equivalent replay discriminator, receive timestamp, integrity check result, acceptance/rejection result, and resulting OBCC mode/state telemetry.
- Existing configuration context: current OBCC source uses `LORA_HEADER = "CSWS"`, `GS_LORA_ID = "GS"`, CanSat ID such as `"M2"`, `LORA_TX_COMMAND = "DATA"`, and `LORA_FOOTER = "DTLB"` for the telemetry request context. Strict command/state evidence must either use this controlled envelope or document the exact as-tested equivalent.
- Valid `DATA` requests solicit one telemetry response and shall not by themselves cause an On/Stand-by state transition or deployment side effect.
- Valid `ON` and `STANDBY` commands shall be accepted exactly once, produce the modeled state transition, and be reflected in telemetry/trace evidence.
- Invalid, corrupt, unsupported, duplicate, replayed, stale-context, or out-of-context commands shall not change operational state, shall not deploy, and shall be logged or telemetry-visible as rejected/ignored where supported.

## 6. Concurrency and DPS pipeline alignment

For OBCC/DPS integrated telemetry evidence that also claims DPS concurrency/load behavior:

- Use the same `10 min`, `2 s`, `N = 300` flight-cadence stream as the range/PDR campaign where practical.
- DPS observations should include frame RX timestamp, decode timestamp, CSV append timestamp, dashboard update timestamp where available, queue depth/backlog, process liveness, memory trend, dropped/rejected frames, and exception/error logs.
- Strict DPS pipeline claim uses p95 RX-to-consumer latency `<1 s`, no crash/deadlock/watchdog reset/unhandled exception, no accepted-frame loss from queue overflow, bounded queue/backlog that returns to zero within `10 s` after the last scheduled frame, and bounded memory.
- Optional high-rate stress remains characterization unless fully instrumented and may use synthetic/serial/RF-cabled injection when open-air duty-cycle or legal margin is inadequate.

## 7. As-tested configuration and evidence records

Before strict execution credit, reports shall record:

- CanSat OBCC article ID, ground-station/DPS radio article ID, antenna build IDs, UUT serial/revision, firmware commits/builds, settings/config files, parser/decoder/dashboard versions, analysis scripts, operator, and evidence archive path.
- Radio settings including frequency, SF, bandwidth, coding rate, preamble, header mode, CRC setting, TX power/EIRP inputs, duty-cycle basis, and legal/site approval.
- Endpoint coordinates/survey marks, endpoint-distance method/uncertainty, antenna feed-point heights, photos showing horizontal line of sight, weather/ambient conditions, observed interference/channel occupancy if available, and safety controls.
- Raw RF frames/bytes where available, sequence/timestamps, RSSI/SNR, validity/reject reasons, decoded payload records, CSV/dashboard evidence, and timebase/correlation method.

## 8. Affected-test update map

| Target | Required update/use of this contract |
|---|---|
| `OBCC-V03-GATE-001` | Replace the planning `96/100` PDR point with `N=300`, `k>=279`; use 500 m horizontal LOS, 915 MHz, RFM96W, matching 22 AWG 81.4 mm antennas, selected LoRa parameters, payload schema ID, and RSSI/SNR/legal/site evidence. |
| `OBCC-V04-GATE-001` | Reference `OBCC-DPS-CMD-v1.0` for `DATA`, `ON`, and `STANDBY` command classes, accepted-once/replay evidence, and as-tested envelope mapping. |
| `OBCC-V09-GATE-001` | Use this contract for integrated rehearsal telemetry, RF, command, payload, and evidence interpretation; do not claim final PDR unless the strict range/PDR campaign evidence exists or is explicitly referenced. |
| `OBCC-V10-FLIGHT-001` | Treat this contract as the selected OBCC/DPS RF/telemetry/command baseline for final readiness closure; verify reports identify as-tested IDs and deviations. |
| `DPS-V10-C-001` / `SYS-RF-RANGE-PDR` | Reuse the same horizontal LOS RF/range/PDR baseline unless stricter system-level conditions are approved. |
| `DPS-V10-C-003` | Use the same 10 min/2 s stream and p95 `<1 s` pipeline criterion for concurrency/load claims where OBCC telemetry is the source. |

## 9. Residual execution follow-up

1. Keep affected Markdown READMEs and D2/model views aligned with this contract when future controlled changes are made; current CON-003 definitions cite/use this baseline.
2. Recalculate airtime if the payload/envelope differs from the 100-byte basis.
3. Align source/configuration values with the selected `2 s` telemetry cadence before strict credit, or record a controlled deviation.
4. Execute only after legal/site approval, as-tested configuration records, evidence paths, and analysis scripts are controlled.
