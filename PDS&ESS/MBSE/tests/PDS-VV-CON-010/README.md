# PDS-VV-CON-010 — 3.3 V and 5 V regulator efficiency at 1 A

**Status:** Defined / not executed. This activity is fully defined for MBSE/report-by-reference use; no execution credit is claimed until an execution report is archived under `results/PDS-VV-CON-010/`.

## Purpose

Defines the regulator-efficiency validation for the PDS README rail requirements and closes the former planning backlog item.

## Controlled references

- PM&SE/IVV.md
- PDS&ESS/MBSE/v1.0 source views
- PDS&ESS/README.md rail requirements

## Verification definition

| Definition field | Controlled value |
|---|---|
| Item under verification | PDS & ESS v1.0 3.3 V and 5 V regulation paths and associated input/output measurement points |
| Verification means | Testing with current-limited bench supply or battery emulator, calibrated power analyzer/DMMs, electronic loads, oscilloscope for ripple, thermocouples/thermal camera, and efficiency analysis sheet |
| Stimulus / input conditions | For each rail: no-load sanity, nominal load from released load matrix, and 1.000 A +/-0.5% load after settling; record input voltage/current and rail voltage/current at converter terminals and required endpoint; hold each load at least 60 s after 10 s settling |
| Environment / configuration | Ambient 20-30 C or recorded equivalent, current-limited safe-energy envelope, stable harness, charger/cell safety controls if battery used, thermal limits predeclared |
| Statistical method | 100% of required rail/load cases executed; continuous samples at >=1 Hz during hold; report mean/min/max and expanded uncertainty guard band for efficiency and voltage |
| Fault-hardening cases | load-step sag, thermal rise, current-limit collapse, wrong measurement point, uncalibrated current, endpoint voltage drop, ripple/outlier hidden by averaging |
| Pass/fail oracle | PASS iff at the 1 A case each rail remains within its voltage tolerance at required endpoint and guard-banded efficiency eta=Pout/Pin >=95.0%, ripple remains within campaign limit or <=50 mVpp if no stricter source exists, no brownout/current-limit/thermal shutdown/smoke/swelling/unsafe heating occurs. If as-built hardware cannot meet 95%, result is FAIL or controlled requirement waiver, not an open definition. |
| Required evidence archive | raw power analyzer/DMM/load logs, scope ripple captures, thermal records, calibration/status records, topology photo, load matrix/waiver, efficiency spreadsheet/script, report.md |

## Execution and reporting rules

1. Predeclare UUT identifiers, hardware revisions, firmware/software commits, tool versions, equipment asset IDs, calibration status, environment, and deviations before execution.
2. Retain raw logs, scripts, screenshots/photos/video/waveforms where applicable, derived analysis files, and the final report under `results/PDS-VV-CON-010/`.
3. A run with missing required evidence is **HOLD**, not pass. A failed guard band, missing required status field, false success, unbounded timing, or unapproved deviation is **FAIL**.
4. Any execution-specific value may refine the as-tested configuration but shall not weaken the oracle in this definition without an approved waiver/deviation record.

## Definition views

| View | Source | Rendered |
|---|---|---|
| Modeled verification chain | [`definition_views/PDS-VV-CON-010_view1_verification_chain.d2`](definition_views/PDS-VV-CON-010_view1_verification_chain.d2) | [`definition_views/PDS-VV-CON-010_view1_verification_chain.png`](definition_views/PDS-VV-CON-010_view1_verification_chain.png) |
