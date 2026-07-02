# SYS-FLIGHT-READINESS-CLOSURE — final CanSat-level readiness closure

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
Final board closure that every required subsystem/system activity is defined, executed or explicitly dispositioned, and evidence/waivers are complete.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | Assembled CanSat, DPS ground station, subsystem reports, waiver/deviation log, requirement-to-test matrix |
| Verification means | Board inspection/analysis using closure matrix, report archive review, configuration audit and final review minutes |
| Stimulus / scenario | Review all subsystem and system rows after execution/disposition; verify matrix and evidence links |
| Environment / configuration | Final as-flown/as-demonstrated configuration frozen; no hardware/software changes after closure except controlled retest |
| Statistical method | 100% closure-matrix census; no sampling claim |
| Fault-hardening cases | missing report, unapproved deviation, changed configuration after test, unresolved safety issue, stale definition-backlog status |
| Pass/fail oracle | PASS iff 100% required tests are executed PASS or have approved waiver/defer disposition, all critical waivers risk-accepted, no open safety/definition blocker remains, configuration IDs match reports, and final board signs closure. Any missing required report/evidence/disposition is HOLD. |
| Required evidence | closure matrix, signed minutes, configuration list, waiver/deviation register, report archive |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-FLIGHT-READINESS-CLOSURE_view1_system_verification_chain.d2`](definition_views/SYS-FLIGHT-READINESS-CLOSURE_view1_system_verification_chain.d2) | [`definition_views/SYS-FLIGHT-READINESS-CLOSURE_view1_system_verification_chain.png`](definition_views/SYS-FLIGHT-READINESS-CLOSURE_view1_system_verification_chain.png) |
