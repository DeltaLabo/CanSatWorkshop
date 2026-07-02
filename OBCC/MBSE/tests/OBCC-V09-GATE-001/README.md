# OBCC-V09-GATE-001 — End-to-end mission-window rehearsal advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V09-GATE-001`
- **SSIV / version gate:** OBCC `v0.9 -> v1.0`
- **Chosen pending activity for this session:** Issue 009, integrated mission-window rehearsal before final v1.0 flight-readiness closure.
- **IADT method(s):** Demonstration + Testing, with Inspection and Analysis hooks.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** `OBCC-UC-StartupHealth`, `OBCC-UC-TelemetryDownlink`, `OBCC-UC-WirelessCommand`, `OBCC-UC-DeploymentGate`, `OBCC-UC-RuntimeFaultHandling`; feared events `OBCC-FE-SilentCriticalFault`, `OBCC-FE-LostTelemetry`, `OBCC-FE-InvalidCommand`, `OBCC-FE-PrematureDeployment`, `OBCC-FE-NonDeployment`, `OBCC-FE-SchedulerBlocked`.
- **Existing v1.0 candidate mapping:** primary `OBCC-VV-FC-006`; regression evidence hooks to `OBCC-VV-FC-001` through `OBCC-VV-FC-005`, plus constraint hooks `OBCC-VV-CON-001` through `OBCC-VV-CON-005`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`.
- **Execution status:** modeled definition complete; execution and evidence report pending.

No `v0.9` Capella/D2 source views exist in this repository. This definition uses copied `v1.0` physical, logical, functional-allocation, and functional-chain views as target-behavior context for the `v0.9 -> v1.0` advancement gate. Source files under `OBCC/MBSE/v1.0/` were not edited.

## References

- Project IVV and statistical policy: `PM&SE/IVV.md`
- OBCC requirements and success criteria: `OBCC/README.md`
- LoRa payload/peripheral context: `OBCC/LoRa_Frame.md`
- Getter/result-code and timing context: `OBCC/Variable_Getter_Template.md`
- OBCC v1.0 IVV planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs:

1. `OBCC_v1.0_view1_physical.*`
2. `OBCC_v1.0_view2_logical.*`
3. `OBCC_v1.0_view3_functional_allocation.*`
4. `OBCC_v1.0_view4_startup_health_chain.*`
5. `OBCC_v1.0_view5_telemetry_downlink_chain.*`
6. `OBCC_v1.0_view6_command_state_chain.*`
7. `OBCC_v1.0_view7_deployment_gating_chain.*`
8. `OBCC_v1.0_view8_runtime_fault_handling_chain.*`

There is no `source_views/v0.9/` because no v0.x Capella/D2 baseline is present in the repository.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V09-GATE-001_view1_mission_rehearsal_physical_setup.d2` | `OBCC-V09-GATE-001_view1_mission_rehearsal_physical_setup.png` | UUT, ground station, ground PC, verification-only evidence workstation, current-limited service harness, RF monitor, ambient/weather recorder, deployment safety fixture, evidence archive, and physical pass/fail constraints for the rehearsal setup. |
| PV2 logical interfaces | `OBCC-V09-GATE-001_view2_mission_rehearsal_logical_interfaces.d2` | `OBCC-V09-GATE-001_view2_mission_rehearsal_logical_interfaces.png` | Component-exchange and allocation-analysis context across startup health, telemetry downlink, command/state, deployment gating, runtime fault injection, evidence, timing, configuration, RF, and ambient/weather logs. |
| PV3 functional allocation | `OBCC-V09-GATE-001_view3_mission_rehearsal_functional_allocation.d2` | `OBCC-V09-GATE-001_view3_mission_rehearsal_functional_allocation.png` | Human/operator functions, test-equipment functions, verification-only workstation functions, and UUT functions allocated to the OBCC/ground logical components used by the mission-window rehearsal. |
| Functional chain — mission-window rehearsal | `OBCC-V09-GATE-001_view4_mission_window_rehearsal_chain.d2` | `OBCC-V09-GATE-001_view4_mission_window_rehearsal_chain.png` | End-to-end sequence from configuration/environment capture through pre-test inspection, boot, Stand-by telemetry, invalid-command challenge, On command, telemetry evidence, deployment no-trigger/trigger branches, selected safe fault injection/recovery, evidence export, oracle comparison, and gate decision. |

