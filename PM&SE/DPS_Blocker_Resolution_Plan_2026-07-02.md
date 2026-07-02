# DPS Blocker Resolution Plan — CON-003 §2.4

Date: 2026-07-02

## End goal

Resolve the DPS definition blockers in `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.4 at definition-decision level. The required outputs are:

1. a complete DPS candidate/detailed-definition backlog,
2. a controlled list of updates to existing DPS tests,
3. selected RF/range/PDR, LoRa/concurrency, UI/browser/CSV/latency parameters, and
4. PM&SE/DPS Markdown updates showing these are no longer open DPS definition blockers.

This pass does **not** execute tests, does **not** claim pass/fail credit, and does **not** edit D2/PNG diagrams. D2/source-model updates are recorded as follow-on. Markdown documentation may be updated.

## User decisions to apply

- `DPS-BLK-001`: redundant once a complete candidate list exists and all candidates are queued for detailed test definitions.
- `DPS-BLK-004`: update model intent to bidirectional CE for ground-station UART. In this pass, document the decision and list D2/source-model edits as follow-on.
- `DPS-BLK-005`: use horizontal line of sight; use 22-gauge wire 81.4 mm antenna for 915 MHz; define remaining RF/PDR parameters.
- `DPS-BLK-006`: define UI/browser/CSV/latency oracle parameters.
- `DPS-BLK-007`: define LoRa parameters sufficient to calculate frame duration, then define concurrency/load profile.
- `DPS-BLK-008`: historical v0.1/v0.2 issue is candidate promotion to detailed definitions if historical closure is required.
- `DPS-BLK-009`: not a DPS-specific blocker once system-level tests are introduced; disposition as system-level traceability follow-up.

## Selected defaults for subagents to verify/use

- RF: 915 MHz; SF7; BW 125 kHz; CR 4/5; explicit header; CRC on; preamble 8; low-data-rate optimization off for SF7/BW125.
- Airtime basis: calculate at least for current `LORA_PAYLOAD_SIZE = 100 bytes`; note `OBCC/LoRa_Frame.md` variable table totals 34 bytes before envelope/schema overhead.
- Range/PDR: 500 m horizontal LOS, matching 22 AWG 81.4 mm antennas, RSSI/SNR logs, legal/EIRP/site approval, `N=300` at 2 s cadence and `k>=279` for one-sided 95% exact-binomial lower bound >=0.90.
- Concurrency: 10 min flight-cadence run at 2 s; optional 20 min 5 Hz synthetic/serial-injected stress if over-air airtime/duty-cycle margin is inadequate; p95 pipeline latency `<1 s`, bounded queues/memory, backlog recovers to zero.
- UI/browser: select a primary browser for strict credit; if current implementation is Tkinter/non-browser, document HOLD/limited status rather than weakening the requirement.
- CSV/latency: no-overwrite unique session names, monotonic rows, row-count/checksum match to source payload log; no alert for `<=1.0 s`, top alert for `>1.0 s`, invalid timestamps rejected/flagged.

## Issues

| Issue | Work | Main outputs |
|---|---|---|
| `ISSUE-DPS-001_candidate_and_update_register.md` | Create central closure record and complete candidate/update backlog. | `PM&SE/DPS_Blocker_Closure_Record_2026-07-02.md` |
| `ISSUE-DPS-002_rf_range_lora_parameters.md` | Create RF/range/PDR, LoRa airtime, and concurrency parameter doc. | `DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md` |
| `ISSUE-DPS-003_ui_csv_latency_oracles.md` | Create UI/browser/CSV/latency oracle doc. | `DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md` |
| `ISSUE-DPS-004_pmse_integration_cleanup.md` | Integrate outputs into DPS/PM&SE Markdown and remove temporary issue files. | Updated PM&SE/DPS docs; issue directory removed |

## Coordination rules

- Work from `/Users/antho/CanSatWorkshop`.
- Do not push. Do not commit; the orchestrator will commit reviewed path-specific changes.
- Do not edit `.d2` or `.png` files.
- Do not execute tests or claim pass/fail execution credit.
- Do not modify unrelated subsystem files.
- Keep definition decisions separate from D2/model/execution follow-up.

## Acceptance criteria

- Closure record lists every `DPS-BLK-001` through `DPS-BLK-009` with selected disposition, affected candidates/tests, execution prerequisites, and follow-on status.
- RF/LoRa/concurrency and UI/CSV/latency parameter docs exist and are linked from DPS test planning.
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.4 and `PM&SE/MBSE_Test_Plan_Assessment.md` are consistent with the selected decisions without overclaiming execution.
- `DPS-BLK-001`, `004`, `005`, `006`, `007`, `008`, and `009` are no longer described as open undefined DPS blockers; remaining work is detailed-definition/D2/execution/system follow-up.
- Temporary issue files under `PM&SE/dps_blocker_resolution_issues/` are removed at the end. This plan remains.

## Execution status

DPS blocker resolution completed at definition-decision level for this pass. Integrated outputs are:

- `PM&SE/DPS_Blocker_Closure_Record_2026-07-02.md` records `DPS-BLK-001` through `DPS-BLK-009` as definition-level closed/dispositioned with D2/source-model, detailed-definition, execution, historical, and system traceability follow-up kept separate.
- `DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md` and `DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md` are linked from DPS test planning.
- DPS test index and existing `DPS-V10-A-001`, `DPS-V10-T-001`, and `DPS-V10-T-002` READMEs are aligned to the selected RF/UI/load baselines and bidirectional ground-station UART model intent.
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.4 and `PM&SE/MBSE_Test_Plan_Assessment.md` no longer describe `DPS-BLK-001`, `004`, `005`, `006`, `007`, `008`, or `009` as open undefined DPS blockers.
- Temporary DPS issue files under `PM&SE/dps_blocker_resolution_issues/` are removed by the final integration cleanup.

No tests were executed, no pass/fail credit is claimed, and no D2, PNG, source-code, or implementation updates are claimed by this pass.
