# SYS-END-TO-END-DATA — truth/reference stimulus to DPS CSV/dashboard

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
End-to-end data observability from ADS/AMS/PDS/PDM status through OBCC LoRa to DPS parser/CSV/dashboard.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | ADS/AMS/PDS/PDM/OBCC data paths, LoRa payload, DPS parser/CSV/dashboard |
| Verification means | Canonical truth/reference payload and fault replay through OBCC/DPS, with timestamp/age/status correlation and dashboard/CSV evidence |
| Stimulus / scenario | Inject known sensor values, status enum cases, deployment_status enum cases, invalid/stale/no-data/timeout/fault cases |
| Environment / configuration | Bench or integrated setup with synchronized monotonic time/sequence or documented correlation, parser/schema versions frozen |
| Statistical method | 100% canonical field/status cases; N>=30 nominal frame replay for parser/display stability |
| Fault-hardening cases | schema drift, stale-valid, missing `deployment_status`, wrong unit, timestamp wrap, invalid/missing/unrecognized enum, CSV/dashboard mismatch, false deployed display/storage |
| Pass/fail oracle | PASS iff `OBCC-LORA-PAYLOAD-v1.0` canonical values, units, timestamps, age/status, and `deployment_status` code/symbol/category are preserved from source observation to DPS CSV/dashboard with exact CSV columns `deployment_status_code`, `deployment_status`, and `deployment_status_category`; only `OPEN_CONFIRMED` is deployed/success; `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, and unrecognized status are non-success; ADS/AMS subsystem evidence keeps the `>=5 Hz` sensor-to-OBCC freshness path separate from the OBCC/DPS `2 s` LoRa packaging; fresh sensor data require `VALID` and `age_ms <= 400 ms`; stale/default/fault/no-data/timeout values are never marked `VALID` or displayed/logged as fresh; no obsolete RH field is required. |
| Required evidence | truth payloads, source/OBCC/DPS logs, CSV, screenshots, parser version, comparison script |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-END-TO-END-DATA_view1_system_verification_chain.d2`](definition_views/SYS-END-TO-END-DATA_view1_system_verification_chain.d2) | [`definition_views/SYS-END-TO-END-DATA_view1_system_verification_chain.png`](definition_views/SYS-END-TO-END-DATA_view1_system_verification_chain.png) |
