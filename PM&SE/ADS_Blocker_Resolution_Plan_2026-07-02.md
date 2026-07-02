# ADS / AMS Sensor-Freshness Blocker Resolution Plan — CON-003 §2.2

Date: 2026-07-02
Repository: CanSat Workshop

## End goal

Resolve `ADS-BLK-001` through `ADS-BLK-010` from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2 so the ADS test suite has:

1. a complete ADS candidate test list,
2. a controlled list of updates to existing ADS tests,
3. selected quantitative criteria and methods for the ADS blockers,
4. local schema/parser/contract files where required, and
5. applied README/test-definition updates where they can be made textually without inventing source-model detail.

Scope update from the user: the ADS data-freshness decision must be solved consistently with AMS. Therefore this plan now also creates one shared **sensor-to-OBCC freshness contract** for ADS and AMS, aligns ADS and AMS freshness tests to that same contract, and references the same PM&SE rule from the planned `SYS-END-TO-END-DATA` system-level test definition.

This pass does **not** execute tests and does **not** claim execution credit. It may leave D2/source-model changes as follow-on updates where diagrams would otherwise become too convoluted or need deliberate modeling review.

## User-approved decisions and constraints

- `ADS-BLK-001`: v1.0 ADS **shall provide data to OBCC at 5 Hz** internally. OBCC uses the latest ADS data for the separate v1.0 LoRa telemetry cadence of **2 s**.
- Shared ADS/AMS freshness rule: ADS and AMS must be able to respond to OBCC data requests at **5 Hz** for parachute-control consumers. At every **2 s** telemetry push, the ADS and AMS samples used in telemetry must be fresh with maximum age equivalent to **two failed samples at 5 Hz = 400 ms**.
- Shared status enum: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Sensor timeout/fault must not leave old data marked `VALID`.
- `ADS-BLK-004`: mission duration is **10 min** and must be used consistently for ADS mission-window criteria and listed as a project-level timing decision.
- `ADS-BLK-008`: the v0.2 I2C timeout should be treated as a **constraint leading to code-analysis / instrumentation evidence**, not forced into convoluted MBSE source diagrams.
- `ADS-BLK-009`: lab external equipment listed in `PM&SE/MBSE_Test_Plan_Assessment.md` is available; remaining criteria must still define instrumentation/source mapping, heartbeat/deadline, and overhead allowance.
- `ADS-BLK-010`: motors and a tachometer are available and approved for angular-rate truth. Use statistics-backed methods if the tachometer reliability/calibration is adequate.
- GPS truth/reference note for `ADS-BLK-010`: consumer mobile phones are acceptable as auxiliary sanity-check/logging tools, but they should **not** be the sole truth source for a strict `<5 m` GPS pass unless their uncertainty is independently controlled and guard-banded. Preferred strict closure is an official/campus/municipal surveyed open-sky reference point with coordinate uncertainty small relative to 5 m. If only phones are available at execution time, the result should be marked characterization/limited unless an approved uncertainty rationale is recorded.

## Selected criteria to encode

These are the starting criteria subagents should apply unless they discover a stronger existing project criterion.

