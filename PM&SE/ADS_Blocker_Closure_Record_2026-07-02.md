# ADS Blocker Closure Record — Definition Decisions

Date: 2026-07-02

## Scope

This record captures definition-blocker resolution decisions for ADS verification planning, plus the shared PM&SE ADS/AMS sensor-to-OBCC freshness decision required by `ADS-BLK-007`. It does not execute tests, does not create execution reports, and does not claim pass/fail credit. Later issues must update the affected ADS test definitions, local schema/contract artifacts, D2/PNG views where needed, AMS freshness alignment, system-level freshness use, and execution reports.

The decisions below use `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`, `PM&SE/IVV.md`, the ADS README, the ADS MBSE test index, and the existing ADS activity READMEs as the baseline. Where existing criteria conflict, this record selects the user-approved decision and records the required follow-up.

## Blocker decision table

| Blocker ID | Selected closure decision | Affected candidate/new tests | Affected existing tests | Execution prerequisites | Closure / follow-up status |
|---|---|---|---|---|---|
| ADS-BLK-001 | v1.0 ADS shall provide internally available data to OBCC at 5 Hz under the shared PM&SE sensor-to-OBCC freshness contract. OBCC LoRa telemetry remains a separate 2 s cadence and samples the latest ADS data with age/status metadata. The current v1.0 N/A rationale for the ADS 5 Hz verdict is superseded. | Add/update a v1.0 ADS-to-OBCC rate/freshness candidate, preferably by extending `ADS-IVV-C-RATE-5HZ` plus `ADS-IVV-FC-OBCC-DELIVERY` rather than adding a duplicate folder. | `ADS-IVV-C-RATE-5HZ`, `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-FC-MISSION-WINDOW`, ADS test index. | Shared PM&SE freshness contract, ADS-specific Pointers/Returns supplement if needed, OBCC log harness, monotonic timestamps or equivalent, firmware build ID, UUT ID, equipment IDs/calibration, and timing-analysis script revision. | Definition decision closed here; README/D2/test-definition update and execution follow-up remain. |
| ADS-BLK-002 | Acceleration is a linear acceleration quantity. Units shall be `m/s²`; raw `g` is acceptable only when converted to `m/s²`. The README wording using `deg/s²` is contradictory and shall not be used as the acceleration oracle. | Add `ADS-IVV-C-ACC-3AXIS` or equivalent acceleration units/accuracy candidate. | `ADS-IVV-FC-ATT` for acceleration data propagation; ADS README requirement text in a later integration/update pass. | Six-face static gravity fixture, axis/sign convention, logger/parser fields, `n >= 30` stable samples per face, uncertainty guard band, UUT/firmware/equipment IDs. | Definition decision closed here; new candidate/test-definition and possible requirement-text/D2 follow-up remain. |
| ADS-BLK-003 | A quantitative heading/north criterion is required; the existing attitude activity remains only plausibility/repeatability unless updated. Heading shall be verified against controlled true/magnetic north reference with magnetic disturbance controls. | Add `ADS-IVV-C-HEADING-NORTH` or fold an explicit heading constraint into `ADS-IVV-FC-ATT`. | `ADS-IVV-FC-ATT`, ADS test index, possibly ADS README requirement text. | Non-magnetic heading/orientation fixture, surveyed true-north line or calibrated magnetic reference with declination, calibration state, local magnetic disturbance survey, `n >= 30` stable samples per heading. | Definition decision closed here; candidate/D2 update and execution follow-up remain. |
| ADS-BLK-004 | ADS mission-window duration is 10 min. At 5 Hz this implies 3000 expected internal ADS update opportunities for the mission window. Mission-window criteria shall include reset/stuck-loop failure rules, mandatory field/marker presence, invalid/stale/corrupt handling, and a maximum gap rule. | No separate new candidate; the v1.0 rate/freshness candidate uses the same mission duration where applicable. | `ADS-IVV-FC-MISSION-WINDOW`, `ADS-IVV-C-RATE-5HZ`, `ADS-IVV-FC-OBCC-DELIVERY`. | Run-controller start/stop markers, synchronized timebase, power/reset/brownout monitoring, logger configuration, expected-update counter/sequence or equivalent. | Definition decision closed here; test-definition/D2 update and execution follow-up remain. |
| ADS-BLK-005 | 5 Hz timing is nominal period 200 ms. Strict timing evidence shall predeclare jitter, mean-rate, worst-gap, stale/drop/duplicate, and timestamp rules; no after-the-fact characterization-only tolerance may be promoted to pass/fail. | Same v1.0 rate/freshness candidate/update as above. | `ADS-IVV-C-RATE-5HZ`, `ADS-IVV-FC-GPS`, `ADS-IVV-FC-MISSION-WINDOW`, `ADS-IVV-FC-OBCC-DELIVERY`. | Reference clock or monotonic firmware timestamps, instrumentation-overhead bound, complete raw logs, sequence/freshness markers, analysis script revision. | Definition decision closed here; test-definition/D2 update and execution follow-up remain. |
| ADS-BLK-006 | v0.1/v0.2 Serial0 closure requires a controlled local schema/parser/campaign baseline before pass/fail. The baseline shall define port/baud/framing, field list, units, validity/stale/error markers, parser version, and expected frame/campaign rules. | No new behavioral test required unless the schema issue elects to create a companion parser self-test; primary closure is an update to Serial0 delivery. | `ADS-IVV-FC-SERIAL`, ADS test index. | Local schema file, parser/tool version, raw-byte capture, expected records/counts, fault-marker vocabulary, PC/logger configuration, equipment IDs/calibration. | Decision captured here; non-D2 schema/parser artifact follow-up remains before full definition closure and execution. |
| ADS-BLK-007 | v1.0 `Pointers`/`Returns` freshness/status semantics are governed by the shared PM&SE sensor-to-OBCC contract for ADS and AMS. ADS-specific supplemental detail may still define field/schema semantics, pointer ownership/lifetime, return/error codes, and watchdog/timeout implementation without redefining freshness/status. | No duplicate candidate if `ADS-IVV-FC-OBCC-DELIVERY` is extended; otherwise create an ADS-specific Pointers/Returns supplement that references the shared PM&SE contract. | `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-RATE-5HZ`, `ADS-IVV-C-NOBLOCK`, ADS test index. | Shared PM&SE contract/header reference, ADS-specific contract/code supplement if needed, OBCC delivery harness, freshness timestamps, watchdog logs, fault injection for null/stale/corrupt/slow calls, firmware commit. | Decision captured here; shared PM&SE contract exists, while ADS-specific supplement and D2/test-definition follow-up remain before execution. |
| ADS-BLK-008 | v0.2 I2C timeout shall be treated as a constraint-derived code-analysis/instrumentation activity or controlled model gap, not forced into cluttered source MBSE diagrams. v1.0 remains the formal modeled I2C timeout baseline. | No new candidate required unless code-analysis artifacts are split out; use the existing I2C timeout activity. | `ADS-IVV-C-I2C-5MS`, `ADS-IVV-C-NOBLOCK`, `ADS-IVV-FC-ANG`, `ADS-IVV-FC-ATT`, `ADS-IVV-FC-INIT`. | Firmware source/build map or instrumentation hooks, I2C fault injector, bus/timing capture, `n = 59` zero-violation samples for formal deadline claims. | Definition decision closed here; text/test-definition update and execution follow-up remain; no source D2 update required by this decision. |
| ADS-BLK-009 | No-blocking pass/fail requires firmware source/build map/symbols or equivalent instrumentation, explicit heartbeat/progress deadline, and instrumentation overhead allowance. External equipment is available, but reports still need asset IDs and calibration status. | No new candidate; update no-blocking and timing activities. | `ADS-IVV-C-NOBLOCK`, `ADS-IVV-C-PROC-5MS`, `ADS-IVV-C-UART-5MS`, `ADS-IVV-C-I2C-5MS`, `ADS-IVV-FC-OBCC-DELIVERY`. | Source or instrumentation access, build map/symbols, heartbeat logger, GPS/I2C fault injectors, overhead measurement, equipment IDs/calibration, analysis scripts. | Definition decision closed here; test-definition/D2 update and execution follow-up remain. |
| ADS-BLK-010 | Accuracy truth/reference methods are selected: strict GPS `<5 m` needs surveyed/open-sky or GNSS-simulator truth; phones are auxiliary unless independently uncertainty-controlled. Angular-rate truth may use motors plus calibrated tachometer, with statistics-backed all-within-limit evidence when making a strict claim. | Supports `ADS-IVV-C-ACC-3AXIS` and `ADS-IVV-C-HEADING-NORTH`; no new GPS/gyro tests if existing activities are updated. | `ADS-IVV-C-POS-5M`, `ADS-IVV-C-GYRO-30DPS`, `ADS-IVV-FC-GPS`, `ADS-IVV-FC-ANG`, `ADS-IVV-FC-ATT`. | Surveyed reference or GNSS simulator, tachometer calibration/reliability evidence, motor stability and axis alignment, truth/ADS timestamp correlation, uncertainty guard bands, `n = 59` all-within-limit gyro evidence for strict claims. | Definition decision closed here; truth-method D2/test-definition update and execution follow-up remain. |

