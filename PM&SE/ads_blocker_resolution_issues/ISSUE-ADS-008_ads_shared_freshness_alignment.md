# ISSUE-ADS-008 — Align ADS v1.0 freshness tests with shared sensor-to-OBCC contract

## Context

The user requires ADS and AMS to use one shared sensor-to-OBCC freshness contract. This issue aligns ADS v1.0 OBCC-delivery/getter/rate test text to that shared PM&SE contract and avoids an ADS-only freshness rule.

Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.h`
- `PM&SE/IVV.md`
- `ADS/README.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-GETTER/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md`

Shared rule to use exactly:

- ADS and AMS must be able to respond to OBCC data requests at **5 Hz** for parachute-control consumers.
- At every **2 s** telemetry push, ADS and AMS samples used in telemetry must be fresh.
- Max fresh age is **400 ms** (two failed samples at 5 Hz).
- Required status enum: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Sensor timeout/fault must not leave old data marked `VALID`.

## Task

Align ADS v1.0 freshness verification with the shared PM&SE contract.

You may either:

1. create a new README-only activity `ADS/MBSE/tests/ADS-V10-DATA-FRESHNESS/README.md`, or
2. extend existing `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ` and add an `ADS-V10-DATA-FRESHNESS` alias/section in `ADS/MBSE/tests/README.md`.

Prefer option 2 if it avoids duplicate tests, but ensure `ADS-V10-DATA-FRESHNESS` is traceable somewhere.

## Required ADS freshness content

The ADS freshness test/section must include:

1. Purpose: verify ADS v1.0 can answer OBCC data requests at 5 Hz and that OBCC/telemetry never treats stale/faulted ADS data as fresh valid data.
2. Scope/model elements: ADS Processing, OBCC consumer/collection path, Pointers/Returns, GPS/IMU/attitude/init fields, getter semantics.
3. Reference shared PM&SE contract paths:
   - `../../../PM&SE/contracts/sensor_obcc_freshness_contract.md` from `ADS/MBSE/tests/<activity>/README.md` if relative path fits,
   - `../../../PM&SE/contracts/sensor_obcc_freshness_contract.h`.
4. Pass criteria:
   - nominal OBCC request period 200 ms / 5 Hz,
   - response metadata includes status and age or equivalent traceability,
   - `VALID` only when age `<=400 ms`, initialized, no active sensor/bus fault, and sample is from a successful update,
   - every 2 s telemetry packaging observation uses age/status and refuses to present non-`VALID` or age `>400 ms` data as fresh,
   - GPS/IMU timeout/fault/init failure transitions status to `TIMEOUT`, `SENSOR_FAULT`, or `INIT_FAIL`, not stale old `VALID`,
   - no unbounded blocking or hidden bypass.
5. Sample/stat basis:
   - `n=59` representative request/response observations with all meeting age/status criteria for formal timing/freshness claim,
   - 10 min ADS mission-window evidence should preserve all request/response/telemetry observations if used.
6. Fault cases:
   - GPS timeout/no fix/malformed/stale,
   - IMU I2C timeout/NACK/stuck/partial read,
   - init fail,
   - non-finite/out-of-range/saturated measurement,
   - OBCC request during fault/recovery.
7. Evidence:
   - ADS firmware/build ID, OBCC build/harness ID,
   - raw request/response logs with timestamps/status/age,
   - telemetry frame logs at 2 s cadence,
   - fault injection evidence,
   - analysis script/tool revision,
   - UUT/equipment IDs/calibration.
8. Status: definition ready / execution pending. Do not claim execution.

## ADS-specific Pointers/Returns supplement

If needed, create a small ADS-specific supplement under `ADS/MBSE/tests/contracts/` for pointer ownership/lifetime/API field details. It must reference the shared PM&SE contract and must not redefine freshness/status differently. This supplement is optional; the shared contract is mandatory.

## Index/update requirements

Update `ADS/MBSE/tests/README.md` so `ADS-V10-DATA-FRESHNESS` or the equivalent extension is visible. It should close the planning-definition gap for v1.0 ADS-to-OBCC 5 Hz freshness but keep execution pending.

Avoid editing D2 diagrams unless absolutely necessary. If D2/model views need later updates, list that follow-up in the README.

Do not update PM&SE blocker tables in this issue; final integration will do it.

## Acceptance criteria

- ADS freshness verification references the shared PM&SE contract and exact status enum.
- ADS pass/fail criteria include 5 Hz request/response, 400 ms max age at 2 s telemetry push, and no old data marked `VALID` after timeout/fault.
- `ADS-V10-DATA-FRESHNESS` is traceable either as a new activity or an alias/section in existing ADS tests/index.
- No ADS-only freshness/status rule contradicts the shared contract.
- Commit your changes with a message like `ADS: align shared freshness contract`.

## Final response

Return a concise summary with files changed, chosen implementation path, any D2 follow-up, and commit hash.
