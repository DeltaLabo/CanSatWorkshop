# OBCC-V05-GATE-001 — v0.5 deployment-gating advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V05-GATE-001`
- **SSIV / version gate:** OBCC `v0.5 -> v0.6`
- **Chosen pending activity for this session:** Issue 005, safe deployment gating before runtime fault-hardening maturity.
- **IADT method(s):** Inspection + Analysis + Demonstration + Testing. The issue-requested primary methods are Testing + Demonstration + Analysis; Inspection is included to satisfy IVV component/link minimums.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** `OBCC-UC-DeploymentGate`, `OBCC-FE-PrematureDeployment`, `OBCC-FE-NonDeployment`, and deployment constraint family `OBCC-VV-CON-003`.
- **Existing v1.0 candidate mapping:** `OBCC-VV-FC-004` and `OBCC-VV-CON-003`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V05-GATE-001/`.
- **Execution status:** modeled definition complete; execution and report evidence pending.

The absence of a `v0.5` Capella/D2 source baseline is an accepted OBCC lifecycle/modeling decision, not a blocker: versions may jump from `v0.x` to `v1.0`, and the mostly software-dependent subsystem was not complex enough to require incremental source-model deliveries. This definition uses copied `v1.0` deployment, runtime-fault, logical, allocation, telemetry, and physical views only as target-behavior context for the v0.5 advancement gate; execution reports must identify the actual `v0.5` code/configuration baseline used and acknowledge the target-context-only model reference where applicable. Do not fabricate a `v0.5` source baseline.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements and deployment timing requirement: `OBCC/README.md`
- LoRa frame/peripheral context: `OBCC/LoRa_Frame.md`
- Getter/result-code context for telemetry-visible runtime faults: `OBCC/Variable_Getter_Template.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.5/` per the accepted lifecycle disposition; the `v1.0` copies are target context only.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V05-GATE-001_view1_test_physical_setup.d2` | `OBCC-V05-GATE-001_view1_test_physical_setup.png` | UUT, OBCC controller, ADS trigger-data harness, PDM/PWM/servo actuation path, safe actuator surrogate, current shunt, test-bench equipment, ambient thermometer, and physical links/safety constraints. |
| PV2 logical interfaces | `OBCC-V05-GATE-001_view2_test_logical_interfaces.d2` | `OBCC-V05-GATE-001_view2_test_logical_interfaces.png` | Mode gate, ADS IMU/alt trigger adapter, emergency-request handler, deployment gate/PDM processing, servo PWM driver, actuator feedback adapter, telemetry publisher, and test-equipment component exchanges. |
| PV3 functional allocation | `OBCC-V05-GATE-001_view3_test_functional_allocation.d2` | `OBCC-V05-GATE-001_view3_test_functional_allocation.png` | Human/operator functions, safety observer, trigger simulator, servo current/position observer, trace logger, bench reset controller, ambient thermometer, and verification-only UUT functions. |
| Functional chain — Stand-by inhibit | `OBCC-V05-GATE-001_view4_standby_inhibit_chain.d2` | `OBCC-V05-GATE-001_view4_standby_inhibit_chain.png` | Stand-by valid-trigger and emergency-request sequences proving no open command/current/position while telemetry continues. |
| Functional chain — On-mode opening | `OBCC-V05-GATE-001_view5_onmode_opening_chain.d2` | `OBCC-V05-GATE-001_view5_onmode_opening_chain.png` | On-mode valid ADS trigger and modeled emergency-request sequences proving observed safe-actuator open position within `<=5 s`. |
| Functional chain — fault hardening | `OBCC-V05-GATE-001_view6_fault_hardening_chain.d2` | `OBCC-V05-GATE-001_view6_fault_hardening_chain.png` | Invalid trigger/emergency, missing/stale ADS data, reset-during-actuation, and servo current/position fault sequences with no false success. |