## Candidate ADS test list selected by this record

These are the complete ADS candidate/new-test actions selected by this closure record. Other ADS closure actions are updates to existing modeled tests.

| Candidate / update ID | Purpose | Selected definition and pass/fail baseline | Later implementation path |
|---|---|---|---|
| `ADS-V10-DATA-FRESHNESS` (alias/extension through `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ`) | Close v1.0 ADS-to-OBCC internal delivery-rate/freshness. | ADS shall make an ADS update record/slot available to OBCC at `5 Hz` for the 10 min mission window using [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](contracts/sensor_obcc_freshness_contract.md): `2 s` LoRa telemetry remains separate, fresh age is `<=400 ms` only with status `VALID`, and the exact status enum is `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`. Missing, duplicate, corrupt, stale-as-valid, no-data-as-valid, timeout-as-valid, fault-as-valid, or init-fail-as-valid records fail the strict delivery claim. | Prefer updating the three existing activities and ADS test index; add D2 definition views only if the existing activities become too overloaded. |
| `ADS-IVV-C-ACC-3AXIS` | Close acceleration quantity, units, sign, and static accuracy. | Use a six-face static gravity fixture. Record `n >= 30` stable samples per face. Convert raw `g` to `m/s²` using `g0 = 9.80665 m/s²`; do not use `deg/s²`. Pass if each axis has the correct sign/axis mapping and absolute error plus expanded uncertainty is `<= 1.0 m/s²` at the expected `+g`, `-g`, or `0` condition. | Create a new constraint-derived activity or fold into attitude only if the heading/attitude package remains clear. Update ADS README wording later. |
| `ADS-IVV-C-HEADING-NORTH` | Close north/heading quantitative acceptance. | Use a non-magnetic fixture/site and a surveyed true-north line or calibrated magnetic reference with declination correction. At minimum, test stable headings near 0°, 90°, 180°, and 270° with `n >= 30` samples each. Pass if circular heading error plus expanded uncertainty is `<= 10°` for each heading and magnetic-disturbance/fault cases are not accepted as valid. | Create a new heading constraint activity or explicitly extend `ADS-IVV-FC-ATT`; update D2/test index accordingly. |

