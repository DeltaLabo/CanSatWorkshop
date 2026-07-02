# PDM-VV-FC-001 — IMU-triggered parachute deployment verification definition

**Selected gate:** PDM v1.0 → flight readiness.
**IADT method:** Testing / Demonstration, with supporting Analysis and Inspection.
**Primary IVV source category:** functional chain/scenario, with linked component-exchange, allocation, component/link, and constraint coverage.
**Status:** Modeled definition ready for review; execution pending.

This package defines a model-based verification activity for the PDM v1.0 IMU-triggered parachute deployment path. The source model remains the authority for the system definition; these views add the verification means, equipment/human actors, environmental conditions, fault-hardening sequences, pass/fail constraints, evidence interfaces, and traceability expected for execution reports.

## Definition-level policy boundaries

- PDM uses the OBCC-owned deployment/fault policy baseline in [`../../../../../OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md`](../../../../../OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md). OBCC owns mode, trigger, emergency-deploy, descent observability, safe/error, and no-false-success decisions.
- PDM deploys when commanded by OBCC and exposes available actuator/servo status evidence. This package does not redefine OBCC emergency policy. PDM/actuator evidence shall be mappable to the OBCC telemetry `deployment_status` / `Parachute Deployment Status` enum so downstream OBCC, DPS CSV, dashboard, and reports can preserve raw code/symbol/category without false success.
- ADS input freshness/status evidence used at the PDM/OBCC trigger observation point follows [`../../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md): `VALID` is usable for normal triggers only when `age_ms <= 400 ms` and all required fields are finite/in range; `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL` are not normal triggers.

## Source-view copies

Copied source baseline under `source_views/v1.0/`:

- `PDM_v1.0_view1_physical.d2/png`
- `PDM_v1.0_view2_logical.d2/png`
- `PDM_v1.0_view3_functional_allocation.d2/png`
- `PDM_v1.0_view4_imu_triggered_deployment_chain.d2/png`

## Definition views

All D2 views were rendered with the required ELK command and have PNGs next to the D2 sources.

| View | Purpose |
|---|---|
| `definition_views/PDM_VV_FC_001_view1_source_chain_coverage_inventory.d2/png` | Source chain and IVV coverage inventory for functions, CEs, allocations, physical context, constraints, statistics, and traceability. |
| `definition_views/PDM_VV_FC_001_view2_physical_test_setup.d2/png` | Physical test setup with PDM v1.0 UUT, verification-only probe pads/witness marks/gauge, IMU stimulus rig, host/logger, logic analyzer, power/current monitor, camera, ambient monitor, and recovery area. |
| `definition_views/PDM_VV_FC_001_view3_verification_functional_allocation.d2/png` | Verification functional allocation to human operators, stimulus/fault/power/camera/analysis EAs, source LCs/functions, and verification-only evidence interface. |
| `definition_views/PDM_VV_FC_001_view4_nominal_fault_sequence.d2/png` | Functional-chain test/demonstration sequence covering setup inspection, nominal deployment, negative/no-manual checks, I2C and IMU faults, jam/no-open, brownout/reset, analysis, and report archiving. |
| `definition_views/PDM_VV_FC_001_view5_evidence_traceability.d2/png` | Evidence/report interface and traceability to use cases, feared events, source CEs, and linked constraints. |

## Coverage summary

| IVV category | Coverage in this activity |
|---|---|
| Functional chain/scenario | IMU data → ADS processing → OBCC/PDM deployment command path → PWM open signal → servo open → holder separates → parachute unfolds → terminal-speed evidence linked to the `<= 11 m/s` criterion. |
| Component exchanges | Linked coverage for `[CE] I2C`, `[CE] Pointers/Returns`, `[CE] PWM`, `[CE] PWM` feedback/status, and `[CE] Torque`, with OBCC-owned no-false-success interpretation. |
| Allocation | ADS Kinematic Sensing, ADS Processing, OBCC, PDM Processing, Trigger, Parachute Holder, and Descent speed control functions are included. |
| Component/link | Supporting inspection of ADS/OBCC/backplane/parachute module PCs and deployment-relevant PLs before credited functional trials. |
| Constraints | Parachute diameter `≤30 cm`; terminal descent speed `<= 11 m/s` via linked `PDM-VV-FC-003` or equivalent evidence; angular-rate error `<30 deg/s` or robust thresholds; no manual/BLE open command; initial servo `0 degrees`/closed; I2C reads `≤5 ms`; process/calculate `<5 ms`; no blocking outside I2C; `OPEN_CONFIRMED` as the only strict deployment-success state. |

## Pass/fail rules

Pass only if all modeled criteria are satisfied and evidenced:

1. A nominal OBCC-accepted IMU-derived trigger profile with fresh-valid ADS input (`status == VALID` and `age_ms <= 400 ms`) produces exactly one complete ordered deployment chain.
2. Negative/non-deploy profiles, manual/BLE attempts, stale/bad data profiles, and other non-`VALID` ADS inputs (`STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`) do not produce a normal flight-mode open command.
3. I2C reads succeed or time out within `≤5 ms`; I2C fault cases are bounded and reported.
4. Process/calculate functions complete in `<5 ms`; no unexpected blocking outside modeled I2C communications.
5. Startup/reset servo position is `0 degrees`/closed; no open pulse occurs before the deployment condition.
6. Angular-rate error is `<30 deg/s` or deployment thresholds are analyzed robust to that error with documented truth/reference and guard-band handling.
7. Parachute diameter is `≤30 cm`; terminal-speed evidence linked from `PDM-VV-FC-003` or an equivalent controlled activity demonstrates `<= 11 m/s` using representative as-tested mass/configuration, deployed parachute condition, calibrated video/time-distance or equivalent measurement, uncertainty/guard band, wind/environment record, and anomaly/deviation rules. If that evidence is absent, this activity cannot claim terminal-speed credit.
8. Open-command timing and status must follow OBCC policy: for accepted On-mode normal or emergency deployment requests, deployment confirmation (or equivalent `OPEN_CONFIRMED` evidence) must be observed within `<=5 s`; otherwise verdict is fault (`TIMEOUT`, `JAM_DETECTED`, `PDM_FAULT`, `UNKNOWN`, etc.). Servo jam/no-open, brownout/reset, bad/stale IMU data, false-trigger profiles, and command-path faults do not create false success claims; deployment success requires `OPEN_CONFIRMED` backed by PDM feedback or independent safe-fixture/current/position observer evidence and mapped to OBCC `deployment_status`.
9. Evidence package includes source model version, UUT configuration, firmware commit/build, stimulus profiles, raw logs/traces/video, timing/accuracy analysis, environmental conditions, deviations, anomalies, waivers, limitations, and retest status.

## Deployment status/no-false-success semantics

Future PDM/OBCC tests shall map implementation-specific names to these controlled meanings for `PDM-VV-CE-004`, this activity, and related no-false-success closure. The same mapping feeds OBCC telemetry `deployment_status` in the OBCC-to-DPS frame.

| Code | Status | Meaning for PDM verification |
|---:|---|---|
| `0` | `NOT_COMMANDED` | No accepted deployment command for the current context. |
| `1` | `INHIBITED_STANDBY` | Request suppressed because OBCC is in Stand-by. |
| `2` | `COMMAND_SENT` | PWM/open command issued; not success by itself. |
| `3` | `OPEN_IN_PROGRESS` | Actuation underway, not confirmed. |
| `4` | `OPEN_CONFIRMED` | Feedback or independent observer confirms open; only strict success state. |
| `5` | `NO_OPEN_CONFIRMED` | Observer/feedback confirms no open after a command or branch. |
| `6` | `TIMEOUT` | Open confirmation missing within the declared timing window. |
| `7` | `JAM_DETECTED` | Jam, overcurrent, or blocked travel evidence. |
| `8` | `PDM_FAULT` | PDM fault or command path unavailable. |
| `9` | `UNKNOWN` | Cannot prove state; never count as success. |

Outline-level evidence options are servo feedback if implemented, PWM trace, current signature, position/witness mark, safe-fixture video, or explicit PDM feedback. `COMMAND_SENT`, `OPEN_IN_PROGRESS`, `NO_OPEN_CONFIRMED`, `TIMEOUT`, `JAM_DETECTED`, `PDM_FAULT`, `UNKNOWN`, and `INHIBITED_STANDBY` shall not be counted as successful deployment. Reports that feed OBCC/DPS shall preserve raw code/symbol/category and the PDM/actuator confirmation evidence for `OPEN_CONFIRMED`.

## Statistical and fault-hardening viewpoints

- Minimum development screening: `≥10` nominal trials plus the enumerated fault cases.
- R90/C95 release evidence requires predeclared independence/representativeness and `29/29` positive and `29/29` negative no-failure trials.
- 95/95 timing claims require `59/59` in-limit samples.
- Fault-hardening coverage includes bad/stale IMU data, I2C NACK/disconnect/stuck bus, false trigger profiles, servo jam/no-open, brownout/reset, and no-manual/BLE regression.

## Pre-execution readiness checklist

`PDM-BLK-005` is resolved at definition-planning level by requiring the following items before execution. Under project IVV report-by-reference rules, no execution credit is available until these are recorded in the report or controlled evidence archive:

- UUT article ID; PDM, ADS, and OBCC hardware revisions; backplane and harness configuration.
- Firmware commits, builds, and configuration for PDM, OBCC, and ADS; source/build maps where timing or source-analysis claims are made.
- IMU stimulus/replay set covering nominal trigger profiles, negative/no-trigger profiles, stale/bad data profiles, I2C NACK/disconnect/stuck bus cases, brownout/reset, servo jam/no-open, and no-manual/BLE regression cases.
- ADS input freshness/status evidence at the PDM/OBCC trigger observation point using the shared freshness contract: `VALID` only when `age_ms <= 400 ms`; `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL` are not normal triggers. Include consumer/request timestamps and clock-correlation IDs/method so cross-instrument timing can be reproduced.
- Angular-rate truth or robust-threshold evidence where relevant: calibrated motor/tachometer or equivalent, `deg/s = RPM x 6` if using RPM, `n = 59` all-in-limit samples for strict timing/accuracy claims, and uncertainty/guard-band handling.
- Timing instrumentation for I2C `<=5 ms`, process/calculate `<5 ms`, `<=5 s` deployment timing where applicable, no-blocking/heartbeat evidence, and instrumentation overhead handling.
- Equipment asset IDs, calibration/status, clock/timebase correlation IDs, environmental limits, safe fixture or live-release authorization, power conditions, evidence archive path, statistical claim type (development screening vs R90/C95 vs 95/95 timing), deviations, and waivers.

## Expected report/evidence location

Execution reports should reference this modeled definition and store evidence under:

- `tests/results/PDM-VV-FC-001/`

The report shall identify referenced model elements, selected SSIV/version, as-tested/as-analyzed configuration, raw evidence, actual conditions, pass/fail or blocked rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and execution records

- PDM v1.0 → flight readiness remains the selected target context.
- Traceability targets are controlled provisional IDs because explicit mission/capability/use-case/feared-event nodes are not present in the PDM v1.0 source views.
- The selected v1.0 terminal descent-speed criterion is `<= 11 m/s`; the existing `PDM-VV-FC-001` source/test D2 views carry this linkage, standalone `PDM-VV-FC-003` is model-defined, and execution evidence remains pending.
- OBCC owns emergency deployment, lost-observability, safe/error, and no-false-success policy; PDM-specific implementation/status field names are report-time mappings, but their meanings shall map to the controlled `deployment_status` enum above before any OBCC/DPS telemetry success claim.
- The pre-execution readiness checklist above is not execution evidence; reports must record it before credit.
