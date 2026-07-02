# DPS-V10 UI, CSV, latency, and dashboard layout oracles

Date: 2026-07-02

## 1. Scope and status

This document freezes definition-level oracles only for:

- `DPS-V10-T-005` — dashboard visualisation;
- `DPS-V10-C-004` — browser-accessible dashboard;
- `DPS-V10-C-005` — unique CSV/session archival integrity;
- `DPS-V10-C-006` — top latency alert when latency is greater than `1.0 s`;
- `DPS-V10-C-008` — `4x4` dashboard plot matrix with top-left attitude model.

It is not an execution report and does not grant pass/fail credit. Execution, detailed activity READMEs, D2/source-model updates, PNG regeneration, implementation changes, and system-level integration updates remain pending.

The current `DPS/dashboard.py` implementation is a Tkinter/customtkinter desktop application, not a browser-accessible dashboard. Strict browser-access execution for `DPS-V10-C-004` is therefore **HOLD/limited** until a browser-accessible dashboard exists. This does not weaken the browser-access requirement.

## 2. Browser/UI access policy for `DPS-V10-C-004`

### 2.1 Browser selection

- **Primary strict-credit browser:** current stable Google Chrome or Chromium on the evidence workstation. The report shall record product name, version, OS, workstation ID, display resolution, zoom level, and whether hardware acceleration or accessibility scaling is enabled.
- **Optional secondary browser:** current Firefox or Firefox ESR on the same or equivalent evidence workstation. Secondary-browser evidence is compatibility evidence unless the detailed definition explicitly makes it part of strict pass/fail credit.

### 2.2 Required browser entry point and launch evidence

Strict credit requires a real HTTP(S) browser entry point, not `file://` screenshots and not a Tkinter/native desktop window.

- **Default local evidence URL:** `http://127.0.0.1:8050/` unless the approved detailed implementation records a different controlled host/port.
- **Start command evidence:** record the exact command used to start the browser-accessible dashboard, its working directory, environment variables, input source, serial/log configuration, CSV output directory, and software commit/build ID. A conforming future command shall expose the dashboard at the declared URL and shall be repeatable from the repository root or a documented deployment directory.
- **Current implementation status:** `python DPS/dashboard.py` starts a Tkinter/customtkinter UI and does not provide the required browser URL. Evidence from this implementation may be retained only as limited characterization for display behavior; it cannot close `DPS-V10-C-004`.

### 2.3 Browser evidence checklist

For each browser used, archive under `DPS/MBSE/tests/results/<test-id>/`:

1. command-line transcript or launcher log showing the dashboard start command and URL;
2. screenshot of the first successful load with URL bar visible;
3. continuous video or screen recording covering payload injection, dashboard update, refresh, reconnect, and alert behavior;
4. browser console log exported after the run, with zero uncaught errors that affect required user functions;
5. network/backend log showing initial connection, refresh, disconnect/reconnect, and graceful recovery;
6. evidence that ordinary operator functions do not require developer-console commands;
7. evidence that browser refresh, browser close/reopen, backend reconnect, and input-source reconnect do not corrupt displayed values, CSV rows, session naming, or command/UI state.

Pass for strict browser-access credit only if the primary browser opens the declared URL, displays the required UI, survives the refresh/reconnect cases without data corruption, and has no required user operation dependent on developer tools.

## 3. Dashboard visualisation and layout oracle for `DPS-V10-T-005` / `DPS-V10-C-008`

### 3.1 Payload field baseline

The display oracle uses the current v1.0 variable table in `OBCC/LoRa_Frame.md` and the DPS README requirements. The obsolete RH/relative-humidity field is not part of the v1.0 dashboard acceptance oracle and shall not be added as a placeholder.

Required v1.0 telemetry fields are:

1. `Pitch` (`rad`)
2. `Roll` (`rad`)
3. `Yaw` (`rad`)
4. `Angular Speed X` (`rad/s`)
5. `Angular Speed Y` (`rad/s`)
6. `Angular Speed Z` (`rad/s`)
7. `Acceleration X` (`m/s2`)
8. `Acceleration Y` (`m/s2`)
9. `Acceleration Z` (`m/s2`)
10. `Altitude` (`m`)
11. `Temperature` (`Celsius`)
12. `Latitude`
13. `Longitude`
14. `Battery Voltage` (`V`)
15. `Battery Current` (`mA`)

