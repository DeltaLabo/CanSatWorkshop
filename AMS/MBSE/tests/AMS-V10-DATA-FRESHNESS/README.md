# AMS-V10-DATA-FRESHNESS — AMS-to-OBCC 5 Hz freshness/status verification

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/AMS-V10-DATA-FRESHNESS/`.

## Purpose

Defines the AMS freshness/status verification path as a concrete model-based activity tied to AMS API, FC, I2C-timeout, and non-blocking tests.

## Controlled references

- PM&SE/contracts/sensor_obcc_freshness_contract.md
- PM&SE/IVV.md
- AMS/MBSE/tests/AMS-VV-API-001
- AMS/MBSE/tests/AMS-VV-CON-003
- AMS/MBSE/tests/AMS-VV-CON-004

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | AMS v1.0 temperature/pressure/altitude update records exposed to OBCC collection/API observation point |
| Verification means | Testing and analysis with OBCC request harness at 5 Hz, AMS log/API capture, fault injection for I2C/no-data/init-fail, and timestamp/age/status analysis |
| Stimulus / input conditions | Run 10 min mission-window equivalent with 5 Hz OBCC requests; package/observe 2 s telemetry snapshots separately; inject stale, no-data, timeout, sensor-fault, and init-fail cases |
| Environment / configuration | Stable powered AMS/OBCC bench, synchronized monotonic timestamp or age source, firmware/build map recorded, instrumentation overhead measured |
| Statistical method | 10 min/3000 scheduled request opportunities for mission-window claim; formal timing sample n=59 intervals all 150-250 ms and no progress gap >400 ms; report overhead <=5 ms or bounded/subtracted |
| Fault-hardening cases | I2C timeout, sensor disconnect, startup init fail, stale cached value, duplicate sequence, slow getter, missing timestamp/age, old value marked VALID |
| Pass/fail oracle | PASS iff fresh records have status VALID and age_ms <=400 ms at observation point, enum is exactly VALID/STALE/NO_DATA/TIMEOUT/SENSOR_FAULT/INIT_FAIL, non-VALID cases never leave old data marked VALID, 5 Hz request path has no silent missing/duplicate catch-up, and 2 s LoRa packaging is not misused as internal freshness evidence. |
| Required evidence archive | raw AMS/OBCC logs, request schedule, sequence/age/status CSV, injected-fault ledger, source/build map, overhead measurement, analysis script/version, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/AMS-V10-DATA-FRESHNESS/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/AMS-V10-DATA-FRESHNESS_view1_verification_chain.d2`](definition_views/AMS-V10-DATA-FRESHNESS_view1_verification_chain.d2) | [`definition_views/AMS-V10-DATA-FRESHNESS_view1_verification_chain.png`](definition_views/AMS-V10-DATA-FRESHNESS_view1_verification_chain.png) |
