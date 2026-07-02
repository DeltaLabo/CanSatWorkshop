# ISSUE-003 — Resolve OBCC-BLK-001 as a non-issue

## Context

`OBCC-BLK-001` currently treats absent OBCC `v0.1`–`v0.9` Capella/D2 source baselines as a blocker because gates use `v1.0` target context.

The project decision for this issue:

- This is a **non-issue**, not an open blocker.
- Versions are allowed to jump from `v0.x` to `v1.0`.
- For OBCC, the subsystem is mostly software-dependent and its complexity was not deemed high enough to require incremental source-model deliveries.
- Do **not** fabricate v0.x source baselines.
- Keep a reporting caveat: if historical gates are executed/reported, reports should identify the actual code/configuration baseline used and acknowledge target-context-only model references where applicable.

## Likely files to inspect and update

- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `OBCC/MBSE/tests/README.md`
- OBCC gate READMEs that mention source gaps/version context, especially:
  - `OBCC/MBSE/tests/OBCC-V01-GATE-001/README.md`
  - `OBCC/MBSE/tests/OBCC-V02-GATE-001/README.md`
  - `OBCC/MBSE/tests/OBCC-V03-GATE-001/README.md`
  - through `OBCC-V10-FLIGHT-001/README.md` if they carry repeated caveats.
- Source-view copied README files under `OBCC/MBSE/tests/*/source_views/v1.0/README.md` if they claim the absent v0.x models are a blocker.

## Required changes

1. In `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, mark `OBCC-BLK-001` as closed/dispositioned non-issue using the exact rationale above.
2. In `PM&SE/MBSE_Test_Plan_Assessment.md`, update OBCC assessment text so absent v0.x source baselines are not a readiness blocker. Keep the evidence-report caveat if useful.
3. Update OBCC test plan/gate language to distinguish:
   - acceptable lifecycle/modeling decision: v0.x gates may reference v1.0 target context because incremental source models were not delivered;
   - required evidence practice: actual code/configuration baseline IDs still belong in execution reports.
4. Do not change technical pass/fail criteria unrelated to the version-baseline caveat.
5. Preserve canonical hardware names from Issue 002 (`RFM96W`, `ICM20948`, `BME280`).

## Acceptance checks

Run and report results:

```bash
rg -n "OBCC-BLK-001|source baselines are absent|source-gap|source gap|v0\.x source" \
  'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md' OBCC/MBSE/tests
```

Acceptable hits should show the non-issue disposition or an execution-report caveat, not an open blocker.

## Commit instructions

- Do not push.
- Stage only files relevant to this issue.
- Commit with a message like: `Disposition OBCC version baseline blocker`.
- Final response: summarize changed files, validation commands, commit hash, and residual caveats.
