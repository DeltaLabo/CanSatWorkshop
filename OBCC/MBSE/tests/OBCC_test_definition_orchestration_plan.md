# OBCC MBSE multi-version test-definition orchestration plan

Date: 2026-07-01  
Target: `OBCC/MBSE/`  
Controller: orchestrator session in `/Users/antho/CanSatWorkshop`

## Goal

Use `/Users/antho/agent-tools/syseng/prompts/capella-pa-tests-definition.md` as the reusable single-test workflow, loaded into subagents with `-e ~/agent-tools/syseng`, to create model-based verification test definitions for the OBCC subsystem. The requested scope is all development versions `v0.1` through `v1.0` flight readiness, with one delegated subagent per verification activity.

## Constraints and assumptions

- The repository currently contains only one OBCC Capella/D2 source baseline: `OBCC/MBSE/v1.0/`.
- Earlier `v0.1`-`v0.9` OBCC Capella/D2 source folders are absent. To avoid blocking the requested multi-version coverage, the v0.x gate definitions will:
  - state the absent source baselines as an explicit model/source gap,
  - use `OBCC/README.md`, `OBCC/LoRa_Frame.md`, `OBCC/Variable_Getter_Template.md`, `OBCC/legacy_tests/`, and the v1.0 Capella model as available context,
  - define transition-gate tests that progressively build toward v1.0 behavior without editing or inventing missing baseline source diagrams.
- The existing `OBCC/MBSE/tests/README.md` is a v1.0 planning inventory, not a set of modeled test definitions. Subagents must reuse its candidate coverage where applicable instead of duplicating uncontrolled alternatives.
- Use the `ivv` skill as controlling guidance and the `capella-d2` skill for D2/Capella semantics, rendering, and visual-quality checks.
- Subagents must be launched with `-e ~/agent-tools/syseng`, `--no-session`, and the reusable prompt plus the issue file.
- Do not push. Do not stage or commit from subagents; the working tree already contains unrelated dirty files.
- Source model files under `OBCC/MBSE/v1.0/` are read-only. Test definitions live only under `OBCC/MBSE/tests/<activity-id>/`.
- To avoid concurrent edits, test-definition subagents must not edit `OBCC/MBSE/tests/README.md`. Each writes `OBCC/MBSE/tests/_subagent_updates/<activity-id>.md`; the integration subagent performs the single master-plan update and removes fragments.
- Temporary issue files under `OBCC/MBSE/tests/orchestration/` are removed after integration. This overarching plan remains as the requested planning artifact.

## Existing OBCC IVV state

- Source views: `OBCC/MBSE/v1.0/OBCC_v1.0_view1_physical.d2` through `view8_runtime_fault_handling_chain.d2` plus rendered PNGs.
- Existing plan: `OBCC/MBSE/tests/README.md`, with candidate rows `OBCC-VV-PC-001`, `OBCC-VV-PL-001`, `OBCC-VV-CE-001` through `003`, `OBCC-VV-ALLOC-001` through `003`, `OBCC-VV-FC-001` through `006`, and `OBCC-VV-CON-001` through `005`.
- At orchestration start, no modeled OBCC test-definition folders were present under `OBCC/MBSE/tests/`; integration status is recorded below.

## Delegated issue set

| Issue | Activity ID | Version gate | Verification definition to create | Main existing v1.0 candidate coverage |
|---|---|---|---|---|
| 001 | `OBCC-V01-GATE-001` | v0.1 -> v0.2 | Breadboard hardware, critical/non-critical peripheral startup-health gate | `OBCC-VV-PC-001`, `OBCC-VV-FC-001`, `OBCC-VV-CON-004` |
| 002 | `OBCC-V02-GATE-001` | v0.2 -> v0.3 | Bus/protocol and getter timing gate for sensor, radio, and servo interfaces | `OBCC-VV-CE-001`, `OBCC-VV-CE-003`, `OBCC-VV-CON-004` |
| 003 | `OBCC-V03-GATE-001` | v0.3 -> v0.4 | LoRa telemetry frame, cadence, payload-schema, and range/PDR gate | `OBCC-VV-CE-002`, `OBCC-VV-FC-002`, `OBCC-VV-CON-001` |
| 004 | `OBCC-V04-GATE-001` | v0.4 -> v0.5 | Wireless command/state transition and invalid-command hardening gate | `OBCC-VV-FC-003`, `OBCC-VV-CON-002` |
| 005 | `OBCC-V05-GATE-001` | v0.5 -> v0.6 | Deployment gating, Stand-by inhibit, On-mode `<=5 s` actuation gate | `OBCC-VV-FC-004`, `OBCC-VV-CON-003` |
| 006 | `OBCC-V06-GATE-001` | v0.6 -> v0.7 | Runtime fault handling, bounded error codes, non-blocking scheduler gate | `OBCC-VV-FC-005`, `OBCC-VV-CON-004`, `OBCC-VV-CON-005` |
| 007 | `OBCC-V07-GATE-001` | v0.7 -> v0.8 | FreeRTOS/task/queue/mutex allocation and interface analysis gate | `OBCC-VV-ALLOC-001`, `OBCC-VV-ALLOC-002`, `OBCC-VV-ALLOC-003`, `OBCC-VV-CE-003` |
| 008 | `OBCC-V08-GATE-001` | v0.8 -> v0.9 | PCB/backplane/link workmanship and integration inspection gate | `OBCC-VV-PC-001`, `OBCC-VV-PL-001`, `OBCC-VV-CE-001` |
| 009 | `OBCC-V09-GATE-001` | v0.9 -> v1.0 | End-to-end mission-window rehearsal and ground evidence gate | `OBCC-VV-FC-006` plus regressions from FC-001..005 |
| 010 | `OBCC-V10-FLIGHT-001` | v1.0 flight readiness | Final flight-readiness regression and closure analysis across all v1.0 candidates | All v1.0 candidates as closure index |
| 011 | integration | all | Merge subagent fragments, update `OBCC/MBSE/tests/README.md`, verify artifacts, clean temporary fragments/issues | Plan consistency and coverage closure |

