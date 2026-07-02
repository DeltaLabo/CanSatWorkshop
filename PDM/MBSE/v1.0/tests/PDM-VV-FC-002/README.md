# PDM-VV-FC-002 — pre-launch preparation scenario

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-FC-002/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Fold/repack/place cap/servo close/retain scenario |
| Verification means | Demonstration/inspection with repeated preparation cycles and no-premature-open checks |
| Stimulus / analysis inputs | Perform 10 repack/close/retain cycles on representative article |
| Statistical method | 10 cycles screening; every flight article inspected |
| Fault-hardening cases | misfold, cap mis-seat, servo drift, damage, premature pulse |
| Pass/fail oracle | Parachute folds/reintroduces without damage, cap seats, servo closes/retains, no premature open pulse, preparation damage/retention checks pass |
| Required evidence | cycle log, photos/video, PWM/position evidence |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-FC-002/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-FC-002_view1_verification_chain.d2`](definition_views/PDM-VV-FC-002_view1_verification_chain.d2) | [`definition_views/PDM-VV-FC-002_view1_verification_chain.png`](definition_views/PDM-VV-FC-002_view1_verification_chain.png) |
