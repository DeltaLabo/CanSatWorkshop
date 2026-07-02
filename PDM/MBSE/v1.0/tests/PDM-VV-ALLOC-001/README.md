# PDM-VV-ALLOC-001 — ADS sensing/processing allocation review

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-ALLOC-001/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | ADS kinematic sensing and ADS processing functions used by deployment decision |
| Verification means | 100% model/source allocation analysis |
| Stimulus / analysis inputs | Review functions, owners, data flows and boundaries |
| Statistical method | 100% allocation census |
| Fault-hardening cases | foreign function, missing freshness, bad calibration ownership |
| Pass/fail oracle | IMU sensing stays in ADS; processing outputs fresh-valid status; all boundary crossings use modeled CEs |
| Required evidence | allocation matrix, owner responses |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-ALLOC-001/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-ALLOC-001_view1_verification_chain.d2`](definition_views/PDM-VV-ALLOC-001_view1_verification_chain.d2) | [`definition_views/PDM-VV-ALLOC-001_view1_verification_chain.png`](definition_views/PDM-VV-ALLOC-001_view1_verification_chain.png) |
