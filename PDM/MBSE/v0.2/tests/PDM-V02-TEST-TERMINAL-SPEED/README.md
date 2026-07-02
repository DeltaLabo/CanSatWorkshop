# PDM-V02-TEST-TERMINAL-SPEED — v0.2 terminal-speed companion

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-V02-TEST-TERMINAL-SPEED/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- PDM/MBSE/v0.2 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | v0.2 parachute terminal speed <=11 m/s or linked applicable evidence |
| Verification means | Drop testing or applicability analysis |
| Stimulus / analysis inputs | Measure v0.2 descent or cite applicable v0.1 evidence with mass/parachute/config rationale |
| Statistical method | 10 drops screening; 29 if reliability claimed |
| Fault-hardening cases | mass mismatch, wind, tangle, linked evidence invalid |
| Pass/fail oracle | Measured/linked speed plus uncertainty <=11 m/s; otherwise HOLD evidence gap |
| Required evidence | video/calibration/applicability report |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-V02-TEST-TERMINAL-SPEED/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-V02-TEST-TERMINAL-SPEED_view1_verification_chain.d2`](definition_views/PDM-V02-TEST-TERMINAL-SPEED_view1_verification_chain.d2) | [`definition_views/PDM-V02-TEST-TERMINAL-SPEED_view1_verification_chain.png`](definition_views/PDM-V02-TEST-TERMINAL-SPEED_view1_verification_chain.png) |
