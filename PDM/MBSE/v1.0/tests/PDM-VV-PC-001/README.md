# PDM-VV-PC-001 — physical component inspection

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-PC-001/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | All PDM v1.0 physical components: parachute module, holder, servo/trigger, ADS/OBCC interfaces, cap/top-module context |
| Verification means | 100% inspection with build record, photos, part IDs, orientation/condition checklist |
| Stimulus / analysis inputs | Inspect every flight/workshop article before functional tests |
| Statistical method | 100% census; no sampling reliability claim |
| Fault-hardening cases | wrong part/orientation, damage, missing holder/servo/parachute/cap context, untraceable article |
| Pass/fail oracle | Every modeled PC present/correct/undamaged/traceable; substitutions or missing critical PCs fail |
| Required evidence | inspection checklist, photos, article IDs, deviations |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-PC-001/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-PC-001_view1_verification_chain.d2`](definition_views/PDM-VV-PC-001_view1_verification_chain.d2) | [`definition_views/PDM-VV-PC-001_view1_verification_chain.png`](definition_views/PDM-VV-PC-001_view1_verification_chain.png) |
