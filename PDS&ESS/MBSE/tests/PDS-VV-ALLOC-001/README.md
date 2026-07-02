# PDS-VV-ALLOC-001 — power-path allocation analysis definition

Primary activity: **PDS-VV-ALLOC-001**. SSIV/version: **PDS & ESS v1.0 final flight acceptance**. Earlier versions are protoflight/development baselines and are out of scope for execution evidence in this folder.

- **IADT method:** Analysis.
- **IVV source category:** Allocation.
- **Model elements:** Battery, Battery Charger, Power Protection, Regulator, and related actor control functions used for power-path and actor-interface allocation reviews.
- **Traceability:** `PDS-UC-ChargeESS`, `PDS-UC-ProvideRegulatedPower`, `PDS-FE-OvercurrentOvervoltage`, `PDS-FE-RailBrownout`, `PDS-FE-LiIonUnsafeCondition`.
- **References cited in diagram titles:** IVV, existing definitions `PDS-VV-FC-001`, `PDS-VV-CON-001`, `PDS-VV-CON-003`, `PDS-VV-CON-004`, `PDS-VV-PC-001`.

## Scope for this definition

This folder defines two coupled allocation activities:

- **ALLOC-001:** verification-only allocation/review of source LCs and functions:
  - `[LC] Battery` — `Store energy`, `Provide power`
  - `[LC] Battery Charger` — `Regulate voltage`
  - `[LC] Power Protection` — `Detect overcurrent`, `Detect overvoltage`, `Restore power`, `Cut off power`
  - `[LC] Regulator` — `Regulate voltage`
- **ALLOC-003 support:** explicit external-actor interface analysis for:
  - `[EA] Charger` — `Provide power`
  - `[EA] User` — `Switch power on`, `Switch power off`

Pass/fail review intent for both is **100% allocation completeness against source v1.0 intent**, with no undocumented foreign functions or flows without discrepancy/waiver disposition.

## Baseline views

`baseline/` is a local copy of all PDS & ESS v1.0 source views used by this definition:

- `PDS_v1.0_view1_physical.d2/png`
- `PDS_v1.0_view2_logical.d2/png`
- `PDS_v1.0_view3_functional_allocation.d2/png`
- `PDS_v1.0_view4_power_and_protection_chain.d2/png`
- `PDS_v1.0_view5_battery_supervision_chain.d2/png`

## Definition views

| File | Purpose |
|---|---|
| `PDS_VV_ALLOC_001_view1_physical_allocation_context.d2/png` | PV1 physical allocation context: source power-path topology, baseline actor interfaces, and source-model switch-access caveat. |
| `PDS_VV_ALLOC_001_view2_logical_allocation_analysis.d2/png` | PV2 logical allocation boundary analysis: LC ownership map, modeled links/exchanges, and ALLOC-003 actor-interface gap. |
| `PDS_VV_ALLOC_001_view3_functional_allocation_review.d2/png` | PV3 functional allocation matrix for intended functions and actor-owned control functions. |
| `PDS_VV_ALLOC_001_view4_power_path_allocation_chain.d2/png` | Power-path allocation analysis chain for charge/regulation/protection ownership and modeled flow boundary checks (with required fault-hardening touchpoints). |
| `PDS_VV_ALLOC_001_view5_external_actor_interface_chain.d2/png` | External actor interface analysis chain for charger setup, wrong-setup hold, user switch control, safe power-off, and source-model blocker/waiver path. |

## Pass/fail constraints

A final ALLOC-001/ALLOC-003 claim is pass only if all are true:

1. **100% review completeness:** all scoped source functions and actor functions above are reviewed against the source model baseline and recorded in this activity.
2. **No foreign/unmodeled ownership:** no unmodeled function is allocated to in-scope LCs; any gap is explicitly recorded as discrepancy with disposition status.
3. **Boundary correctness:** power/resource flows cross only modeled links/exchanges (`USB-C`, `Battery cable`, `Battery connector`, protected rail paths). Additional modeled interfaces are blocked for discrepancy and must be justified by waiver or source-model update.
4. **Source constraints preserved:** ALLOC-001 ownership checks align to existing chain/constraints from **FC-001/CON-004** (power path/rail behavior) and **CON-001** (safe charge setup).
5. **Fault-hardening reviewed:** overcurrent, overvoltage, restore, wrong charger, power-off safety, and Li-ion preconditions are reviewed as allocation assumptions/discrepancy conditions for each actor-controlled function.
6. **Master-switch/accessibility source/interface closure:** ALLOC-003 requires explicit evidence of a safe switch/access path. Where the source model does not expose explicit master-switch hardware, the selected closure path is a source-model/interface edit or controlled waiver, not a reason to create another test candidate; final allocation closure remains pending until that edit/waiver and later execution evidence are controlled.

## Environmental and procedural constraints attached

- Charger/interface checks use `4.2 V` and `0.5 A` limit setup controls as setup controls for review context, consistent with **CON-001**.
- Li-ion prerequisites and safety prerequisites are assumed from the safety-document evidence path in `PDS-VV-SAFE-001` and/or campaign acceptance evidence before actor interface closure.
- Master-switch/accessibility gaps remain **blocked** for unqualified allocation closure until the selected source-model/interface edit is made or a controlled waiver path is approved.

## Evidence path

Execution reporting should be stored under:

`PDS&ESS/MBSE/tests/results/PDS-VV-ALLOC-001/`

and references this definition plus the copied baseline views. Cross-reference `PDS-VV-FC-001`, `PDS-VV-CON-001`, `PDS-VV-CON-003`, `PDS-VV-CON-004`, and `PDS-VV-PC-001` for supporting chain/evidence context.
