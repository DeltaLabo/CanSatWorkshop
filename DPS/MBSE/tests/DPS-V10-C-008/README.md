# DPS-V10-C-008 — 4x4 plot matrix/layout

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-C-008/`.

## Purpose

Defines the DPS v1.0 4x4 plot matrix/layout verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS dashboard 4x4 layout/mapping with selected top-left attitude model, telemetry cells, and separate deployment-status indicator/banner |
| Verification means | Inspection/demonstration with canonical payload replay, resize/display checks, screenshots, and mapping table |
| Stimulus / input conditions | Load dashboard, replay canonical valid/missing/stale payloads including all `deployment_status` enum codes `0..9` and missing/unrecognized status cases, resize through declared window sizes |
| Environment / configuration | Declared screen/browser/Tkinter version, selected v1.0 telemetry cells, top-left pitch/roll/yaw attitude model |
| Statistical method | 100% layout/mapping inspection over declared display sizes; no sampling reliability claim |
| Fault-hardening cases | cell swap, hidden axis label, missing/unrecognized `deployment_status`, false deployed display for non-`OPEN_CONFIRMED` status, stale field shown valid, resize clipping |
| Pass/fail oracle | PASS iff 4x4 matrix is present, top-left renders pitch/roll/yaw attitude, selected telemetry cells match oracle, `deployment_status` is visible in a persistent adjacent indicator/banner without replacing required cells, raw code/symbol/category are shown, only `OPEN_CONFIRMED` is displayed as deployed, missing/unrecognized/non-success statuses are not shown as deployed, missing/stale fields are flagged, and resize does not hide required data |
| Required evidence archive | screenshots/video, mapping checklist including status code/symbol/category and no-false-deployed cases, replay log, display/version record, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-C-008/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-C-008_view1_verification_chain.d2`](definition_views/DPS-V10-C-008_view1_verification_chain.d2) | [`definition_views/DPS-V10-C-008_view1_verification_chain.png`](definition_views/DPS-V10-C-008_view1_verification_chain.png) |