No additional ADS planning candidates are selected by this record. Serial0 schema/parser files, the shared PM&SE freshness contract, and any ADS-specific Pointers/Returns supplement are definition artifacts for existing activities, not additional mission-behavior candidates.

## Shared ADS/AMS freshness-contract note

- [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](contracts/sensor_obcc_freshness_contract.md) governs freshness/status for both ADS and AMS sensor-to-OBCC responses and `2 s` telemetry packaging.
- ADS v1.0 uses `ADS-V10-DATA-FRESHNESS` as the candidate/alias implemented by explicit extensions of `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ`; no new standalone ADS folder is required unless those extensions become unclear.
- The ADS freshness oracle is exactly: OBCC requests/responses at `5 Hz` (`200 ms` nominal), `2 s` LoRa telemetry packaging remains separate from internal `5 Hz` evidence, fresh data requires `status == VALID` and `age_ms <= 400 ms`, and the status enum is exactly `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL` conditions shall not leave old ADS data marked `VALID`; old values may be carried only as non-`VALID` with age/status evidence.
- ADS `Pointers`/`Returns` ownership, lifetime, API names, return-code mapping, and watchdog implementation remain ADS-specific supplemental detail and shall reference the shared PM&SE contract.
- AMS data freshness must be aligned through `AMS-V10-DATA-FRESHNESS` or through explicit extensions of `AMS-VV-API-001` and/or `AMS-VV-FC-001`.
- `SYS-END-TO-END-DATA` must use the same shared freshness rule as the sensor freshness oracle for ADS/AMS age/status fields and stale/error behavior.

