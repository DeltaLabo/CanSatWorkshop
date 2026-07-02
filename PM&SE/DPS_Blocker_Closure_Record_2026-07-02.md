# DPS Blocker Closure Record — 2026-07-02

Status: definition-decision closure record for the DPS portion of `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.4.

## 1. Scope and guardrails

- This record closes definition decisions only. It does not execute tests, create evidence, or claim pass/fail credit.
- No D2, PNG, source-code, implementation, or generated-diagram edits are made by this record.
- No candidate activity folders are created by this record. Candidate rows are only queued for later detailed modeled definitions.
- v1.0 remains the active DPS detailed-definition baseline. v0.1/v0.2 closure is conditional historical work only if the project later requires it.
- Reports must still identify the exact as-tested hardware, firmware, PC software, payload/schema, radio settings, equipment, calibration state, deviations, waivers, and limitations.
- Controlled parameter/oracle outputs linked by this closure record:
  - [DPS-V10 RF range, LoRa airtime, PDR, and concurrency parameters](../DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md).
  - [DPS-V10 UI, CSV, latency, and dashboard layout oracles](../DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md).

## 2. Decision table

| Blocker ID | Selected disposition | Affected candidate/new tests | Affected existing tests/docs | Execution prerequisites | Follow-up status |
|---|---|---|---|---|---|
| `DPS-BLK-001` | Closed at definition-decision level as redundant once the complete candidate backlog is registered here and all remaining v1.0 rows are queued for detailed definitions. | `DPS-V10-T-004`, `DPS-V10-T-005`, `DPS-V10-T-006`, `DPS-V10-C-001`, `DPS-V10-C-003`, `DPS-V10-C-004`, `DPS-V10-C-005`, `DPS-V10-C-006`, `DPS-V10-C-008`; optional/retired signoffs `DPS-V10-C-002`, `DPS-V10-C-007`. | `DPS/MBSE/tests/README.md`, `DPS/README.md`, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`. | Detailed modeled definitions, reviewed pass/fail oracles, as-tested configuration IDs, and result reports before any execution credit. | Candidate-definition backlog remains; no open undefined decision remains for the listed v1.0 rows. |
| `DPS-BLK-002` | Already closed: obsolete RH dashboard/payload field was removed rather than adding a placeholder or expanding the OBCC frame. | None. Broader payload/schema control remains system-level. | DPS dashboard/model/test baselines and OBCC frame table. | Confirm final payload schema/version and field mapping before execution. | No DPS-specific follow-up except maintaining payload-schema consistency in reports and system data tests. |
| `DPS-BLK-003` | Already closed: top-left dashboard model is the CanSat attitude rendering from pitch/roll/yaw; altitude remains a 2D plot/value. | `DPS-V10-T-005`, `DPS-V10-C-008`. | `DPS/README.md`, `DPS/MBSE/tests/README.md`, dashboard visualization artifacts. | Detailed UI oracle, payload-to-display mapping, and evidence capture before display credit. | Definition choice closed; UI/detail work continues under candidate definitions. |
| `DPS-BLK-004` | Closed at definition-decision level by selecting ground-station UART model intent as bidirectional, either one bidirectional component exchange or paired UART exchanges. | Updates/dispositions affect `DPS-V10-A-001`, `DPS-V10-T-002`, and command/downlink path definitions; no new test ID is required solely for the decision. | DPS v1.0 PV2/source model, `DPS-V10-A-001`, `DPS-V10-T-002`, `DPS/MBSE/tests/README.md`. | Source-model/D2 update or approved waiver, plus evidence that telemetry bytes and command bytes both use the intended serial path. | D2/source-model follow-up remains; unconditional CE/command pass stays on hold until updated or waived. |
| `DPS-BLK-005` | Closed at definition-decision level with selected RF/range/PDR baseline: 500 m horizontal LOS, 915 MHz, matching 22 AWG 81.4 mm antennas, legal/EIRP/site approval, RSSI/SNR logging, and exact-binomial PDR acceptance. | `DPS-V10-C-001`, `SYS-RF-RANGE-PDR`; range aspects also inform `DPS-V10-T-001` setup. | `DPS/MBSE/tests/README.md`, future range/radio parameter references, `PM&SE/MBSE_Test_Plan_Assessment.md`. | Final radio configuration, antenna installation, range site or RF-equivalent validation, weather/interference record, `N=300` at 2 s cadence with `k>=279` for one-sided 95% lower bound `>=0.90`, and retained raw logs. | Detailed definition and execution remain; RF decision is no longer undefined. |
| `DPS-BLK-006` | Closed at definition-decision level with selected UI/browser/CSV/latency oracles: strict browser credit requires a named primary browser; non-browser/Tkinter implementation is limited/HOLD for browser requirement; CSV and latency criteria are fixed below. | `DPS-V10-T-005`, `DPS-V10-C-004`, `DPS-V10-C-005`, `DPS-V10-C-006`, `DPS-V10-C-008`; CSV aspects also inform `DPS-V10-T-001`. | `DPS/MBSE/tests/README.md`, `DPS-V10-T-001`, dashboard/CSV planning docs, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`. | Primary browser and UI automation/evidence method; canonical payload/schema; monotonic timestamp source; filesystem/session naming; invalid/stale-field behavior; scripts or checklists for screenshot/layout/CSV/latency checks. | Detailed UI/CSV/latency definitions remain; oracle decisions are selected. |
| `DPS-BLK-007` | Closed at definition-decision level with selected LoRa and concurrency baseline: LoRa airtime parameters are fixed sufficiently for frame-duration calculation, and mission/stress load profiles are selected. | `DPS-V10-C-003`; airtime/rate assumptions also inform `DPS-V10-C-001` and `DPS-V10-T-001`. | `DPS/MBSE/tests/README.md`, future RF/range/concurrency parameter references. | Airtime calculation for current `LORA_PAYLOAD_SIZE = 100 bytes` and the 34-byte OBCC variable-table basis before envelope/schema overhead; 10 min flight-cadence run at 2 s; optional 20 min 5 Hz synthetic/serial stress if over-air margin is inadequate; queue/memory/backlog/latency instrumentation. | Detailed concurrency definition remains; load-profile decision is selected. |
| `DPS-BLK-008` | Closed/dispositioned as conditional historical-closure work, not an active v1.0 definition blocker. v0.1/v0.2 rows become candidate promotions only if historical closure is required. | All v0.1 rows listed below; inferred v0.2 candidate groups listed below. | `DPS/MBSE/v0.1/tests/README.md`, `DPS/MBSE/v0.2/README.md`, `DPS/README.md`, `DPS/MBSE/tests/README.md`. | Project decision that historical v0.1/v0.2 closure is required, then creation of version-specific detailed definitions and reports. | Deferred/conditional; no historical candidate folders are created by this pass. |
| `DPS-BLK-009` | Dispositioned as not DPS-specific once system-level tests and traceability controls are introduced. DPS may retain provisional trace labels until source mission/capability/use-case/feared-event elements or a requirement-to-test matrix exist. | System-level candidates such as `SYS-FLIGHT-READINESS-CLOSURE`, `SYS-MISSION-REHEARSAL`, `SYS-RF-RANGE-PDR`, `SYS-END-TO-END-DATA`, and `SYS-WORKSHOP-READINESS`; no DPS-only test ID required. | `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, `DPS/MBSE/tests/README.md`. | Modeled system tests, source trace nodes or controlled provisional-label policy, and final requirement-to-test closure matrix. | System/PM&SE traceability follow-up remains; not an open DPS-only definition blocker. |

