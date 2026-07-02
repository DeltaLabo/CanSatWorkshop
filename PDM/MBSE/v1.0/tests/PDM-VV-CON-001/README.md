# PDM-VV-CON-001 — parachute diameter <=30 cm

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-001/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | PDM parachute deployed/stowed diameter and fit |
| Verification means | Inspection/demonstration with calibrated ruler/calipers and stowed/ deployed photos |
| Stimulus / analysis inputs | Measure maximum deployed diameter and stowed clearance |
| Statistical method | 100% measurement of each accepted parachute article |
| Fault-hardening cases | post-fold deformation, measurement uncertainty, interference |
| Pass/fail oracle | Deployed maximum diameter <=30 cm and stowed pack does not interfere with cap/servo path |
| Required evidence | measurements, photos, uncertainty |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-001/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-001_view1_verification_chain.d2`](definition_views/PDM-VV-CON-001_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-001_view1_verification_chain.png`](definition_views/PDM-VV-CON-001_view1_verification_chain.png) |
