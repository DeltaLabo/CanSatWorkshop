# ADS MBSE test-definition orchestration plan

Date: 2026-06-30  
Target: `ADS/MBSE/`  
Controller: orchestrator session in `/Users/antho/CanSatWorkshop`

## Goal

Convert the single-test prompt at `/Users/antho/agent-tools/syseng/prompts/capella-pa-tests-definition.md` into parallel delegated work so subagents define the remaining ADS IVV test definitions. The target scope is every ADS MBSE baseline currently present between early development and flight readiness: `v0.1`, `v0.2`, `v0.3`, and `v1.0`.

## Constraints and assumptions

- The user selected all versions; no further version-disambiguation is required for subagents.
- The repository currently contains only `ADS/MBSE/v0.1`, `ADS/MBSE/v0.2`, `ADS/MBSE/v0.3`, and `ADS/MBSE/v1.0`; no `v0.4`-`v0.9` directories are present.
- Use the `ivv` skill as controlling guidance and the `capella-d2` skill for Capella/D2 semantics and rendering.
- Subagents must be launched with `-e ~/agent-tools/syseng` and given the reusable prompt plus a self-contained issue file.
- Do not push. Do not commit unless explicitly coordinated later. The working tree already contains unrelated dirty files, so subagents must not stage or commit.
- Subagents must not edit source ADS diagrams under `ADS/MBSE/v*/`.
- To avoid parallel conflicts, test-definition subagents must not edit `ADS/MBSE/tests/README.md`; each writes a `coverage_update.md` snippet in its own test directory. A final integration issue updates the master plan.
- Issue files are temporary orchestration artifacts and will be removed after the delegated work is integrated and approved.

## Current ADS IVV state

Existing ADS-wide modeled definitions already present under `ADS/MBSE/tests/`:

- `ADS-IVV-I-PCPL-ALL` — all-version physical component / physical link inspection.
- `ADS-IVV-A-CE-ALL` — all-version component exchange analysis.
- `ADS-IVV-A-ALLOC-ALL` — all-version functional allocation analysis.
- `ADS-IVV-FC-GPS` — GPS functional-chain testing/analysis.
- `ADS-IVV-FC-ANG` — angular velocity functional-chain testing/analysis.
- `ADS-IVV-FC-ATT` — attitude estimation demonstration/testing/analysis.

Stale note superseded 2026-07-02: active ADS activities in `ADS/MBSE/tests/README.md` now have modeled definitions or explicit N/A/gap treatment.

## Delegated issue set

| Issue | Verification activity | Primary versions | Purpose |
|---|---|---|---|
| 001 | `ADS-IVV-FC-INIT` | v0.1, v0.2, v1.0; v0.3 N/A | Peripheral initialization-state verification. |
| 002 | `ADS-IVV-FC-SERIAL` | v0.1, v0.2; v0.3/v1.0 N/A | Serial0 development logging verification. |
| 003 | `ADS-IVV-FC-OBCC-DELIVERY` | v1.0; earlier versions N/A | ADS Processing to OBCC Pointers/Returns delivery verification. |
| 004 | `ADS-IVV-FC-MISSION-WINDOW` | v0.1, v0.2, v1.0; v0.3 N/A | End-to-end runtime mission-window scenario. |
| 005 | `ADS-IVV-C-POS-5M` | v0.1, v0.2, v1.0; v0.3 N/A | GPS `<5 m` constraint-focused verification. |
| 006 | `ADS-IVV-C-RATE-5HZ` | v0.1, v0.2; v0.3/v1.0 N/A | Internal `5 Hz` collection-rate constraint verification. |
| 007 | `ADS-IVV-C-GYRO-30DPS` | v0.2, v1.0; v0.1/v0.3 N/A | Angular-rate `<30 deg/s` constraint verification. |
| 008 | `ADS-IVV-C-NOBLOCK` | v0.1, v0.2, v1.0; v0.3 N/A | No unintended blocking constraint verification. |
| 009 | `ADS-IVV-C-GETTER` | v0.1, v0.2, v1.0; v0.3 N/A | Variable Getter template constraint verification. |
| 010 | `ADS-IVV-C-PROC-5MS` | v0.1, v0.2, v1.0; v0.3 N/A | Process/calculate `<5 ms` constraint verification. |
| 011 | `ADS-IVV-C-UART-5MS` | v0.1, v0.2, v1.0; v0.3 N/A | UART timeout `<=5 ms` verification. |
| 012 | `ADS-IVV-C-I2C-5MS` | v1.0; v0.2 gap/characterization; v0.1/v0.3 N/A | I2C timeout `<=5 ms` verification. |
| 013 | `ADS-IVV-C-MFG` | v0.3, v1.0; support all hardware versions | Manufacturing/workmanship/PCB-backplane verification. |
| 014 | Integration | all | Update `ADS/MBSE/tests/README.md`, verify artifacts, and summarize residual gaps. |