## 3. Selected definition baselines registered by this record

### 3.1 RF, range, PDR, and LoRa airtime ([parameter baseline](../DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md))

- Frequency: 915 MHz.
- LoRa settings for airtime calculations: SF7, BW 125 kHz, CR 4/5, explicit header, CRC on, preamble 8, low-data-rate optimization off for SF7/BW125.
- Payload-size basis: calculate at least for current `LORA_PAYLOAD_SIZE = 100 bytes`; note that `OBCC/LoRa_Frame.md` variable-table content totals 34 bytes before envelope/schema overhead.
- Range/PDR campaign baseline: 500 m horizontal line of sight, matching 22 AWG 81.4 mm antennas for 915 MHz, RSSI/SNR logs, legal/EIRP/site approval, and retained raw frame logs.
- PDR acceptance baseline: `N=300` frames at 2 s cadence; `k>=279` successful valid frames gives a one-sided 95% exact-binomial lower bound of at least 0.90.

### 3.2 Concurrency and load ([parameter baseline](../DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md))

- Primary mission run: 10 min at the v1.0 flight telemetry cadence of one frame every 2 s.
- Optional stress run: 20 min at 5 Hz synthetic or serial-injected input if over-air airtime/duty-cycle margin is inadequate for a radio stress campaign.
- Acceptance baseline: no crash/deadlock, queues bounded, memory bounded, backlog recovers to zero, p95 pipeline latency `<1 s`, and all data-loss/late-frame behavior logged or rejected according to the detailed definition.

