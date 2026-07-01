# OBCC-V07-GATE-001 — FreeRTOS allocation and interface analysis advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V07-GATE-001`
- **SSIV / version gate:** OBCC `v0.7 -> v0.8`
- **Chosen pending activity for this session:** Issue 007, advancement definition for FreeRTOS allocation, task/queue/mutex ownership, ISR/timer consistency, software interface ownership, and pre-PCB/integration hardening.
- **IADT method(s):** Analysis + Inspection. Optional RTOS trace/stress evidence is modeled as an analysis input/hook, not as final demonstration evidence unless an execution report states its statistical basis.
- **IVV source categories:** allocation; component exchange; functional chain/scenario; constraint; verification-artifact/component-link setup inspection. Full OBCC hardware PC/PL closure remains assigned to the dedicated hardware inspection gates.
- **Primary v1.0 candidate-row mapping:** `OBCC-VV-ALLOC-001`, `OBCC-VV-ALLOC-002`, `OBCC-VV-ALLOC-003`, and software `OBCC-VV-CE-003`.
- **Traceability targets:** `OBCC-UC-StartupHealth`, `OBCC-UC-TelemetryDownlink`, `OBCC-UC-WirelessCommand`, `OBCC-UC-DeploymentGate`, and `OBCC-FE-SchedulerBlocked`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`.
- **Execution status:** modeled definition complete; review/execution evidence pending.

No `v0.7` Capella/D2 source views exist in this repository. This definition uses copied `v1.0` OBCC views as target-architecture context and explicitly requires the execution report to identify the actual `v0.7` code/configuration baseline analyzed.

## References

- Project IVV and statistical policy: `PM&SE/IVV.md`
- OBCC requirements and derived fault/getter behavior: `OBCC/README.md`
- Getter/result-code convention: `OBCC/Variable_Getter_Template.md`
- Telemetry and peripheral criticality context: `OBCC/LoRa_Frame.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Orchestration plan: `OBCC/MBSE/tests/OBCC_test_definition_orchestration_plan.md`
- Source context copied from: `OBCC/MBSE/v1.0/`
- Implementation context to identify during execution: `OBCC/main/main.ino`, `OBCC/main/settings.h`, `OBCC/main/pins.h`, or the actual v0.7 firmware/configuration under review.
- Reference family from the master plan: `OBCC-R7` FreeRTOS / ESP-IDF task, queue, timer, mutex, and ISR references.

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README copy plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.7/` because no v0.x Capella/D2 baseline is present.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical/artifact setup | `OBCC-V07-GATE-001_view1_test_physical_artifact_setup.d2` | `OBCC-V07-GATE-001_view1_test_physical_artifact_setup.png` | Review workstation, RTOS event logger, stress exerciser hook, controlled source/config snapshot, allocation matrix, RTOS inventory, trace pins, and inspection/source-gap constraints. |
| PV2 logical interface analysis | `OBCC-V07-GATE-001_view2_rtos_interface_analysis.d2` | `OBCC-V07-GATE-001_view2_rtos_interface_analysis.png` | Aggregated logical CE analysis for FreeRTOS, getter, queue, state, mode-gate, IMU/altitude, command, payload, ground, and evidence interfaces. |
| PV3 allocation inspection | `OBCC-V07-GATE-001_view3_allocation_inspection.d2` | `OBCC-V07-GATE-001_view3_allocation_inspection.png` | Function-level allocation view for reviewer/operator/tool functions plus OBCC and ground functions to be dispositioned against the v0.7 code/task matrix. |
| Analysis/inspection chain | `OBCC-V07-GATE-001_view4_allocation_interface_analysis_chain.d2` | `OBCC-V07-GATE-001_view4_allocation_interface_analysis_chain.png` | End-to-end analysis workflow from source-gap declaration through artifact inspection, static extraction, allocation/CE analysis, optional trace-hook review, finding closure, and evidence archive. |

All four D2 files render successfully with the required `d2 --layout=elk` command and ELK spacing flags.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V07-GATE-001-I01` | v0.7 -> v0.8 | Source/build/config snapshot; allocation matrix; task, queue, timer, mutex, ISR inventory; trace-hook definition; review checklist and evidence path | Inspection; allocation; component exchange; constraint | Inspection | All listed trace targets; `OBCC-FE-SchedulerBlocked` | Stat: 100% presence/absence inspection of required artifacts; no sampling claim. Fault hardening: missing queue/mutex/ISR evidence is a blocking finding because it prevents RTOS-fault rationale. | `PF-001`, `PF-007`, `PF-008` | PV1, PV2, PV3, analysis chain; expected report `results/OBCC-V07-GATE-001/artifact_presence_inspection.md` | Definition ready; execution pending |
| `OBCC-V07-GATE-001-A01` | v0.7 -> v0.8 | OBCC Supervisor, Health Monitor, FreeRTOS Kernel, task creation, timers, message queues, mutex/shared-bus protection, ISRs, startup/runtime status paths | Allocation; constraint | Analysis | `OBCC-UC-StartupHealth`; `OBCC-FE-SchedulerBlocked`; `OBCC-VV-ALLOC-001` | Stat: 100% model-function to LC/task disposition. Fault hardening: deadlock, priority inversion, queue overflow, ISR-unsafe calls, watchdog/liveness, unbounded blocking/allocation. | `PF-002`, `PF-003`, `PF-004`, `PF-007`, `PF-008` | PV2, PV3, analysis chain; expected report `results/OBCC-V07-GATE-001/supervisor_rtos_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V07-GATE-001-A02` | v0.7 -> v0.8 | ADS/AMS/ESS sensing and getter providers; Telemetry Collector; Telemetry Encoder; measurement queue; health/status metadata; getter result-code contracts | Allocation; component exchange; constraint | Analysis | `OBCC-UC-TelemetryDownlink`; `OBCC-FE-SchedulerBlocked`; `OBCC-VV-ALLOC-002`; `OBCC-VV-CE-003` | Stat: 100% getter/API/function-to-LC review; trace samples characterize only unless a 95/95 timing claim is explicitly supported. Fault hardening: stale values, getter timeout/error codes, queue overflow, hidden cross-task bus ownership. | `PF-002`, `PF-003`, `PF-005`, `PF-006`, `PF-007`, `PF-008` | PV2, PV3, analysis chain; expected report `results/OBCC-V07-GATE-001/sensing_telemetry_allocation_ce_analysis.md` | Definition ready; execution pending |
| `OBCC-V07-GATE-001-A03` | v0.7 -> v0.8 | Command Handler, State Manager role, deployment controller/PDM Processing, mode gate, IMU/altitude decision data, ground decode/display/store, command and payload paths | Allocation; component exchange; functional chain/scenario; constraint | Analysis | `OBCC-UC-WirelessCommand`; `OBCC-UC-DeploymentGate`; `OBCC-FE-SchedulerBlocked`; `OBCC-VV-ALLOC-003`; `OBCC-VV-CE-003` | Stat: 100% allocation and interface review. Fault hardening: invalid state owner, unmodeled deployment bypass, Stand-by mode-gate bypass, command replay/invalid-command path hidden in wrong LC, ground storage/display ownership mismatch. | `PF-002`, `PF-003`, `PF-005`, `PF-006`, `PF-007`, `PF-008` | PV2, PV3, analysis chain; expected report `results/OBCC-V07-GATE-001/command_deploy_ground_allocation_ce_analysis.md` | Definition ready; execution pending |
| `OBCC-V07-GATE-001-A04` | v0.7 -> v0.8 | Optional RTOS trace/stress evidence: task switches, queue depth/overflow, mutex lock/unlock, ISR notifications, scheduler heartbeat/liveness under representative load | Constraint; component exchange; functional chain/scenario | Analysis using optional trace/stress hook | `OBCC-FE-SchedulerBlocked`; runtime portions of startup/telemetry/command/deployment use cases | Stat: trace is characterization unless execution defines independence and sample size. Use `n=59` in-limit representative timing samples only for a 95/95 deadline claim. Fault hardening: scheduler blocked, deadlock, priority inversion, queue overflow, ISR misuse, unbounded dynamic allocation. | `PF-004`, `PF-006`, `PF-007`, `PF-008` | PV1, PV2, PV3, analysis chain; expected report `results/OBCC-V07-GATE-001/rtos_trace_fault_hardening_analysis.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — required artifact presence:** source/build/configuration snapshot, model-baseline reference, allocation matrix, task list, queue list, timer list, mutex/shared-bus protection list, ISR list, trace-hook definition, review checklist, and expected evidence path are present; absence is dispositioned as a blocking finding or waiver.
- **PF-002 — allocation completeness:** every modeled function in the copied v1.0 target context that is applicable to v0.7 is mapped to the intended LC and software task/role; non-applicable functions are explicitly dispositioned; no unallocated or foreign function is accepted silently.
- **PF-003 — no hidden ownership:** queue ownership, state ownership, mode/deployment-gate ownership, command ownership, and ground decode/display/store ownership are unique and match the model; no hidden serial-console flight operator path or unmodeled deployment bypass is accepted.
- **PF-004 — FreeRTOS primitive hardening:** task creation, timers, queues, mutex/shared-bus protection, ISR-safe API use, queue overflow handling, watchdog/liveness, bounded blocking, and no unanalyzed unbounded dynamic allocation are shown consistent with the model and FreeRTOS assumptions.
- **PF-005 — software component-exchange contracts:** getter contracts, measurement queue, state, mode gate, IMU/altitude data, payload, command, and trace-evidence interfaces have modeled direction, data contract, accountable owner, and observable evidence endpoint.
- **PF-006 — trace/liveness rationale:** if trace/stress hooks are used, RTOS event logs show no unexplained scheduler blocking, deadlock, priority inversion, queue overflow, or ISR misuse during the analyzed scenario; if hooks are not executed, no trace-based reliability or timing claim is made.
- **PF-007 — evidence/report archive:** review notes, static-analysis outputs, allocation matrices, RTOS inventories, trace logs if used, UUT firmware/configuration ID, tool versions, findings/waivers, and decision record are archived under `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`.
- **PF-008 — source-gap declaration:** diagrams and reports state that no v0.7 Capella/D2 baseline exists and that copied v1.0 views are target-context inputs only; the actual v0.7 code/configuration analyzed is identified.

## Statistics and fault-hardening viewpoints

- This gate is a **v0.7 advancement analysis/inspection**, not final v1.0 reliability evidence.
- Analysis/inspection minimum: 100% disposition of applicable model elements and required evidence artifacts.
- Optional trace/stress hook: repeated trace samples are characterization unless the report defines independence, operating conditions, and claim-specific sample size.
- Timing/deadline claim policy: use the project IVV rule of `n = 59` representative in-limit samples for a 95/95 non-parametric one-sided tolerance claim; smaller samples must be reported as screening/characterization.
- Fault-hardening focus: scheduler blocking, task starvation, queue overflow, stale getter values, hidden shared-bus ownership, mutex deadlock/priority inversion, ISR-unsafe calls, invalid state transitions, Stand-by deployment bypass, command/deployment bypass, and unbounded dynamic allocation or blocking.

## Coverage mapping to existing OBCC v1.0 candidate rows

- **`OBCC-VV-ALLOC-001`:** covered by `I01`, `A01`, and `A04` for OBCC Supervisor, Health Monitor, FreeRTOS Kernel, task/queue/timer/mutex/ISR ownership, startup/runtime status, and scheduler-blocking rationale.
- **`OBCC-VV-ALLOC-002`:** covered by `A02` for ADS/AMS/ESS sensing/getters, Telemetry Collector, Telemetry Encoder, measurement queue, health/status metadata, and getter result-code contracts.
- **`OBCC-VV-ALLOC-003`:** covered by `A03` for Command Handler, State Manager role, deployment controller/PDM Processing, mode gate, ground Decoder/Dashboard/CSV Writer allocation, and absence of hidden command/deployment bypasses.
- **`OBCC-VV-CE-003`:** covered by `A02`, `A03`, and `A04` for `Getters`, `Queue`, `State`, `Mode gate`, `IMU/alt`, payload/command software exchanges, and RTOS trace/liveness evidence hooks.

## Assumptions and gaps for feedback / execution planning

- No v0.x Capella/D2 baseline is present; v1.0 source views are context only and shall not be edited.
- The actual v0.7 firmware/task configuration is not controlled by the model artifacts read here. The execution report must identify the code baseline, FreeRTOS configuration, build flags, toolchain, and board configuration used.
- `OBCC/main/main.ino` appears to be a non-FreeRTOS Arduino-style loop context and must not be assumed to satisfy the modeled v1.0 FreeRTOS architecture unless confirmed by the team.
- Exact task names, priorities, queue depths, timer periods, mutex names, ISR entry points, heap/allocation policy, watchdog policy, and trace/export hook mechanism are not specified in the repository artifacts read here.
- Ground decode/display/store allocation is modeled from v1.0 context; execution must identify the actual ground software baseline reviewed for v0.7.
- Trace/stress evidence requires defined load profiles and tool IDs. Without that, the gate still supports 100% static analysis/inspection but not runtime timing/reliability claims.
