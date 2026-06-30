# PDS-VV-PC-001 — PDS & ESS v1.0 physical component / physical link inspection definition

**Primary activity ID:** `PDS-VV-PC-001`.

**Companion coverage:** this same modeled definition may also be referenced as companion coverage for `PDS-VV-PL-001` physical-link inspection and `PDS-VV-SAFE-001` Li-ion safety-document inspection/analysis.

**SSIV / version:** PDS & ESS subsystem integration version `v1.0`, **final flight acceptance**. Earlier PDS & ESS versions are protoflight/development baselines and are out of scope for execution evidence in this folder.

**IADT method:** Inspection. Continuity, polarity, isolation, current-limited power-path status, ambient-condition readings, calibration/status checks, and Li-ion safety-document readings are supporting inspection/analysis evidence, not a substitute for the 100% modeled-item inspection.

**IVV source category:** component/link.

**Traceability targets:** `PDS-UC-ProvideRegulatedPower`, `PDS-FE-LiIonUnsafeCondition`, `PDS-FE-RailBrownout`, and the PCB manufacturability constraint `[C] All PCBs must be machinable in a Carvera Air CNC`.

**References cited in diagram titles/comments:** IVV, PDS-R1, PDS-R2, and PDS-R4–PDS-R8 from `../references/INDEX.md` and `../../../../PM&SE/IVV.md`.

## Baseline copied for this definition

All PDS & ESS v1.0 D2 and PNG source views were copied to `baseline/`:

- `PDS_v1.0_view1_physical.d2/png`
- `PDS_v1.0_view2_logical.d2/png`
- `PDS_v1.0_view3_functional_allocation.d2/png`
- `PDS_v1.0_view4_power_and_protection_chain.d2/png`
- `PDS_v1.0_view5_battery_supervision_chain.d2/png`

## Test-definition views

| View | Purpose |
|---|---|
| `PDS_VV_PC_001_view1_physical_inspection_context.d2/png` | PV1 physical inspection setup: v1.0 article PC inventory, modeled physical links, verification equipment External Actors, temporary inspection links, and PC/PL/environment/safety constraints. |
| `PDS_VV_PC_001_view2_logical_inspection_interfaces.d2/png` | PV2 logical inspection interfaces: human reviewer/operator component exchanges with verification-support logical components and evidence records; no PLs or functions. |
| `PDS_VV_PC_001_view3_functional_allocation_inspection.d2/png` | PV3 allocation of verification-only functions to the article inventory and to human/equipment External Actors; no PLs, CEs, or FEs. |
| `PDS_VV_PC_001_view4_pc_pl_presence_inspection_chain.d2/png` | Functional-chain procedure reference for the inspection sequence; contains only functions, functional exchanges, and constraints. |

## Scope inventory to inspect

The inspection covers 100% of the physical components and physical links shown in `baseline/PDS_v1.0_view1_physical.d2`, including the ESS module and Li-ion cell, PDS PCB components, protection/INA219/regulator path, OBCC PCB and XIAO, backplane PCB/header/spine elements, fixtures, screws, footprints, traces, cables, battery cable, and charger interface.

## Pass/fail constraints

Pass only when all of the following are true:

- **Enumeration:** every modeled PDS & ESS v1.0 PC and PL is explicitly inspected, recorded, and traceable to evidence; no uninspected or unresolved item remains.
- **Physical components:** each PC is present, correct for the baseline/BOM, identifiable, installed in the modeled containment, properly oriented, undamaged, secure, and workmanlike.
- **Physical links:** each PL is present, routed/mated to modeled endpoints, continuous where electrical, correctly polarized where applicable, isolated from unintended shorts, mechanically retained, and free of contact, cable, trace, solder, or fixture workmanship defects.
- **Li-ion safety:** cell/pack identity, datasheet/SDS or equivalent safety documentation, UN 38.3/IEC 62133 evidence when available, charge/discharge/storage limits, and safe handling status are recorded before powered inspection. Defer if the cell is damaged, swollen, leaking, undocumented, or outside declared safe limits.
- **PCB manufacturability:** PDS, OBCC, and backplane PCB workmanship and DFM evidence remain consistent with the modeled Carvera Air CNC manufacturability constraint and with PCB current/thermal rationale from PDS-R8.
- **Fault hardening:** fail or hold for anomaly disposition on open/short links, reversed battery/backplane/cable polarity, swapped/mis-mated headers, high-resistance or weak rail/ground path, loose screws/fixtures, lifted pads, solder bridges, cracked/damaged connectors, unsafe Li-ion condition, or evidence suggesting rail-brownout susceptibility.

## Environmental and safety conditions

- Record ambient temperature and humidity using the modeled thermometer/hygrometer before the article or batch inspection.
- Use an ESD-safe workbench/fixture and current-limited bench supply only after equipment calibration/status has been checked.
- Defer the inspection or powered support readings on condensation, unsafe ESD state, unresolved calibration/function-check issues, unsafe cell condition, or missing safe-handling limits.
- Current-limited powered readings support link/polarity/rail-path inspection only; destructive or abuse Li-ion evidence shall come from certified documentation or an accredited lab.

## Statistical significance and fault-hardening viewpoints

- **Statistical significance:** this definition is a complete enumeration inspection of each inspected article, not lot sampling. It provides pass/fail evidence for the inspected article when 100% of modeled PCs and PLs are inspected. It does not by itself support population reliability inference; any future lot-sampling claim requires a separate sampling plan.
- **Fault hardening:** the inspection intentionally targets failure modes relevant to `PDS-FE-LiIonUnsafeCondition` and `PDS-FE-RailBrownout`: reversed polarity, high resistance, open/short, loose/mis-mated connectors, poor retention, footprint/orientation mistakes, workmanship defects, unsafe Li-ion documentation/limits, and PCB manufacturability/current-path defects.

## Evidence path and reporting

Execution evidence should be stored under `../results/PDS-VV-PC-001/` from this folder, unless a campaign-level evidence folder is later agreed. If `PDS-VV-PL-001` or `PDS-VV-SAFE-001` are reported as separate records, store those records under `../results/PDS-VV-PL-001/` and `../results/PDS-VV-SAFE-001/` while referencing this same modeled definition. Reports should reference this modeled definition, the copied baseline, actual article identifier/revision, equipment IDs/calibration status, operator, witness/reviewer, ambient readings, photographs, continuity/isolation/polarity readings, Li-ion document records, anomalies/waivers, retest status, and pass/fail rationale.

## Assumptions and caveats

- The campaign is PDS & ESS `v1.0` final flight acceptance; the report still identifies the exact article ID, hardware revision/BOM, and accepted deviations.
- The inspection covers model presence/correctness/workmanship and supporting continuity/isolation/safety-document evidence; it is not a substitute for later rail-load, protection-demand, endurance, or software timing tests.
- If the as-built article intentionally differs from the copied source baseline, the report shall record the deviation, rationale, waiver or model update reference, and retest decision.
