# SYS-ENVIRONMENTAL-REGRESSION — critical functions after mechanical/environmental screens

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
Post-screen regression of critical functions after approved tailored S&A drop/vibration/landing screens.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Assembled CanSat physical structure, backplane, connectors, rails, RF, sensor, command, deployment-safe and dashboard critical functions |
| Verification means | Execute approved screens, inspect before/after, then run functional regression subset |
| Stimulus / scenario | Tailored screens per S&A definitions: controlled orientations/axes/events/durations/surfaces, no reseat/tighten before post-check unless recorded as fail/hold |
| Environment / configuration | Approved lab/workshop screen fixture, calibrated event/measurement tools, safety boundary |
| Statistical method | 100% post-screen inspection of required features plus regression subset; no reliability claim unless repeated articles/trials defined |
| Fault-hardening cases | connector unseat, battery movement, backplane crack, rail short, RF antenna shift, parachute interference |
| Pass/fail oracle | PASS iff no unapproved movement/damage/loose link, continuity/isolation/rails remain valid, RF/telemetry/dashboard basic regression passes, deployment clearance/safe status preserved, and any anomaly has disposition/retest. |
| Required evidence | pre/post photos/witness marks, screen logs, continuity/rail/RF/function logs, anomaly ledger |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-ENVIRONMENTAL-REGRESSION_view1_system_verification_chain.d2`](definition_views/SYS-ENVIRONMENTAL-REGRESSION_view1_system_verification_chain.d2) | [`definition_views/SYS-ENVIRONMENTAL-REGRESSION_view1_system_verification_chain.png`](definition_views/SYS-ENVIRONMENTAL-REGRESSION_view1_system_verification_chain.png) |