### 3.2 Selected `4x4` cell mapping

The required dashboard matrix is four rows by four columns. Cell `(1,1)` is the attitude model. The remaining cells display current value and trend/plot or equivalent recent-history visualization for the controlled v1.0 fields.

| Cell | Selected display |
|---|---|
| `(1,1)` | CanSat attitude model rendered from `Pitch`, `Roll`, and `Yaw` |
| `(1,2)` | `Pitch` numeric/trend, `rad` |
| `(1,3)` | `Roll` numeric/trend, `rad` |
| `(1,4)` | `Yaw` numeric/trend, `rad` |
| `(2,1)` | `Angular Speed X`, `rad/s` |
| `(2,2)` | `Angular Speed Y`, `rad/s` |
| `(2,3)` | `Angular Speed Z`, `rad/s` |
| `(2,4)` | `Acceleration X`, `m/s2` |
| `(3,1)` | `Acceleration Y`, `m/s2` |
| `(3,2)` | `Acceleration Z`, `m/s2` |
| `(3,3)` | `Altitude`, `m` |
| `(3,4)` | `Temperature`, `Celsius` |
| `(4,1)` | `Latitude` |
| `(4,2)` | `Longitude` |
| `(4,3)` | `Battery Voltage`, `V` |
| `(4,4)` | `Battery Current`, `mA` |

A strict pass requires all cells to be present, labeled with field name and unit where a unit is defined, and updated from the same accepted payload stream used for CSV evidence. Pressure and RH are not acceptance cells for v1.0 because they are not in the current OBCC frame table.

### 3.3 Attitude rendering oracle

The top-left cell shall render CanSat attitude from `Pitch`, `Roll`, and `Yaw` using a documented convention. For strict credit, the detailed definition shall include a deterministic known-payload sequence that isolates each axis and a reference expected-rendering record.

Minimum attitude sequence:

| Step | `Pitch` | `Roll` | `Yaw` | Expected observable behavior |
|---|---:|---:|---:|---|
| A0 | `0.00 rad` | `0.00 rad` | `0.00 rad` | Level/reference attitude shown. |
| A1 | `+0.50 rad` | `0.00 rad` | `0.00 rad` | Pitch-only movement; roll and yaw do not move. |
| A2 | `0.00 rad` | `+0.50 rad` | `0.00 rad` | Roll-only movement; pitch and yaw do not move. |
| A3 | `0.00 rad` | `0.00 rad` | `+0.50 rad` | Yaw-only movement; pitch and roll do not move. |
| A4 | `-0.40 rad` | `+0.30 rad` | `-0.60 rad` | Combined attitude matches reference image/video for the selected convention. |

Failure modes include swapped axes, ignored yaw/pitch/roll, stale attitude after a new accepted payload, attitude sourced from obsolete fields, or an altitude-only display in the top-left cell.

### 3.4 Payload-to-display and hardening cases

Use at least `N=300` known accepted v1.0 payloads at the flight cadence for the normal display sequence when this oracle is executed with `DPS-V10-T-005`. For every accepted payload, the displayed current values shall match the source payload after the declared decode/scaling rules.

Fault and stale-data behavior:

- Missing mandatory field, malformed frame, checksum/integrity failure, non-finite value, or out-of-range value for a field with a controlled range shall be rejected or visibly flagged; it shall not silently update the display as valid current data.
- If any mandatory field in a frame is invalid and the detailed definition does not support field-level validity, the whole frame is rejected from accepted dashboard and CSV streams.
- If field-level validity is supported, invalid cells shall show `INVALID`/equivalent, not a plausible numeric value; previous valid values may remain visible only when marked stale/non-current.
- If no accepted payload is received for more than two expected flight-cadence intervals (`>4 s` at the v1.0 `2 s` cadence), affected cells shall visibly indicate stale or disconnected status.
- Browser refresh/reconnect shall not duplicate, reorder, or invent display points.

Evidence shall include the source payload log, dashboard update log, screenshots/video at selected sequence IDs, invalid/stale-case screenshots, and a mapping comparison table or script output showing expected versus displayed values by cell.

