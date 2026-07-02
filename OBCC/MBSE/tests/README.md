# OBCC multi-version IVV test-definition plan

Integrated verification-definition index for the OBCC subsystem. The Capella/D2 model remains the source of truth; this file maps the original OBCC v1.0 IVV candidate inventory to the modeled multi-version advancement gates now present under `OBCC/MBSE/tests/`.

Project-wide IVV conventions, evidence paths, statistical policy, fault semantics, and report-by-reference rules are defined in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md). Evidence for each modeled activity below is expected under `OBCC/MBSE/tests/results/<activity-id>/`.

## 1. Source model and target-context status

- **Available source baseline:** `OBCC/MBSE/v1.0/` only.
- **Lifecycle/modeling disposition:** no OBCC Capella/D2 source folders for `v0.1` through `v0.9` were delivered, and this is an accepted non-issue: OBCC versions may jump from `v0.x` to `v1.0`, and the mostly software-dependent subsystem was not complex enough to require incremental source-model deliveries. The `v0.x` gate definitions use copied `v1.0` views as target-context only; they do not invent missing historical model views.
- **Execution-report caveat:** historical gate reports must identify the actual code/configuration baseline IDs used and acknowledge target-context-only `v1.0` model references where applicable.
- **Read-only source model:** files under `OBCC/MBSE/v1.0/` are not modified by these test definitions.
- **Execution status:** modeled definitions are ready; execution evidence and controlled reports remain pending unless a downstream results folder states otherwise.

## 2. v1.0 model views used as source context

- `OBCC_v1.0_view1_physical.d2`: integrated CanSat, OBCC module/PCB, XIAO ESP32-S3, RFM96W, sensors, PDS/ESS/PDM context, ground station, PC, and physical links.
- `OBCC_v1.0_view2_logical.d2`: FreeRTOS/task topology, queues, drivers, getters, telemetry, command/state, deployment, and ground-station logical components.
- `OBCC_v1.0_view3_functional_allocation.d2`: startup health, sensor acquisition, telemetry payload, LoRa downlink/uplink, On/Stand-by modes, deployment gating, and runtime fault functions.
- `OBCC_v1.0_view4_startup_health_chain.d2`: startup critical/non-critical peripheral health chain.
- `OBCC_v1.0_view5_telemetry_downlink_chain.d2`: sensing, telemetry encoding, LoRa downlink, ground decode/display/store.
- `OBCC_v1.0_view6_command_state_chain.d2`: wireless On/Stand-by command path.
- `OBCC_v1.0_view7_deployment_gating_chain.d2`: Stand-by inhibit and On-mode deployment actuation.
- `OBCC_v1.0_view8_runtime_fault_handling_chain.d2`: getter timeouts, error codes, runtime fault disclosure, and emergency-deploy request policy.

## 3. Multi-version advancement-gate definitions

