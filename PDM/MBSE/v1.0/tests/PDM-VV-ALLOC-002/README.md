# PDM-VV-ALLOC-002 — OBCC/PDM policy allocation review

**Status:** Model-defined / not executed. This activity is no longer a planning backlog item; no pass/fail credit is claimed until `results/PDM-VV-ALLOC-002/report.md` binds execution evidence to this definition.

## Controlled references
- PM&SE/IVV.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PDM/MBSE/v1.0 source views

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | OBCC decision ownership and PDM command execution/status allocation |
| Verification means | 100% state-machine/allocation review |
| Stimulus / analysis inputs | Review OBCC mode/trigger/emergency/safe/error and PDM command execution boundary |
| Statistical method | 100% allocation census |
| Fault-hardening cases | premature deployment, lost observability, policy redefinition in PDM |
| Pass/fail oracle | OBCC owns deployment policy; PDM executes commanded actuation and exposes status; no manual/BLE flight path allocated |
| Required evidence | allocation matrix, OBCC policy cross-reference |

## Reporting rules

Predeclare UUT/configuration, firmware/build/source references, equipment IDs/calibration, environment, safety controls, deviations and waivers. Missing required evidence is **HOLD**. False deployment success, unbounded timing, unsafe actuator/power behavior, or unapproved deviation is **FAIL**. Archive raw evidence, derived analysis, photos/video/waveforms where applicable, and final `report.md` under `results/PDM-VV-ALLOC-002/`.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Verification chain | [`definition_views/PDM-VV-ALLOC-002_view1_verification_chain.d2`](definition_views/PDM-VV-ALLOC-002_view1_verification_chain.d2) | [`definition_views/PDM-VV-ALLOC-002_view1_verification_chain.png`](definition_views/PDM-VV-ALLOC-002_view1_verification_chain.png) |
