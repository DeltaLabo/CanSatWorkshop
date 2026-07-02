# SYS-WORKSHOP-READINESS — educational/reproducibility closure

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
Workshop reproducibility and learning-readiness verification for independent users and materials/documentation.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Workshop guide, root/subsystem READMEs, BOM/materials, code/MBSE test suite, build procedure |
| Verification means | Independent-user dry-run/rebuild review with checklist, BOM procurement check, documentation trace and learning-objective assessment |
| Stimulus / scenario | At least one independent user follows guide to identify parts, build/configure or dry-run safe equivalent, run smoke checks and locate MBSE tests |
| Environment / configuration | Workshop-safe tools/materials, no hazardous powered Li-ion work without safety controls, documented deviations |
| Statistical method | At least one independent-user rebuild/dry-run; 100% checklist closure |
| Fault-hardening cases | missing part, ambiguous wiring, unsafe step, undocumented software setup, inaccessible report template |
| Pass/fail oracle | PASS iff guide enables independent user to identify materials, assemble/configure safe article or dry-run equivalent, run smoke checks, locate evidence/report templates, and explain learning objectives; BOM/materials complete and no critical undocumented step remains. |
| Required evidence | completed user checklist, issue log, BOM snapshot, guide version, photos/screenshots |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-WORKSHOP-READINESS_view1_system_verification_chain.d2`](definition_views/SYS-WORKSHOP-READINESS_view1_system_verification_chain.d2) | [`definition_views/SYS-WORKSHOP-READINESS_view1_system_verification_chain.png`](definition_views/SYS-WORKSHOP-READINESS_view1_system_verification_chain.png) |
