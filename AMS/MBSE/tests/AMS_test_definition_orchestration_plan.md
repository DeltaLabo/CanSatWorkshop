# AMS MBSE multi-version verification-test definition orchestration plan

## Goal

Define AMS Capella/D2 verification activities by delegating one modeled test definition per subagent, using the reusable prompt at `/Users/antho/agent-tools/syseng/prompts/capella-pa-tests-definition.md` and loading the `~/agent-tools/syseng` extension package. The target model root is `AMS/MBSE/`.

## Constraints and coordination rules

- Cover the AMS development baselines present in the repository: `v0.1`, `v0.2`, and `v1.0`.
  - `v0.1` tests advance the breadboard/subsystem baseline to the PCB-delivery baseline.
  - `v0.2` tests advance the PCB-delivery baseline to the integrated flight-readiness baseline.
  - `v1.0` tests support final flight-readiness acceptance.
- Existing model-defined v1.0 tests must not be duplicated: `AMS-VV-PC-001`, `AMS-VV-PL-001`, `AMS-VV-CE-001`, and `AMS-VV-CON-003`.
- Each test-definition subagent creates or updates one activity folder under `AMS/MBSE/tests/<activity-id>/`, including baseline copies, Capella-style D2 test-definition views, rendered PNGs, and a local `README.md`.
- To avoid concurrent edits to the shared plan, test-definition subagents write their proposed global-plan update to `AMS/MBSE/tests/_subagent_updates/<activity-id>.md` instead of editing `AMS/MBSE/tests/README.md` directly. A final integration issue merges those fragments into `AMS/MBSE/tests/README.md` and removes temporary fragments.
- All D2 files must render with the Capella-D2 tight ELK settings:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```

- Subagents must use the `ivv` and `capella-d2` skills, treat the model as the source of truth, include IADT classification, include traceability targets, define pass/fail constraints in the model, and document statistical significance and fault-hardening viewpoints where applicable.
- Subagents must not push and must not commit; the orchestrator will review, integrate, clean up issue files, and decide whether to commit selected AMS-scope changes.

## Work breakdown

| Issue | Activity ID | Version / transition | Verification definition to create | Primary IVV coverage |
|---|---|---|---|---|
| 001 | `AMS-V01-INTEG-001` | v0.1 → v0.2 | Breadboard physical/link/component-exchange/allocation readiness inspection and analysis | Physical components, physical links, I2C CE, logical allocation |
| 002 | `AMS-V01-FC-001` | v0.1 → v0.2 | Breadboard atmospheric measurement, init-state, and serial-logging functional-chain bench test | Functional chains/scenarios, accuracy/timing/serial-output constraints |
| 003 | `AMS-V02-PCB-001` | v0.2 → v1.0 | PCB delivery/manufacturability and physical-link inspection | PCB physical components, footprints/traces, manufacturing constraint |
| 004 | `AMS-V02-BRINGUP-001` | v0.2 → v1.0 | PCB BME280 power/I2C continuity and bring-up demonstration using external fixture | PCB link implementation, BME280 presence, I2C stimulus/response |
| 005 | `AMS-VV-FC-001` | v1.0 flight readiness | Atmospheric measurement accuracy and altitude functional-chain test | Pressure, temperature, altitude, atmospheric chain |
| 006 | `AMS-VV-FC-002` | v1.0 flight readiness | Peripheral initialisation and startup-fault functional-chain test | Init-state chain, startup fault, bounded response |
| 007 | `AMS-VV-API-001` | v1.0 flight readiness | Pointer/return API and allocation consistency analysis covering `AMS-VV-CE-002`, `AMS-VV-CE-003`, and allocation candidates | Component exchanges, LC allocations, variable-getter contract |
| 008 | `AMS-VV-CON-004` | v1.0 flight readiness | Process/calculate timing and non-blocking path test/analysis covering `AMS-VV-CON-004` and `AMS-VV-CON-005` | Timing constraints, blocking/fault hardening |
| 009 | `AMS-VV-CON-001` | v1.0 flight readiness | Sunlight-blocking and airflow exposure inspection/demonstration | Environmental physical constraint, exposure fault hardening |
| 010 | integration | all | Merge subagent fragments into `AMS/MBSE/tests/README.md`; clean temporary coordination files | Plan consistency and coverage closure |

## Review and acceptance checklist

1. Every issue has produced a test-definition folder, unless the issue is the final integration issue.
2. Each folder contains baseline copies from the targeted version, D2 test-definition files, rendered PNGs, and a local README.
3. D2 render commands complete successfully.
4. The global `AMS/MBSE/tests/README.md` covers v0.1, v0.2, and v1.0, distinguishes existing model-defined tests from newly defined ones, and references expected report/evidence paths.
5. Temporary issue files and `_subagent_updates` fragments are removed after integration.
6. No unrelated repository paths are changed by this orchestration.
