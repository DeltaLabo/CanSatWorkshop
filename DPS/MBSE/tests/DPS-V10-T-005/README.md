# DPS-V10-T-005 — dashboard visualization

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-T-005/`.

## Purpose

Defines the DPS v1.0 dashboard visualization verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS decoder-to-dashboard visualization of v1.0 telemetry including pitch/roll/yaw attitude, deployment_status, stale/invalid fields, and latency alert |
| Verification means | Demonstration/testing with canonical payload replay, browser evidence where applicable, screenshots/video, DOM/UI/CSV mapping checks |
| Stimulus / input conditions | Replay canonical valid, stale, invalid, missing-field, high-latency, every `deployment_status` enum code `0..9`, and missing/unrecognized status payloads |
| Environment / configuration | Primary Chrome/Chromium strict-credit path if browser implementation exists; Tkinter evidence is limited/HOLD for browser-only claim |
| Statistical method | N=30 canonical payload cases covering valid/boundary/fault classes; no unmapped UI cells |
| Fault-hardening cases | invalid timestamp, stale values, missing deployment_status, unrecognized enum, browser refresh/reconnect, plot resize |
| Pass/fail oracle | PASS iff each payload field maps to selected plot/cell, top-left attitude renders pitch/roll/yaw, a separate persistent `deployment_status` indicator/banner preserves raw code/symbol/category, only `OPEN_CONFIRMED` displays as deployed, `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, and unrecognized states remain non-success, stale/invalid fields are visibly flagged/rejected, and latency alert follows threshold |
| Required evidence archive | payload replay log, screenshots/video covering deployed/non-success/fault/unknown/missing-status states, browser start command/URL or Tkinter limitation, mapping table with expected versus displayed status code/symbol/category, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-T-005/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-T-005_view1_verification_chain.d2`](definition_views/DPS-V10-T-005_view1_verification_chain.d2) | [`definition_views/DPS-V10-T-005_view1_verification_chain.png`](definition_views/DPS-V10-T-005_view1_verification_chain.png) |
