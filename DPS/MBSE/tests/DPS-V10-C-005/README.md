# DPS-V10-C-005 — CSV/session archive integrity

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-C-005/`.

## Purpose

Defines the DPS v1.0 CSV/session archive integrity verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS CSV file/session naming, no-overwrite policy, monotonic rows, checksum/source-log match including deployment_status columns |
| Verification means | Testing with repeated starts/restarts/same-second sessions, canonical payload replay, file-system checksum/content comparison |
| Stimulus / input conditions | Run at least 10 sessions including rapid restart and same-second collision cases; replay all valid `deployment_status` enum codes `0..9` plus missing/unrecognized invalid-status cases |
| Environment / configuration | Declared CSV directory, clock/timezone, file naming pattern, source accepted-payload log retained |
| Statistical method | 10/10 sessions no overwrite; 100% row/content match for replayed accepted frames |
| Fault-hardening cases | same-second collision, restart during write, invalid timestamp, disk permission/full, missing `deployment_status` columns, missing/unrecognized deployment status |
| Pass/fail oracle | PASS iff every session creates unique non-overwriting filename, rows are monotonic by source sequence/timestamp, row count and checksum/content match accepted source log, exact `deployment_status_code`, `deployment_status`, and `deployment_status_category` columns are preserved, only `OPEN_CONFIRMED` is categorized as deployed, and partial/corrupt writes are detected |
| Required evidence archive | directory listing, file hashes/checksums, source/replayed logs, CSVs, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-C-005/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-C-005_view1_verification_chain.d2`](definition_views/DPS-V10-C-005_view1_verification_chain.d2) | [`definition_views/DPS-V10-C-005_view1_verification_chain.png`](definition_views/DPS-V10-C-005_view1_verification_chain.png) |
