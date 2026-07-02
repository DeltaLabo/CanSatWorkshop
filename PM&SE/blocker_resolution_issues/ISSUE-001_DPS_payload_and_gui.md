# ISSUE-001 — Resolve DPS-BLK-002 and DPS-BLK-003

## Context

The repository has a CON-003 blocker register at `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` and an assessment at `PM&SE/MBSE_Test_Plan_Assessment.md`.

This issue resolves two DPS blockers with these decisions:

- `DPS-BLK-002`: remove relative humidity from the controlled OBCC/DPS payload and dashboard model. Do **not** add an absent/error-coded RH placeholder and do **not** update OBCC to add RH.
- `DPS-BLK-003`: the GUI must show the **orientation of the CanSat as the orientation of a 3D model**. The 3D model is not an altitude model. Altitude may remain as a 2D plot/value.

Do not claim that `DPS-BLK-001` (candidate definitions backlog) is resolved.

## Likely files to inspect and update

- `OBCC/LoRa_Frame.md`
- `DPS/README.md`
- `DPS/MBSE/v1.0/DPS_v1.0_view3_functional_allocation.d2`
- `DPS/MBSE/v1.0/DPS_v1.0_view8_dashboard_visualisation_chain.d2`
- Baseline copies under `DPS/MBSE/tests/*/baseline/` that still contain the v1.0 dashboard/functional-allocation RH function.
- `DPS/MBSE/tests/README.md`
- `DPS/MBSE/tests/DPS-V10-A-002/README.md`
- `DPS/MBSE/tests/DPS-V10-A-002/DPS-V10-A-002_view1_functional_allocation_analysis_context.d2`
- Optional UI/demo docs/code under `DPS/3dmodel/` if they describe the 3D view generically; keep hardware renaming for Issue 002 unless it is directly needed to clarify the title/purpose.
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`

Use `rg -n -U "rel\.\s*humidity|relative humidity|DPS-BLK-002|DPS-BLK-003|3D altitude|3D model" ...` to find occurrences in controlled files.

## Required changes

1. Remove the `Rel. humidity` row from `OBCC/LoRa_Frame.md` variables.
2. Remove/update DPS MBSE functions/flows for relative humidity:
   - Delete or replace `Update rel. humidity 2D plot` and the associated FE from active v1.0 dashboard/functional-allocation views.
   - Ensure the dashboard still has orientation 3D, temperature 2D, altitude 2D, latency alert, command widgets, and plot-creation functions.
   - Update baseline copies/checklists that would otherwise continue to define RH as part of the v1.0 model.
3. Update DPS requirements and test-plan text:
   - `DPS/README.md` must say the interface generates a real-time report with a 3D model that displays the CanSat orientation (e.g., pitch/roll/yaw or attitude), not altitude.
   - `DPS/MBSE/tests/README.md` and `DPS-V10-A-002/README.md` must remove RH-mismatch language and reflect the closed decision.
   - `DPS-V10-T-005` / `DPS-V10-C-008` candidate descriptions should now have a clear UI oracle for orientation 3D model vs altitude 2D display, while remaining candidates if detailed definitions are still absent.
4. Update PM&SE closure records:
   - In `CON-003_Candidates_and_Definition_Blockers.md`, mark `DPS-BLK-002` and `DPS-BLK-003` as resolved/closed with the selected decisions.
   - In `MBSE_Test_Plan_Assessment.md`, update `SUB-DPS-004`, `SUB-DPS-005`, `GAP-004`, and `ACT-003` style text so they no longer present these two as open decisions.

## D2 rendering

For every `.d2` you change that has a sibling `.png`, regenerate the PNG with:

```bash
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  path/to/file.d2 path/to/file.png
```

## Acceptance checks

Run and report results:

```bash
rg -n -U "rel\.\s*humidity|relative humidity|DPS humidity|RH exclusion" \
  OBCC/LoRa_Frame.md DPS/README.md DPS/MBSE 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md'

rg -n -i "3d.*altitude|altitude.*3d" DPS/README.md DPS/MBSE 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md'
```

The first command should have no open controlled-project RH requirement/mismatch hits. The second should have no statement that the 3D model displays altitude.

## Commit instructions

- Do not push.
- Stage only files relevant to this issue.
- Commit with a message like: `Resolve DPS payload and GUI blockers`.
- Final response: summarize changed files, validation commands, commit hash, and any residual risks.
