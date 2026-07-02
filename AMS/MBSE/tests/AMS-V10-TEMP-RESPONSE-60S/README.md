# AMS-V10-TEMP-RESPONSE-60S — temperature step response <=60 s

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/AMS-V10-TEMP-RESPONSE-60S/`.

## Purpose

Defines AMS/BME280 temperature response-time verification for the v1.0 atmospheric measurement chain.

## Controlled references

- PM&SE/IVV.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- AMS/MBSE/v1.0 source views

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | AMS v1.0 BME280 temperature measurement as collected by AMS processing and exposed to OBCC/API observation point |
| Verification means | Testing with controlled temperature step source or chamber, calibrated reference temperature sensor, synchronized AMS log, and response-time analysis script |
| Stimulus / input conditions | Apply a predeclared temperature step of at least 10 C between stable initial and final plateaus; start t0 when reference sensor crosses 10% of step; sample AMS and reference at >=1 Hz until final condition is reached or 120 s expires |
| Environment / configuration | Sensor exposure matches flight/workshop mounting or documented fixture; airflow/sunlight context recorded; stable power; ambient and chamber/source model recorded |
| Statistical method | At least 5 valid rising or falling step repetitions for acceptance screening; report each response time and max; stricter reliability claims use PM&SE/IVV binomial/timing policy |
| Fault-hardening cases | poor sensor exposure, airflow/sunlight mismatch, reference lag, timestamp drift, stale/default value marked VALID, I2C timeout, sensor init failure |
| Pass/fail oracle | PASS iff AMS reported temperature enters and remains within the guard-banded final acceptance band by t0+60 s. Final band is reference final value +/- max(1.0 C, expanded reference+AMS uncertainty) unless the source requirement is stricter. Missing timestamps, hidden filtering delay, or default/stale valid value is FAIL/HOLD. |
| Required evidence archive | raw reference and AMS logs with timestamps/status, fixture/chamber photos, calibration records, analysis script/version, response-time table, deviations, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/AMS-V10-TEMP-RESPONSE-60S/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/AMS-V10-TEMP-RESPONSE-60S_view1_verification_chain.d2`](definition_views/AMS-V10-TEMP-RESPONSE-60S_view1_verification_chain.d2) | [`definition_views/AMS-V10-TEMP-RESPONSE-60S_view1_verification_chain.png`](definition_views/AMS-V10-TEMP-RESPONSE-60S_view1_verification_chain.png) |
