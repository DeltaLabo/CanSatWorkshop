# ISSUE-AMS-002 — Shared ADS/AMS sensor-to-OBCC freshness contract

## Context

Resolve `AMS-BLK-002` consistently for ADS and AMS by creating one PM&SE-controlled freshness contract.

Read first:

- `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `AMS/MBSE/tests/README.md`
- `ADS/MBSE/tests/README.md`

## Required shared rule

- ADS and AMS shall support OBCC data requests at `5 Hz` for parachute-control consumers.
- At every `2 s` telemetry push, required ADS/AMS data is fresh only if max age `<=400 ms` (two failed samples at 5 Hz).
- Required status enum exactly: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Sensor timeout/fault/init failure/no-data must not leave old data marked `VALID`.

## Task

Create or complete the PM&SE contract files. Preferred path if not already present:

- `PM&SE/contracts/README.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md`
- optional reference header `PM&SE/contracts/sensor_obcc_freshness_contract.h` if useful and kept consistent with the Markdown.

If untracked contract files already exist, review them against this issue, fix any gaps, and include them in your commit.

The Markdown contract must define scope, terminology (`5 Hz`, 200 ms period, `2 s` telemetry push, sample age, freshness threshold), the exact enum and semantics, forbidden stale-valid behavior, required timestamp/sequence/age/status evidence, telemetry packaging rule, and alignment paths for AMS, ADS, and `SYS-END-TO-END-DATA`.

Then update `PM&SE/IVV.md` in the cross-subsystem semantics section to reference the contract and summarize the `5 Hz` / `2 s` / `<=400 ms` / enum rule.

Optionally update `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md` only to add a link to the contract.

Do not update CON-003, assessment, AMS test READMEs, ADS test READMEs, D2, or PNG files in this issue.

## Acceptance criteria

- Contract Markdown exists and includes all required rules and enum tokens exactly.
- IVV references the contract.
- Timeout/fault cannot leave old data marked `VALID` is explicit.
- AMS, ADS, and `SYS-END-TO-END-DATA` alignment paths are named.
- Commit with message `AMS: add shared sensor freshness contract`.

## Final response

Return files changed, contract path, thresholds/statuses, and later references to update.
