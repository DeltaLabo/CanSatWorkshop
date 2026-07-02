# PDM-V02-ANA-LC-FUNC-ALLOC — v0.2 allocation review

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-V02-ANA-LC-FUNC-ALLOC/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- PDM/MBSE/v0.2 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | v0.2 OBCC/parachute trigger/descent-speed/power allocations |
| Verification means | 100% allocation analysis |
| Stimulus / analysis inputs | Review source v0.2 allocation view and evidence |
| Statistical method | 100% allocation census |
| Fault-hardening cases | foreign function, missing owner |
| Pass/fail oracle | Functions allocated to modeled LCs/EAs with no foreign IMU/altitude fallback; power functions owned by PDS context |
| Required evidence | allocation matrix |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-V02-ANA-LC-FUNC-ALLOC/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-V02-ANA-LC-FUNC-ALLOC_view1_verification_chain.d2`](definition_views/PDM-V02-ANA-LC-FUNC-ALLOC_view1_verification_chain.d2) | [`definition_views/PDM-V02-ANA-LC-FUNC-ALLOC_view1_verification_chain.png`](definition_views/PDM-V02-ANA-LC-FUNC-ALLOC_view1_verification_chain.png) |
