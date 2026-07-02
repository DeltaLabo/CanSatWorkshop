# ISSUE-AMS-007 — Align AMS v1.0 data freshness with shared sensor-to-OBCC contract

## Context

The user requires ADS and AMS data freshness to be solved with one shared contract. This issue adds or aligns AMS v1.0 verification so AMS uses the PM&SE shared sensor-to-OBCC freshness rule.

Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.h`
- `PM&SE/IVV.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` (`AMS-BLK-002` and cross-cutting `SYS-BLK-004` context)
- `PM&SE/MBSE_Test_Plan_Assessment.md` (`SUB-AMS-003`, `GAP-001`, `SYS-END-TO-END-DATA` context)
- `AMS/README.md`
- `AMS/MBSE/tests/README.md`
- `AMS/MBSE/tests/AMS-VV-API-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-001/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-004/README.md` if useful for non-blocking/timing context

Shared rule to use exactly:

- ADS and AMS must be able to respond to OBCC data requests at **5 Hz** for parachute-control consumers.
- At every **2 s** telemetry push, ADS and AMS samples used in telemetry must be fresh.
- Max fresh age is **400 ms** (two failed samples at 5 Hz).
- Required status enum: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Sensor timeout/fault must not leave old data marked `VALID`.

## Task

Add or extend AMS v1.0 data-freshness verification to reference the shared contract.

Preferred path: create a new README-only candidate/definition package:

- `AMS/MBSE/tests/AMS-V10-DATA-FRESHNESS/README.md`

Alternative path: extend `AMS-VV-API-001` and/or `AMS-VV-FC-001` directly if that is cleaner. If you use the alternative, clearly add an `AMS-V10-DATA-FRESHNESS` alias/section in `AMS/MBSE/tests/README.md` so the candidate is traceable.

## Required AMS freshness test content

The AMS freshness test/section must include:

1. Purpose: verify AMS v1.0 can answer OBCC data requests at 5 Hz and that OBCC/telemetry never treats stale/faulted AMS data as fresh valid data.
2. Scope/model elements: AMS Processing, OBCC consumer/collection path, Pointers/Returns or equivalent modeled CEs, BME280/I2C read/process values, AMS init state.
3. Reference the shared PM&SE contract paths:
   - `../../../PM&SE/contracts/sensor_obcc_freshness_contract.md` from `AMS/MBSE/tests/<activity>/README.md` if relative path fits,
   - `../../../PM&SE/contracts/sensor_obcc_freshness_contract.h`.
4. Pass criteria:
   - nominal OBCC request period 200 ms / 5 Hz,
   - response metadata includes status and age or equivalent traceability,
   - `VALID` only when age `<=400 ms`, initialized, no active fault, and current sample is from a successful update,
   - every 2 s telemetry packaging observation uses age/status and refuses to present non-`VALID` or age `>400 ms` data as fresh,
   - timeout/I2C fault/init failure transitions status to `TIMEOUT`, `SENSOR_FAULT`, or `INIT_FAIL`, not stale old `VALID`,
   - no unbounded blocking or hidden bypass.
5. Sample/stat basis:
   - `n=59` representative request/response observations with all meeting the age/status criteria for formal timing/freshness claim,
   - 10 min mission-window optional/companion evidence should preserve all request/response/telemetry observations if used.
6. Fault cases:
   - BME280 timeout/no response,
   - stale producer/no new sample,
   - init fail,
   - non-finite/out-of-range measurement if applicable,
   - OBCC request during fault/recovery.
7. Evidence:
   - AMS firmware/build ID, OBCC build/harness ID,
   - raw request/response logs with timestamps/status/age,
   - telemetry frame logs at 2 s cadence,
   - I2C/fault injection evidence,
   - analysis script/tool revision,
   - UUT/equipment IDs/calibration.
8. Status: definition ready / execution pending. Do not claim execution.

## Index/update requirements

Update `AMS/MBSE/tests/README.md` so the new or extended AMS freshness verification is visible. It should close the planning-definition gap for AMS-to-OBCC 5 Hz freshness but keep execution pending.

If `AMS/README.md` has a rate requirement section that conflicts with this, update it minimally to point to the shared contract. Do not make unrelated AMS changes.

Avoid editing D2 diagrams unless absolutely necessary. If D2/model views need later updates, list that follow-up in the README.

Do not update PM&SE blocker tables in this issue; final integration will do it.

## Acceptance criteria

- `AMS-V10-DATA-FRESHNESS` exists or there is a clear `AMS-V10-DATA-FRESHNESS` alias/section in existing AMS tests.
- AMS freshness verification references the shared PM&SE contract and exact status enum.
- AMS pass/fail criteria include 5 Hz request/response, 400 ms max age at 2 s telemetry push, and no old data marked `VALID` after timeout/fault.
- AMS test index is updated and execution remains pending.
- Commit your changes with a message like `AMS: align data freshness contract`.

## Final response

Return a concise summary with files changed, chosen implementation path, any D2 follow-up, and commit hash.