## Version-gate interpretation

- **v0.1 -> v0.2:** GPS-only prototype must have PC/PL, CE, allocation, GPS, Serial0 logging, initialization, position, rate, no-blocking/getter/timing/UART-timeout coverage.
- **v0.2 -> v0.3:** GPS+IMU prototype adds angular velocity, attitude, IMU/I2C, gyro accuracy, and integrated initialization/logging coverage before PCB delivery.
- **v0.3 -> v1.0:** PCB delivery is mainly physical/manufacturing/workmanship and trace/connectivity verification; logical/functional tests are N/A unless behavior is modeled.
- **v1.0 flight readiness:** integrated CanSat/backplane/OBCC path needs all physical, CE, allocation, GPS/IMU/attitude/init, OBCC delivery, timing/timeout, getter/no-blocking, manufacturing, and mission-window coverage.

## Subagent protocol

Each test-definition subagent must:

1. Read the reusable prompt, `ADS/MBSE/tests/README.md`, `ADS/MBSE/tests/model_inventory.json`, and relevant existing test definitions.
2. Work only inside `ADS/MBSE/tests/<activity-id>/` except for reading source views.
3. Copy relevant source D2/PNG views into `source_views/<version>/`.
4. Create rendered D2 definition views under `definition_views/` using:

   ```sh
   d2 --layout=elk      --elk-padding="[top=20,left=20,bottom=20,right=20]"      --elk-nodeNodeBetweenLayers=30      --elk-edgeNodeBetweenLayers=20      input.d2 output.png
   ```

5. Write `README.md` with scope, IADT method, IVV category, source-view copies, definition-view catalogue, version coverage, pass/fail constraints, viewpoints including statistics and fault hardening, expected report locations, status, assumptions, and residual gaps.
6. Write `coverage_update.md` containing the exact proposed master-plan row/status text for the integration subagent.
7. Do not stage, commit, push, or edit `ADS/MBSE/tests/README.md`.
8. Return a concise final summary with changed files, render status, and open assumptions.

## Acceptance criteria

The orchestration is successful when:

- Every issue 001-013 has a corresponding `ADS/MBSE/tests/<activity-id>/README.md`.
- Each activity has copied source views and at least one rendered D2 definition view; more views are expected for functional-chain/scenario tests.
- `ADS/MBSE/tests/README.md` is updated once by the integration subagent so all newly defined activities are marked definition-ready or explicitly gap/N/A-limited.
- Residual ambiguities are documented, not silently resolved by invented requirements.
- Temporary issue files are removed after integration.
- No push is performed.

## Completion status

- Issues 001-013 produced modeled definitions under `ADS/MBSE/tests/<activity-id>/` with copied source views and rendered definition views.
- The master plan `ADS/MBSE/tests/README.md` has been integrated and now marks the newly modeled activities as definition-ready/execution-pending or explicitly N/A/gap-limited.
- Temporary issue files, subagent logs, and consumed coverage-update snippets were removed after integration; this plan file remains as the overarching plan artifact requested by the user.
- No push was performed.
