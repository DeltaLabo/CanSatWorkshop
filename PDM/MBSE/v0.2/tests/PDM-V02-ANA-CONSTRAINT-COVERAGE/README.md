# PDM-V02-ANA-CONSTRAINT-COVERAGE — v0.2 constraint coverage analysis

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-V02-ANA-CONSTRAINT-COVERAGE/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- PDM/MBSE/v0.2 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | v0.2 BLE/range/power/terminal-speed constraints |
| Verification means | Coverage analysis |
| Stimulus / analysis inputs | Map each v0.2 constraint to modeled definition/evidence |
| Statistical method | 100% coverage census |
| Fault-hardening cases | orphan constraint, obsolete power criteria |
| Pass/fail oracle | Every active constraint assigned to definition/evidence or controlled N/A/deferred rationale |
| Required evidence | coverage matrix |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-V02-ANA-CONSTRAINT-COVERAGE/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-V02-ANA-CONSTRAINT-COVERAGE_view1_verification_chain.d2`](definition_views/PDM-V02-ANA-CONSTRAINT-COVERAGE_view1_verification_chain.d2) | [`definition_views/PDM-V02-ANA-CONSTRAINT-COVERAGE_view1_verification_chain.png`](definition_views/PDM-V02-ANA-CONSTRAINT-COVERAGE_view1_verification_chain.png) |
