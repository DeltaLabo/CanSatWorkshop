# SYS-MISSION-REHEARSAL — full assembled CanSat + DPS mission sequence

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
Integrated operational rehearsal across startup, Stand-by, On, sensor collection, telemetry, command, deployment-safe branch, logging, dashboard and shutdown.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Full assembled CanSat, PDS, ADS, AMS, OBCC, PDM, S&A, DPS dashboard/ground station |
| Verification means | Safe-fixture rehearsal with scripted mission timeline, canonical commands, telemetry capture, dashboard/CSV evidence, and deployment inhibit/trigger branches |
| Stimulus / scenario | Boot -> Stand-by telemetry -> On -> nominal sensor telemetry -> command/uplink -> deployment-safe trigger/emergency branch -> fault branch -> shutdown |
| Environment / configuration | Lab safe fixture for actuator/parachute, live release inhibited unless separately authorized, legal RF or cabled/near-field setup |
| Statistical method | At least one complete nominal rehearsal plus required branch cases; 29/29 if making R90/C95 mission-rehearsal reliability claim |
| Fault-hardening cases | stale sensor data, invalid command, RF loss, PDM jam/no-open, brownout, dashboard disconnect, CSV restart |
| Pass/fail oracle | PASS iff startup reaches readiness, Stand-by inhibits deployment while telemetry continues, On branch uses fresh-valid ADS/AMS data, accepted trigger/emergency produces `deployment_status = OPEN_CONFIRMED` within `<=5 s` in safe fixture with PDM/actuator observer evidence or fault status without false success, DPS displays/records telemetry including raw `deployment_status` code/symbol/category, all non-`OPEN_CONFIRMED` statuses (`COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, unrecognized) remain non-success, and no reset/brownout/unbounded fault occurs. |
| Required evidence | timeline log, OBCC/DPS raw frames, CSV with `deployment_status_code`/`deployment_status`/`deployment_status_category`, screenshots/video, actuator observer evidence, fault ledger |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-MISSION-REHEARSAL_view1_system_verification_chain.d2`](definition_views/SYS-MISSION-REHEARSAL_view1_system_verification_chain.d2) | [`definition_views/SYS-MISSION-REHEARSAL_view1_system_verification_chain.png`](definition_views/SYS-MISSION-REHEARSAL_view1_system_verification_chain.png) |
