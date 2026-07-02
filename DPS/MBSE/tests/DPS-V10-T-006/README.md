# DPS-V10-T-006 — forwarder initialization

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-T-006/`.

## Purpose

Defines the DPS v1.0 forwarder initialization verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS LoRa forwarder startup, readiness reporting, and missing SPI/radio/UART fault handling |
| Verification means | Testing with 59 restart trials plus deliberate missing radio/SPI/UART/fault-injection cases and log capture |
| Stimulus / input conditions | Power/software restart, disconnect or disable radio/SPI/UART paths before startup, then restore and retest |
| Environment / configuration | As-built ground station hardware/software, selected serial/radio settings, clean power and declared tool versions |
| Statistical method | 59/59 nominal in-limit restarts for 95/95 timing/readiness claim; injected fault cases are 100% pass/fail |
| Fault-hardening cases | missing radio, wrong band/SF/BW, UART absent, SPI fail, stale ready flag, crash/deadlock |
| Pass/fail oracle | PASS iff all nominal restarts reach ready with correct configuration, injected missing interfaces produce explicit not-ready/error logs, and no false-ready state occurs; recovery after restoration is bounded and logged |
| Required evidence archive | startup logs, fault-injection photos/configs, readiness timing table, versions, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-T-006/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-T-006_view1_verification_chain.d2`](definition_views/DPS-V10-T-006_view1_verification_chain.d2) | [`definition_views/DPS-V10-T-006_view1_verification_chain.png`](definition_views/DPS-V10-T-006_view1_verification_chain.png) |
