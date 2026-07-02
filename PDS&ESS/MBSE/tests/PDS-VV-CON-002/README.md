# PDS-VV-CON-002 — 6h On-mode endurance constraint (v1.0)

## Purpose
Create a full modeled verification definition for the explicit final flight constraint:
> `[C] Enough for 6 hours continuous operation in On mode`.

## Current status
- Baseline from `v1.0` copied into `baseline/`.
- Chain/teardown definitions modeled and ready for review.
- Execution evidence still pending.

## IADT / IVV context
- **IADT method:** Testing / Analysis
- **Category:** Constraint-derived endurance campaign definition with explicit margin/fault-hardening chain.
- **IVV linkage:** `IVV`
- **Referenced requirements:** `PDS-R2`, `PDS-R6`, `PDS-R7`
- **Referenced constraint sources:** `PDS-VV-CON-002`

## Model scope and added artifacts
This folder contains 5 modeled views:

1. `PDS_VV_CON_002_view1_physical_endurance_testbench.d2`
   - Physical testbench and interface wiring for 6h On-mode execution
   - Includes pre-test setup, load-profile/emulation, continuous rail logging, INA219 capture, ambient/thermal supervision, and safe containment links.
2. `PDS_VV_CON_002_view2_logical_endurance_interfaces.d2`
   - Logical test actors, logical components, and verification-only exchange/model interfaces.
   - Adds explicit functions for pre-test review, battery preconditioning, On-mode load profile control, continuous rail/supervision logging, anomaly handling, and safe end-of-run cutoff.
3. `PDS_VV_CON_002_view3_functional_allocation_testbench.d2`
   - Functional allocation of verification-only functions and external fixtures to source LCs.
4. `PDS_VV_CON_002_view4_six_hour_endurance_chain.d2`
   - Endurance functional chain for one full 6h run including looped sampling, quality checks, and fault response path.
5. `PDS_VV_CON_002_view5_margin_fault_hardening_analysis_chain.d2`
   - Explicit margin/fault-hardening analysis chain for load variation, logging burden, thermal rise, battery aging, and stale-data/error scenarios.

All five views have companion PNG renderings.

## Traceability and reuse (no duplicate modeling)
The activity intentionally reuses the already-modeled intent from:
- `PDS-VV-CON-001` (charge readiness and charger/profile assumptions)
- `PDS-VV-CON-004` (rail supply test intent)
- `PDS-VV-CON-003` (protection-failure probability/demand style)
- `PDS-VV-FC-001` (full power/protection function behavior)
- `PDS-VV-FC-002` (battery-monitoring/INA219 timing and I2C fault handling intent)

This provides reuse without re-instantiating full chain internals already covered by the above test definitions.

## Pass/fail criteria encoded in the model
- Pre-test: ambient/safety review + battery preconditioning + fixture readiness complete before start.
- Run: On-mode 6h execution proceeds with continuous load-profile control and periodic sample capture.
- Acceptance checks: rail samples continuous and fresh; INA219 data and status not stale/faulty; no brownout/reset/unsafe thermal rise observed; no protected unsafe-rail condition that should command cutoff.
- End: clean safe cutoff and safe-state observation with complete evidence package.
- Failure handling: stale data, telemetry-load overload indicators, thermal margin violations, or repeated protection anomalies fail the run and move to safe-state path.

## Execution-only prerequisites (predeclared before run)
- The 6 h On-mode run is valid only after the campaign records the exact representative load profile/current budget, load-emulator settings, battery preconditioning/SOC method, logging/sample cadence, rail/freshness monitoring points, ambient/thermal envelope, anomaly ledger fields, stop/abort criteria, and end-of-run safe-state criteria.
- If the representative load profile/current budget is not predeclared and approved before the run, the evidence is limited to characterization and shall not be used for strict final flight acceptance.
- Protection-demonstration and failure-probability credit is not claimed by this activity unless linked to accepted `PDS-VV-CON-003` evidence; this activity defines 6 h endurance behavior and records any protection anomaly as a run failure/hold.

## Evidence path
- Planned evidence: `tests/results/PDS-VV-CON-002/`
- Execution data expected: raw rail/current/INA219/status logs, declared load profile/current-budget sheet, load-emulator settings, battery preconditioning/SOC evidence, sampling metadata, ambient/thermal records, anomaly ledger, stop/abort decisions, pre/post environmental and safety checks, and run-termination/safe-state artifacts.

## Baseline artifacts
- Baseline files are copied from `v1.0` into `baseline/`:
  - `PDS_v1.0_view1_physical.d2`
  - `PDS_v1.0_view2_logical.d2`
  - `PDS_v1.0_view3_functional_allocation.d2`
  - `PDS_v1.0_view4_power_and_protection_chain.d2`
  - `PDS_v1.0_view5_battery_supervision_chain.d2`
