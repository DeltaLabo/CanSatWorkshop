# Blocker Resolution Plan — CON-003 First Pass

Date: 2026-07-01
Repository: CanSat Workshop

## End goal

Resolve the first selected CON-003 open definition blockers so the MBSE test suite can move closer to executable status:

1. `DPS-BLK-002`: remove the DPS/OBCC payload mismatch by removing relative humidity from the controlled payload/dashboard model.
2. `SYS-BLK-003`: freeze the hardware naming/configuration to use only `RFM96W`, `ICM20948`, and `BME280` for the affected radio/IMU/environmental-sensor artifacts.
3. `DPS-BLK-003`: clarify the GUI expectation: the dashboard shows the CanSat orientation as the orientation of a 3D model.
4. `OBCC-BLK-001`: disposition as a non-issue: versions may jump from `v0.x` to `v1.0`, and the mostly software-dependent subsystem was not complex enough to require incremental deliveries.
5. `PDS-BLK-001`: freeze the ESS battery architecture as `1S1P Li-Ion`.

## Coordination rules

- Work is delegated to subagents through temporary issue files in `PM&SE/blocker_resolution_issues/`.
- Subagents must not push.
- Subagents should make focused commits for their issue and stage only relevant files.
- When editing D2 files, subagents should use the Capella/D2 style and render any changed D2 with `d2 --layout=elk` plus the project tight-spacing flags.
- PM&SE assessment/register documents are controlled closure records and should be updated as blockers are resolved.
- Do not claim that unrelated candidate-definition backlogs are closed.
- External captured reference/search artifacts may remain unchanged when they quote outside sources; active project docs, MBSE views, tests, BOM rows, and source sketches should use the selected project decisions.

## Work breakdown and dependencies

| Issue | Delegated work | Main dependencies | Expected commit result |
|---|---|---|---|
| `ISSUE-001_DPS_payload_and_gui.md` | Resolve `DPS-BLK-002` and `DPS-BLK-003`: remove relative humidity from controlled DPS/OBCC payload/dashboard artifacts and clarify 3D orientation-model GUI behavior. | First, because later hardware canonicalization may touch the same DPS/OBCC files. | DPS/OBCC payload and dashboard docs/models no longer require RH; DPS README/test plan says 3D orientation model. |
| `ISSUE-002_SYS_hardware_config.md` | Resolve `SYS-BLK-003`: canonicalize radio/IMU/environmental sensor names to `RFM96W`, `ICM20948`, `BME280`. | After Issue 001 to avoid overlapping DPS dashboard files. | Active docs/models/source sketches and BOM use only canonical part names for the affected hardware. |
| `ISSUE-003_OBCC_version_baseline.md` | Resolve `OBCC-BLK-001` as a non-issue with lifecycle rationale while preserving evidence-report caveats. | After Issue 002 so canonical hardware names remain stable in OBCC docs. | PM&SE and OBCC gate docs no longer treat absent v0.x Capella/D2 baselines as a blocker. |
| `ISSUE-004_PDS_battery_config.md` | Resolve `PDS-BLK-001`: select `1S1P Li-Ion` in README/register/assessment/BOM references. | After Issue 002/003 because PM&SE register rows may have changed. | PDS/ESS and PM&SE docs consistently freeze `1S1P Li-Ion`; no 2S/1P conflict remains. |
| `ISSUE-005_validation_and_cleanup.md` | Validate all closure criteria, make minor consistency fixes if required, update this plan with final status, and remove temporary issue files. | Last. | Validation commands pass or documented exclusions are justified; temporary issue files are deleted. |

## Final acceptance criteria

- `DPS-BLK-002`, `DPS-BLK-003`, `SYS-BLK-003`, `OBCC-BLK-001`, and `PDS-BLK-001` are explicitly marked closed/resolved/dispositioned in `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` and aligned assessment text in `PM&SE/MBSE_Test_Plan_Assessment.md`.
- Controlled DPS/OBCC payload/dashboard files no longer include a relative-humidity telemetry/dashboard requirement.
- Controlled project files use `RFM96W`, `ICM20948`, and `BME280` as the selected radio/IMU/environmental-sensor configuration.
- DPS documentation says the GUI shows the CanSat orientation as a 3D model orientation; altitude remains a 2D telemetry plot/value, not the 3D model purpose.
- OBCC version history caveat is no longer a blocker; reports still identify actual executed code/configuration baselines.
- PDS/ESS battery architecture is `1S1P Li-Ion` wherever the final architecture is specified.
- Changed D2 sources have regenerated PNGs when a corresponding PNG exists.
- Temporary issue files are removed after validation; this plan remains as the high-level record.

## Execution status

Pending delegation.