### 3.3 UI, browser, CSV, latency, and layout ([oracle baseline](../DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md))

- Strict browser-access credit requires a declared primary browser and repeatable evidence that the dashboard opens and supports the required user functions without developer-console dependence.
- If the current implementation is Tkinter or otherwise non-browser, browser-access credit is HOLD/limited rather than weakening the browser requirement.
- CSV acceptance baseline: unique no-overwrite session names, monotonic row order, row count and checksum/content match to the accepted source payload log, restart/same-second collision cases covered, and malformed/invalid frames excluded.
- Latency-alert acceptance baseline: no alert for latency `<=1.0 s`; top alert for latency `>1.0 s`; invalid or non-monotonic timestamps rejected or flagged rather than silently accepted.
- Dashboard layout baseline: required plot matrix present; top-left cell renders CanSat attitude from pitch/roll/yaw; altitude remains a 2D telemetry plot/value; selected cells are mapped to controlled v1.0 telemetry fields.

## 4. Complete candidate backlog

### 4.1 Active v1.0 detailed-definition queue

| Candidate ID | Coverage / purpose | Definition work queued | Status after this record |
|---|---|---|---|
| `DPS-V10-T-004` | FC04 CanSat transmit path. | Define near-field/final receiver setup, sequence-number oracle, radio-busy/not-ready handling, and buffer-overrun hardening. | Candidate; detailed definition required before execution. |
| `DPS-V10-T-005` | FC05 dashboard visualization and related UI constraints. | Define payload-to-plot mapping, attitude-rendering oracle, selected telemetry cells, stale/invalid-field behavior, browser evidence, and latency alert evidence using the selected UI/CSV/latency oracle. | Candidate; selected UI/layout oracle exists; detailed definition and execution required. |
| `DPS-V10-T-006` | FC06 forwarder initialization. | Define restart campaign, SPI/radio/UART missing-fault injections, logging requirements, and false-ready prohibition. | Candidate; fault-injection detail required. |
| `DPS-V10-C-001` | C01 500 m separation/range. | Define horizontal LOS or RF-equivalent setup, radio settings, antenna details, PDR sample/statistics, RSSI/SNR logging, and legal/site prerequisites using the selected RF/range/PDR baseline. | Candidate; selected RF/range/PDR baseline exists; detailed definition and execution required. |
| `DPS-V10-C-003` | C03 concurrent Decoder/CSV/Dashboard execution. | Define 10 min flight-cadence run, optional 20 min 5 Hz stress, queue/memory/backlog instrumentation, and p95 latency criterion using the selected concurrency/load baseline. | Candidate; selected load profile exists; detailed definition and execution required. |
| `DPS-V10-C-004` | C04 browser-accessible dashboard. | Apply the selected primary Chrome/Chromium strict-credit browser policy, define refresh/reconnect and user-operation evidence, and record limited/HOLD handling for non-browser implementation. | Candidate; browser/evidence policy selected; detailed definition, implementation, and execution required. |
| `DPS-V10-C-005` | C05 unique CSV name and archive integrity. | Apply the selected session/restart/same-second cases, no-overwrite oracle, filename uniqueness, monotonic rows, row-count/checksum comparison to source log. | Candidate; selected CSV/session oracle exists; detailed definition and execution required. |
| `DPS-V10-C-006` | C06 top alert when latency is greater than 1 s. | Apply the selected monotonic timestamp source policy, threshold-boundary cases around `1.0 s`, alert placement, invalid timestamp handling, and evidence capture. | Candidate; selected latency threshold oracle exists; detailed definition and execution required. |
| `DPS-V10-C-008` | C08 4x4 plot matrix and top-left attitude model. | Apply the selected layout/mapping oracle, pitch/roll/yaw attitude rendering evidence, selected telemetry cells, missing-field behavior, and resize/display checks. | Candidate; selected UI layout oracle exists; detailed definition and execution required. |