## Existing ADS test update list

| Existing activity | Required update for later issues |
|---|---|
| `ADS-IVV-C-RATE-5HZ` | Replace the v1.0 N/A-only rationale with the `ADS-V10-DATA-FRESHNESS` branch, or explicitly reference that branch in `ADS-IVV-FC-OBCC-DELIVERY`. Add the `200 ms` nominal period, `3000` expected internal update opportunities over 10 min, jitter/sample rule, worst-gap rule, stale/drop/duplicate criteria, contract age/status evidence (`<=400 ms`, `VALID`/`STALE`/`NO_DATA`/`TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL`), no stale/no-data/timeout/fault/init-fail data marked `VALID`, and instrumentation-overhead handling. Keep `2 s` LoRa telemetry separate from internal `5 Hz` evidence. |
| `ADS-IVV-FC-MISSION-WINDOW` | Set mission window to 10 min. Define 3000 expected internal update opportunities at 5 Hz, mandatory field/marker presence, no reset/brownout/stuck-loop acceptance, no unrecovered peripheral failure, invalid/stale/corrupt marker handling, and maximum gap `<= 400 ms` for ADS internal delivery observation. |
| `ADS-IVV-FC-SERIAL` | Reference the controlled Serial0 schema/parser/campaign baseline for v0.1/v0.2: port/baud/framing, fields, units, validity/stale/error markers, parser version, expected count/campaign duration, and raw-byte retention. Keep v0.3/v1.0 N/A rationale. |
| `ADS-IVV-FC-OBCC-DELIVERY` | Reference the shared PM&SE sensor-to-OBCC freshness contract for `5 Hz` delivery/freshness, `<=400 ms` age, exact enum `VALID`/`STALE`/`NO_DATA`/`TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL`, telemetry age/status, and no-old-data-as-`VALID` behavior after stale/no-data/timeout/fault/init-fail conditions. Add ADS-specific supplemental watchdog thresholds, pointer ownership/lifetime, return/error-code mapping, and null/dangling/stale/corrupt/slow-call fault cases. |
| `ADS-IVV-C-GETTER` | Map ADS getter/process/collector validity and return/error semantics to the shared PM&SE enum or a controlled one-to-one evidence mapping, preserve ADS-specific details as subordinate evidence, require timestamp/sequence/age evidence at the ADS-to-OBCC observation point, and prove stale/no-data/timeout/fault/init-fail paths do not leave old data marked `VALID`. |
| `ADS-IVV-C-I2C-5MS` | Update v0.2 from an unresolved model gap to a selected code-analysis/instrumentation or documented-gap path. Do not require cluttered v0.2 source D2 changes for this timeout. Preserve v1.0 formal `<=5 ms` I2C timeout. |
| `ADS-IVV-C-NOBLOCK` | Add source/build map/symbols or equivalent instrumentation prerequisite; heartbeat/progress deadline `<= 400 ms`; instrumentation-overhead allowance; and explicit blocked/limited status if source/instrumentation access is absent. |
| `ADS-IVV-C-POS-5M` | Add strict GPS truth policy: GNSS simulator or surveyed/open-sky reference with uncertainty guard band. State that consumer phones are auxiliary/limited unless their uncertainty is independently controlled and guard-banded. Preserve `n >= 30` matched valid samples and invalid/no-fix/stale handling. |
| `ADS-IVV-C-GYRO-30DPS` | Add motor plus calibrated tachometer as an approved angular-rate truth path. Require tachometer reliability/calibration, motor stability, RPM-to-deg/s conversion, axis alignment, time correlation, uncertainty guard band, and `n = 59` all-within-limit evidence for strict claims. |
| `ADS-IVV-FC-ATT` | Either reference new acceleration and heading candidates or incorporate them explicitly. If not incorporated, keep current attitude plausibility wording and link to `ADS-IVV-C-ACC-3AXIS` and `ADS-IVV-C-HEADING-NORTH` for quantitative claims. |
| `ADS-IVV-FC-GPS` | Align v1.0 delivery/rate note with the selected ADS-to-OBCC 5 Hz decision and strict GPS truth policy. |
| `ADS-IVV-FC-ANG` | Align angular-rate truth/reference assumptions with the motor/tachometer method and strict-statistics rule. |
| `ADS-IVV-C-PROC-5MS` / `ADS-IVV-C-UART-5MS` | Align instrumentation overhead and `n = 59` zero-violation deadline wording with the no-blocking and timing decisions. |

