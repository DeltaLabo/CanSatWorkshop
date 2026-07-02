# SYS-DEPLOYMENT-SAFE-LIVE — ADS/OBCC/PDM/PDS/S&A deployment interaction

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
System deployment safety interaction with safe fixture and any live authorization separated.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | ADS freshness/status, OBCC deployment policy, PDM actuator/parachute, PDS power, S&A clearance/retention, DPS status display |
| Verification means | Safe-fixture branch testing of Stand-by inhibit, On normal trigger/emergency request, no-open/jam/fault, clearance and power interaction; live release only with approved authorization |
| Stimulus / scenario | Apply valid and invalid ADS trigger stimuli, emergency command, Stand-by and On modes, PDM jam/no-open, power transient and S&A clearance checks |
| Environment / configuration | Safe fixture blocks uncontrolled release; live deployment requires separate hazard review and range authorization |
| Statistical method | 29/29 positive and 29/29 negative no-failure trials for R90/C95 if claimed; otherwise declared functional branch coverage |
| Fault-hardening cases | premature open, stale ADS trigger, jam, no-open, PDS brownout, cap interference, false GUI success |
| Pass/fail oracle | PASS iff Stand-by inhibits all deployment, On valid trigger/emergency produces `deployment_status = OPEN_CONFIRMED` within `<=5 s` with PDM/actuator observer evidence or explicit fault/safe/error status with no false success; `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, and unrecognized status are never counted deployed; S&A clearance is maintained, PDS rails are safe, and DPS shows raw status code/symbol/category correctly. |
| Required evidence | mode/trigger logs, actuator video/current/position, raw `deployment_status` code/symbol/category evidence, DPS screenshots, power traces, S&A clearance photos |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-DEPLOYMENT-SAFE-LIVE_view1_system_verification_chain.d2`](definition_views/SYS-DEPLOYMENT-SAFE-LIVE_view1_system_verification_chain.d2) | [`definition_views/SYS-DEPLOYMENT-SAFE-LIVE_view1_system_verification_chain.png`](definition_views/SYS-DEPLOYMENT-SAFE-LIVE_view1_system_verification_chain.png) |
