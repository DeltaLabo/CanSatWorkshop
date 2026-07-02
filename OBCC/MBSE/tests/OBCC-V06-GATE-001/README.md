# OBCC-V06-GATE-001 — v0.6 runtime fault-handling advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V06-GATE-001`
- **SSIV / version gate:** OBCC `v0.6 -> v0.7`
- **Chosen pending activity for this session:** Issue 006, runtime fault injection, bounded error/result codes, health telemetry disclosure, and non-blocking scheduler advancement.
- **IADT method(s):** Inspection + Analysis + Testing. Inspection is included to satisfy IVV component/link minimums; the issue-requested primary methods are Testing + Analysis.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** `OBCC-UC-RuntimeFaultHandling`, `OBCC-FE-SchedulerBlocked`, `OBCC-FE-NonDeployment`, `OBCC-FE-LostTelemetry`, and runtime fault constraint families `OBCC-VV-CON-004` / `OBCC-VV-CON-005`.
- **Existing v1.0 verification-row mapping:** `OBCC-VV-FC-005`, `OBCC-VV-CON-004`, and `OBCC-VV-CON-005`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V06-GATE-001/`.
- **Execution status:** modeled definition complete; execution and report evidence pending.

The absence of a `v0.6` Capella/D2 source baseline is an accepted OBCC lifecycle/modeling decision, not a blocker: versions may jump from `v0.x` to `v1.0`, and the mostly software-dependent subsystem was not complex enough to require incremental source-model deliveries. This definition uses copied `v1.0` runtime fault-handling, logical, allocation, telemetry, deployment, and physical views only as target-behavior context for the v0.6 advancement gate; execution reports must identify the actual `v0.6` code/configuration baseline used and acknowledge the target-context-only model reference where applicable. Do not fabricate a `v0.6` source baseline.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements and derived runtime-fault requirement: `OBCC/README.md`
- OBCC deployment/fault policy: `OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md`
- OBCC/DPS telemetry contract: `PM&SE/contracts/obcc_dps_lora_telemetry_contract.md`
- LoRa frame/peripheral context: `OBCC/LoRa_Frame.md`
- Getter/result-code API and runtime health-code context: `OBCC/Variable_Getter_Template.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.6/` per the accepted lifecycle disposition; the `v1.0` copies are target context only.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V06-GATE-001_view1_test_physical_setup.d2` | `OBCC-V06-GATE-001_view1_test_physical_setup.png` | UUT, XIAO/RFM96W context, fault-injection ports, RTOS trace hook, health/mode/emergency/safe-error probes, trace/RF/power/reset bench equipment, ambient thermometer, and physical setup constraints. |
| PV2 logical interfaces | `OBCC-V06-GATE-001_view2_test_logical_interfaces.d2` | `OBCC-V06-GATE-001_view2_test_logical_interfaces.png` | Test operator, safety observer, fault injectors, trace/timing collector, RF/health monitor, bus timeout/mutex protection, getters, scheduler/queue monitor, health telemetry, emergency policy, and safe/error component exchanges. |
| PV3 functional allocation | `OBCC-V06-GATE-001_view3_test_functional_allocation.d2` | `OBCC-V06-GATE-001_view3_test_functional_allocation.png` | Human/operator functions, fault injection, RTOS trace, RF monitor, power/reset, ambient measurement, and verification-only UUT functions introduced for fault handling and liveness evidence. |
| Functional chain — bounded codes | `OBCC-V06-GATE-001_view4_fault_injection_bounded_codes_chain.d2` | `OBCC-V06-GATE-001_view4_fault_injection_bounded_codes_chain.png` | I2C/UART/SPI/radio/queue fault injection sequence proving bounded result/error codes, `<=5 ms` read timeouts where applicable, health telemetry disclosure, and no unbounded queueing. |
| Functional chain — scheduler/emergency policy | `OBCC-V06-GATE-001_view5_scheduler_liveness_emergency_policy_chain.d2` | `OBCC-V06-GATE-001_view5_scheduler_liveness_emergency_policy_chain.png` | Concurrent runtime fault/load sequence proving scheduler liveness, bounded telemetry degradation, On/Stand-by emergency-deploy request policy, and safe/error behavior for critical runtime faults. |