## Selected quantitative criteria

### Mission duration and ADS update count

- ADS mission-window duration: **10 min = 600 s**.
- Expected internal ADS update opportunities at **5 Hz**: **3000** per mission window.
- The mission-window run starts after the declared ADS ready/start marker. Startup before that marker is not counted unless a later activity explicitly says so.
- Any reset, brownout, stuck loop, unrecovered peripheral failure, unreported logger loss, or unmodeled bypass invalidates the strict mission-window pass.

### 5 Hz timing, jitter, freshness, and gap rules

- Nominal internal ADS update period: **200 ms**.
- Strict rate/freshness pass for a selected version requires all of the following:
  - at least **3000 scheduled ADS update slots/events** observed over the 600 s mission window at the declared observation point;
  - observed mean delivery rate **>= 5.0 Hz** over the mission window;
  - no silent missing slot; no duplicate or catch-up burst may compensate for a missed slot;
  - no update gap greater than **400 ms** anywhere in the mission window;
  - for the formal jitter/deadline sample, collect **`n = 59` representative consecutive intervals** and require every interval to be **150 ms to 250 ms** inclusive;
  - every record shall carry enough timestamp/sequence/freshness information to identify stale, dropped, duplicate, or corrupt records;
  - stale/error sensor data may be delivered only when explicitly marked and shall not be consumed or counted as fresh valid measurement data.