All four verification D2 files were rendered with the required `d2 --layout=elk` command and ELK spacing flags; `d2` reported successful compilation for every PNG.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V09-GATE-001-I01` | v0.9 -> v1.0 | Rehearsal-critical physical components and links: integrated CanSat, OBCC PCB/XIAO/RFM96W/backplane connector, source-module header context, ground station, ground PC, evidence workstation, service harness, RF monitor, deployment safety fixture, ambient/weather recorder, evidence archive | Component/link; constraint | Inspection | `OBCC-UC-StartupHealth`; integration readiness; `OBCC-FE-LostTelemetry`; `OBCC-FE-PrematureDeployment`; `OBCC-FE-NonDeployment` | Stat: 100% pre-test inspection of rehearsal-critical modeled PCs/PLs for the gate article. Fault hardening: antenna/dummy-load safety, current limit, connector retention, safe deployment fixture, no shorts/loose deployment links/uncontrolled substitutions. | `PF-001`, `PF-002`, `PF-008`, `PF-010` | PV1, PV3, chain; expected report `results/OBCC-V09-GATE-001/pretest_inspection.md` | Definition ready; execution pending |
| `OBCC-V09-GATE-001-A01` | v0.9 -> v1.0 | v1.0 source-view copies; missing v0.9 source baseline; logical interfaces for I2C/UART/SPI/PWM/LoRa/Payload/Command/Getters/Queue/State/Mode gate/IMU-alt/evidence; function-to-LC allocation used by the rehearsal | Component exchange; allocation; constraint | Analysis | `OBCC-VV-FC-006`; all five OBCC use cases; `OBCC-FE-SchedulerBlocked` | Stat: 100% CE-by-CE and allocation review for elements used by this rehearsal; no reliability inference. Fault hardening: hidden bypass, foreign allocation, mismatched protocol direction, missing evidence interface, undispositioned v0.9/v1.0 source delta. | `PF-001`, `PF-004`, `PF-005`, `PF-007`, `PF-008`, `PF-009` | PV2, PV3, chain; expected report `results/OBCC-V09-GATE-001/interface_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V09-GATE-001-D01` | v0.9 -> v1.0 | Integrated mission-window sequence across startup health, Stand-by heartbeat/telemetry, valid On command, telemetry downlink/decode/store, ground evidence, deployment no-trigger and safe-trigger branches | Functional chain/scenario; constraint | Demonstration | `OBCC-UC-StartupHealth`; `OBCC-UC-TelemetryDownlink`; `OBCC-UC-WirelessCommand`; `OBCC-UC-DeploymentGate`; `OBCC-FE-LostTelemetry`; `OBCC-FE-PrematureDeployment`; `OBCC-FE-NonDeployment` | Stat: integrated demonstration is SSIV advancement evidence only unless independent repetitions justify stronger claims. Timing/PDR claims must use project IVV counts/bounds. Fault hardening: no silent critical fault, no lost mandatory telemetry/evidence path, no unintended deployment, no missed On-mode required deployment. | `PF-003`, `PF-004`, `PF-005`, `PF-006`, `PF-008`, `PF-009`, `PF-010` | PV1-PV3, chain; expected report `results/OBCC-V09-GATE-001/mission_window_rehearsal.md` | Definition ready; execution pending |
| `OBCC-V09-GATE-001-T01` | v0.9 -> v1.0 | Selected safe fault injections: invalid/corrupt command challenge, safe getter timeout/NACK or sensor-result-code fault, RF/frame disturbance where safe, recovery or safe/error persistence | Functional chain/scenario; component exchange; constraint | Testing | `OBCC-UC-WirelessCommand`; `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-InvalidCommand`; `OBCC-FE-SchedulerBlocked`; `OBCC-FE-SilentCriticalFault` | Stat: each fault trial is pass/fail classified; no reliability claim unless independent count is planned. Fault hardening: bounded result codes, health telemetry disclosure, no FreeRTOS scheduler block, correct emergency-deploy/safe-error policy, no invalid-command state transition. | `PF-005`, `PF-007`, `PF-008`, `PF-009`, `PF-010` | PV2, PV3, chain; expected report `results/OBCC-V09-GATE-001/fault_injection_recovery.md` | Definition ready; execution pending |
| `OBCC-V09-GATE-001-A02` | v0.9 -> v1.0 | Evidence package, as-tested configuration, statistics interpretation, unresolved gaps/waivers, regression oracle mapping to `OBCC-VV-FC-001`..`005` and primary `OBCC-VV-FC-006` | Constraint; functional chain/scenario; SSIV completeness | Analysis | `OBCC-VV-FC-006`; all listed use cases and feared events; v1.0 advancement closure | Stat: report must separate integration demonstration from reliability/PDR/deadline claims. Use exact binomial/tolerance calculations only when sample independence/counts support them. Fault hardening: no open safety-critical gap, no unreferenced evidence, deviations dispositioned. | `PF-001`, `PF-008`, `PF-009`, `PF-010` | Chain, README, expected report `results/OBCC-V09-GATE-001/closure_analysis.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — source/configuration identity:** UUT serial/revision, firmware/commit/configuration, radio settings, copied v1.0 source-view references, test equipment IDs/calibration status, and missing v0.9 source-baseline gap are recorded before any pass/fail classification.
- **PF-002 — pre-test physical safety:** 100% of rehearsal-critical components and links are present, connected, retained, and safe; antenna or dummy load, current limit, deployment fixture, evidence links, and connector retention are confirmed before powered rehearsal. Unresolved shorts, loose deployment links, unsafe RF path, or undispositioned substitutions fail the gate.
- **PF-003 — startup health:** nominal boot reaches Stand-by telemetry/heartbeat; startup-critical RFM96W, BME280, and Servo checks pass. Any critical startup fault blocks operational mode; non-critical faults are telemetry-visible and degraded only.
- **PF-004 — telemetry downlink:** Stand-by and On telemetry continue at the modeled 2 s cadence; frames use the v1.0 payload without relative humidity; downlinked frames are decoded, displayed, stored, and traceable to RF/timing evidence. `>=500 m` and `>=90%` PDR claims require independent packet evidence and exact one-sided confidence bounds.
- **PF-005 — command/state behavior:** valid On and Stand-by commands change state exactly once and appear in telemetry. Invalid/corrupt/duplicate/out-of-context commands do not change state, do not deploy, and are recorded in health/status evidence.
- **PF-006 — deployment gating:** Stand-by never produces an open-servo command, including emergency-deploy requests. In On mode, a valid trigger or safe emergency-request proxy produces an open command/fixture travel within `<=5 s`; the no-trigger branch remains closed.
- **PF-007 — runtime fault hardening:** selected safe I2C/UART/SPI/getter/RF/sensor faults return bounded result codes or health flags, do not block FreeRTOS scheduling, and follow the modeled emergency-deploy/safe-error policy. Forbidden events include scheduler hang, silent critical fault, premature deployment, non-deployment under required trigger, and lost evidence.
- **PF-008 — evidence completeness:** reports reference the modeled definition and record actual results, as-tested configuration, raw telemetry/CSV/RF/timing/photo/video evidence, deviations, anomalies, waivers, and pass/fail rationale under `tests/results/OBCC-V09-GATE-001/`.
- **PF-009 — statistical interpretation:** this mission rehearsal is integration demonstration/testing evidence and shall not overclaim reliability. Use project IVV statistical policy when a stronger claim is made: e.g., 29/29 for R90/C95 binary screening, 59/59 for 95/95 timing limits, and exact binomial bounds for PDR.
- **PF-010 — environmental/fault context:** ambient/weather instruments, range geometry, RF settings, power state/current limit, fixture state, and selected fault profiles are formalized as evidence-producing means and recorded before interpretation.

