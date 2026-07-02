# DPS-V10-C-004 — browser-accessible dashboard

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-C-004/`.

## Purpose

Defines the DPS v1.0 browser-accessible dashboard verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | Browser-accessible DPS dashboard strict-credit path and fallback/limited handling for non-browser implementation |
| Verification means | Inspection/demonstration with declared Chrome/Chromium version, URL/start command, refresh/reconnect tests, and evidence capture |
| Stimulus / input conditions | Launch dashboard from clean session, connect/reconnect, refresh, operate controls, replay canonical payloads |
| Environment / configuration | Primary Chrome/Chromium strict-credit environment; if only Tkinter exists, record HOLD/limited for browser requirement |
| Statistical method | 100% of declared browser operations; no statistical reliability claim |
| Fault-hardening cases | bad URL, refresh loses state, reconnect corrupts data, browser incompatibility, non-browser-only UI |
| Pass/fail oracle | PASS iff dashboard is accessible in declared browser at repeatable URL/start command, required data and deployment_status are visible after refresh/reconnect without developer console dependence, and stale/invalid cases remain flagged. Tkinter-only implementation cannot pass browser strict credit. |
| Required evidence archive | browser version/start command, screenshots/video, replay log, limitation/waiver if Tkinter-only, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-C-004/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-C-004_view1_verification_chain.d2`](definition_views/DPS-V10-C-004_view1_verification_chain.d2) | [`definition_views/DPS-V10-C-004_view1_verification_chain.png`](definition_views/DPS-V10-C-004_view1_verification_chain.png) |
