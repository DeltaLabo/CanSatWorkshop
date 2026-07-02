# DPS-V10-T-004 — CanSat transmit path

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-T-004/`.

## Purpose

Defines the DPS v1.0 CanSat transmit path verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS datalogger/ground-station transmit path from PC command/source payload to final or near-field receiver |
| Verification means | Testing with final receiver or near-field RF-equivalent, sequence-number monitor, radio busy/not-ready fault injection, and buffer-overrun stress |
| Stimulus / input conditions | Send predeclared sequence of >=60 transmit requests plus busy/not-ready/overrun cases; capture receiver frames and forwarder logs |
| Environment / configuration | 915 MHz/RFM96W settings per contract or near-field shielded equivalent; antennas/settings recorded |
| Statistical method | 60/60 nominal sequence for functional acceptance; stronger PDR uses DPS-V10-C-001 N=300/k>=279 |
| Fault-hardening cases | radio not ready, busy channel, buffer full, bad sequence, payload length mismatch, deployment_status corruption |
| Pass/fail oracle | PASS iff every accepted transmit request produces exactly one ordered frame at receiver, no missing/duplicate sequence, radio-busy/not-ready cases are logged and not falsely ready, buffer overrun is bounded/recovered, and payload including deployment_status is not corrupted |
| Required evidence archive | TX request log, receiver raw frames, sequence table, RSSI/SNR if RF, fault ledger, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-T-004/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-T-004_view1_verification_chain.d2`](definition_views/DPS-V10-T-004_view1_verification_chain.d2) | [`definition_views/DPS-V10-T-004_view1_verification_chain.png`](definition_views/DPS-V10-T-004_view1_verification_chain.png) |
