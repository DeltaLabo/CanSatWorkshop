# PDS & ESS Blocker Closure Record — 2026-07-02

Status: definition-planning closure record only. This document records selected dispositions, candidate/update backlog, source-model follow-ons, and execution-only prerequisites for PDS & ESS verification planning.

## 1. Scope and controls

- Scope is limited to definition decisions and planning records for PDS & ESS verification closure.
- No verification activity is executed by this record, and no pass/fail execution credit is claimed.
- No `.d2` or `.png` diagram/source files are edited by this issue.
- No candidate test folders, baseline copies, result folders, reports, binaries, or hardware-test artifacts are created by this issue.
- Later D2/source-model, Markdown integration, and execution evidence remain separate controlled follow-on work.
- Earlier PDS & ESS development-version gates remain useful incremental evidence definitions, but they do not substitute for v1.0 final flight-acceptance evidence.

## 2. Decision table

| Blocker ID | Selected disposition | Affected candidate/new tests | Affected existing tests/docs | Source-model or execution prerequisites | Follow-up status |
|---|---|---|---|---|---|
| `PDS-BLK-002` | Source-model quick fix selected: add an explicit INA219 `[CE] I2C` exchange between ESS Processing/XIAO and Battery monitoring/INA219. This pass documents the D2/source-model follow-on only. | No new candidate; existing CE completeness path remains. | `PDS-VV-FC-002`, `PDS-VV-CE-003`, `PDS-VV-CON-007`, `PDS&ESS/MBSE/tests/README.md`. | Edit `PDS&ESS/MBSE/v1.0/PDS_v1.0_view2_logical.d2`, regenerate the PNG, and refresh affected baseline copies if project policy requires. Later execution still records bus topology, address, pullups, voltage levels, transaction direction, timeout policy, and fault evidence. | Source-model edit pending; execution pending; no waiver selected here. |
| `PDS-BLK-003` | Regulator-efficiency validation candidate queued as `PDS-VV-CON-010`; no conflicting established PDS test ID was found in the reviewed PDS test index. The candidate targets the PDS README 3.3 V and 5 V at 1 A / 95% efficiency requirements. | New candidate `PDS-VV-CON-010`, detailed definition pending, not executed. | `PDS&ESS/README.md`, `PDS&ESS/MBSE/tests/README.md`, `PDS-VV-CON-004`, PM&SE assessment/register artifacts. | Later definition must select efficiency measurement topology, input/output voltage/current/power instrumentation, load cases, uncertainty/guard-band treatment, thermal limits, and result/evidence paths. | Candidate added at planning level; modeled definition and execution pending. |
| `PDS-BLK-004` | On-mode load/current budget and 6 h endurance profile remain campaign-defined; no separate modeled load-profile estimation test is selected. | No new candidate. | `PDS-VV-CON-002`, system power/endurance planning such as `SYS-POWER-ENDURANCE-TRANSIENT`. | Before execution, freeze representative On-mode load profile, current budget, battery preconditioning, logging/sample cadence, ambient/thermal envelope, anomaly handling, and end-of-run criteria. | Reclassified as campaign/execution prerequisite; existing test definition remains usable. |
| `PDS-BLK-005` | Master-switch/accessibility hardware detail requires a source/interface fix; document as pending source-model/interface edit rather than execution evidence. | No new candidate. | `PDS-VV-ALLOC-001`, `PDS-VV-ALLOC-003`, related power/protection and charge-interface definitions, PDS physical/source model. | Add or clarify master switch/accessibility hardware/interface in the relevant PDS physical/source model and regenerate the PNG; later execution records actor-interface evidence, safe access, de-energized state, and any waiver/deviation. | Source-model/interface edit pending; allocation closure remains blocked until updated or formally waived. |
| `PDS-BLK-006` | Li-ion safety documents, charger model/certification, and cell safety evidence are literal execution prerequisites, not unresolved definition blockers. | No new candidate. | `PDS-VV-CON-001`, `PDS-VV-SAFE-001`, `PDS-VV-PC-001`, `PDS-VV-FC-001`. | Execution package must identify cell/pack, datasheet/SDS or equivalent safety documents, UN 38.3 / IEC 62133 or equivalent evidence when available, charge/discharge/storage limits, certified charger model/settings, fire-safe containment, and safety observer controls. | Execution prerequisite retained; no definition blocker remains from this item. |
| `PDS-BLK-007` | DFM rule set is documented in `S&A/PCB_General_Rules.md`; PDS DFM verification should reference it and keep deviation records as execution evidence. | No new candidate. | `PDS-VV-CON-009`, `PDS&ESS/MBSE/tests/README.md`, `S&A/PCB_General_Rules.md`. | Execution must map applicable Carvera Air/PCB rules to board/coupon IDs and record disposition for trace/space, via, pad, drill, WCS origin, operation selection, tool-size, keepout, continuity/isolation, and workmanship evidence. | Documentation update pending; deviation/waiver records remain execution evidence. |
| `PDS-BLK-008` | Quantitative protection-probability criteria are selected using the conservative missed-demand interpretation, exact-binomial statistics, predeclared setpoints, safe-outcome rules, and independence rules recorded in this closure. | No new candidate; update existing `PDS-VV-CON-003` criteria and related `PDS-VV-FC-001` references. | `PDS-VV-CON-003`, `PDS-V03-GATE-001`, `PDS&ESS/MBSE/tests/README.md`, PM&SE assessment/register artifacts. | Execution must predeclare article/configuration IDs, safe rail/cell/PCB/temperature limits, overcurrent and overvoltage thresholds, fixture current limits, trial sequence, reset/cooldown, independent instrumentation, exact-binomial analysis, and deviation handling. | Definition criteria selected; Markdown/model update and execution pending. |
| `PDS-BLK-009` | Rail nominal-load, thermal, and settling parameters are literal campaign/execution confirmations, not a test-definition flaw. | No new candidate. | `PDS-VV-CON-004`, `PDS-VV-CON-002`, system power/endurance planning. | Execution must freeze no-load, nominal-load, and 1 A cases; thermal limits; thermal-soak method; startup/load-step settling windows; ripple treatment; sample count; load-bank settings; and equipment calibration/status. | Reclassified as campaign/execution prerequisite; existing rail test definition remains usable. |

