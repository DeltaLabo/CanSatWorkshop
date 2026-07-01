# PDM-VV-FC-001 — IMU-triggered parachute deployment verification definition

**Selected gate:** PDM v1.0 → flight readiness.
**IADT method:** Testing / Demonstration, with supporting Analysis and Inspection.
**Primary IVV source category:** functional chain/scenario, with linked component-exchange, allocation, component/link, and constraint coverage.
**Status:** Modeled definition ready for review; execution pending.

This package defines a model-based verification activity for the PDM v1.0 IMU-triggered parachute deployment path. The source model remains the authority for the system definition; these views add the verification means, equipment/human actors, environmental conditions, fault-hardening sequences, pass/fail constraints, evidence interfaces, and traceability expected for execution reports.

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
| Functional chain/scenario | IMU data → ADS processing → OBCC/PDM deployment evaluation → PWM open signal → servo open → holder separates → parachute unfolds → terminal-speed limiting evidence. |
| Component exchanges | Linked coverage for `[CE] I2C`, `[CE] Pointers/Returns`, `[CE] PWM`, `[CE] PWM` feedback/status, and `[CE] Torque`. |
| Allocation | ADS Kinematic Sensing, ADS Processing, OBCC, PDM Processing, Trigger, Parachute Holder, and Descent speed control functions are included. |
| Component/link | Supporting inspection of ADS/OBCC/backplane/parachute module PCs and deployment-relevant PLs before credited functional trials. |
| Constraints | Parachute diameter `≤30 cm`; angular-rate error `<30 deg/s` or robust thresholds; no manual/BLE open command; initial servo `0 degrees`/closed; I2C reads `≤5 ms`; process/calculate `<5 ms`; no blocking outside I2C; terminal-speed evidence linked. |

## Pass/fail rules

Pass only if all modeled criteria are satisfied and evidenced:

1. Nominal IMU-derived trigger profile produces exactly one complete ordered deployment chain.
2. Negative/non-deploy profiles and manual/BLE attempts do not produce a flight-mode open command.
3. I2C reads succeed or time out within `≤5 ms`; I2C fault cases are bounded and reported.
4. Process/calculate functions complete in `<5 ms`; no unexpected blocking outside modeled I2C communications.
5. Startup/reset servo position is `0 degrees`/closed; no open pulse occurs before the deployment condition.
6. Angular-rate error is `<30 deg/s` or deployment thresholds are analyzed robust to that error.
7. Parachute diameter is `≤30 cm`; terminal-speed limiting evidence is recorded or linked.
8. Servo jam/no-open, brownout/reset, bad/stale IMU data, and false-trigger profiles do not create false success claims.
9. Evidence package includes source model version, UUT configuration, firmware commit/build, stimulus profiles, raw logs/traces/video, timing/accuracy analysis, environmental conditions, deviations, anomalies, waivers, limitations, and retest status.

## Statistical and fault-hardening viewpoints

- Minimum development screening: `≥10` nominal trials plus the enumerated fault cases.
- R90/C95 release evidence requires predeclared independence/representativeness and `29/29` positive and `29/29` negative no-failure trials.
- 95/95 timing claims require `59/59` in-limit samples.
- Fault-hardening coverage includes bad/stale IMU data, I2C NACK/disconnect/stuck bus, false trigger profiles, servo jam/no-open, brownout/reset, and no-manual/BLE regression.

## Expected report/evidence location

Execution reports should reference this modeled definition and store evidence under:

- `tests/results/PDM-VV-FC-001/`

The report shall identify referenced model elements, selected SSIV/version, as-tested/as-analyzed configuration, raw evidence, actual conditions, pass/fail or blocked rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and open items

- The issue file selects PDM v1.0 → flight readiness, so no user disambiguation was required.
- Traceability targets are provisional IDs because explicit mission/capability/use-case/feared-event nodes are not present in the PDM v1.0 source views.
- The v1.0 model does not define a numeric descent-speed requirement; this definition records or links terminal-speed limiting evidence and treats the missing numeric limit as a report limitation unless a project requirement is confirmed before execution.
- Final UUT ID, hardware revision, firmware commit/build, exact IMU profiles, equipment model/serial/calibration IDs, and statistical claim type must be fixed before execution.
