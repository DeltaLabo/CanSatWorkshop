# PDM-VV-CON-003 — no manual/BLE flight-command path

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-003/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Flight deployment command path boundary |
| Verification means | Static release review and black-box command attempts |
| Stimulus / analysis inputs | Review build flags/UI/BLE/debug paths; attempt legacy/manual/BLE commands in flight mode |
| Statistical method | 100% release review; 29 no-open attempts for R90/C95 if claimed |
| Fault-hardening cases | debug leakage, legacy BLE, standby bypass |
| Pass/fail oracle | No manual/BLE/debug command reaches open path in flight mode; only OBCC policy path can command open |
| Required evidence | source/build review, attempt logs |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-003/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-003_view1_verification_chain.d2`](definition_views/PDM-VV-CON-003_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-003_view1_verification_chain.png`](definition_views/PDM-VV-CON-003_view1_verification_chain.png) |