### 4.2 Optional or retired v1.0 constraint signoffs

| Optional ID | Covered by | Disposition |
|---|---|---|
| `DPS-V10-C-002` | `DPS-V10-I-001` | Ground Station PCB reuse/no-backplane constraint is covered by physical inspection; keep a separate constraint signoff only if a review board requires it. |
| `DPS-V10-C-007` | `DPS-V10-T-002` | Five-second cooldown constraint is covered by the command/uplink and cooldown test; keep a separate constraint signoff only if a review board requires it. |

### 4.3 Conditional v0.1 historical backlog

These rows remain candidates only if historical v0.1 closure is required; otherwise they are deferred without creating folders.

| Candidate ID | Historical definition topic | Conditional action |
|---|---|---|
| `DPS-V01-I-001` | v0.1 physical component/link inspection. | Define checklist for datalogger and ground-station circuitboard PCs/PLs, wiring, polarity, shorts, antenna-before-TX, and USB power safety. |
| `DPS-V01-A-001` | v0.1 component-exchange analysis. | Define six-CE protocol/direction/data evidence template and stale/corrupt/lost-interface review. |
| `DPS-V01-A-002` | v0.1 logical allocation analysis. | Define allocation review after code baseline, including queues/ISR paths and no foreign/missing functions. |
| `DPS-V01-T-001` | v0.1 downlink decode/storage and CSV uniqueness. | Define detailed 5 Hz development run or selected cadence, PDR/statistics, latency, CSV integrity, and corrupt-frame rejection. |
| `DPS-V01-T-002` | v0.1 command/uplink and cooldown. | Define valid toggle screening, cooldown burst suppression, RF/serial evidence, and stale/duplicate command hardening. |
| `DPS-V01-T-003` | v0.1 datalogger receive path. | Define valid command receipt, spoof/no-frame/old-buffer rejection, and stale command prevention. |
| `DPS-V01-T-004` | v0.1 datalogger transmit path. | Define transmit sequence oracle, near-field receiver evidence, radio-busy/not-ready behavior, and buffer-overrun handling. |
| `DPS-V01-T-005` | v0.1 dashboard visualization. | Define payload-to-display oracle, browser evidence, attitude top-left rendering, alert behavior, and stale/invalid-field handling. |
| `DPS-V01-T-006` | v0.1 forwarder initialization. | Define restart/fault-injection campaign, missing SPI/radio/UART behavior, error logging, and false-ready prohibition. |
| `DPS-V01-C-001` | v0.1 500 m separation/range. | Define field or RF-equivalent campaign, legal radio settings, PDR threshold/sample count, RSSI/SNR, and antenna/interference controls. |
| `DPS-V01-C-002` | v0.1 concurrent process/store/display. | Define stress duration/rate, queue depth, memory growth, backlog recovery, deadlock/crash criteria, and p95 latency. |
| `DPS-V01-C-003` | v0.1 browser access. | Select browser set and define refresh/reconnect and no developer-console-dependence evidence. |
| `DPS-V01-C-004` | v0.1 unique CSV name. | Define restart/same-second collision cases, filename uniqueness, no overwrite, monotonic rows, and checksum/row-count comparison. |
| `DPS-V01-C-005` | v0.1 latency alert. | Define threshold-boundary samples, no alert at/below `1.0 s`, alert above `1.0 s`, and invalid timestamp rejection/flagging. |
| `DPS-V01-C-006` | v0.1 5 s cooldown. | Define rapid-toggle bursts, queue/RF suppression, UI disable/re-enable timing, and clock-jitter handling. |
| `DPS-V01-C-007` | v0.1 4x4 plots and attitude top-left. | Define layout/mapping inspection, pitch/roll/yaw attitude rendering, remaining cell mappings, missing fields, and resize behavior. |

### 4.4 Conditional v0.2 historical backlog

No detailed v0.2 test plan exists under `DPS/MBSE/v0.2/tests/`. If historical v0.2 closure is required, create detailed definitions for these inferred groups from the v0.2 views and README; otherwise defer them.

