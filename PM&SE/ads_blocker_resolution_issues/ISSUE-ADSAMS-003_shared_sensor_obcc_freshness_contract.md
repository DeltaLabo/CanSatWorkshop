# ISSUE-ADSAMS-003 — Shared ADS/AMS sensor-to-OBCC freshness contract

## Context

The ADS blocker-resolution scope was expanded by the user: the data freshness issue must be solved consistently across ADS and AMS. This issue creates the one shared PM&SE-controlled sensor-to-OBCC freshness contract that ADS and AMS tests must reference.

Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-GETTER/README.md`
- `AMS/MBSE/tests/AMS-VV-API-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-001/README.md`
- `AMS/MBSE/tests/README.md`

User-required shared rule:

- ADS and AMS must be able to respond to OBCC data requests at **5 Hz** for parachute-control consumers.
- At every **2 s** telemetry push, ADS and AMS samples used in telemetry must be fresh.
- Maximum fresh age is equivalent to **2 failed samples at 5 Hz = 400 ms**.
- Required status enum: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Sensor timeout/fault must not leave old data marked `VALID`.

## Task

Create one shared local contract under PM&SE and update the ADS closure record so later ADS/AMS issues can reference it.

Expected files:

- `PM&SE/contracts/README.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.h`
- update `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`

Do **not** create an ADS-only freshness contract. If you need ADS-specific Pointers/Returns detail, leave it to a later ADS alignment issue and make it reference this shared PM&SE contract.

## Contract content requirements

The Markdown contract must be self-contained and include:

1. Purpose and scope: shared ADS/AMS sensor-to-OBCC data freshness contract for v1.0 internal OBCC consumers and telemetry packaging.
2. Definitions:
   - OBCC request/response capability at 5 Hz,
   - nominal request period 200 ms,
   - two failed samples = 400 ms max fresh age,
   - 2 s LoRa telemetry push uses latest ADS/AMS samples but must expose status/age.
3. Required status enum exactly:
   - `VALID`
   - `STALE`
   - `NO_DATA`
   - `TIMEOUT`
   - `SENSOR_FAULT`
   - `INIT_FAIL`
4. Status semantics:
   - `VALID`: data age `<= 400 ms`, sensor initialized, no active fault, fields finite/in range, and sample produced from a successful update.
   - `STALE`: last successful sample exists but age `> 400 ms`, or freshness cannot be proven.
   - `NO_DATA`: no successful sample has ever been produced since boot/reset or after reinitialization.
   - `TIMEOUT`: latest request/read exceeded the subsystem's bounded timeout.
   - `SENSOR_FAULT`: runtime sensor/bus/value fault detected.
   - `INIT_FAIL`: startup initialization failed or never completed.
5. Forbidden behavior: timeout/fault/init failure must not leave old samples marked `VALID`; old values may only be returned with non-`VALID` status and age.
6. Required fields for any ADS/AMS response envelope:
   - `contract_version`,
   - `subsystem_id` (`ADS` or `AMS`),
   - `sample_id`,
   - `sample_time_ms`,
   - `request_time_ms` or consumer timestamp,
   - `age_ms`,
   - `status`,
   - payload validity/field-status indicators if applicable.
7. Telemetry packaging rule:
   - every 2 s telemetry frame that includes ADS/AMS sensor values shall include or be traceable to age/status for those values;
   - if age `> 400 ms` or status is not `VALID`, telemetry shall not present the value as fresh valid data.
8. Statistical/test oracle:
   - strict freshness evidence should use `n=59` representative request/response observations with every response meeting age/status criteria for formal timing/tolerance claims;
   - mission-window evidence should preserve all request/response/telemetry packaging logs.
9. Relationship to subsystem tests:
   - ADS: `ADS-V10-DATA-FRESHNESS` or extensions of `ADS-IVV-FC-OBCC-DELIVERY` / `ADS-IVV-C-GETTER` / `ADS-IVV-C-RATE-5HZ`.
   - AMS: `AMS-V10-DATA-FRESHNESS` or extensions of `AMS-VV-API-001` / `AMS-VV-FC-001`.
   - System: `SYS-END-TO-END-DATA` uses this contract as the sensor freshness oracle.

The `.h` reference must be ESP32/FreeRTOS Arduino-compatible in style and include:

- include guard or `#pragma once`,
- enum for the exact status values,
- constants for version string, nominal period `200`, freshness max age `400`, telemetry period `2000`,
- common response metadata struct,
- helper function or inline predicate for whether a response is fresh valid,
- no nonstandard dependencies beyond standard C/C++ integer/bool types; guard Arduino/FreeRTOS specifics if used.

## Closure-record update requirements

Update `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` so it no longer says ADS-BLK-007 is only an ADS/OBCC local contract. It should say:

- shared PM&SE sensor-to-OBCC contract governs freshness/status for ADS and AMS,
- ADS Pointers/Returns ownership/lifetime remains ADS-specific supplemental detail,
- AMS data freshness must be aligned through `AMS-V10-DATA-FRESHNESS` or AMS API/FC test extension,
- `SYS-END-TO-END-DATA` must use the same freshness rule.

Do not update `CON-003` or `MBSE_Test_Plan_Assessment` in this issue; final integration will do that.

## Acceptance criteria

- Shared contract Markdown and header exist under `PM&SE/contracts/`.
- Contract contains all user-required freshness/status rules.
- Header is syntactically plausible; run `python3` is not applicable, but at least inspect it for no obvious syntax errors.
- Closure record references the shared ADS/AMS contract.
- Commit your changes with a message like `PMSE: add shared sensor freshness contract`.

## Final response

Return a concise summary with files changed, selected constants/status semantics, and commit hash.