All five verification D2 files were rendered with the required `d2 --layout=elk` command and ELK spacing flags; `d2` reported successful compilation for every PNG.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V06-GATE-001-I01` | v0.6 -> v0.7 | Runtime-fault UUT, XIAO ESP32-S3, RFM96W, bus-fault ports, RTOS queue/state trace hook, health/status telemetry output, mode-gate probe, emergency-deploy request probe, safe/error-state probe, test-bench fault injectors, trace/timing collector, RF monitor, bench power/reset, ambient thermometer | Component/link; constraint | Inspection | `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-SchedulerBlocked`; setup integrity constraints | Stat: 100% inspection of the integrated test article and test means. Fault hardening: probes attached before injecting faults; no live deployment hazard; current-limited power/reset and RF/trace evidence paths present. | `PF-001`, `PF-010` | PV1, PV3; expected report `results/OBCC-V06-GATE-001/inspection.md` | Definition ready; execution pending |
| `OBCC-V06-GATE-001-A01` | v0.6 -> v0.7 | I2C/UART/SPI/radio fault interfaces, bus timeout/mutex protection, variable getter wrapper, scheduler/queue/state monitor, health telemetry publisher, command/state manager, emergency-deploy policy gate, safe/error-state manager | Component exchange; allocation; constraint | Analysis | `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-SchedulerBlocked`; `OBCC-FE-LostTelemetry`; `OBCC-VV-CON-004`; `OBCC-VV-CON-005` | Stat: 100% interface/allocation review for the modeled runtime-fault path before trial execution. Fault hardening: no unmodeled blocking call or deployment bypass; all fault classes have a bounded status and observable evidence path. | `PF-002`, `PF-005`, `PF-006`, `PF-008`, `PF-009` | PV2, PV3; expected report `results/OBCC-V06-GATE-001/interface_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V06-GATE-001-T01` | v0.6 -> v0.7 | Variable getters, I2C/UART/SPI/radio driver paths, bus mutex, timeout counters, runtime fault classifier, stale/missing-value replacement, health/status telemetry, trace/RF evidence | Functional chain/scenario; component exchange; constraint | Testing / Analysis | `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-SchedulerBlocked`; `OBCC-FE-LostTelemetry`; `OBCC-VV-FC-005`; `OBCC-VV-CON-004` | Stat: plan `59/59` in-limit timeout samples per applicable getter/fault class where feasible for 95/95 timing claims; fault-class trials classified pass/fail. Fault hardening: I2C NACK/stuck bus, UART silence/malformed/late frame, SPI radio busy/status fault, RF loss, queue/state fault. | `PF-002`, `PF-003`, `PF-004`, `PF-010` | PV2, PV3, bounded-code chain; expected report `results/OBCC-V06-GATE-001/bounded_codes_timeouts.md` | Definition ready; execution pending |
| `OBCC-V06-GATE-001-T02` | v0.6 -> v0.7 | FreeRTOS scheduler heartbeat, queue depth/overflow, state/mode gate, shared-bus mutex holds, telemetry enqueue/send path, telemetry cadence and worst-gap evidence | Functional chain/scenario; allocation; constraint | Testing / Analysis | `OBCC-FE-SchedulerBlocked`; `OBCC-FE-LostTelemetry`; `OBCC-VV-CON-004` | Stat: sustained-performance evidence records every interval and worst gap; repeated samples on one article are screening unless independence is justified. Fault hardening: deadlock, priority inversion, queue overflow, stale state, watchdog/reset, telemetry backlog. | `PF-005`, `PF-006`, `PF-007`, `PF-010` | PV2, PV3, bounded-code chain, scheduler/emergency-policy chain; expected report `results/OBCC-V06-GATE-001/scheduler_liveness.md` | Definition ready; execution pending |
| `OBCC-V06-GATE-001-T03` | v0.6 -> v0.7 | Descent-state observability loss, On/Stand-by state metadata, emergency-deploy policy gate, PDM gate context, runtime radio/deployment/power critical faults, safe/error-state manager, health/status and `deployment_status` telemetry/trace disclosure | Functional chain/scenario; constraint | Testing / Analysis | `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-NonDeployment`; `OBCC-FE-LostTelemetry`; `OBCC-VV-CON-005` | Stat: classify each policy/fault trial pass/fail; separate Stand-by and On-mode equivalence classes; do not pool emergency-policy evidence unless the report justifies common causality. Fault hardening: lost descent observability, conflicting mode state, radio loss, deployment-path fault, safe power fault, false safe/success telemetry; `TIMEOUT`, `JAM_DETECTED`, `PDM_FAULT`, and `UNKNOWN` are not deployed. | `PF-008`, `PF-009`, `PF-010` | PV2, PV3, scheduler/emergency-policy chain; expected report `results/OBCC-V06-GATE-001/emergency_policy_safe_error.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — setup/component/link inspection:** OBCC controller, RFM96W, bus/protocol fault-injection ports, RTOS queue/state trace hook, health/status telemetry output, mode-gate probe, emergency-deploy request probe, safe/error-state probe, fault-injection rack, trace/timing collector, RF monitor, bench power/reset controller, ambient thermometer, test operator, and safety observer are present, identified, connected as modeled, and dispositioned before fault injection.
- **PF-002 — fault-class coverage and bounded result codes:** every declared I2C, UART, SPI/radio, RF, queue/state, mode-gate, power, and deployment-path fault case returns a bounded result/error code or modeled safe/error result. No function may hang, spin indefinitely, or return an unbounded/unmodeled status.
- **PF-003 — read timeout constraint:** faulted I2C/UART read attempts meet `<=5 ms` where applicable. SPI/radio busy/status faults are bounded by the modeled driver result. Timeout timing is measured at getter/driver entry and return, not inferred only from telemetry.
- **PF-004 — health/status disclosure:** injected runtime faults update health/status telemetry and/or local trace evidence with fault class, result/error code, stale/missing-value marker, degraded-mode status, `deployment_status` where deployment-path interpretation is affected, and recovery/reset marker. Missing disclosure is a failure unless the only path under test is an RF-loss case and local trace preserves the evidence.
- **PF-005 — scheduler liveness:** no FreeRTOS task, ISR path, queue, mutex, getter, mode gate, or telemetry path remains unboundedly blocked. Watchdog reset, blocked-task assertion, permanently held mutex, permanently full queue, or unrecoverable scheduler starvation is a failure unless explicitly expected by the safe/error-state scenario.
- **PF-006 — shared-bus and allocation consistency:** shared bus protection, queue ownership, state/mode-gate ownership, getter ownership, telemetry ownership, emergency-policy ownership, and safe/error ownership match the modeled allocation and component exchanges. No unmodeled bypass may command deployment or suppress health reporting.
- **PF-007 — bounded telemetry degradation:** nominal telemetry target remains the modeled `2 s` cadence. For non-RF getter/bus faults, the worst inter-frame gap shall not exceed two scheduled intervals (`<=4 s`) without an anomaly record. For RF-loss/radio-fault trials, internal send attempts and local trace must show bounded behavior, and the first post-fault health frame after RF restoration must disclose the fault/recovery within two scheduled intervals.
- **PF-008 — emergency-deploy policy:** emergency deploy request is issued only when descent-state observability is lost or another modeled safety condition applies, and only when the On/Stand-by policy permits it. Stand-by inhibits the request. Any request from an invalid condition or any missing request in a modeled On-mode safety condition is a failure.
- **PF-009 — safe/error behavior and no false deployed status:** runtime radio, deployment-path, or power critical faults may enter safe/error behavior, but the transition, reason, and observable state must be traceable. The system must not masquerade as a normal successful run after a critical safe/error condition. Deployment-path fault evidence shall map to `TIMEOUT`, `JAM_DETECTED`, `PDM_FAULT`, `UNKNOWN`, or another controlled non-success status unless independent PDM/actuator evidence confirms `OPEN_CONFIRMED`; `COMMAND_SENT` and `OPEN_IN_PROGRESS` are not deployed.
- **PF-010 — evidence, environment, and statistics:** before repetitions, record calibrated ambient thermometer model/serial and reading, UUT hardware identity, firmware/configuration IDs, fault-injector configuration, RF monitor settings, trace clock synchronization, power/reset settings, and as-tested wiring. Timeout claims use the project `59/59` in-limit 95/95 planning point where feasible; smaller or non-independent sets are v0.6 advancement characterization only.

