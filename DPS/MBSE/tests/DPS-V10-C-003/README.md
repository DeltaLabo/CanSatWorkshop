# DPS-V10-C-003 — concurrency/load

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-C-003/`.

## Purpose

Defines the DPS v1.0 concurrency/load verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | Concurrent decoder, CSV/session archive, dashboard, and RF/serial ingest under flight cadence and synthetic stress |
| Verification means | Testing with 10 min 2 s flight-cadence stream plus optional 20 min 5 Hz serial stress, queue/memory/latency instrumentation |
| Stimulus / input conditions | Replay or receive scheduled frames while dashboard and CSV logging run; inject backlog burst and recovery segment |
| Environment / configuration | As-built PC, OS, Python/browser versions, declared payload size, instrumentation overhead recorded |
| Statistical method | 10 min flight cadence required; 20 min 5 Hz stress if over-air margin insufficient; p95 over accepted frames |
| Fault-hardening cases | queue growth, memory leak, slow disk, UI freeze, invalid frames, deployment_status under load |
| Pass/fail oracle | PASS iff no crash/deadlock/data loss beyond defined invalid rejects, queue/backlog returns to zero after burst, memory remains bounded, p95 pipeline latency <1.0 s, CSV rows match accepted source log, dashboard remains responsive |
| Required evidence archive | source/accepted logs, queue/memory/latency CSV, screenshots, CPU/memory monitor, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-C-003/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-C-003_view1_verification_chain.d2`](definition_views/DPS-V10-C-003_view1_verification_chain.d2) | [`definition_views/DPS-V10-C-003_view1_verification_chain.png`](definition_views/DPS-V10-C-003_view1_verification_chain.png) |
