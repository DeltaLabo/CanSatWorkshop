# ADS-IVV-C-ACCEL-3AXIS — 3-axis linear acceleration units and static accuracy

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/ADS-IVV-C-ACCEL-3AXIS/`.

## Purpose

Defines the quantitative ADS acceleration verification that was formerly README-only, including units, six-face fixture, sample count, guard bands, and evidence paths.

## Controlled references

- PM&SE/IVV.md
- PM&SE/CON-003_Candidates_and_Definition_Blockers.md ADS-BLK-002
- ADS/MBSE/v0.2 and ADS/MBSE/v1.0 source views

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | ADS v0.2 and v1.0 ICM20948 acceleration output at the applicable ADS observation point: v0.2 Serial0/log/API development evidence or v1.0 ADS Processing / OBCC collection evidence |
| Verification means | Testing with six-face static gravity fixture, calibrated alignment reference, timestamped ADS log/API capture, and analysis script |
| Stimulus / input conditions | Place +X, -X, +Y, -Y, +Z, -Z faces in 1 g static orientation; collect n=59 consecutive strict samples per face after settling; convert any g values with g0=9.80665 m/s^2 |
| Environment / configuration | Non-vibrating bench, stable power, ambient temperature recorded, sensor calibrated/initialized per firmware, fixture alignment uncertainty included |
| Statistical method | n=59 all-within-limit samples per face for strict claim; report exact sample count and uncertainty/guard-band method; fewer samples are characterization only |
| Fault-hardening cases | wrong unit conversion, axis sign swap, stale/duplicate timestamp, invalid sensor status, calibration failure, vibration or fixture slip, missing uncertainty |
| Pass/fail oracle | PASS iff every face has correct axis/sign, driven-axis error plus expanded uncertainty <=1.0 m/s^2, off-axis leakage plus uncertainty <=0.75 m/s^2, vector-norm error plus uncertainty <=1.0 m/s^2, units are m/s^2 or controlled g conversion, and no stale/error/non-finite/out-of-range sample is treated `VALID`. For v1.0, freshness/status follows the shared PM&SE contract (`status == VALID`, finite/in range, `age_ms <= 400 ms`, exact enum). Any deg/s^2 acceleration oracle is FAIL. |
| Required evidence archive | raw ADS log/API records, fixture orientation photos, calibration/alignment records, analysis script/version, per-face CSV and guard-band table, status/age/field-validity mapping where applicable, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/ADS-IVV-C-ACCEL-3AXIS/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/ADS-IVV-C-ACCEL-3AXIS_view1_verification_chain.d2`](definition_views/ADS-IVV-C-ACCEL-3AXIS_view1_verification_chain.d2) | [`definition_views/ADS-IVV-C-ACCEL-3AXIS_view1_verification_chain.png`](definition_views/ADS-IVV-C-ACCEL-3AXIS_view1_verification_chain.png) |