| Area / blocker | Resolution decision to encode |
|---|---|
| Shared ADS/AMS freshness | Create one PM&SE-controlled sensor-to-OBCC freshness contract for ADS and AMS. It defines a 5 Hz OBCC request/response capability for parachute-control consumers, 400 ms maximum age at each 2 s telemetry push, status enum `VALID`/`STALE`/`NO_DATA`/`TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL`, and the rule that timeout/fault cannot leave old data marked `VALID`. |
| `ADS-BLK-001` | Add/update candidate definition for v1.0 ADS-to-OBCC delivery-rate/freshness using the shared contract: ADS internal data delivered/available to OBCC at 5 Hz, separate from 2 s LoRa telemetry. OBCC telemetry samples latest ADS data and reports freshness/age/status metadata. |
| AMS alignment | Add `AMS-V10-DATA-FRESHNESS` or extend AMS API/FC tests so AMS uses the same shared freshness contract for OBCC requests and 2 s telemetry freshness. |
| `SYS-END-TO-END-DATA` | Reference the shared PM&SE freshness rule as the system-level oracle for ADS/AMS sensor freshness, payload age/status fields, and stale/error behavior. |
| `ADS-BLK-002` | Add acceleration candidate: clarify acceleration units as m/s² (or g converted to m/s²), not `deg/s²`; six-face static gravity fixture; per-axis sign/units check; quantitative accuracy threshold to be defined in the candidate as a workshop-feasible value with uncertainty guard band. |
| `ADS-BLK-003` | Add heading/north candidate: non-magnetic fixture/site, true/magnetic north reference method, calibration state, magnetic disturbance controls, circular error calculation, and quantitative heading error threshold. |
| `ADS-BLK-004` | Mission window is 10 min. Expected internal ADS update count at 5 Hz is 3000 updates. Define required field presence, reset/stuck-loop rules, invalid/stale/corrupt handling, and maximum gap. |
| `ADS-BLK-005` | Define 5 Hz timing tolerance: nominal period 200 ms; predeclared jitter/worst-gap rules; mean rate, per-sample intervals, stale/drop/duplicate criteria, and formal timing statistics using `PM&SE/IVV.md`. |
| `ADS-BLK-006` | Create controlled local Serial0 schema and parser/campaign baseline for v0.1/v0.2; reference from `ADS-IVV-FC-SERIAL`. |
| `ADS-BLK-007` | Use the shared sensor-to-OBCC freshness contract for v1.0 ADS/OBCC Pointers/Returns freshness/status semantics. Add ADS-specific Pointers/Returns ownership/lifetime/API detail only as a supplement that references the shared contract. |
| `ADS-BLK-008` | Update `ADS-IVV-C-I2C-5MS` text so v0.2 is closed as a constraint-derived code-analysis/instrumentation activity or a documented model gap, not by adding cluttered MBSE diagrams. |
| `ADS-BLK-009` | Update `ADS-IVV-C-NOBLOCK` text with source/build map, symbols or equivalent instrumentation, heartbeat deadline, and instrumentation overhead allowance. |
| `ADS-BLK-010` | Predeclare truth/reference and statistics: GPS strict pass requires controlled surveyed/open-sky truth; gyro uses motor/tachometer per axis/rate with calibrated tachometer, stable motor, axis alignment, and `n=59` all-within-limit 95/95-style timing/accuracy evidence where applicable. |

## Work breakdown and dependencies

