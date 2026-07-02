# ISSUE-004 — Resolve PDS-BLK-001 by selecting 1S1P Li-Ion

## Context

`PDS-BLK-001` is a battery architecture conflict: `PDS&ESS/README.md` said the ESS battery must use `2S1P`, while MBSE/tests repeatedly model `1S1P Li-Ion`.

The project decision for this issue:

- Final ESS battery architecture is `1S1P Li-Ion`.
- Update README/register/assessment/BOM references so there is no remaining `2S1P` final-architecture conflict.
- Do not alter unrelated PDS blockers such as INA219 CE, regulator efficiency, load profile, master switch, Li-ion safety documents, etc.

## Likely files to inspect and update

- `PDS&ESS/README.md`
- `PDS&ESS/MBSE/tests/README.md` (probably already uses `1S1P Li-Ion`; inspect for consistency)
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/BOM/BOM.csv` if the ESS cell row can be clarified as `1S1P Li-Ion` without inventing unavailable quantities/specs.

## Required changes

1. In `PDS&ESS/README.md`, update the ESS battery requirement to use `1S1P Li-Ion` rechargeable cell/pack architecture and keep external charging wording if applicable.
2. In PM&SE closure records:
   - Mark `PDS-BLK-001` resolved/closed with selected `1S1P Li-Ion`.
   - Update assessment rows such as `SUB-PDS-002`, `GAP-003`, and `ACT-003` so they no longer present an open `2S1P` vs `1S1P` conflict.
   - If `SYS-BLK-003` battery architecture text remains after Issue 002, ensure it reflects the frozen `1S1P Li-Ion` decision.
3. Ensure existing PDS MBSE/test docs that use `1S1P Li-Ion` still read consistently.
4. Do not claim PDS final power acceptance is complete; only the architecture conflict is resolved.

## Acceptance checks

Run and report results:

```bash
rg -n -i "2s\s*1p|2s1p|2S1P|2S 1P" 'PDS&ESS' 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md' --glob '!*.pdf' --glob '!*.png' --glob '!*.jpg' --glob '!*.xlsx' --glob '!*.pptx'

rg -n "1S1P Li-Ion|PDS-BLK-001|SUB-PDS-002|GAP-003" 'PDS&ESS/README.md' 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md'
```

The first command should return no active final-architecture conflict. If an external quote remains, justify it.

## Commit instructions

- Do not push.
- Stage only files relevant to this issue.
- Commit with a message like: `Select PDS ESS battery architecture`.
- Final response: summarize changed files, validation commands, commit hash, and residual non-battery PDS blockers.
