# PDM-VV-CON-006 — process/no-blocking timing

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-006/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | PDM/OBCC deployment processing path timing |
| Verification means | Instrumentation/static analysis |
| Stimulus / analysis inputs | Exercise nominal/fault decision path under load |
| Statistical method | n=59 zero-violation for strict deadline |
| Fault-hardening cases | infinite loop, blocking wait, overloaded scheduler |
| Pass/fail oracle | Process/calculate path remains bounded (<5 ms where applicable) and no unbounded blocking prevents safe/error telemetry |
| Required evidence | timing traces, source review |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-006/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-006_view1_verification_chain.d2`](definition_views/PDM-VV-CON-006_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-006_view1_verification_chain.png`](definition_views/PDM-VV-CON-006_view1_verification_chain.png) |