All six verification D2 files were re-rendered with the required `d2 --layout=elk` command and ELK spacing flags; `d2` reported successful compilation for every PNG.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V05-GATE-001-I01` | v0.5 -> v0.6 | OBCC/PDM deployment-gate UUT, XIAO/RFM96W context, ADS stimulus harness, emergency injection port, PWM/open-command test point, servo connector, current shunt, instrumented servo/actuator surrogate, test-bench equipment, ambient thermometer | Component/link; constraint | Inspection | `OBCC-UC-DeploymentGate`; `OBCC-FE-PrematureDeployment`; safe-fixture constraint | Stat: 100% inspection of the integrated test article and test means. Fault hardening: no live-release hazard, current-limited safe fixture present, observer and logger attached before energizing. | `PF-001`, `PF-007`, `PF-009` | PV1, PV3; expected report `results/OBCC-V05-GATE-001/inspection.md` | Definition ready; execution pending |
| `OBCC-V05-GATE-001-A01` | v0.5 -> v0.6 | Mode gate, ADS IMU/alt trigger data exchange, emergency-request exchange, deployment gate/PDM processing, servo PWM/open command path, actuator feedback adapter, telemetry/health publisher, test harness and trace interfaces | Component exchange; allocation; constraint | Analysis | `OBCC-UC-DeploymentGate`; `OBCC-VV-CON-003`; `OBCC-FE-PrematureDeployment`; `OBCC-FE-NonDeployment` | Stat: 100% interface/allocation review for the deployment path before trial execution. Fault hardening: no unmodeled bypass around Stand-by inhibit; only modeled PDM/PWM path may drive actuator; all inhibit/fault reasons observable. | `PF-006`, `PF-007` | PV2, PV3, fault-hardening chain; expected report `results/OBCC-V05-GATE-001/interface_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V05-GATE-001-T01` | v0.5 -> v0.6 | Stand-by mode gate, valid ADS trigger path, modeled emergency-request path, inhibit function, PDM open-command suppression, actuator observer, LoRa/trace telemetry continuity | Functional chain/scenario; constraint | Testing / Demonstration | `OBCC-UC-DeploymentGate`; `OBCC-FE-PrematureDeployment`; Stand-by inhibit constraint | Stat: plan `59/59` zero-open Stand-by trials where feasible for 95/95 forbidden-event screening; valid-trigger and emergency-request equivalence classes both represented. Fault hardening: any PWM-open edge, opening current, open position, or unexplained telemetry loss is a failure. | `PF-002`, `PF-007`, `PF-008`, `PF-009` | PV2, PV3, Stand-by chain; expected report `results/OBCC-V05-GATE-001/standby_inhibit.md` | Definition ready; execution pending |
| `OBCC-V05-GATE-001-T02` | v0.5 -> v0.6 | On-mode state metadata, accepted ADS trigger, modeled emergency request, deployment condition/emergency evaluation, open command, PWM output, current/position evidence, deployment-status telemetry | Functional chain/scenario; constraint | Testing / Demonstration | `OBCC-UC-DeploymentGate`; `OBCC-FE-NonDeployment`; On-mode `<=5 s` opening constraint | Stat: plan `59/59` in-limit On-mode timing trials where feasible for 95/95 deadline screening; trigger and emergency-request cases separated or explicitly dispositioned. Fault hardening: telemetry success must agree with independent current/position observer evidence. | `PF-003`, `PF-007`, `PF-008`, `PF-009` | PV2, PV3, On-mode chain; expected report `results/OBCC-V05-GATE-001/onmode_opening_timing.md` | Definition ready; execution pending |
| `OBCC-V05-GATE-001-T03` | v0.5 -> v0.6 | Invalid trigger/emergency request, missing/stale ADS data, reset during actuation, servo jam/current fault load, reset marker, actuator fault detection, telemetry fault/status publication, oracle comparison | Functional chain/scenario; component exchange; constraint | Testing / Analysis | `OBCC-UC-DeploymentGate`; `OBCC-FE-PrematureDeployment`; `OBCC-FE-NonDeployment`; deployment fault-hardening constraints | Stat: classify each injected fault trial as pass/fail; repeated fault trials are screening unless independence is justified. Fault hardening: forbidden events include open in Stand-by, open from invalid/missing data, scheduler hang, and false deployment-success report. | `PF-004`, `PF-005`, `PF-006`, `PF-007`, `PF-008`, `PF-009` | PV1, PV2, PV3, fault-hardening chain; expected report `results/OBCC-V05-GATE-001/fault_hardening.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — setup/component/link inspection:** OBCC controller, ADS stimulus harness, emergency injection path, PDM/PWM path, servo connector, current shunt, instrumented actuator surrogate, telemetry/trace logger, bench power/reset controller, ambient thermometer, and safety observer/test-operator roles are present, identified, connected as modeled, and dispositioned before energizing.
- **PF-002 — Stand-by inhibit/no-open:** for every valid trigger and modeled emergency request while in Stand-by, there is no open-servo command, no opening current signature, and no open position; heartbeat/status/measurement telemetry continues. Any open evidence or lost telemetry without disposition is a failure.
- **PF-003 — On-mode opening timing:** for valid ADS trigger or modeled emergency request while On, observed safe-actuator open position occurs `<=5.0 s` after the accepted trigger/request timestamp; telemetry success agrees with current/position observer evidence.
- **PF-004 — invalid/missing input hardening:** invalid trigger/emergency requests and missing/stale ADS data are observable, do not command open in a forbidden context, and do not report deployment success without observer evidence.
- **PF-005 — reset/actuator-fault hardening:** reset during actuation and servo current/position faults are observable in trace/telemetry; no false success is allowed, and safe/error/degraded status is recorded where applicable.
- **PF-006 — exchange/allocation consistency:** implemented mode gate, ADS IMU/alt data path, emergency-request path, PDM/PWM actuation path, actuator feedback, telemetry/status publication, and verification-only harness interfaces match the modeled allocation and exchanges; no unmodeled bypass can command open around Stand-by inhibit.
- **PF-007 — environmental/evidence condition:** before repetitions, record calibrated ambient thermometer model/serial and reading, safe-fixture/current-limit configuration, firmware/configuration IDs, UUT hardware identity, trigger-simulator settings, telemetry/trace logger clock synchronization, and as-tested wiring. Missing records are report deviations.
- **PF-008 — statistical and coverage interpretation:** no-open and timing claims follow the project binomial/tolerance policy (`59/59` zero-failure planning point for 95/95 screening where feasible); smaller or non-independent sets are v0.5 advancement characterization only.
- **PF-009 — deployment safety:** routine repeated trials use a current-limited safe deployment fixture or actuator surrogate. Live parachute-release hardware requires a separate safety review and explicit authorization before use.