- v1.0 OBCC LoRa telemetry remains **2 s**. The LoRa frame may carry the latest ADS record plus `age`/status metadata; it is not the 5 Hz internal delivery evidence.
- Shared ADS/AMS freshness/status thresholds selected for v1.0:
  - age `<= 400 ms`: usable as fresh for internal OBCC consumers only when status is `VALID` and required fields are finite/in range;
  - age `> 400 ms`: status shall be `STALE` or another applicable non-`VALID` status and fail strict freshness if uncorrected in the rate run;
  - timeout, sensor fault, and initialization failure shall use `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, `NO_DATA`, or `STALE` as applicable and shall not leave old data marked `VALID`.

### Acceleration units and accuracy

- Linear acceleration units are **`m/s²`**. If firmware or logs use `g`, convert using **`g0 = 9.80665 m/s²`** before comparison.
- The existing `deg/s²` acceleration wording is contradictory and shall be corrected or overridden by test text; `deg/s` remains the angular-rate unit for gyro tests.
- Candidate static acceleration criterion: six-face fixture, `n >= 30` stable samples per face, correct axis/sign convention, and per-axis error plus expanded uncertainty **`<= 1.0 m/s²`** for expected `+g`, `-g`, or `0` conditions.

### Heading / north criterion

- Quantitative heading claim: circular heading error plus expanded uncertainty **`<= 10°`** at each tested heading.
- Minimum heading set: near **0°, 90°, 180°, and 270°** with `n >= 30` stable samples per heading.
- Required controls: non-magnetic fixture/site, declared true-north or magnetic-north reference, declination correction when needed, calibration state before/after, local disturbance survey, axis/sign convention, timestamp correlation, and explicit invalid/disturbed marker handling.
- If these controls are absent, `ADS-IVV-FC-ATT` remains plausibility/repeatability only and may not claim heading accuracy closure.

### GPS strict truth method

- Strict GPS `<5 m` pass requires one of:
  - GNSS simulator with declared scenario and uncertainty, or
  - surveyed/open-sky reference point or reference antenna setup with coordinate uncertainty small relative to 5 m and multipath/sky conditions controlled.
- Maintain `n >= 30` matched valid ADS/truth samples and require horizontal error plus truth/measurement uncertainty guard band to remain `<5 m`.
- Consumer phones may support logs, sanity checks, or field notes. A phone-only truth source is **limited/characterization** unless its uncertainty is independently controlled and guard-banded enough to support the `<5 m` pass.

### Gyro truth/statistics method

- Motors plus tachometer are approved as the angular-rate truth path when the tachometer is calibrated/reliable and the motor setpoint is stable.
- Convert tachometer speed using **`deg/s = RPM × 6`**.
- For a strict angular-rate claim, collect **`n = 59`** matched ADS/truth samples per selected axis/rate condition and require every guard-banded absolute error to remain **`< 30 deg/s`**.
- Required controls: tachometer equipment ID/calibration, motor stability evidence, axis alignment, fixture slip/vibration check, timestamp correlation, ambient/power records, and explicit saturation/stale/non-finite/I2C-fault marker handling.
- If tachometer calibration/reliability is inadequate, use a calibrated rate table or mark the motor/tachometer result as characterization only.

### No-blocking / instrumentation criteria

- Runtime progress heartbeat for `Loop` / `ADS Processing` shall be observable under nominal and fault cases with no progress gap greater than **400 ms**.
- Formal timeout/deadline claims use **`n = 59` zero-violation samples** unless a stricter project rule is later selected.
- Instrumentation overhead shall be measured before verdicts. As a planning allowance, overhead shall be `<= 10 ms` per 200 ms loop/delivery cycle and `<= 1 ms` for any individual 5 ms function/timeout timing hook, or it shall be subtracted/bounded with a documented uncertainty. Higher or unknown overhead makes timing evidence limited/characterization.
- External lab equipment listed in the assessment is considered available, but every execution report still needs actual equipment asset IDs, calibration/function-check status, tool versions, and environmental readings.

## Contradictions resolved by this record

| Contradiction or TBD | Selected resolution |
|---|---|
| ADS README requires v1.0 internal delivery to OBCC at least 5 Hz, while `ADS-IVV-C-RATE-5HZ` treats v1.0 as N/A. | v1.0 internal ADS-to-OBCC 5 Hz is required; LoRa 2 s cadence is separate. |
| ADS README acceleration unit says `deg/s²`, while acceleration is linear. | Use `m/s²` or converted `g`; do not use `deg/s²` as the acceleration oracle. |
| `ADS-IVV-FC-ATT` forbids formal numerical attitude accuracy unless a new constraint exists. | Keep attitude plausibility unless a heading/north constraint candidate is added or explicitly folded in. |
| Mission duration, maximum gap, and jitter tolerance were TBD. | Use 10 min, 3000 expected updates, 200 ms nominal, 150-250 ms formal jitter sample, and 400 ms maximum gap/watchdog threshold. |
| v0.2 I2C timeout is a model gap. | Resolve by code-analysis/instrumentation or controlled gap text; do not force cluttered v0.2 source diagrams. |
| GPS truth equipment and phone use were ambiguous. | Use surveyed/open-sky or simulator truth for strict `<5 m`; phones are auxiliary unless uncertainty-controlled. |
| Angular-rate truth fixture was assumed but not fixed. | Motors plus calibrated tachometer are approved with n=59 all-within-limit strict evidence if reliable/calibrated. |

## Follow-on D2/model and artifact update list

The following updates are intentionally not performed in this pass:

1. Update `ADS-IVV-C-RATE-5HZ` definition views/README and the ADS test index so v1.0 is no longer N/A for internal ADS-to-OBCC `5 Hz` delivery/freshness, or add a clearly linked `ADS-V10-DATA-FRESHNESS` rate/freshness definition view. Any D2 views that still say v1.0 rate is N/A require model/D2 follow-up; they are not edited in this Markdown alignment pass.
2. Update `ADS-IVV-FC-MISSION-WINDOW` definition views/README for the 10 min mission, 3000 expected update slots, strict reset/stuck-loop/freshness rules, and 400 ms maximum gap.
3. Create the Serial0 schema/parser/campaign baseline and reference it from `ADS-IVV-FC-SERIAL`.
4. Create any ADS-specific `Pointers`/`Returns` contract/header/code supplement for field/schema, ownership/lifetime, return-code mapping, and watchdog implementation; it shall reference the shared PM&SE freshness/status contract from `ADS-IVV-FC-OBCC-DELIVERY` rather than redefining freshness.
5. Add or update acceleration and heading/north candidate test-definition packages and regenerate any D2/PNG views.
6. Update `ADS-IVV-C-I2C-5MS` and linked activities to show the v0.2 code-analysis/instrumentation or controlled-gap path without adding cluttered v0.2 source-model diagrams.
7. Update `ADS-IVV-C-NOBLOCK` and timing activities with source/build-map/symbol prerequisites, heartbeat deadline, overhead allowance, and blocked/limited wording when instrumentation is absent.
8. Update `ADS-IVV-C-POS-5M`, `ADS-IVV-C-GYRO-30DPS`, `ADS-IVV-FC-GPS`, `ADS-IVV-FC-ANG`, and `ADS-IVV-FC-ATT` with the selected truth/reference methods, phone limitation, motor/tachometer method, and strict statistics.
9. Later integration shall update `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` and `PM&SE/MBSE_Test_Plan_Assessment.md`; this issue intentionally does not edit those files.

## Residual uncertainties before execution

- Exact Serial0 field names, parser implementation, campaign duration/count, and raw log format.
- Exact ADS/OBCC `Pointers`/`Returns` field schema, header/API names, ownership/lifetime details, watchdog implementation, and OBCC log harness; freshness/status semantics are controlled by the shared PM&SE contract.
- UUT serials, hardware revisions, firmware commits, build maps/symbols, and instrumentation hook names.
- Actual equipment asset IDs, calibration certificates/function checks, tool versions, and environmental limits.
- Surveyed GPS coordinates or simulator scenario, tachometer calibration/reliability, motor stability, and heading-reference calibration.
- Whether acceleration and heading are implemented as new standalone D2 packages or folded into existing attitude-related packages.
