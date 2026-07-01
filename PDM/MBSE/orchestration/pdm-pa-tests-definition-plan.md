# PDM PA verification-test definition orchestration plan

## Goal

Apply the workflow in `/Users/antho/agent-tools/syseng/prompts/capella-pa-tests-definition.md` to the PDM Capella/D2 Physical Architecture views, but delegate the test-by-test work to subagents. Each subagent must receive the `~/agent-tools/syseng` extension package and define one model-based verification activity.

## Scope and assumptions

- Target repository: `/Users/antho/CanSatWorkshop`.
- Target model root: `PDM/MBSE/`.
- Source versions currently present under `PDM/MBSE/`: `v0.1`, `v0.2`, and `v1.0`.
  - No `v0.3` through `v0.9` source folders exist in this repository at planning time.
  - This plan therefore treats the incremental gates as `v0.1 -> v0.2`, `v0.2 -> v1.0`, and `v1.0 -> flight readiness`.
- Existing PDM v1.0 planning artifact: `PDM/MBSE/v1.0/tests/README.md`.
- `v0.1` and `v0.2` do not currently have `tests/README.md`; their subagents are authorized to create initial IVV-aligned testing plans for those versions before defining their selected activity.
- Existing repository worktree is not clean before this orchestration. Subagents must only touch their assigned PDM paths and must not push. To avoid accidentally including unrelated local work, subagents must not commit; the orchestrator will decide how to commit after review.

## Controlling guidance

- Original workflow prompt: `/Users/antho/agent-tools/syseng/prompts/capella-pa-tests-definition.md`.
- Required subagent extension: `-e ~/agent-tools/syseng`.
- Use the `ivv` skill as controlling verification-completeness guidance.
- Use the `capella-d2` skill and its Physical Architecture rules for all D2 views.
- Render every new D2 definition view to PNG using the PDM tight ELK command:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```

## Delegated issues

| Issue file | Assigned activity | Version gate | Output root |
|---|---|---|---|
| `PDM/MBSE/orchestration/issues/001-pdm-v01-fall-terminal-speed.md` | `PDM-V01-FC-FALL` — fall-test terminal-speed verification definition | `v0.1 -> v0.2` | `PDM/MBSE/v0.1/tests/PDM-V01-FC-FALL/` |
| `PDM/MBSE/orchestration/issues/002-pdm-v02-ble-deployment.md` | `PDM-V02-FC-BLE-DEPLOY` — BLE/manual parachute deployment verification definition | `v0.2 -> v1.0` | `PDM/MBSE/v0.2/tests/PDM-V02-FC-BLE-DEPLOY/` |
| `PDM/MBSE/orchestration/issues/003-pdm-v10-imu-deployment.md` | `PDM-VV-FC-001` — IMU-triggered deployment verification definition | `v1.0 -> flight readiness` | `PDM/MBSE/v1.0/tests/PDM-VV-FC-001/` |

## Coordination rules for subagents

1. Work only inside the assigned version folder and its `tests/` subtree, except for reading shared context files such as `PDM/MBSE/README.md`, `PM&SE/IVV.md`, and existing reference files.
2. Do not edit canonical source D2 views in `PDM/MBSE/v*/`; copy them under the test package's `source_views/<version>/` directory.
3. Create or update the assigned version's `tests/README.md` with an IVV coverage table containing at minimum:
   - verification activity ID,
   - SSIV/development version,
   - model element(s) covered,
   - IVV source category,
   - IADT method,
   - traceability target,
   - relevant viewpoints including statistical significance and fault hardening where applicable,
   - pass/fail constraint(s),
   - diagram/report references,
   - status.
4. Define exactly one detailed verification activity per issue, but keep the plan/table broad enough to show coverage and gaps across physical components, physical links, component exchanges, allocations, functional chains/scenarios, and constraints for the selected version.
5. Each test package should contain:
   - `README.md` describing the modeled verification definition,
   - `source_views/<version>/` containing copied D2 and PNG source views,
   - `definition_views/` containing new D2 and PNG verification-definition views.
6. New definition views should model test equipment, human operators, verification-only functions/components/links/exchanges, environmental conditions, pass/fail constraints, traceability, and expected report/evidence references per the original workflow prompt.
7. Do not perform external web research unless unavoidable; prefer existing local references, `PM&SE/IVV.md`, `PDM/MBSE/README.md`, and PDM v1.0 reference artifacts.
8. Do not commit or push. Return a concise summary listing created/modified files, render status, and any blockers.

## Orchestrator review/approval criteria

A delegated issue is complete when:

- The assigned test package exists in the expected output root.
- All source views for the selected version were copied into the package.
- The package has multiple definition D2 views and rendered PNGs.
- `d2` renders all new definition D2 files without errors.
- The version `tests/README.md` contains or updates an IVV coverage table with the required columns and marks the delegated activity as modeled/ready for review.
- The work does not modify unrelated subsystems or other version gates.
- The subagent reports any assumptions, limitations, or blockers rather than silently inventing requirements.

After all issues pass review, remove the transient issue files under `PDM/MBSE/orchestration/issues/`. Keep this plan file as the durable orchestration record unless the user requests otherwise.

## Execution status

- Delegated subagents completed all three version-gate issues without committing or pushing.
- Created/updated version test plans:
  - `PDM/MBSE/v0.1/tests/README.md`
  - `PDM/MBSE/v0.2/tests/README.md`
  - `PDM/MBSE/v1.0/tests/README.md`
- Created detailed test-definition packages:
  - `PDM/MBSE/v0.1/tests/PDM-V01-FC-FALL/`
  - `PDM/MBSE/v0.2/tests/PDM-V02-FC-BLE-DEPLOY/`
  - `PDM/MBSE/v1.0/tests/PDM-VV-FC-001/`
- Orchestrator re-rendered all 15 new definition D2 files with the required ELK command; all rendered successfully.
- Transient issue files and subagent logs were removed after review; this plan file remains as the durable orchestration record.
