# PDM-VV-CON-004 — 0-degree init/no false open

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-004/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Servo initial closed/0-degree state and no false open |
| Verification means | Boot/standby/reset demonstration with PWM/position observer |
| Stimulus / analysis inputs | Power cycle and mode changes with cap/holder installed |
| Statistical method | 59/59 timing/position samples for strict timing claim |
| Fault-hardening cases | boot pulse, reset, brownout, servo drift |
| Pass/fail oracle | Servo initializes closed/0-degree, no false open pulse, no status success unless OPEN_CONFIRMED |
| Required evidence | PWM/position traces, video |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-004/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-004_view1_verification_chain.d2`](definition_views/PDM-VV-CON-004_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-004_view1_verification_chain.png`](definition_views/PDM-VV-CON-004_view1_verification_chain.png) |
