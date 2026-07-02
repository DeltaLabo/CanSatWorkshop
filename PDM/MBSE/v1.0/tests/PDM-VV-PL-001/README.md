# PDM-VV-PL-001 — physical link retention/continuity inspection

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-PL-001/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | All PDM v1.0 physical/electrical/mechanical links: servo cable/PWM/power, trigger-holder linkage, parachute/cap retention, ADS/OBCC paths |
| Verification means | 100% continuity/polarity/retention/workmanship inspection with pre/post handling checks |
| Stimulus / analysis inputs | Inspect links before actuation and after representative handling/environmental screens |
| Statistical method | 100% census; post-screen repeat for affected article |
| Fault-hardening cases | intermittent servo cable, reversed polarity, jammed holder, loose cap, thread/cap interference |
| Pass/fail oracle | Electrical links continuous/polarized with no shorts; mechanical links retain, move freely, and show no jam/looseness; post-screen checks remain within thresholds |
| Required evidence | continuity logs, photos/video, witness marks, retention notes |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-PL-001/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-PL-001_view1_verification_chain.d2`](definition_views/PDM-VV-PL-001_view1_verification_chain.d2) | [`definition_views/PDM-VV-PL-001_view1_verification_chain.png`](definition_views/PDM-VV-PL-001_view1_verification_chain.png) |
