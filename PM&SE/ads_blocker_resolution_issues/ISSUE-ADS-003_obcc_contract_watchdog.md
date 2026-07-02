# ISSUE-ADS-003 — Resolve ADS-BLK-007 with local ADS/OBCC contract files

## Context

The orchestrator is resolving ADS blockers from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2. Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` if it already exists
- `PM&SE/IVV.md`
- `ADS/README.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md`
- `OBCC/Variable_Getter_Template.md`
- `OBCC/LoRa_Frame.md` if useful for telemetry cadence context

Relevant blocker:

- `ADS-BLK-007`: v1.0 Pointers/Returns data schema and delivery watchdog/timeout threshold are not fixed. Closure action: freeze Pointers/Returns contract, delivery watchdog, timing overhead treatment, formal claim type.

User-approved semantic decision:

- v1.0 ADS must provide data internally to OBCC at 5 Hz. OBCC LoRa telemetry remains 2 s and samples latest ADS data with freshness/age/stale/error metadata.

## Task

Create local controlled v1.0 ADS/OBCC Pointers/Returns contract files and update ADS delivery docs to reference them.

Expected new/updated files:

- `ADS/MBSE/tests/contracts/README.md`
- `ADS/MBSE/tests/contracts/ads_obcc_v1_pointers_returns_contract.md`
- `ADS/MBSE/tests/contracts/ads_obcc_v1_interface.h`
- optionally `ADS/MBSE/tests/contracts/ads_obcc_v1_reference.ino` or `.cpp` if useful and small
- update `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md`
- optionally update `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md` only to reference the contract; avoid broad timing edits reserved for another issue

## Contract requirements

The contract should be ESP32-compatible, FreeRTOS-based Arduino C/C++ in spirit, but it does not need to be wired into production firmware. It is a controlled test/reference contract.

Define at minimum:

- Contract version, e.g. `ads.obcc.ptrret.v1`.
- Data struct(s) for ADS sample delivered to OBCC:
  - monotonic `sample_id`,
  - producer timestamp in milliseconds,
  - validity/freshness/status flags,
  - GPS latitude/longitude/fix/age,
  - angular-rate x/y/z in deg/s,
  - acceleration x/y/z in m/s²,
  - attitude/heading/PRY fields if modeled/available,
  - init/status/error flags for GPS and IMU.
- Pointer/ownership/lifetime rules:
  - no dangling pointers,
  - atomic or critical-section protected snapshot semantics,
  - consumer sees a coherent sample,
  - producer remains single writer.
- Return/status vocabulary:
  - OK / no new sample / stale / invalid / timeout / unavailable / internal error.
- Watchdog/freshness thresholds:
  - nominal ADS update period 200 ms,
  - select a predeclared stale threshold and delivery watchdog threshold consistent with 5 Hz and the plan,
  - telemetry every 2 s must use latest sample and expose stale/error if age exceeds threshold.
- Timing overhead treatment:
  - contract call/snapshot overhead must be measured or bounded,
  - overhead budget should not mask the 5 Hz delivery requirement.
- Fault semantics:
  - null pointer, stale producer, invalid sensor, corrupt/non-finite values, timeout, and slow/stuck call are not consumed as valid ADS data.

## README update requirements

Update `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md` so it:

- references the new local contract files,
- states the Pointers/Returns schema/watchdog baseline is now controlled,
- describes how `ADS-IVV-FC-OBCC-DELIVERY` uses the contract for pass/fail,
- keeps execution pending and requires firmware commit/build/UUT IDs in reports,
- notes the 5 Hz internal ADS-to-OBCC delivery and separate 2 s LoRa telemetry cadence.

Do not update PM&SE blocker tables in this issue; final integration will do it.

## Acceptance criteria

- Contract README/Markdown is clear enough for a test implementer to use without external conversation.
- Header/code is syntactically plausible Arduino C++ and contains no project-breaking includes beyond common Arduino/FreeRTOS headers guarded as needed.
- `ADS-IVV-FC-OBCC-DELIVERY/README.md` references the local contract and no longer says schema/watchdog are wholly undefined.
- Commit your changes with a message like `ADS: add OBCC delivery contract baseline`.

## Final response

Return a concise summary with files changed, selected watchdog/stale thresholds, and any assumptions.
