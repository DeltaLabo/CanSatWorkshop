# DPS-V10-C-006 — latency alert threshold

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-C-006/`.

## Purpose

Defines the DPS v1.0 latency alert threshold verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS latency computation and top alert behavior around the >1.0 s threshold |
| Verification means | Testing with monotonic timestamp source/replay harness and UI/CSV evidence for boundary values |
| Stimulus / input conditions | Inject frames with latency 0.0, 0.5, 1.0, 1.001, >1.0 s, negative/non-monotonic/invalid timestamps |
| Environment / configuration | Clock source, synchronization/monotonic method, browser/Tkinter evidence path declared |
| Statistical method | At least 30 boundary/fault samples, all classified correctly |
| Fault-hardening cases | clock jump, stale timestamp, string parse error, duplicate sequence, UI alert not topmost |
| Pass/fail oracle | PASS iff no top alert for latency <=1.0 s, top alert for >1.0 s, invalid/non-monotonic timestamps are rejected or flagged, and p95 latency reporting uses the same monotonic basis |
| Required evidence archive | timestamp replay file, UI screenshots/video, classification CSV, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-C-006/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-C-006_view1_verification_chain.d2`](definition_views/DPS-V10-C-006_view1_verification_chain.d2) | [`definition_views/DPS-V10-C-006_view1_verification_chain.png`](definition_views/DPS-V10-C-006_view1_verification_chain.png) |
