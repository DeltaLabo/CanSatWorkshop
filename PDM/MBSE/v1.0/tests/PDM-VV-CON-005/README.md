# PDM-VV-CON-005 — I2C timing/fault semantics

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-CON-005/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | I2C/process interaction used by deployment trigger |
| Verification means | Testing/analysis tied to CE-001 and ADS freshness |
| Stimulus / analysis inputs | Inject I2C faults and observe no normal trigger from non-VALID data |
| Statistical method | n=59 timing samples where deadline claimed |
| Fault-hardening cases | stuck bus, timeout masked valid |
| Pass/fail oracle | I2C faults/status propagate bounded non-VALID states; no stale-valid trigger |
| Required evidence | fault logs, timing table |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-CON-005/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-CON-005_view1_verification_chain.d2`](definition_views/PDM-VV-CON-005_view1_verification_chain.d2) | [`definition_views/PDM-VV-CON-005_view1_verification_chain.png`](definition_views/PDM-VV-CON-005_view1_verification_chain.png) |
