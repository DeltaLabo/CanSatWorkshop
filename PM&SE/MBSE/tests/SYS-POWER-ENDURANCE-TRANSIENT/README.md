# SYS-POWER-ENDURANCE-TRANSIENT — full-system power under mission load

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
System power endurance and transient behavior with assembled subsystem loads, RF, sensors, dashboard/ground station and servo/PDM actuation branch.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Assembled CanSat PDS/ESS rails, OBCC/ADS/AMS/PDM/S&A loads, DPS where applicable |
| Verification means | 6 h On-mode load profile plus startup, RF transmit, sensor collection, command, servo transient and fault branches |
| Stimulus / scenario | Run representative mission load profile, load steps, servo actuation safe fixture, RF transmit cadence, sensor updates; monitor rails/current/thermal/reset |
| Environment / configuration | Current-limited safe setup, battery/emulator policy, thermal limits, ambient recorded, Li-ion safety controls if cell used |
| Statistical method | 6 h single-run functional evidence; repeated survival claims per IVV; continuous samples >=1 Hz or declared cadence |
| Fault-hardening cases | servo stall, RF transmit current, load step, low battery, regulator thermal shutdown, connector heating |
| Pass/fail oracle | PASS iff required rails remain in tolerance, no brownout/reset/watchdog/reconnect caused by transients, thermal/current limits remain safe, 6 h endurance completes under predeclared load profile, and anomalies are dispositioned. |
| Required evidence | rail/current/thermal logs, reset markers, load profile, photos, safety records, report |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-POWER-ENDURANCE-TRANSIENT_view1_system_verification_chain.d2`](definition_views/SYS-POWER-ENDURANCE-TRANSIENT_view1_system_verification_chain.d2) | [`definition_views/SYS-POWER-ENDURANCE-TRANSIENT_view1_system_verification_chain.png`](definition_views/SYS-POWER-ENDURANCE-TRANSIENT_view1_system_verification_chain.png) |
