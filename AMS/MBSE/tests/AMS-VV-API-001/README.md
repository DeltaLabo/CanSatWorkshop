# AMS-VV-API-001 — Pointer/return API and allocation analysis

- **SSIV / development version:** AMS v1.0 final acceptance / flight readiness.
- **IADT method:** Analysis with supporting Inspection.
- **Traceability:** `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault`; `AMS-FE-StaleMeasurement`; variable-getter constraint.
- **References cited in diagram titles:** IVV; model/API-contract analysis; AMS-R1 (BME280 context); AMS-R2 (I2C context). No new external source is used for the API contract beyond the v1.0 model and controlled code/API evidence to be attached in the report.
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-VV-API-001/report.md`.

## Baseline views copied

Untouched baseline copies of all AMS v1.0 D2/PNG views are in `baseline/`.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_API_001_view2_logical_api_ce_analysis_testbench.d2` | PV2 logical/API analysis testbench showing target `[CE] Pointers` and `[CE] Returns`, context `[CE] I2C`, VV-only API/allocation analysis record, code reviewer, static-analysis tool, API contract checklist, unit-test/log evidence repository, QA reviewer, and pass/fail constraints. |
| `AMS_VV_API_001_view3_functional_allocation_api_analysis.d2` | PV3 allocation view with AMS Sensing, AMS Processing, OBCC, VV-only analysis functions, external actor/tool functions, and allocation/API pass/fail constraints. |
| `AMS_VV_API_001_view4_variable_getter_contract_analysis_chain.d2` | Analysis chain mapping baseline identification, getter inventory, allocations, modeled CEs, getter calls, pointer ownership/lifetime/units, return semantics, stale-data prevention, bounded error behavior, static analysis, evidence inspection, and report archiving. |

Rendered PNGs with matching names are generated beside each D2 file.

## Scope

This activity is a model-defined analysis of:

1. `[CE] Pointers` between `[LC] AMS Processing` and `[LC] OBCC`.
2. `[CE] Returns` between `[LC] AMS Processing` and `[LC] OBCC`.
3. The variable-getter template constraint for read/process and read/calculate pairs.
4. Functional allocation of `[LC] AMS Sensing`, `[LC] AMS Processing`, and `[LC] OBCC`.
5. Data/resource crossings through modeled CEs: `[CE] I2C`, `[CE] Pointers`, and `[CE] Returns`.

`[CE] I2C` protocol/timing proof remains under `AMS-VV-CE-001` / `AMS-VV-CON-003`; it is included here only as crossing context.

## Covered candidate activities

If accepted by the global plan, this model-defined activity can cover or supersede:

- `AMS-VV-CE-002` — `[CE] Pointers` analysis.
- `AMS-VV-CE-003` — `[CE] Returns` analysis.
- `AMS-VV-ALLOC-001` — AMS Sensing allocation analysis.
- `AMS-VV-ALLOC-002` — AMS Processing allocation analysis.
- `AMS-VV-ALLOC-003` — OBCC allocation analysis.
- `AMS-VV-CON-002` — variable-getter template constraint analysis/testing candidate, by analysis with supporting inspection.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. Pointer ownership, lifetime, null/invalid pointer policy, units/scaling, and concurrency/aliasing assumptions are explicit and consistent with variable-getter semantics.
2. Return values/statuses distinguish valid measurement, startup fault, runtime sensor fault, timeout/bus error, invalid input, and stale/no-data cases as applicable.
3. No AMS Sensing functions are allocated to AMS Processing or OBCC; AMS Sensing owns only modeled BME280 measurement and I2C-response behavior.
4. No OBCC collection functions are allocated to AMS Sensing or AMS Processing except through modeled Pointers/Returns exchange semantics.
5. All crossings between LCs use modeled CEs (`I2C`, `Pointers`, `Returns`) and no foreign/unmodeled exchange, global data path, bypass, or substitute interface is required.
6. The analysis checklist covers 100% of modeled AMS Processing getters and 100% of OBCC collection paths from the atmospheric-measurement and peripheral-initialisation chains.
7. Missing, ambiguous, inconsistent, unauditable, or waived API evidence is classified in the report; unresolved items fail unless a controlled model update/waiver exists.

## Statistical and fault-hardening viewpoints

- **Statistical basis:** 100% model/API review of the enumerated getter and OBCC collection paths; analysis/inspection only, with no sampling or fleet reliability claim.
- **Fault hardening:** invalid or null pointers, stale/no-data cases, startup fault, runtime sensor fault, timeout/bus error, unit/scaling mismatch, overflow/NaN, aliasing/concurrency hazards, unmodeled data crossings, and bounded non-blocking error propagation.

## Assumptions and limitations

- The v1.0 model does not define explicit mission/capability/use-case/feared-event nodes; traceability targets are the candidate IDs already used in the global plan.
- The API contract is treated as a controlled model/code contract to be inspected during execution. No additional API standard was available in the model.
- This definition does not prove environmental accuracy, I2C timing, process/calculate timing, or physical PC/PL presence; those remain assigned to other AMS v1.0 activities.
