# ISSUE-SAA-003 — PM&SE integration for S&A blocker closure

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/SAA_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `S&A/README.md`
- `S&A/MBSE/tests/README.md`
- Any S&A README changed by `ISSUE-SAA-002`

## Output

Update only these PM&SE Markdown files if needed:

- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`

Do not edit S&A files in this issue. Do not edit `.d2`, `.png`, binary files, source code, or unrelated subsystem files. Do not execute tests. Do not commit or push.

## Required integration

### 1. Update CON-003 §2.8 S&A blocker rows

Revise the S&A blocker table so it no longer presents the resolved decisions as open undefined blockers. Each row should distinguish definition-decision closure from execution/model follow-up:

- `SAA-BLK-001`: Closed/dispositioned non-issue at definition-decision level. Baseline S&A is intentionally physical-only; no forced S&A source CE modeling is required. `SAA-VV-CE-001` remains execution-time ownership/cross-reference analysis for implied backplane/interface CEs. Execution evidence remains pending.
- `SAA-BLK-002`: Closed/dispositioned non-issue at definition-decision level. Baseline S&A is intentionally physical-only; no forced S&A LC/F/allocation source modeling is required. `SAA-VV-ALLOC-001` remains execution-time ownership/disposition analysis. Execution evidence remains pending.
- `SAA-BLK-003`: Approved at definition-decision level. Record that tailored drop/vibration/landing environmental screen levels, surfaces, orientations, durations, and success criteria are approved for later test-definition update. Do not imply that S&A test definitions were edited in this pass; use “pending edit” language. Execution evidence remains pending.
- `SAA-BLK-004`: Closed/confirmed at definition-decision level. Use `122 mm` height and conservative mass guard band (`measured mass + U_M < 350.0 g`) unless a later authority selects stricter criteria. Execution measurement remains pending.
- `SAA-BLK-005`: Closed at definition-decision level. Pinout frozen by Fusion 360 design; selected quantitative criteria for rail load, I2C Standard-mode/rise-time/capacitance, SPI/UART endpoint/loading review, and DFM/IPC disposition are controlled by `PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md` and S&A Markdown updates. Execution evidence remains pending.
- `SAA-BLK-006`: Closed at definition-decision level. PLA selected; layer/infill policy and screw/proof criteria selected. Execution build/profile/screw/fixture evidence remains pending.
- `SAA-BLK-007`: Closed at definition-decision level. Movement/witness-mark thresholds released. Execution retention-screen evidence remains pending.

Add a folded subsection after the S&A table, similar to existing ADS/AMS/DPS folded closure sections but shorter, summarizing:

- scope: definition decisions only, no execution credit, no D2/PNG edits;
- active/model-defined S&A verification activity list;
- selected quantitative criteria summary for backplane, print/material/screw/proof, and movement thresholds;
- pending edit list, explicitly including `SAA-BLK-003` environmental-screen definition edits not applied in this pass;
- residual execution-only prerequisites.

### 2. Update candidate backlog §1.2 if needed

Ensure the S&A row still states that all listed S&A activities are model-defined and there is no S&A planning-candidate backlog. Update wording to say remaining work is execution/reporting plus selected Markdown/D2/source-model follow-up, not unresolved candidate creation.

### 3. Update MBSE test plan assessment S&A findings

Update `PM&SE/MBSE_Test_Plan_Assessment.md` only where it currently says S&A blockers are unresolved:

- Keep `SUB-SAA-001` as execution-on-final-article pending.
- Update `SUB-SAA-002` to reflect that the physical-only S&A model disposition is accepted/non-issue at definition-decision level; CE/allocation ownership analyses remain execution-time closure, and no forced baseline logical/CE source modeling is required unless later desired.
- Update `SUB-SAA-003` to say environmental screen decisions are approved at definition-decision level, with detailed test-definition edit and execution still pending.
- Update `SUB-SAA-004` to say height/mass interpretation is confirmed at definition-decision level: `122 mm` height and conservative `<350 g` guard-band policy; execution measurement remains pending.
- If there is a cross-cutting mechanical environment gap, change wording from “not controlled/unapproved” to “approved/pending S&A test-definition edit and execution” without overclaiming.

## Style and safeguards

- Do not claim any S&A test has passed or been executed.
- Do not say D2/model diagrams were updated.
- Link or mention `PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md` as the controlled S&A definition-decision record.
- Keep wording concise; avoid duplicating the full closure record in multiple places except for a compact folded summary in CON-003.
- Preserve existing resolved ADS/AMS/DPS/PDS/OBCC content unless directly necessary for S&A consistency.

## Done

- CON-003 §2.8 and any S&A candidate-backlog wording reflect closed/dispositioned S&A definition decisions and pending execution/model follow-up.
- MBSE assessment S&A conclusions are consistent with the closure record.
- No S&A files, D2/PNG, binary, source-code, or unrelated subsystem files changed.
