# PDM-VV-CON-007 — non-VALID/fault deployment behavior

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-007/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Non-VALID ADS/PDM/fault statuses and OBCC safe/error behavior |
| Verification means | Fault-injection testing/analysis |
| Stimulus / analysis inputs | Inject stale/no-data/timeout/sensor-fault/init-fail/jam/no-open/unknown cases |
| Statistical method | 29 no-false-open attempts per class if claiming R90/C95 |
| Fault-hardening cases | stale valid, jam false open, timeout hidden |
| Pass/fail oracle | Non-VALID required input is not a normal trigger; no false success; safe/error/fault status exposed |
| Required evidence | fault matrix, telemetry/status logs |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-007/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-007_view1_verification_chain.d2`](definition_views/PDM-VV-CON-007_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-007_view1_verification_chain.png`](definition_views/PDM-VV-CON-007_view1_verification_chain.png) |
