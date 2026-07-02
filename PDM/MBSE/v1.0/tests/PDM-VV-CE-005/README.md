# PDM-VV-CE-005 — torque margin analysis/test

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CE-005/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Servo/trigger torque exchange to parachute holder under representative pack/cap load |
| Verification means | Mechanical analysis plus controlled actuation trials and current/thermal observation |
| Stimulus / analysis inputs | Actuate representative holder load, worst-case cap/preload/friction, jam/stall fault cases |
| Statistical method | 10 acceptance actuations screening; 29/29 for R90/C95 release claim |
| Fault-hardening cases | friction, jam, weak servo, cap preload, thread interference, thermal/stall |
| Pass/fail oracle | Torque/linkage margin releases holder without unsafe heating/reset; jam/stall detected and not falsely successful |
| Required evidence | torque/current data, videos, load setup, thermal notes |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CE-005/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CE-005_view1_verification_chain.d2`](definition_views/PDM-VV-CE-005_view1_verification_chain.d2) | [`definition_views/PDM-VV-CE-005_view1_verification_chain.png`](definition_views/PDM-VV-CE-005_view1_verification_chain.png) |