## Statistics and fault-hardening viewpoints

- This is a `v0.5 -> v0.6` advancement gate, not final v1.0 flight-readiness closure.
- Stand-by no-open evidence should target `59/59` zero-open trials when the fixture and trial independence permit a 95/95 forbidden-event screening claim. The set must include both valid ADS-trigger and modeled emergency-request equivalence classes, or explicitly disposition any missing class.
- On-mode timing evidence should target `59/59` in-limit trials for the `<=5 s` deadline when representative triggering and timing instrumentation are available. Trigger-based and emergency-request-based openings should be reported separately unless the report justifies pooling.
- Fault-injection coverage is by declared equivalence class: invalid/out-of-context trigger, invalid/out-of-context emergency request, missing ADS data, stale ADS data, reset during actuation, servo jam/current fault, and telemetry/observer mismatch. Each forbidden event is a failure.
- Repeated trials on one bench article are screening evidence unless independence, as-tested configuration stability, and reset/restoration procedures are justified in the execution report.
- Fault-hardening emphasis: Stand-by emergency-deploy inhibition, invalid/missing ADS data, reset during actuation, actuator-current/position anomalies, scheduler/trace liveness, and avoidance of false deployment-success telemetry.

## Candidate mapping and coverage notes

- **`OBCC-VV-FC-004`:** modeled by `OBCC-V05-GATE-001-T01/T02/T03` with the verification means, stimuli, expected behavior, pass/fail constraints, statistics, and fault-hardening viewpoints added to the deployment-gating functional chains.
- **`OBCC-VV-CON-003`:** modeled by `OBCC-V05-GATE-001-I01/A01/T01/T02/T03`, covering Stand-by inhibit, On-mode `<=5 s` opening, ADS IMU/alt trigger data, emergency policy, and safe actuator/observer constraints.
- The component-exchange and allocation rows in this definition support the deployment gate only. They do not replace the broader v1.0 `OBCC-VV-CE-003` or `OBCC-VV-ALLOC-003` closure activities.

## Assumptions and gaps for feedback

- Lifecycle disposition: no `v0.5` Capella/D2 source baseline is required or fabricated; copied v1.0 views are target context only, and the report identifies the actual v0.5 code/configuration baseline.
- Exact v0.5 ADS trigger thresholds, trigger-data encoding, emergency-request API, and actuator-status telemetry fields are not controlled in the repository artifacts read here.
- Emergency-deploy policy details and reset-during-actuation recovery semantics need confirmation before execution.
- Safe fixture design, current limit, actuator surrogate/servo model, and ambient thermometer model/calibration are TBD and must be recorded in execution evidence.
- The `LoRa_Frame.md` peripheral list and v1.0 model use the selected `RFM96W` radio and `ICM20948` IMU names; execution must record the actual fitted hardware.
- Statistical independence of repeated deployment trials is not established by the model; reports must avoid overstating reliability if trials share one article, fixture, or unchanged software state.
- This was a non-interactive subagent run; needed feedback is captured here instead of requested live.
