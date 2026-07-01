# PDS & ESS multi-version MBSE verification plan

Assumption: the requested `DPS&ESS/MBSE/` target refers to the repository path `PDS&ESS/MBSE/`.

## Goal

Use the Capella physical-architecture test-definition workflow (`/Users/antho/agent-tools/syseng/prompts/capella-pa-tests-definition.md`) with the `~/agent-tools/syseng` package to create model-based verification definitions for every existing PDS & ESS development baseline: `v0.1`, `v0.2`, `v0.3`, and `v1.0` flight readiness. Existing `v1.0` definitions are reused rather than duplicated.

## Delegated work packages

- `PDS-V01-GATE-001` — v0.1 advancement gate to v0.2: power-path inspection/smoke characterization, connector/cable constraint, power on/off safe state.
- `PDS-VV-V02-FC-001` — v0.2 advancement gate to v0.3: INA219 measurement, I2C/Serial0 reporting, 5 Hz cadence, variable-getter/timing/no-blocking constraints.
- `PDS-V03-GATE-001` — v0.3 advancement gate to v1.0: protection detection/cutoff/restore screening, endurance setup, and battery-supervision regression.
- `PDS-VV-CON-002` — v1.0 flight-readiness 6 h On-mode endurance definition.
- `PDS-VV-CON-009` — v1.0 PCB manufacturability / Carvera Air DFM and coupon/board inspection definition.
- `PDS-VV-ALLOC-001` — v1.0 power-path allocation and external-actor interface analysis, also covering `PDS-VV-ALLOC-003`.

Existing v1.0 definitions preserved and indexed: `PDS-VV-PC-001`, `PDS-VV-FC-001`, `PDS-VV-FC-002`, `PDS-VV-CON-001`, `PDS-VV-CON-003`, and `PDS-VV-CON-004`.

## Integration rules applied

- Baseline source views under `PDS&ESS/MBSE/v*/` remain read-only; each test folder carries `baseline/` copies.
- Per-test READMEs document scope, IADT method, traceability, pass/fail constraints, statistical/fault-hardening viewpoint, evidence path, assumptions, and blockers.
- `PDS&ESS/MBSE/tests/README.md` remains the master index for both incremental development gates and v1.0 final acceptance.
- Generated D2 views were rendered to PNG and spot-checked for D2 syntax with ELK rendering.
- No push is allowed until user approval.

## Remaining execution blockers

Definitions are model-ready, but execution still requires campaign data such as load profiles, instrument IDs/calibration status, Carvera Air rule-set closure, software/firmware commit IDs, safety documents, and actual evidence archives under `PDS&ESS/MBSE/tests/results/<activity-id>/`.
