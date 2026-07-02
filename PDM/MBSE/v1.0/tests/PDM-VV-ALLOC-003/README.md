# PDM-VV-ALLOC-003 — mechanical/preparation/descent allocation review

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-ALLOC-003/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | User, holder, trigger, parachute, descent speed control allocations |
| Verification means | 100% mechanical/function allocation review |
| Stimulus / analysis inputs | Review fold/repack/cap/holder/servo/parachute/descent-speed functions |
| Statistical method | 100% allocation census |
| Fault-hardening cases | misfold, cap mis-seat, missing descent-speed owner |
| Pass/fail oracle | All preparation, retain/open/unfold/limit functions are allocated to modeled actors/components; no missing/foreign functions |
| Required evidence | allocation checklist, photos/model refs |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-ALLOC-003/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-ALLOC-003_view1_verification_chain.d2`](definition_views/PDM-VV-ALLOC-003_view1_verification_chain.d2) | [`definition_views/PDM-VV-ALLOC-003_view1_verification_chain.png`](definition_views/PDM-VV-ALLOC-003_view1_verification_chain.png) |