## 4. CSV/session oracle for `DPS-V10-C-005`

### 4.1 Unique no-overwrite session naming

Strict CSV archival credit requires a unique session identity created at dashboard/decoder session start using atomic no-overwrite file creation. The selected naming rule is:

```text
DPS-v1.0_<UTC-start-timestamp>_<monotonic-session-token>_<short-unique-id>.csv
```

where:

- `<UTC-start-timestamp>` is ISO-like UTC with at least millisecond resolution, e.g. `20260702T153012.123Z`;
- `<monotonic-session-token>` is derived from a monotonic clock value or launch counter to harden same-second restarts;
- `<short-unique-id>` is a collision-resistant suffix such as a UUID fragment or an atomic increment chosen before file creation;
- file creation uses an exclusive create/no-clobber operation. If a collision is detected, the implementation shall create a new unique name and log the collision; it shall never truncate or append to a prior session file unless explicitly opened as a controlled continuation with report approval.

A filename that uses only whole-second wall-clock time is not sufficient for strict credit unless an additional atomic suffix/counter prevents same-second collisions.

### 4.2 Restart/session campaign oracle

Minimum strict evidence for this definition:

- at least `10` dashboard/decoder sessions or restarts;
- include rapid restarts with at least two starts attempted within the same wall-clock second, or a justified equivalent generator-level collision test if the OS/operator cannot reliably launch that quickly;
- zero overwritten files, zero truncated prior files, and zero ambiguous duplicate session names;
- each session report records start time, session ID, CSV path, raw input log path, accepted-frame count, and hash/comparison result.

### 4.3 CSV row integrity

For every session:

- rows are append-only and monotonically ordered by row index and accepted frame sequence/time;
- each accepted decoded frame appears exactly once in the CSV;
- CSV row count equals the accepted-frame count from the decoder/source payload log;
- invalid, rejected, stale, duplicate, malformed, or missing-field frames do not appear as valid CSV rows;
- the CSV field order and units are controlled and traceable to the v1.0 payload schema used for the run;
- raw input logs are retained, including raw serial/RF bytes or the deterministic source payload log used for synthetic injection.

The report shall include either:

1. a checksum/hash over a normalized canonical representation of accepted source payloads and normalized CSV rows, with matching hashes; or
2. a deterministic comparison table/script output showing every accepted source frame mapped to exactly one CSV row with matching field values, scaling, timestamp/sequence, and session ID.

A strict pass requires zero mismatches, zero overwrites, zero duplicate accepted rows, and retained raw input evidence.

## 5. Latency alert oracle for `DPS-V10-C-006`

### 5.1 Timestamp source and latency definition

Latency for the dashboard alert is defined as:

```text
latency_s = dashboard_render_decision_time_monotonic - accepted_frame_rx_time_monotonic
```

where both timestamps are taken on the DPS/evidence workstation from the same monotonic clock domain, or from a documented synchronized monotonic-equivalent method with bounded uncertainty. Wall-clock UTC may be logged for correlation, but wall-clock jumps shall not drive the pass/fail threshold.

The accepted-frame RX timestamp is the time at which the Decoder accepts a frame as valid for payload fan-out. The dashboard render decision time is the time at which the UI decides whether to show or clear the top latency alert for that accepted payload.

### 5.2 Alert threshold rule

- If `latency_s <= 1.0`, the top latency alert shall not be visible for that payload.
- If `latency_s > 1.0`, a visible alert shall appear in the top alert region of the dashboard for that payload.
- The alert text/color/icon may be implementation-specific, but the evidence must make it unambiguous that the top alert is active because latency exceeded `1.0 s`.
- Boundary comparisons are strict: exactly `1.000 s` is no alert; `1.001 s` is alert, subject to the declared timing uncertainty/guard band.

### 5.3 Threshold sample set

Minimum strict sample set:

- at least `30` no-alert cases with latency at or below threshold, including representative below-threshold cases and boundary cases at `1.0 s` within the timing uncertainty budget;
- at least `30` alert cases with latency greater than threshold, including near-boundary cases just above `1.0 s` and larger late cases;
- a justified equivalent is allowed only if it provides equal or stronger boundary coverage and records the weaker/alternate claim explicitly.