## 3. Selected quantitative protection-probability criteria

These criteria are selected for the existing demanded-protection probability verification path and do not constitute execution evidence.

- Formal claim: source `[C] Probability < 1%` means missed demanded unsafe protection-action probability `<1%` per demanded mode: overcurrent/output-short-equivalent and overvoltage.
- Statistics: strict verification requires 299 valid independent demanded trials with zero missed unsafe actions per mode, supporting a one-sided 95% exact-binomial upper bound below 1%. Fewer trials are screening/characterization with the exact upper bound reported.
- Overcurrent/output-short-equivalent demand: use a current-limited source/load or short-equivalent fixture; predeclare the nominal trip/current-limit threshold from the protection design or test article datasheet; valid trials demand at least 110% of the declared trip threshold, or the minimum current that reliably enters the protection region while staying inside the testbench safe-energy envelope. Direct uncontrolled battery shorts are out of scope.
- Overvoltage demand: use a current-limited injection source; predeclare the nominal overvoltage threshold from the protection design or datasheet; valid trials exceed that threshold by at least 5%, or by the smallest campaign-approved margin that reliably demands protection without exceeding absolute maximum ratings.
- Per-trial safe outcome: protection detects/acts, removes or limits unsafe output before declared rail/cell/PCB/temperature limits are violated, inhibits restore until the fault is cleared, and controlled restore returns to nominal without uncontrolled restart/reset.
- Independence: trials require cooldown/reset or randomized/procedure-separated demand order, recorded source/load settings, independent instrumentation triggers, stable ambient/thermal preconditions, and anomaly/deviation disposition. If independence is not defensible, classify the evidence as screening.

## 4. Candidate and definition backlog