| Candidate group | Historical definition topic | Conditional action |
|---|---|---|
| Physical/link inspection | Circuitboard-based datalogger/ground-station hardware, IMU-only datalogger scope, no PCBs represented. | Define PC/PL presence, wiring, power, USB, antenna, and safe bring-up checklist. |
| Component-exchange analysis | SPI, UART/USB serial, payload, command, and IMU-related exchanges. | Define protocol/direction/data semantics and stale/corrupt/disconnect hardening analysis. |
| Allocation analysis | Dummy Datalogger, AMS Processing IMU Only, ground radio, forwarder, decoder, CSV writer, dashboard, and USB power allocations. | Define function-to-LC allocation checks and cross-boundary exchange consistency. |
| IMU downlink decode/storage | View 4 IMU downlink chain. | Define IMU payload source, decode/schema, timestamp, CSV row, PDR/latency, and corrupt-frame rejection oracle. |
| Command/uplink | View 5 dashboard command/uplink chain. | Define command sequence, cooldown behavior, serial/radio evidence, duplicate/stale command rejection, and bidirectional UART disposition. |
| Datalogger receive/transmit | Views 6 and 7 datalogger receive and transmit paths. | Define valid/invalid command receive, transmit sequence evidence, radio not-ready handling, and stale-buffer prevention. |
| Dashboard visualisation/no-jitter | View 8 dashboard visualization and no perceptible orientation jitter constraint. | Define pitch/roll/yaw mapping, orientation model update, jitter acceptance method, stale/invalid-field behavior, and evidence capture. |
| Forwarder initialization | View 9 forwarder initialization chain. | Define restart count, SPI/radio/UART initialization checks, error logging, and no false-ready behavior. |
| IMU-only processing | View 10 IMU-only processing chain. | Define IMU sample acquisition/processing, field units, validity/status, timing, and downlink handoff oracle. |
| Range | v0.2 datalogger-to-ground RF separation. | Define 500 m or RF-equivalent setup, antennas, legal settings, PDR sample/statistics, RSSI/SNR, and environmental/interference controls. |
| Concurrency | Decoder/CSV/Dashboard and forwarder concurrent behavior. | Define duration/rate, queue/memory/backlog/latency criteria, and crash/deadlock failure rules. |
| Browser | Browser-accessible dashboard constraint. | Select browser set and define access, refresh/reconnect, and user-operation evidence. |
| CSV | Unique storage and archive integrity. | Define no-overwrite naming, monotonic rows, checksum/row-count matching, and restart cases. |
| Latency | Top alert for latency greater than 1 s. | Define timestamp source, threshold cases, alert placement, and invalid timestamp handling. |
| Layout | Plot matrix and attitude-model placement. | Define 4x4 layout, top-left attitude model, selected cell mappings, missing fields, and resize/display behavior. |

## 5. Existing-test and document update list

| Artifact / activity | Required update or controlled status | Reason |
|---|---|---|
| `DPS/MBSE/tests/DPS-V10-A-001/README.md` | Update CE-03 analysis wording after source-model decision so the UART path is explicitly bidirectional or split into paired telemetry/command UART CEs; until then, record limitation/waiver for unconditional pass. | Align CE analysis with command/uplink behavior and selected model intent. |
| `DPS/MBSE/tests/DPS-V10-T-002/README.md` | Preserve existing valid-command/cooldown definition, but bind the model discrepancy watch to the selected bidirectional-or-paired UART follow-up; report must include command bytes from Decoder to Forwarder and RF command capture. | Avoid overclaiming command/uplink pass while the source PV2 arrow is unresolved. |
| `DPS/MBSE/tests/DPS-V10-T-001/README.md` | Align range/radio/PDR setup with selected 915 MHz, LoRa airtime assumptions, 500 m horizontal LOS or RF-equivalent controls, `N=300`, `k>=279`, CSV uniqueness, p95 `<1 s`, and corrupt-frame rejection. | Keep downlink decode/storage consistent with selected RF, CSV, and latency oracles. |
| `DPS/MBSE/tests/DPS-V10-I-001/README.md` | Preserve coverage of the ground-station PCB reuse/no-backplane constraint and keep `DPS-V10-C-002` retired unless separate signoff is requested. | Prevent duplicate candidate work for the physical reuse constraint. |
| `DPS/MBSE/tests/README.md` | Replace open-ended candidate notes with the backlog and selected baselines in this record; retain no-execution-credit wording; mark historical v0.1/v0.2 work conditional. | Make the central DPS v1.0 test plan consistent with the closure decisions. |
| `DPS/MBSE/v0.1/tests/README.md` | If historical closure is required, update the v0.1 rows using the selected RF, concurrency, UI, CSV, latency, cooldown, and layout baselines; otherwise leave as deferred candidates. | Keep historical v0.1 scope explicit without creating unneeded definitions. |
| `DPS/MBSE/v0.2/README.md` | If historical closure is required, create a version-local tests plan for the inferred groups; otherwise keep v0.2 as view-only historical scope. | No detailed v0.2 test plan exists today. |
| `DPS/README.md` | Preserve v1.0 flight cadence as 2 s, optional 5 Hz lab stress as non-flight stress, top-left attitude rendering from pitch/roll/yaw, and local storage requirement. | Keep subsystem requirements aligned with test baselines. |
| `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` | Replace the DPS open-blocker wording with definition-closed dispositions, candidate backlog, D2/source-model follow-up, and execution prerequisites from this record. | Integrate the closure into the project candidate/blocker register. |
| `PM&SE/MBSE_Test_Plan_Assessment.md` | Update DPS assessment lines to state that definition decisions are selected, while detailed modeling, D2/source updates, execution, system traceability, and historical closure remain pending. | Prevent finished-CanSat or DPS pass claims from this definition-only closure. |

