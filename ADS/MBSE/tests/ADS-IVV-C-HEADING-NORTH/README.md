# ADS-IVV-C-HEADING-NORTH — heading/north quantitative accuracy

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/ADS-IVV-C-HEADING-NORTH/`.

## Purpose

Defines the quantitative ADS heading/north verification and links it to attitude-chain closure.

## Controlled references

- PM&SE/IVV.md
- PM&SE/CON-003_Candidates_and_Definition_Blockers.md ADS-BLK-003
- ADS/MBSE/v0.2 and ADS/MBSE/v1.0 source views

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | ADS v0.2 and v1.0 heading/yaw output at the applicable ADS observation point: v0.2 Serial0/log/API development evidence or v1.0 ADS Processing / OBCC collection evidence |
| Verification means | Testing with surveyed true-north line or calibrated magnetic reference with declination correction, non-magnetic fixture/site survey, timestamped ADS logs, and circular-error analysis |
| Stimulus / input conditions | Orient UUT near 0, 90, 180, and 270 degrees; collect n=59 consecutive strict samples per heading after settling; record reference heading, declination, and local magnetic-disturbance survey |
| Environment / configuration | Non-magnetic test area, stable power, fixed mounting, reference uncertainty recorded, disturbed/invalid marker policy active |
| Statistical method | n=59 all-within-limit samples per heading for strict claim; circular statistics with wrap-around handling; report uncertainty and any exclusions |
| Fault-hardening cases | magnetic disturbance, reference misalignment, wrap-around error near 0/360, stale/duplicate sample, calibration failure, invalid/disturbed marker ignored |
| Pass/fail oracle | PASS iff circular heading error plus expanded uncertainty <=10 degrees for every strict sample at all four headings, timestamps/status are valid, and disturbed/invalid/no-calibration cases are marked non-valid rather than credited. For v1.0, freshness/status follows the shared PM&SE contract (`status == VALID`, finite/in range, `age_ms <= 400 ms`, exact enum). Ambiguous true/magnetic reference is HOLD. |
| Required evidence archive | raw ADS log/API records, reference survey/calibration, fixture photos, analysis script/version, per-heading circular-error CSV, disturbance log, status/age/field-validity mapping where applicable, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/ADS-IVV-C-HEADING-NORTH/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/ADS-IVV-C-HEADING-NORTH_view1_verification_chain.d2`](definition_views/ADS-IVV-C-HEADING-NORTH_view1_verification_chain.d2) | [`definition_views/ADS-IVV-C-HEADING-NORTH_view1_verification_chain.png`](definition_views/ADS-IVV-C-HEADING-NORTH_view1_verification_chain.png) |