### 4.1 Existing modeled PDS v1.0 definitions

These definitions remain part of the PDS & ESS v1.0 final flight-acceptance backlog. Their existence does not imply execution completion.

| Category | Activity IDs | Planning status |
|---|---|---|
| Physical/component and safety inspections | `PDS-VV-PC-001`, `PDS-VV-PL-001`, `PDS-VV-SAFE-001` | Modeled definitions exist; execution evidence and exact as-tested configuration records remain pending. |
| Component exchanges | `PDS-VV-CE-001`, `PDS-VV-CE-002`, `PDS-VV-CE-003` | Modeled/supporting definitions exist; INA219 I2C source CE follow-on remains pending for final CE completeness. |
| Allocation analyses | `PDS-VV-ALLOC-001`, `PDS-VV-ALLOC-002`, `PDS-VV-ALLOC-003` | Modeled/supporting definitions exist; master switch/accessibility source/interface detail remains pending. |
| Functional chains | `PDS-VV-FC-001`, `PDS-VV-FC-002` | Modeled definitions exist; execution pending and source-model caveats remain where listed in this record. |
| Constraints | `PDS-VV-CON-001`, `PDS-VV-CON-002`, `PDS-VV-CON-003`, `PDS-VV-CON-004`, `PDS-VV-CON-005`, `PDS-VV-CON-006`, `PDS-VV-CON-007`, `PDS-VV-CON-008`, `PDS-VV-CON-009` | Modeled definitions exist directly or through linked FC definitions; execution and campaign confirmations remain pending. |

### 4.2 New candidate

| Candidate ID | Purpose | Status |
|---|---|---|
| `PDS-VV-CON-010` | Regulator efficiency validation for the PDS README requirements that the 3.3 V and 5 V rails supply 1 A with 95% efficiency. | Candidate/detailed definition pending; not modeled here; not executed. |

### 4.3 Incremental gates already modeled

| Gate ID | Development baseline | Closure interpretation |
|---|---|---|
| `PDS-V01-GATE-001` | v0.1 power-path advancement gate toward v0.2 | Incremental/development gate only; not a substitute for v1.0 final acceptance. |
| `PDS-VV-V02-FC-001` | v0.2 INA219 measurement/reporting advancement gate toward v0.3 | Incremental/development gate only; not a substitute for v1.0 final acceptance. |
| `PDS-V03-GATE-001` | v0.3 protection/endurance advancement gate toward v1.0 | Incremental/development gate only; not a substitute for v1.0 final acceptance. |

## 5. Existing-test and documentation update register

No files in this list are edited by this issue. The entries define what should be updated in later Markdown/model integration passes.

| Artifact or activity | Update now in this closure record | Later artifact update |
|---|---|---|
| `PDS&ESS/MBSE/tests/README.md` | Record the selected dispositions, new efficiency candidate, incremental-gate caveat, and reclassification of campaign/execution prerequisites. | Add the candidate/update register entries and status wording without claiming execution credit. |
| `PDS-VV-FC-002` / `PDS-VV-CE-003` | Record that the selected closure path is an explicit INA219 I2C CE source edit, not a waiver. | After the source model is changed, align the README, diagrams/baselines if required, and CE completeness wording. |
| `PDS-VV-CON-002` | Retain the 6 h On-mode endurance definition; keep load profile/current budget campaign-defined. | Add explicit wording that representative load profile, current budget, logging cadence, and thermal envelope are execution campaign inputs rather than a new modeled estimation test. |
| `PDS-VV-CON-003` | Record the selected quantitative missed-demand criteria, sample plan, setpoints, safe-outcome, and independence rules from this closure. | Update README/D2 definition text as needed; execution still supplies actual trials and exact-binomial evidence. |
| `PDS-VV-CON-004` | Record that nominal-load, thermal, and settling values are execution confirmations. | Update wording to require campaign-declared no-load/nominal/1 A settings, thermal limit, settling windows, ripple treatment, and calibrated evidence. |
| `PDS-VV-CON-009` | Record that PDS DFM checks reference `S&A/PCB_General_Rules.md`. | Add explicit rule-file reference and require deviation/waiver records as execution evidence. |
| `PDS-VV-ALLOC-001` / `PDS-VV-ALLOC-003` | Record that master switch/accessibility needs a source/interface edit before unqualified allocation closure. | Update source-model caveat wording after the physical/interface model is clarified or a controlled waiver is approved. |
| `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` and `PM&SE/MBSE_Test_Plan_Assessment.md` | Use this closure as the integration source. | Later PM&SE integration should add the efficiency candidate, disposition the source-model follow-ons and execution prerequisites, and avoid execution pass/fail claims. |