For each case, retain frame ID, RX monotonic timestamp, dashboard decision monotonic timestamp, computed latency, expected alert state, observed alert state, screenshot/video reference, and pass/fail result.

### 5.4 Invalid timestamp hardening

The dashboard/decoder shall reject or visibly flag, rather than silently accept as valid latency evidence:

- missing RX timestamp;
- non-numeric or non-finite timestamp;
- non-monotonic timestamp relative to the accepted-frame stream;
- future timestamp beyond the declared clock-uncertainty tolerance;
- timestamp from an unknown or mixed clock domain;
- negative computed latency;
- stale replay that reuses an older timestamp/sequence as current.

Invalid timestamp cases shall not produce false no-alert credit. They shall be logged with reject/flag reason and shown in evidence as rejected or flagged.

## 6. Evidence/report checklist

Each affected report shall reference this oracle document and record, as applicable:

- model baseline and test/activity ID;
- as-tested DPS software commit/build, dashboard implementation, decoder/CSV implementation, browser product/version, OS/workstation, display settings, serial/RF/input configuration, and payload schema/version;
- exact dashboard start command, working directory, environment, URL, and browser-launch method;
- source payload log and raw input log retained unchanged;
- accepted/rejected frame log with sequence, timestamps, reject reasons, and field values;
- CSV session files, session IDs, row counts, file hashes, canonical comparison output, and overwrite/collision evidence;
- dashboard screenshots/video for initial load, `4x4` layout, attitude sequence, normal payload updates, stale/invalid/missing-field cases, refresh/reconnect, and latency alert boundary cases;
- browser console/network/backend logs;
- monotonic time source description and timing uncertainty/guard band;
- pass/fail rationale, deviations, anomalies, waivers, limitations, and any HOLD/limited status.

## 7. Affected-test update map

| Target | Required use of this oracle baseline |
|---|---|
| `DPS-V10-T-005` | Use the v1.0 payload-to-display mapping, top-left pitch/roll/yaw attitude sequence, stale/invalid/missing-field behavior, browser evidence policy, and latency-alert evidence when dashboard visualization is exercised. |
| `DPS-V10-C-004` | Use the primary Chrome/Chromium strict-credit browser, declared URL/start-command evidence, refresh/reconnect checks, console/network logs, and HOLD/limited disposition for the current Tkinter-only implementation. |
| `DPS-V10-C-005` | Use the no-overwrite session naming rule, `10` session/restart campaign including same-second collision hardening, monotonic row/order checks, row-count match, canonical hash/comparison, and raw input log retention. |
| `DPS-V10-C-006` | Use the monotonic RX-to-dashboard latency definition, strict `<=1.0 s` no-alert / `>1.0 s` top-alert rule, threshold sample set, and invalid timestamp hardening. |
| `DPS-V10-C-008` | Use the selected `4x4` cell map, required labels/units, top-left CanSat attitude model, no RH/pressure acceptance cell, resize/refresh evidence, and stale/invalid display behavior. |

## 8. Residual prerequisites and D2/model follow-up

Before strict execution credit:

1. Provide or implement a browser-accessible dashboard entry point; the current Tkinter `DPS/dashboard.py` leaves `DPS-V10-C-004` HOLD/limited.
2. Freeze the concrete payload schema/envelope, decode/scaling rules, sequence/timestamp fields, CSV column order, and source payload generator/log format used for the campaign.
3. Create/update detailed modeled definitions for `DPS-V10-T-005`, `DPS-V10-C-004`, `DPS-V10-C-005`, `DPS-V10-C-006`, and `DPS-V10-C-008` so their pass/fail constraints reference this oracle.
4. Update D2/source-model views and regenerate PNGs only in the later model-update pass; no D2 or PNG updates are made by this oracle file.
5. Define the actual browser start command, URL/port, input mode, CSV output directory, logging switches, and analysis/comparison scripts in the execution procedure.
6. Execute only after the detailed definitions and evidence paths are approved; archive results under the applicable `DPS/MBSE/tests/results/<test-id>/` paths.

With these definition decisions, `DPS-BLK-006` is closed at definition level after final integration, while execution, implementation, and D2/model updates remain pending.
