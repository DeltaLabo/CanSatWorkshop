# PDS-V01-GATE-001 — v0.1 power-path progression gate

## Verification identity

- **Activity ID:** `PDS-V01-GATE-001`
- **SSIV / version:** PDS & ESS `v0.1` incremental advancement gate toward `v0.2`
- **IADT method:** Inspection / Testing / Demonstration (combined model)
- **Primary traceability targets:**
  - `PDS-v0.1-AdvanceToV0.2`
  - `PDS-UC-ProvideRegulatedPower`
  - `PDS-FE-ReversePolarityOrOpenPowerPath`
  - `[C] Screw terminal or crimped cables`

## Source views read

- `PDS&ESS/MBSE/v0.1/PDS_v0.1_view1_physical.d2`
- `PDS&ESS/MBSE/v0.1/PDS_v0.1_view2_functional_allocation.d2`
- `PDS&ESS/MBSE/v0.1/PDS_v0.1_view3_power_chain.d2`
- `PDS&ESS/MBSE/tests/README.md`
- `PM&SE/IVV.md`

## Baseline copies (read-only)

Created `baseline/` and copied source views + PNG renders from `PDS&ESS/MBSE/v0.1/`:
`PDS_v0.1_view1_physical.*`, `PDS_v0.1_view2_functional_allocation.*`, `PDS_v0.1_view3_power_chain.*`.
No baseline copies were edited after copying.

## Assumptions and conservative defaults

- v0.1 gate is modeled for **one prototype article** (article-level presence/condition inspection).
- Because the issue did not specify fixture details, test use is **bench supply + supervised 1S1P Li-Ion fixture** with current limits set by operator judgement.
- Only smoke-path validation is defined for this gate: **one short sequence with 3 repeat cycles** and evidence logging. This is explicit as *screening* (no statistical reliability claim).
- Rail pass/fail numeric limits are interpreted from existing project convention and issue text: `5V in [4.75, 5.25] V`, `3V3 in [3.14, 3.47] V` under light load.
- Ambient conditions are recorded before repetitions using an ambient thermometer.
- Destructive abuse or non-workshop-safe conditions are out of scope; Li-ion use is restricted to normal safe testing posture.
- Execution evidence not available yet; status remains modeled-definition ready, execution pending.

## Coverage and modeling approach

The gate model covers all requested minimum IVV breadth for v0.1:

- **Physical components inspected:**
  - `[System] PDS v0.1 Subsystem`
  - `[PC] PDS Circuitboard`
  - `[PC] Protection Circuit`
  - `[PC] Regulator`
  - `[PC] Connector Terminal`
  - `[PC] 1S1P Li-Ion`

- **Physical links inspected:**
  - battery cable JST
  - PC Out / GND
  - 5V / 3V3 / GND

- **Functional chain/scenario modeled:**
  - `Switch power on`
  - `Restore power`
  - `Store energy`
  - `Provide power`
  - `Regulate voltage`
  - `Switch power off`
  - `Cut off power`

- **Constraint coverage:**
  - `[C] Screw terminal or crimped cables` as explicit pass/fail condition on connector/termination path.

- **External actors and equipment introduced (verification-only):**
  - Bench operator, bench supply, supervised Li-Ion fixture, DMM/continuity tester,
  - electronic load, ambient thermometer, data logger/log sheet.

- **Verification-only model additions:**
  - Verification-only test actor functions (authorize, set conditions, measure, log, stop unsafe).
  - Verification harness component + logical interfaces in allocation view for source, measurement, and reporting.

## Pass/fail constraints assigned

| Constraint ID | Constraint definition | Model location |
|---|---|---|
| `PDS-V01-GATE-001-C-PC` | All v0.1 modeled PCs listed above are present, identifiable, intact, and in the modeled containment. | View 1 constraint note (`PDS_V01_GATE_001_view1_physical_inspection_testbench.d2`) |
| `PDS-V01-GATE-001-C-PL` | All modeled PLs are present with expected route/endpoints; continuity, polarity checks, and no accidental discontinuity for inspected runs. | View 1 constraint note (`..._view1...`) |
| `PDS-V01-GATE-001-C-SCREW` | `[C] Screw terminal or crimped cables` path is mechanically secure and electrically suitable; no exposed/capricious terminations. | View 1 note + View 3 constraint note |
| `PDS-V01-GATE-001-C-RAIL` | `5V` measured within `[4.75, 5.25] V` and `3V3` within `[3.14, 3.47] V` under light load; no fault trip, smoke, unsafe heat, or residual unsafe power path. | View 3 |
| `PDS-V01-GATE-001-C-SEQ` | Gate chain must follow environment check → termination/continuity check → controlled source setup → on → provide/regulate → load/measure → off/cut off → evidence closeout with explicit pass/fail decision. | View 3 |

## Relevant viewpoints

- **Statistical significance:** article-level verification with 3 nominal smoke repetitions; this is an execution coverage screening gate and not a reliability-rate claim.
- **Fault hardening:** reverse polarity / open-path checks are included in setup and exchange/constraint notes; abnormal thermal / over-current response is blocked from execution (abort) if detected.

## Modeled files

- `PDS_V01_GATE_001_view1_physical_inspection_testbench.d2`
- `PDS_V01_GATE_001_view1_physical_inspection_testbench.d2.png`
- `PDS_V01_GATE_001_view2_functional_allocation_testbench.d2`
- `PDS_V01_GATE_001_view2_functional_allocation_testbench.d2.png`
- `PDS_V01_GATE_001_view3_power_path_smoke_chain.d2`
- `PDS_V01_GATE_001_view3_power_path_smoke_chain.d2.png`

## Evidence/report placeholder

Execution evidence and reporting folder:

- `PDS&ESS/MBSE/tests/results/PDS-V01-GATE-001/`

Status: **modeled definition ready for review; execution pending**.

## Notes on execution readiness

- Source-model constraint meaning beyond this gate was not over-constrained; all constraints and conditions are conservative and explicitly documented.
- No changes were made to source v0.1 model files.
- Central plan entry in `tests/README.md` was updated to index this gate activity.