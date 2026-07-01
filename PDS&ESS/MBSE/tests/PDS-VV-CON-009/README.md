# PDS-VV-CON-009 — PCB manufacturability/Carvera Air DFM flight-readiness definition

Model-based verification definition for the PDS & ESS v1.0 final-flight acceptance constraint
`[C] All PCBs machinable in a Carvera Air CNC`.

- **Activity ID:** `PDS-VV-CON-009`
- **SSIV/version/campaign:** PDS & ESS **v1.0 final flight acceptance**. Earlier versions are protoflight/development baselines and are out of scope.
- **IADT method:** Inspection + Analysis.
- **IVV source category:** Constraint, with supporting component/context presence inspection for PCB manufacturability.
- **Model elements:** `[C] All PCBs must be machined in a Carvera Air CNC`; `[PC] PDS PCB`; `[PC] OBCC PCB`; `[PC] Backplane PCB`; `[PC] PDS Headers`; `[PC] OBCC Headers`; traces and features for battery/protection/INA/5V/3V3 paths; `1S1P Li-Ion` context; `Backplane Connector` context.
- **Traceability targets:** source constraint `[C] All PCBs machinable in a Carvera Air CNC`; `PDS-FE-LiIonUnsafeCondition` (for workmanship/retention risks); `PDS-FE-RailBrownout` (for high-resistance or thermal overstress precursors).
- **References cited in view titles/comments:** IVV, PDS-R8 (IPC-2152), PDS-R1, PDS-R2.

## Baseline views (copied)

All PDS & ESS v1.0 source views are copied for report-by-reference under `baseline/`:

- `PDS_v1.0_view1_physical.d2/png`
- `PDS_v1.0_view2_logical.d2/png`
- `PDS_v1.0_view3_functional_allocation.d2/png`
- `PDS_v1.0_view4_power_and_protection_chain.d2/png`
- `PDS_v1.0_view5_battery_supervision_chain.d2/png`

## Definition views

| View | File | Purpose |
|---|---|---|
| PV1 physical inspection context | `PDS_VV_CON_009_view1_physical_dfm_inspection_context.d2/png` | v1.0 physical article and board/coupon context, verification actors, fixture links, and rule/defect annotations. |
| PV2 logical/evidence interfaces | `PDS_VV_CON_009_view2_logical_evidence_interfaces.d2/png` | Logical/evidence interfaces for test operator, QA owner, evidence repository, and constraint-check logic. |
| PV3 functional allocation review | `PDS_VV_CON_009_view3_functional_allocation_dfm_review.d2/png` | Allocation of source functions and verification-only DFM/evidence functions for review coverage and ownership. |
| PV4 Carvera Air DFM analysis chain | `PDS_VV_CON_009_view4_carvera_air_dfm_analysis_chain.d2/png` | Analysis chain implementing the pre-execution rule set and pass/fail classification. |
| PV5 coupon/board inspection chain | `PDS_VV_CON_009_view5_coupon_board_inspection_chain.d2/png` | Prepowered board/coupon inspection chain: visual/dimensional/continuity/isolation/workmanship and disposition. |

## Pass/fail constraints

1. **Mandatory DFM pre-check:** execution is blocked until **all** Carvera Air rules are identified as available/assessed and recorded: trace/space, drill/tool size, annular ring, isolation/clearance, milling depth, board thickness, keepouts. Any unknown/failed mandatory rule prevents proceeding.
2. **Coverage:** 100% of v1.0 PDS flight boards/coupons in scope are reviewed, including PDS PCB, OBCC PCB, and backplane context.
3. **Context completeness:** review includes backplane connectors, headers, footprints, screw holes, and retention interfaces shown in the v1.0 model.
4. **Trace review scope:** battery/protection/INA and 5V/3V3 high-current or power-trace features are analyzed against IPC/DFM assumptions for modeled `1 A` load behavior.
5. **Board/coupon checks:** all boards/coupons pass **visual**, **dimensional**, **fit**, **continuity**, **isolation**, and **workmanship** checks before any powered integration or long-form functional testing.
6. **Deviation handling:** any mismatch, rule gap, or inspection anomaly is traced to a waiver/disposition record with explicit owner/action before closure.
7. **Fault-hardening checks:** explicit holds/dispositions are required for shorts, opens, high-resistance suspicion, wrong footprint/orientation, clearance intrusion, thermal overstress, connector retention failures, and vibration/handling workmanship defects.

## Statistical significance and fault-hardening viewpoint

- **Statistical significance:** the activity is a complete-batch board/coupon inspection for the selected campaign; not a lot sampling for production population inference unless a separate sampling plan is later defined.
- **Fault hardening:** failure modes are tracked at feature-level (open/short/high-resistance), mechanical (wrong footprint/orientation, retention, screw-hole defects), electrical (trace continuity/isolation), thermal, and handling/transport robustness.

## Environmental and execution conditions

- Read ambient temperature/humidity before each board/coupon review set.
- Confirm metrology fixtures, AOI/microscopy, continuity instruments, and evidence repository are calibrated or status-checked before evidence capture.
- Use the strict “deviation hold” behavior: hold execution for any blocking rule, unresolved tooling uncertainty, unknown requirement interpretation, or unsafe handling condition.
- No powered acceptance claim is made from this activity.

## Evidence path

Store evidence under `PDS&ESS/MBSE/tests/results/PDS-VV-CON-009/` (`../results/PDS-VV-CON-009/` relative to this folder):
- Board/coupon IDs and lot/article mapping
- Ambient condition captures
- Inspection checklists (visual, dimensional, continuity/isolation, fit)
- Thermal/workmanship observations and photos
- Carvera Air rule-by-rule evidence for each of:
  trace/space, drill/tool, annular ring, isolation, milling depth, thickness, keepouts
- High-current trace review notes tied to battery/protection/INA/5V/3V3 features
- Hold/waiver/disposition records and final pass/fail rationale

## Assumptions and caveats

- This is a **constraint-derived pre-powered inspection definition** for PDS & ESS v1.0 final acceptance evidence planning.
- Rule thresholds beyond model scope (exact numeric Carvera process limits, tool libraries, and panelization allowances) must be finalized by manufacturing/test management and then reflected in this definition.
- If any required toolpath or rule specification is unavailable, the activity remains in hold with an explicit disposition and no progression to powered tests.