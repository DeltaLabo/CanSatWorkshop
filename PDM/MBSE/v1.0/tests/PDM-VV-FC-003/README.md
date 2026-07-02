# PDM-VV-FC-003 — terminal descent-speed verification

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-FC-003/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Deployed parachute descent-speed limiting to <=11 m/s |
| Verification means | Drop/descent-speed testing or applicable linked evidence analysis |
| Stimulus / analysis inputs | Drop representative mass/configuration with deployed parachute; calibrated video/time-distance or equivalent; wind recorded |
| Statistical method | 10 measured drops screening; 29 independent drops for R90/C95 if claimed |
| Fault-hardening cases | partial unfold, tangle, mass mismatch, video calibration, wind >3 m/s |
| Pass/fail oracle | Measured terminal speed plus uncertainty/guard band <=11 m/s with representative mass/configuration and accepted wind/environment; failed/partial-open/tangle handled by predeclared anomaly rules |
| Required evidence | raw video/logs, calibration, mass, wind, speed analysis |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-FC-003/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-FC-003_view1_verification_chain.d2`](definition_views/PDM-VV-FC-003_view1_verification_chain.d2) | [`definition_views/PDM-VV-FC-003_view1_verification_chain.png`](definition_views/PDM-VV-FC-003_view1_verification_chain.png) |
