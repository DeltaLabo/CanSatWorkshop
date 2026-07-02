# PDM-V02-INS-PC-PL-INVENTORY — v0.2 PC/PL inventory inspection

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-V02-INS-PC-PL-INVENTORY/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- PDM/MBSE/v0.2 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | PDM v0.2 physical components/links for BLE/manual deployment |
| Verification means | 100% inspection/continuity/retention checklist |
| Stimulus / analysis inputs | Inspect source v0.2 article and BLE/servo/power paths |
| Statistical method | 100% census |
| Fault-hardening cases | missing component, wrong wiring, loose servo cable |
| Pass/fail oracle | All modeled PCs/PLs present/correct, BLE/range/power/servo paths traceable; no unsafe open/short |
| Required evidence | checklist/photos/continuity |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-V02-INS-PC-PL-INVENTORY/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-V02-INS-PC-PL-INVENTORY_view1_verification_chain.d2`](definition_views/PDM-V02-INS-PC-PL-INVENTORY_view1_verification_chain.d2) | [`definition_views/PDM-V02-INS-PC-PL-INVENTORY_view1_verification_chain.png`](definition_views/PDM-V02-INS-PC-PL-INVENTORY_view1_verification_chain.png) |
