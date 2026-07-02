# PDM-V01-INSP-PC — v0.1 physical inspection

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-V01-INSP-PC/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- PDM/MBSE/v0.1 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | v0.1 Dummy CanSat, Top module, Parachute configuration |
| Verification means | Inspection with setup photos and damage check |
| Stimulus / analysis inputs | Inspect before/after fall-test campaign |
| Statistical method | 100% census |
| Fault-hardening cases | damaged parachute, wrong mass/top module |
| Pass/fail oracle | All modeled PCs present/configured; no damage invalidates accepted fall-test segment |
| Required evidence | photos/checklist |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-V01-INSP-PC/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-V01-INSP-PC_view1_verification_chain.d2`](definition_views/PDM-V01-INSP-PC_view1_verification_chain.d2) | [`definition_views/PDM-V01-INSP-PC_view1_verification_chain.png`](definition_views/PDM-V01-INSP-PC_view1_verification_chain.png) |
