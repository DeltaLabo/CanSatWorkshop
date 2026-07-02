# PDM-V01-ALLOC-DSC — v0.1 descent-speed allocation analysis

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-V01-ALLOC-DSC/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- PDM/MBSE/v0.1 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | v0.1 Descent speed control LC and Limit terminal speed function |
| Verification means | Allocation analysis |
| Stimulus / analysis inputs | Review v0.1 source allocation and fall-test evidence link |
| Statistical method | 100% allocation census |
| Fault-hardening cases | missing/foreign allocation |
| Pass/fail oracle | LC remains under parachute and contains intended function only; no foreign allocation |
| Required evidence | allocation matrix |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-V01-ALLOC-DSC/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-V01-ALLOC-DSC_view1_verification_chain.d2`](definition_views/PDM-V01-ALLOC-DSC_view1_verification_chain.d2) | [`definition_views/PDM-V01-ALLOC-DSC_view1_verification_chain.png`](definition_views/PDM-V01-ALLOC-DSC_view1_verification_chain.png) |
