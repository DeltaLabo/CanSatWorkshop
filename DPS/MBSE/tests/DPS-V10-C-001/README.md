# DPS-V10-C-001 — 500 m RF range/PDR

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/DPS-V10-C-001/`.

## Purpose

Defines the DPS v1.0 500 m RF range/PDR verification activity and closes its former planning-backlog status.

## Controlled references

- DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md
- DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/IVV.md

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | DPS/OBCC RF downlink path and ground-station reception at 500 m horizontal LOS or approved RF-equivalent |
| Verification means | Field RF test or validated RF-equivalent with RSSI/SNR logging and exact-binomial PDR analysis |
| Stimulus / input conditions | Schedule N=300 unique 2 s frames over 10 min with legal 915 MHz settings and matching antennas |
| Environment / configuration | 500 m horizontal LOS or RF-equivalent, RFM96W, 22 AWG 81.4 mm monopoles, legal/EIRP/site/weather/interference recorded |
| Statistical method | Exact binomial N=300/k>=279 strict PDR; independence rationale required |
| Fault-hardening cases | antenna orientation, interference, duplicate/lost frames, invalid CRC/schema, illegal settings, weather/site deviations |
| Pass/fail oracle | PASS iff k>=279 of N=300 scheduled unique frames are valid with one-sided 95% exact-binomial lower bound >=0.90; RSSI/SNR and invalid/lost reason logs retained; payload schema including deployment_status preserved |
| Required evidence archive | raw receive log, scheduled-frame list, RSSI/SNR, site/legal evidence, exact-binomial calculation, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/DPS-V10-C-001/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/DPS-V10-C-001_view1_verification_chain.d2`](definition_views/DPS-V10-C-001_view1_verification_chain.d2) | [`definition_views/DPS-V10-C-001_view1_verification_chain.png`](definition_views/DPS-V10-C-001_view1_verification_chain.png) |