## Statistics and fault-hardening viewpoints

- This is a `v0.9 -> v1.0` advancement rehearsal, not final v1.0 flight-readiness closure by itself.
- Statistical significance is limited to the executed sample plan. A single integrated rehearsal supports integration behavior evidence only. Repeated samples must be classified for independence before being used for reliability, PDR, or deadline confidence claims.
- Packet delivery evidence must use exact one-sided binomial / Clopper-Pearson lower bounds if claiming `PDR >= 0.90`; `96/100` valid frames is a useful planning point but still requires as-executed context.
- Timing/deadline evidence such as `<=5 s` deployment and 2 s cadence requires representative samples; `59/59` in-limit samples supports a 95/95 non-parametric one-sided tolerance claim under the project IVV policy.
- Fault-hardening emphasis: combined-load behavior, RF loss/degraded PDR, invalid command rejection, stale/timeout getter values, bounded result codes, scheduler liveness, Stand-by deployment inhibition, On-mode required deployment, recovery/safe-error behavior, and evidence continuity.
- Safety-critical forbidden events for this gate: silent critical startup fault, loss of mandatory telemetry/evidence path without disposition, invalid-command state change/deployment, premature deployment, non-deployment under required On-mode trigger, unbounded scheduler blocking, and unresolved safety gap entering v1.0.