## Statistics and fault-hardening viewpoints

- This is a `v0.6 -> v0.7` advancement gate, not final v1.0 flight-readiness closure.
- Timeout evidence should target `59/59` in-limit samples per applicable getter/fault class for a 95/95 non-parametric deadline claim. Smaller samples are characterization and must be labeled as such.
- Fault-injection success is classified by declared equivalence class: I2C NACK/stuck bus, UART silence/malformed/late frame, SPI radio busy/status fault, RF loss, queue overflow, stale state/message, mode-gate delay, safe power fault, deployment-path critical fault, and recovery/restoration. For deployment-path classes, the report shall predeclare the expected `deployment_status` code/symbol/category sequence and any local-trace correlation method.
- Telemetry cadence evidence records interval distribution, worst gap, stale/dropped frames, result codes, and health/status flags. Repeated intervals on one article are sustained-performance evidence, not automatically independent reliability trials.
- Emergency-policy evidence separates Stand-by inhibit and On-mode emergency-request cases. The report must not pool cases unless it justifies common control logic and comparable fault stimulus. `INHIBITED_STANDBY` and `NOT_COMMANDED` are non-deployed outcomes, not missing evidence.
- Fault-hardening emphasis: deadlock, priority inversion, stuck bus, malformed serial data, radio busy/loss, queue overflow, stale mode/state data, lost descent-state observability, lost telemetry, non-deployment, premature-deployment prevention, and safe/error diagnosability.