## Subagent protocol

Each test-definition subagent must:

1. Read the reusable prompt, this issue file, `OBCC/MBSE/tests/README.md`, `OBCC/MBSE/v1.0/README.md`, and relevant OBCC context (`OBCC/README.md`, `OBCC/LoRa_Frame.md`, `OBCC/Variable_Getter_Template.md`, legacy tests when useful).
2. Use `ivv` and `capella-d2`; if the prompt says `capella2d2`, interpret it as the available `capella-d2` skill.
3. Work only inside `OBCC/MBSE/tests/<activity-id>/` and `OBCC/MBSE/tests/_subagent_updates/<activity-id>.md`.
4. Copy relevant v1.0 source D2/PNG views into `source_views/v1.0/` or `baseline/v1.0/`, and document that v0.x source Capella views are absent where applicable.
5. Create Capella-style verification-specific D2 definition views and render PNGs with:

   ```sh
   d2 --layout=elk \
     --elk-padding="[top=20,left=20,bottom=20,right=20]" \
     --elk-nodeNodeBetweenLayers=30 \
     --elk-edgeNodeBetweenLayers=20 \
     input.d2 output.png
   ```

6. Write a local `README.md` containing scope, IADT method(s), IVV category, version coverage, source-view copies, diagram catalogue, pass/fail constraints, statistical significance, fault-hardening viewpoint, traceability, expected evidence path, assumptions, gaps, and execution status.
7. Write `_subagent_updates/<activity-id>.md` with the exact proposed row/status text for the integration subagent.
8. Do not edit `OBCC/MBSE/tests/README.md`, do not stage, do not commit, and do not push.
9. Return a concise final summary with changed files, render status, and open assumptions.

## Acceptance criteria

- Issues 001-010 each create a modeled test-definition folder with a README, baseline/source copies, D2 views, and rendered PNGs.
- The definitions collectively cover every requested version gate from `v0.1` through `v1.0`, and they explicitly document that v0.x Capella source baselines are absent.
- The final integration issue updates `OBCC/MBSE/tests/README.md` once, mapping the original v1.0 candidate rows to the new modeled definitions or documenting remaining gaps.
- Temporary issue files and `_subagent_updates` fragments are removed after integration.
- No push is performed.

## Completion status

Integration completed on 2026-07-01. Issues 001-010 produced modeled definition folders and Issue 011 integrated them into the master test-definition index.

| Issue | Activity ID | Completion status | Notes |
|---|---|---|---|
| 001 | `OBCC-V01-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.1` source gap documented |
| 002 | `OBCC-V02-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.2` source gap documented |
| 003 | `OBCC-V03-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.3` source gap documented |
| 004 | `OBCC-V04-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.4` source gap documented |
| 005 | `OBCC-V05-GATE-001` | Definition integrated; execution pending | 6 verification D2/PNG views; `v0.5` source gap documented |
| 006 | `OBCC-V06-GATE-001` | Definition integrated; execution pending | 5 verification D2/PNG views; `v0.6` source gap documented |
| 007 | `OBCC-V07-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.7` source gap documented |
| 008 | `OBCC-V08-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.8` source gap documented |
| 009 | `OBCC-V09-GATE-001` | Definition integrated; execution pending | 4 verification D2/PNG views; `v0.9` source gap documented; now maps `OBCC-VV-FC-006` |
| 010 | `OBCC-V10-FLIGHT-001` | Definition integrated; final review execution pending | 4 verification D2/PNG views; closure index updated to account for current `OBCC-V09-GATE-001` folder |
| 011 | integration | Completed | `OBCC/MBSE/tests/README.md` updated; all original v1.0 candidates mapped; consumed fragments and temporary issue files removed |

Artifact verification at integration found all 10 activity folders with local README files, copied `source_views/v1.0/` D2/PNG source context, and paired verification-specific D2/PNG views. A full render check of the 43 verification-specific D2 files completed successfully with the required ELK command and spacing flags. No D2 render is missing or broken. Execution evidence remains pending under `OBCC/MBSE/tests/results/<activity-id>/`.
