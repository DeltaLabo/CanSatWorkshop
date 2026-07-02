# ISSUE-PDS-002 — PDS Markdown-only test planning updates

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/PDS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md` (created by issue 001)
- `PM&SE/IVV.md`
- `PDS&ESS/README.md`
- `PDS&ESS/MBSE/tests/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-FC-002/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-002/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-003/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-004/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-009/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-ALLOC-001/README.md`
- `S&A/PCB_General_Rules.md`

## Scope

Apply Markdown-only planning/definition updates. Do **not** edit `.d2`, `.png`, binary, or unrelated subsystem files. Do **not** execute tests. Do **not** commit or push.

## Required edits

Update PDS Markdown files so they align with the closure record while preserving “execution pending” wording.

### 1. `PDS&ESS/MBSE/tests/README.md`

Add/update content to show:

- `PDS-VV-CON-010` is a new candidate for regulator efficiency validation of the PDS README 3.3 V and 5 V at 1 A / 95% efficiency requirements.
- Suggested candidate purpose: measure input power and output power at the 3.3 V and 5 V rails under the declared 1 A and nominal load cases; strict pass requires efficiency `>=95%` with expanded uncertainty/guard band, no unsafe thermal behavior, and retained power-analyzer/raw logs. Detailed modeled definition and execution remain pending.
- `PDS-VV-CE-003` / INA219 I2C CE source-model update is selected as a pending quick D2/source edit, not an unresolved definition decision.
- `PDS-VV-CON-002` load profile may remain campaign-defined; do not add a separate load-profile estimation candidate.
- `PDS-VV-CON-003` has quantitative missed-demand/setpoint/trial-validity criteria selected.
- `PDS-VV-CON-004` nominal-load/thermal/settling values are campaign execution parameters.
- `PDS-VV-CON-009` should reference `S&A/PCB_General_Rules.md` for baseline Carvera/PCB rules.
- Master switch/accessibility remains a pending source-model/interface edit, not a new test candidate.
- Keep incremental gates caveat: v0.1/v0.2/v0.3 gates do not substitute for v1.0 final acceptance.

### 2. `PDS&ESS/MBSE/tests/PDS-VV-FC-002/README.md`

Update assumptions/caveats or scope to say the INA219 I2C CE source edit has been selected as a follow-on: add explicit `[CE] I2C` between ESS Processing/XIAO and Battery monitoring/INA219 in the v1.0 logical/source model. Until the D2/source update and any baseline refresh are done, final CE completeness credit remains pending. Do not claim the D2 has been changed.

### 3. `PDS&ESS/MBSE/tests/PDS-VV-CON-003/README.md`

Add concise quantitative criteria from the plan/closure record:

- Conservative missed-demand interpretation per mode.
- 299 zero-miss independent trials per mode for strict `<1%` claim; fewer trials are screening with exact upper bound.
- Overcurrent/output-short-equivalent demand validity: current-limited, predeclared threshold, at least 110% of trip threshold or campaign-approved minimum to demand protection while inside safe-energy envelope.
- Overvoltage demand validity: current-limited, predeclared threshold, at least 5% over threshold or campaign-approved minimum margin without exceeding absolute maximum ratings.
- Per-trial safe outcome and independence/cooldown/randomization/instrumentation criteria.

Avoid duplicating too much existing text; integrate with existing pass/fail and assumptions.

### 4. `PDS&ESS/MBSE/tests/PDS-VV-CON-009/README.md`

Reference `S&A/PCB_General_Rules.md` as the controlled baseline for current Carvera/PCB general rules. Include the numeric rules from that file or a direct relative link plus enough visible content for reviewers:

- minimum track width 0.8 mm,
- minimum via diameter 1.2 mm,
- minimum via drill 0.8 mm,
- minimum pad diameter 75 mil,
- minimum pad drill 45 mil,
- wire-to-wire spacing 0.8 mm,
- plus Carvera operation notes as applicable.

State that board-specific deviations/DFM pre-check records remain execution evidence.

### 5. `PDS&ESS/MBSE/tests/PDS-VV-ALLOC-001/README.md`

Clarify that master-switch/accessibility closure requires a source-model/interface edit or controlled waiver. It is selected as a pending edit, not a reason to create another test candidate.

### 6. Optional small consistency edits

If needed, make small wording updates in `PDS-VV-CON-002` and `PDS-VV-CON-004` README caveats to classify load profile / nominal load / thermal / settling values as campaign execution parameters rather than open definition blockers. Keep this concise.

## Done

- Markdown updates are focused and consistent with the closure record.
- No `.d2`/`.png` files are modified.
- No execution pass/fail credit is claimed.
- Run `git diff --stat` and summarize changed files in your final response.