## Candidate mapping and coverage notes

- **`OBCC-VV-FC-006`:** directly modeled by `OBCC-V09-GATE-001-D01/T01/A02` as the end-to-end mission-window rehearsal and closure analysis.
- **`OBCC-VV-FC-001` startup health:** regression evidence from `startup_health` and `publish_standby_health` in the chain, with `PF-003` and pre-test inspection support.
- **`OBCC-VV-FC-002` telemetry downlink:** regression evidence from Stand-by/On downlink, RF logging, payload schema check, CSV/dashboard storage, and `PF-004`.
- **`OBCC-VV-FC-003` command/state:** regression evidence from invalid-command challenge, valid On command, state metadata, and `PF-005`.
- **`OBCC-VV-FC-004` deployment gating:** regression evidence from Stand-by inhibit, On no-trigger branch, safe trigger/emergency proxy branch, fixture travel/timing, and `PF-006`.
- **`OBCC-VV-FC-005` runtime fault handling:** regression evidence from selected safe fault injection/recovery and `PF-007`.
- Constraint families `OBCC-VV-CON-001` through `OBCC-VV-CON-005` are assigned to the chain through `PF-004` through `PF-007` and the statistical/evidence constraints `PF-008` through `PF-010`.

## Assumptions and gaps for feedback

- No v0.9 Capella/D2 source baseline is present; copied v1.0 views are target context only.
- Exact v0.9 hardware revision, firmware commit/configuration, radio settings, RF monitor model, weather instruments, deployment fixture model, and calibrated timing source are not controlled in the repository artifacts read here.
- The source context and `LoRa_Frame.md` use the selected `RFM96W` radio and `ICM20948` IMU names; execution must still record the actual fitted hardware and configuration baseline.
- The safe fault-injection matrix must be selected before execution to avoid damaging hardware or creating unsafe deployment behavior.
- The exact emergency-deploy policy and actuator status semantics still need confirmation for final v1.0 closure; this rehearsal records observed behavior but does not replace final safety-policy review.
- This was a non-interactive subagent run; needed feedback is captured here instead of requested live.