## Verification-row mapping and coverage notes

- **`OBCC-VV-FC-005`:** modeled by `OBCC-V06-GATE-001-T01/T02/T03` with verification means, injected fault classes, expected bounded codes, health/status evidence, pass/fail constraints, statistical interpretation, and scheduler/emergency-policy fault-hardening viewpoints added to the v1.0 runtime fault-handling chain.
- **`OBCC-VV-CON-004`:** modeled by `OBCC-V06-GATE-001-I01/A01/T01/T02`, covering bounded getter/result codes, I2C/UART `<=5 ms` timeout evidence where applicable, shared-bus/mutex protection, queue/state/mode-gate liveness, startup-policy context, and no unbounded scheduler blocking. Full startup-health closure remains covered by the startup-health activity rather than this runtime gate.
- **`OBCC-VV-CON-005`:** modeled by `OBCC-V06-GATE-001-A01/T03`, covering runtime radio/deployment/power critical safe/error behavior, telemetry/trace diagnosability, and emergency-deploy request policy when sensor faults remove descent-state observability.
- Related context only: this activity analyzes the runtime-fault-relevant portions of software component exchanges and functional allocation. It does **not** claim full closure of broader v1.0 `OBCC-VV-CE-003` or `OBCC-VV-ALLOC-*` rows.

## Assumptions and gaps for feedback

- Lifecycle disposition: no `v0.6` Capella/D2 source baseline is required or fabricated; copied v1.0 views are target context only, and the report identifies the actual v0.6 code/configuration baseline.
- Exact v0.6 fault-injection hooks, getter result-code enumeration beyond the generic `Variable_Getter_Template.md`, queue/state thresholds, watchdog behavior, and safe/error state encoding are not controlled in the repository artifacts read here.
- The `<=4 s` telemetry-gap bound in `PF-007` is a v0.6 gate constraint derived from the modeled `2 s` telemetry cadence; confirm or tailor it before execution if a different degradation allowance is intended.
- Emergency-deploy policy details, descent-state observability criteria, actuator-status mapping, and safe/error interaction are controlled by `OBCC-V10_Deployment_Fault_Policy.md`; execution still records implementation-specific field mappings and deviations.
- Safe power/deployment-path fault-injection methods, RF monitor configuration, ambient thermometer model/calibration, parser/decoder version, telemetry status-byte mapping, and trace-clock synchronization method are execution records that must be recorded before strict credit.
- The `LoRa_Frame.md` peripheral list and v1.0 model use the selected `RFM96W` radio and `ICM20948` IMU names; execution must record the actual fitted hardware.
- Statistical independence of repeated runtime-fault trials is not established by the model; reports must avoid overstating reliability if trials share one article, fixture, or unchanged software state.
- This was a non-interactive subagent run; needed feedback is captured here instead of requested live.
