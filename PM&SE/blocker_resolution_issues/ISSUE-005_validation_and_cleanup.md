# ISSUE-005 — Final validation and issue cleanup

## Context

This is the final coordination issue. Earlier issues should have resolved:

- `DPS-BLK-002`: relative humidity removed from controlled payload/dashboard requirements.
- `DPS-BLK-003`: GUI clarified as CanSat orientation shown through a 3D model.
- `SYS-BLK-003`: hardware naming/configuration frozen to `RFM96W`, `ICM20948`, `BME280`.
- `OBCC-BLK-001`: dispositioned as a non-issue with lifecycle rationale.
- `PDS-BLK-001`: ESS battery architecture frozen to `1S1P Li-Ion`.

The overarching plan file is `PM&SE/Blocker_Resolution_Plan_2026-07-01.md`.

## Required work

1. Inspect `git status` and recent commits to understand what previous subagents changed.
2. Run the validation checks below.
3. Make small consistency fixes if a check reveals a missed active-project occurrence. Do not perform broad unrelated rewrites.
4. Update `PM&SE/Blocker_Resolution_Plan_2026-07-01.md` execution status with a concise completion summary and any justified exclusions/residual blockers.
5. Remove the temporary issue files/directory `PM&SE/blocker_resolution_issues/` after validation. The overarching plan file should remain.
6. Commit validation fixes, plan status update, and issue-file cleanup.

## Validation checks

Run from repo root and include outputs/summaries in your final response.

### Relative humidity / DPS GUI

```bash
rg -n -U "rel\.\s*humidity|relative humidity|DPS humidity|RH exclusion" \
  OBCC/LoRa_Frame.md DPS/README.md DPS/MBSE 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md'

rg -n -i "3d.*altitude|altitude.*3d" DPS/README.md DPS/MBSE 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md'
```

Expected: no active controlled statement that RH is part of the payload/dashboard or that the 3D model displays altitude.

### Hardware naming/configuration

```bash
rg -n "RFM95W|MPU6050|BMP280|ICM-20948|rfm95w|mpu6050|bmp280" \
  README.md ADS AMS DPS OBCC PDM 'PDS&ESS' 'PM&SE' 'S&A' Workshop \
  --glob '!*.pdf' --glob '!*.png' --glob '!*.jpg' --glob '!*.xlsx' --glob '!*.pptx' --glob '!*.synctex.gz' \
  --glob '!**/references/**'

rg -n "RFM96W|ICM20948|BME280" PM\&SE/BOM/BOM.csv OBCC/LoRa_Frame.md OBCC/MBSE/v1.0/README.md DPS/MBSE/tests/README.md AMS/README.md ADS/MBSE/tests/README.md
```

Expected: no legacy active-project hardware naming hits, or only justified external/archival exclusions recorded in the plan.

### OBCC-BLK-001 disposition

```bash
rg -n "OBCC-BLK-001|source baselines are absent|source-gap|source gap|v0\.x source" \
  'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md' OBCC/MBSE/tests
```

Expected: hits show non-issue disposition or execution-report caveat, not open blocker language.

### PDS battery

```bash
rg -n -i "2s\s*1p|2s1p|2S1P|2S 1P" 'PDS&ESS' 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md' --glob '!*.pdf' --glob '!*.png' --glob '!*.jpg' --glob '!*.xlsx' --glob '!*.pptx'

rg -n "1S1P Li-Ion|PDS-BLK-001|SUB-PDS-002|GAP-003" 'PDS&ESS/README.md' 'PM&SE/CON-003_Candidates_and_Definition_Blockers.md' 'PM&SE/MBSE_Test_Plan_Assessment.md'
```

Expected: no active `2S1P` final-architecture conflict; `1S1P Li-Ion` selected.

### D2/render sanity

Use `git diff --name-only HEAD~4..HEAD` (or appropriate range) to identify changed `.d2` files. Confirm each changed `.d2` with a same-named `.png` has a regenerated PNG in the commit history or regenerate it now.

## Commit instructions

- Do not push.
- Commit with a message like: `Validate blocker resolution and clean issues`.
- Final response: summarize validation results, cleanup, commit hash, and any residual blockers outside this goal.