## 6. Follow-on D2/source-model list

1. Add explicit INA219 `[CE] I2C` exchange between ESS Processing/XIAO and Battery monitoring/INA219 to `PDS&ESS/MBSE/v1.0/PDS_v1.0_view2_logical.d2`, then regenerate the corresponding PNG.
2. Refresh baseline copies in affected test folders after the source-model update if project policy requires baseline recopy for report-by-reference consistency.
3. Add or clarify master switch/accessibility hardware/interface in the relevant PDS physical/source model and regenerate the corresponding PNG.
4. Later create/model `PDS-VV-CON-010` if and when the efficiency candidate is promoted to a detailed verification definition.

## 7. Residual execution-only prerequisites

These items remain execution/report prerequisites and do not block the definition decisions recorded here.

| Area | Required execution record |
|---|---|
| As-tested configuration | Exact PDS & ESS article IDs, PCB assembly IDs, hardware revisions, regulator/protection/INA219 part identities, harness/backplane configuration, firmware/software commits, source/build maps, and any configuration deviations. |
| Charger and cell safety | Certified charger model/settings, cell/pack identity, datasheet/SDS or equivalent safety documents, UN 38.3 / IEC 62133 or equivalent evidence when available, charge/discharge/storage limits, fire-safe containment, safety observer approval, and E-stop/abort controls. |
| Equipment and calibration | Asset IDs and calibration/status for bench supplies, battery emulator, electronic loads, power analyzer, DMM/DAQ, oscilloscope/logger, logic analyzer, thermal camera/thermocouples, ambient meter, timing source, analysis scripts, and evidence workstation. |
| Thermal and safety limits | Predeclared rail, cell, PCB, connector, regulator, and ambient temperature limits; safe-energy/current-limit envelope; protection cutoff/restore limits; unsafe-current, smoke, swelling, latch-up, reset, and anomaly stop conditions. |
| 6 h campaign settings | Representative On-mode load profile, current budget, load-emulator settings, battery preconditioning, logging/sample cadence, rail/freshness monitoring, ambient/thermal envelope, anomaly ledger, and end-of-run safe-state criteria. |
| Rail campaign settings | No-load, nominal-load, and 1 A load cases for both rails; actual nominal-load values; thermal-soak method; startup and load-step settling windows; ripple treatment; measurement uncertainty; and sample-count basis. |
| Protection trial settings | Overcurrent/output-short-equivalent and overvoltage thresholds, demanded setpoints, fixture current limits, fault energy limits, sequence/randomization or procedure order, cooldown/reset criteria, independent instrumentation triggers, trial classification sheet, exact-binomial calculation, and independence rationale. |
| DFM/manufacturing evidence | Board/coupon IDs, mapping to `S&A/PCB_General_Rules.md`, Carvera Air/toolpath rule checks, visual/dimensional/fit/continuity/isolation/workmanship evidence, high-current trace review, and deviation/waiver/disposition records. |
| Deviation and waiver control | Owner, rationale, affected requirement/test, risk disposition, retest need, and approval record for every anomaly, deviation, waiver, unavailable document, or campaign assumption. |
| Report/evidence archive | Raw logs, photos, waveforms, scripts, ambient records, calibration/status records, baseline/model references, final reports, and explicit statement that any unexecuted or limited evidence is not final pass/fail credit. |
