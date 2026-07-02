# ISSUE-ADS-002 — Resolve ADS-BLK-006 with local Serial0 schema/parser

## Context

The orchestrator is resolving ADS blockers from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2. Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` if it already exists
- `PM&SE/IVV.md`
- `ADS/README.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-SERIAL/README.md`

Relevant blocker:

- `ADS-BLK-006`: Controlled Serial0 schema/parser/campaign-size baseline is missing. Blocks `ADS-IVV-FC-SERIAL` pass/fail for v0.1/v0.2. Closure action: declare schema, port/baud/framing, field list, marker vocabulary, parser version, expected count.

## Task

Create controlled local Serial0 baseline files for ADS v0.1/v0.2 and update `ADS-IVV-FC-SERIAL` to reference them.

Expected new/updated files:

- `ADS/MBSE/tests/schemas/README.md`
- `ADS/MBSE/tests/schemas/ads_serial0_v0_1_v0_2.schema.json`
- `ADS/MBSE/tests/tools/parse_ads_serial0.py`
- optionally `ADS/MBSE/tests/tools/README.md` if helpful
- update `ADS/MBSE/tests/ADS-IVV-FC-SERIAL/README.md`

## Required schema/parser content

The schema must be local and deterministic. It should support the modeled v0.1/v0.2 Serial0 evidence even if exact legacy firmware formats vary. Define one controlled canonical line format and parser behavior; legacy logs must either conform or be transformed by a documented adapter.

Include at minimum:

- Interface: Serial0 over USB CDC/UART to PC logger, default baud if applicable, newline-delimited UTF-8 text.
- Schema version, e.g. `ads.serial0.v1` for the test baseline.
- Required envelope fields:
  - `schema_version`
  - `ads_version` (`v0.1` or `v0.2`)
  - `sample_id`
  - `timestamp_ms`
  - `record_type` (`init`, `measurement`, `fault`, `heartbeat` or similar)
  - `validity` / `status` / `stale` indicators
- v0.1 measurement fields: GPS latitude/longitude, GPS fix/status, freshness/age.
- v0.2 measurement fields: v0.1 GPS fields plus IMU angular-rate, acceleration, magnetic/heading or PRY fields where modeled, IMU init/status.
- Marker vocabulary for missing/stale/error/unavailable fields.
- Campaign-size baseline:
  - 10 min mission-window campaign at 5 Hz means 3000 expected measurement records for applicable versions.
  - For shorter serial functional checks, declare how expected count is computed from configured duration and nominal rate.
- Pass/fail parser behavior:
  - fail or nonzero exit on unparseable JSON/CSV/line records, missing required fields, unsupported schema version, duplicate/non-monotonic `sample_id` unless explicitly allowed, timestamp reversal, and unflagged stale/error fields.

The parser should be a small Python 3 script with `--help` and at least these behaviors:

- Accept an input log path.
- Validate JSON Lines if possible. If you choose CSV instead, document it clearly and validate headers/rows.
- Emit a summary to stdout: total records, measurement records, init/fault/heartbeat records, missing fields, stale/error counts, sample/timestamp issues.
- Exit `0` when the log structurally conforms, nonzero when it does not.
- Avoid external dependencies outside Python standard library.

## README update requirements

Update `ADS/MBSE/tests/ADS-IVV-FC-SERIAL/README.md` so it:

- names the local schema and parser files,
- states that the Serial0 verdict is no longer blocked by an undefined schema/parser,
- still says execution is pending,
- states that actual logs must identify firmware commit/build and any adapter from legacy output to the controlled schema,
- references the 10 min / 5 Hz campaign-size rule where applicable.

Do not update PM&SE blocker tables in this issue; final integration will do it.

## Acceptance criteria

- Schema JSON is valid JSON.
- Parser runs with `python3 ADS/MBSE/tests/tools/parse_ads_serial0.py --help`.
- Parser uses only standard library.
- `ADS-IVV-FC-SERIAL/README.md` references the schema/parser paths and no longer says the schema/parser baseline is entirely missing.
- Commit your changes with a message like `ADS: add Serial0 schema parser baseline`.

## Final response

Return a concise summary with files changed, parser command tested, and any assumptions about canonical line format.
