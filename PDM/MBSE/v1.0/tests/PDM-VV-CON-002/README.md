# PDM-VV-CON-002 — angular-rate accuracy <30 deg/s

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-002/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | ADS angular-rate input used by deployment trigger robustness |
| Verification means | Testing/analysis referencing ADS gyro definition or robust-threshold analysis |
| Stimulus / analysis inputs | Use calibrated tachometer/motor or ADS evidence and threshold robustness review |
| Statistical method | n=59 matched samples per axis/rate for strict claim |
| Fault-hardening cases | bias drift, saturation, stale IMU |
| Pass/fail oracle | Angular-rate error plus uncertainty <30 deg/s over trigger range or deployment threshold robustness proven |
| Required evidence | ADS evidence reference, analysis table |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-002/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-002_view1_verification_chain.d2`](definition_views/PDM-VV-CON-002_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-002_view1_verification_chain.png`](definition_views/PDM-VV-CON-002_view1_verification_chain.png) |