| Issue | Delegated work | Main files / outputs | Dependencies / status |
|---|---|---|---|
| `ISSUE-ADS-001_criteria_candidate_register.md` | Create the central ADS blocker closure record with closure decisions, candidate test list, and existing-test update list. | `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`. | Completed by commit `6c36860`; later issues may update it for shared ADS/AMS freshness. |
| `ISSUE-ADS-002_serial0_schema_parser.md` | Resolve `ADS-BLK-006` by creating local Serial0 schema/parser/campaign baseline and referencing them from ADS serial test docs. | `ADS/MBSE/tests/schemas/`, `ADS/MBSE/tests/tools/`, `ADS-IVV-FC-SERIAL/README.md`. | Completed by commit `936e478`. |
| `ISSUE-ADSAMS-003_shared_sensor_obcc_freshness_contract.md` | Create the one shared ADS/AMS sensor-to-OBCC freshness contract and reusable ESP32/FreeRTOS-compatible status/type reference. | `PM&SE/contracts/`, closure record updates. | Next; required before ADS/AMS freshness test alignment. |
| `ISSUE-ADS-004_accuracy_candidate_tests.md` | Resolve candidate/criteria work for `ADS-BLK-002`, `ADS-BLK-003`, and accuracy-method portions of `ADS-BLK-010`. | ADS README/test index plus candidate README files or clearly listed future modeled-definition updates. | After issue 001; avoid editing files already touched by freshness issues except with care. |
| `ISSUE-ADS-005_timing_timeout_noblock_updates.md` | Apply ADS text updates for `ADS-BLK-001`, `ADS-BLK-004`, `ADS-BLK-005`, `ADS-BLK-008`, and `ADS-BLK-009`, using the shared freshness contract for v1.0 freshness/status. | `ADS-IVV-C-RATE-5HZ`, `ADS-IVV-FC-MISSION-WINDOW`, `ADS-IVV-C-I2C-5MS`, `ADS-IVV-C-NOBLOCK`, ADS test index as needed. | After issues 003/004 if editing shared test index. |
| `ISSUE-AMS-007_data_freshness_alignment.md` | Add or extend AMS v1.0 data-freshness verification so AMS uses the same shared sensor-to-OBCC contract. | `AMS/MBSE/tests/AMS-V10-DATA-FRESHNESS/` or AMS API/FC READMEs/test index. | After issue 003; can run before final PM&SE integration. |
| `ISSUE-ADS-008_ads_shared_freshness_alignment.md` | Ensure ADS OBCC-delivery/getter/rate tests explicitly reference the shared contract rather than an ADS-only freshness rule. | ADS OBCC-delivery/getter/rate READMEs and optional ADS local contract supplement. | After issue 003; coordinate with issue 005 if both edit the same files. |
| `ISSUE-ADS-006_pmse_integration_validation_cleanup.md` | Integrate all outputs, update PM&SE blocker/assessment records including AMS/SYS freshness alignment, validate consistency, and remove temporary issue files. | `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, closure record final status, deletion of `PM&SE/ads_blocker_resolution_issues/`. | Last. |

## Coordination rules for subagents

- Subagents must work from the repository root and must not push.
- Each subagent must read its issue file, the referenced PM&SE docs, `PM&SE/IVV.md`, and the ADS/AMS test READMEs it edits.
- Keep edits focused and commit only relevant files. Use clear commit messages beginning with `ADS:`, `AMS:`, or `PMSE:` as appropriate.
- Do not claim test execution or final pass credit. Use wording like "definition decision selected", "candidate definition added", "execution pending", or "D2 update pending" when appropriate.
- If editing D2 files, use the `capella-d2` skill, render with the project ELK tight-spacing flags, inspect the PNG, and commit regenerated PNGs. Avoid D2 edits unless the issue explicitly needs them.
- If a criterion cannot be made strict with available equipment, document the strict pass path and the limited/characterization path instead of weakening the requirement silently.
- Do not create separate contradictory ADS-only and AMS-only freshness rules. The PM&SE shared contract is the source rule; subsystem test text must reference it.
- If conflicts or unexpected scope appear, stop and summarize rather than making broad unrelated changes.

## Final acceptance criteria

- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` exists and lists every `ADS-BLK-001` through `ADS-BLK-010` with selected decision, candidate test impact, existing-test updates, and execution prerequisites.
- `PM&SE/contracts/` contains one shared ADS/AMS sensor-to-OBCC freshness contract and reusable status/type reference defining 5 Hz request/response, 400 ms max age at 2 s telemetry, the required status enum, and no-old-data-as-valid behavior.
- ADS tests include or reference `ADS-V10-DATA-FRESHNESS` behavior via ADS OBCC-delivery/getter/rate tests using the shared contract.
- AMS tests include `AMS-V10-DATA-FRESHNESS` or an explicit extension of AMS API/FC tests using the shared contract.
- `SYS-END-TO-END-DATA` planning text in PM&SE uses the same shared freshness rule for system-level ADS/AMS data-path verification.
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2 no longer lists ADS blockers as undefined; it records closed/resolved/dispositioned decisions and any remaining execution/D2-modeling follow-up without calling it an open definition blocker. AMS freshness/cross-cutting rows are aligned without overclaiming execution.
- `PM&SE/MBSE_Test_Plan_Assessment.md` ADS/AMS findings are consistent with the selected decisions and do not continue to say the same criteria are TBD.
- Local controlled files exist for Serial0 schema/parser and ADS/AMS shared freshness contract/watchdog semantics.
- ADS candidate list includes v1.0 ADS-to-OBCC 5 Hz delivery/freshness, acceleration accuracy/units, and heading/north accuracy, with quantitative criteria and evidence methods.
- Existing ADS test README updates cover 10 min mission duration, 5 Hz jitter/worst-gap tolerance, v0.2 I2C code-analysis constraint handling, no-blocking instrumentation criteria, and GPS/gyro truth/statistics methods.
- Any D2/source-model updates not applied in this pass are listed explicitly as follow-on updates, not hidden inconsistencies.
- Temporary issue files under `PM&SE/ads_blocker_resolution_issues/` are removed by the final cleanup issue. This plan remains as the high-level orchestration record.

## Execution status

In progress.

- `ISSUE-ADS-001` completed in commit `6c36860`.
- `ISSUE-ADS-002` completed in commit `936e478`.
- Scope was expanded after `ISSUE-ADS-002` to add one shared ADS/AMS sensor-to-OBCC freshness contract and aligned AMS/SYS freshness tests.
- Remaining issue files are under `PM&SE/ads_blocker_resolution_issues/` and will be removed after final validation.