| Activity ID | Version gate | Modeled definition folder | Verification-specific D2/PNG views | Primary coverage | Expected evidence path | Status |
|---|---|---|---:|---|---|---|
| `OBCC-V01-GATE-001` | `v0.1 -> v0.2` | `OBCC/MBSE/tests/OBCC-V01-GATE-001/` | 4 | Breadboard hardware and critical/non-critical startup-health gate | `OBCC/MBSE/tests/results/OBCC-V01-GATE-001/` | Definition-ready; execution-pending; `v0.1` source views absent |
| `OBCC-V02-GATE-001` | `v0.2 -> v0.3` | `OBCC/MBSE/tests/OBCC-V02-GATE-001/` | 4 | Bus/protocol bring-up, getter timing, bounded interface faults | `OBCC/MBSE/tests/results/OBCC-V02-GATE-001/` | Definition-ready; execution-pending; `v0.2` source views absent |
| `OBCC-V03-GATE-001` | `v0.3 -> v0.4` | `OBCC/MBSE/tests/OBCC-V03-GATE-001/` | 4 | LoRa telemetry frame, cadence, decode/store, range/PDR gate | `OBCC/MBSE/tests/results/OBCC-V03-GATE-001/` | Definition-ready; execution-pending; `v0.3` source views absent |
| `OBCC-V04-GATE-001` | `v0.4 -> v0.5` | `OBCC/MBSE/tests/OBCC-V04-GATE-001/` | 4 | Wireless On/Stand-by command/state and invalid-command hardening | `OBCC/MBSE/tests/results/OBCC-V04-GATE-001/` | Definition-ready; execution-pending; `v0.4` source views absent |
| `OBCC-V05-GATE-001` | `v0.5 -> v0.6` | `OBCC/MBSE/tests/OBCC-V05-GATE-001/` | 6 | Deployment gating, Stand-by inhibit, On-mode `<=5 s` actuation | `OBCC/MBSE/tests/results/OBCC-V05-GATE-001/` | Definition-ready; execution-pending; `v0.5` source views absent |
| `OBCC-V06-GATE-001` | `v0.6 -> v0.7` | `OBCC/MBSE/tests/OBCC-V06-GATE-001/` | 5 | Runtime fault handling, bounded error codes, scheduler liveness, emergency policy | `OBCC/MBSE/tests/results/OBCC-V06-GATE-001/` | Definition-ready; execution-pending; `v0.6` source views absent |
| `OBCC-V07-GATE-001` | `v0.7 -> v0.8` | `OBCC/MBSE/tests/OBCC-V07-GATE-001/` | 4 | FreeRTOS/task/queue/mutex allocation and software interface analysis | `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/` | Definition-ready; execution-pending; `v0.7` source views absent |
| `OBCC-V08-GATE-001` | `v0.8 -> v0.9` | `OBCC/MBSE/tests/OBCC-V08-GATE-001/` | 4 | PCB/backplane/link workmanship, continuity, RF/antenna safety, integration inspection | `OBCC/MBSE/tests/results/OBCC-V08-GATE-001/` | Definition-ready; execution-pending; `v0.8` source views absent |
| `OBCC-V09-GATE-001` | `v0.9 -> v1.0` | `OBCC/MBSE/tests/OBCC-V09-GATE-001/` | 4 | End-to-end mission-window rehearsal and regressions across startup, telemetry, command, deployment, and runtime-fault chains | `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/` | Definition-ready; execution-pending; `v0.9` source views absent |
| `OBCC-V10-FLIGHT-001` | `v1.0` flight readiness | `OBCC/MBSE/tests/OBCC-V10-FLIGHT-001/` | 4 | Final readiness closure matrix across all v1.0 candidates and modeled gate definitions | `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Definition-ready; final review/execution-pending; final PASS requires evidence and board disposition |

## 4. Original v1.0 candidate row mapping

All original v1.0 candidate rows are now mapped to modeled definition folders. Status is **definition-ready / execution-pending** unless an execution report is later added under the listed results paths.

| Original candidate row | Modeled definition folder(s) now controlling the definition | Expected evidence path(s) | Mapping status |
|---|---|---|---|
| `OBCC-VV-PC-001` | `OBCC-V08-GATE-001`; closure by `OBCC-V10-FLIGHT-001`; breadboard subset informed by `OBCC-V01-GATE-001` | `OBCC/MBSE/tests/results/OBCC-V08-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; v1.0 integrated-PC closure defined, execution pending |
| `OBCC-VV-PL-001` | `OBCC-V08-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V08-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CE-001` | `OBCC-V02-GATE-001`; physical/protocol workmanship support from `OBCC-V08-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V02-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V08-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CE-002` | `OBCC-V03-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V03-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CE-003` | `OBCC-V02-GATE-001`; runtime context from `OBCC-V06-GATE-001`; allocation/interface closure from `OBCC-V07-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V02-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V06-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-ALLOC-001` | `OBCC-V07-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-ALLOC-002` | `OBCC-V07-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-ALLOC-003` | `OBCC-V07-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-FC-001` | `OBCC-V01-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V01-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-FC-002` | `OBCC-V03-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V03-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-FC-003` | `OBCC-V04-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V04-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-FC-004` | `OBCC-V05-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V05-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-FC-005` | `OBCC-V06-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V06-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-FC-006` | `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; no modeled-definition gap remains; execution pending |
| `OBCC-VV-CON-001` | `OBCC-V03-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V03-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CON-002` | `OBCC-V04-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V04-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CON-003` | `OBCC-V05-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V05-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CON-004` | Startup subset in `OBCC-V01-GATE-001`; timing/interface subset in `OBCC-V02-GATE-001`; runtime fault subset in `OBCC-V06-GATE-001`; RTOS/allocation subset in `OBCC-V07-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V01-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V02-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V06-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V07-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |
| `OBCC-VV-CON-005` | `OBCC-V06-GATE-001`; regression in `OBCC-V09-GATE-001`; closure by `OBCC-V10-FLIGHT-001` | `OBCC/MBSE/tests/results/OBCC-V06-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V09-GATE-001/`; `OBCC/MBSE/tests/results/OBCC-V10-FLIGHT-001/` | Mapped; execution pending |

## 5. Current coverage and residual gaps

- **Modeled definition coverage:** complete for the issued multi-version set `OBCC-V01-GATE-001` through `OBCC-V10-FLIGHT-001`. The mission-window rehearsal folder `OBCC-V09-GATE-001/` exists and maps `OBCC-VV-FC-006`.
- **Target-context caveat preserved:** `v0.1` through `v0.9` Capella/D2 source baselines were not delivered by lifecycle decision; each corresponding gate documents that it uses `v1.0` source copies as target context only, and execution reports must name the actual code/configuration baseline analyzed or tested.
- **Execution/evidence gap:** no final PASS is implied by definition readiness. Execution reports, raw logs, photos/video, RF/timing evidence, closure matrices, deviations, waivers, and board decisions must be stored under the expected `OBCC/MBSE/tests/results/<activity-id>/` paths.
- **Technical assumptions to close during execution:** exact as-built hardware/firmware/radio settings, command and payload schemas, emergency-deploy policy, actuator status semantics, environment/instrument IDs, and statistical independence/sample-size claims.
- **D2 render status at integration:** every verification-specific D2 view has a paired PNG and all 43 verification-specific D2 files rendered successfully with the required ELK command and spacing flags.