## 6. Follow-on D2 and source-model work

1. Update DPS v1.0 PV2/source model so CE-03 is either a bidirectional UART component exchange labeled `LoRa Forwarder ↔ PC Decoder` or two explicit paired UART exchanges, one for forwarder-to-decoder telemetry bytes and one for decoder-to-forwarder command bytes.
2. Regenerate corresponding PNGs only after the D2/source-model update is reviewed; no diagram regeneration occurs in this pass.
3. Update `DPS-V10-A-001` verification-specific diagrams/checklists to match the final UART modeling choice.
4. Update `DPS-V10-T-002` verification-specific diagrams/checklists so command bytes from Decoder to Forwarder are represented without relying on a one-way source-model arrow.
5. Create detailed modeled definitions for active v1.0 candidates `DPS-V10-T-004`, `DPS-V10-T-005`, `DPS-V10-T-006`, `DPS-V10-C-001`, `DPS-V10-C-003`, `DPS-V10-C-004`, `DPS-V10-C-005`, `DPS-V10-C-006`, and `DPS-V10-C-008`.
6. Add RF/range/PDR, LoRa airtime, and concurrency assumptions to the relevant detailed views and source-model constraints where appropriate.
7. Add UI/browser/CSV/latency/layout oracles to the relevant detailed views and source-model constraints where appropriate.
8. Create v0.1/v0.2 detailed modeled definitions only if the project requires historical closure.
9. Model system-level trace elements, requirement-to-test matrix entries, and final system-level tests so DPS provisional trace labels are replaced or explicitly controlled.

## 7. Residual uncertainties before execution

- Final as-tested hardware revisions, UUT serial numbers, radio modules, antenna build/installation details, firmware commits, PC software revisions, parser versions, and tool/script versions.
- Final payload schema/version, field units, timestamp source, monotonic clock behavior, clock synchronization if needed, and OBCC-to-DPS field mapping.
- Legal/EIRP approval, range site geometry, RF-equivalent validation if used, weather/interference conditions, antenna orientation, and independence rationale for packet trials.
- Actual `LORA_PAYLOAD_SIZE`, envelope/schema overhead beyond the 34-byte OBCC variable-table basis, and final airtime/duty-cycle margin.
- Primary browser choice, whether the current UI is truly browser-accessible or non-browser/HOLD, UI automation method, screenshot/video evidence method, and dashboard field/layout oracle scripts.
- CSV output location, session-naming implementation, restart/same-second collision handling, checksum method, and raw source-payload log retention.
- Queue-depth, memory, backlog, p95 latency, and crash/deadlock instrumentation for concurrency and stress tests.
- CE-03 source-model update or accepted waiver before unconditional component-exchange and command/uplink pass credit.
- Equipment asset IDs, calibration certificates/function checks, RF monitor configuration, timebase accuracy, environmental limits, and lab configuration.
- Decision on whether v0.1/v0.2 historical closure is required.
- System-level mission/capability/use-case/feared-event trace nodes or controlled provisional-label policy, plus the final requirement-to-test matrix.
