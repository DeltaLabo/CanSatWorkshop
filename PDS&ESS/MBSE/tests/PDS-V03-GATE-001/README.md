# PDS-V03-GATE-001 — v0.3 protection & endurance progression gate

## Verification identity

- **Activity ID:** `PDS-V03-GATE-001`
- **SSIV / version:** PDS & ESS `v0.3` incremental advancement gate toward `v1.0`
- **IADT method:** Testing / Demonstration / Analysis (single modeled campaign)
- **Primary traceability targets:**
  - `PDS-v0.3-AdvanceToV1.0`
  - `PDS-UC-ProvideRegulatedPower`
  - `PDS-UC-SuperviseBattery`
  - `PDS-FE-OvercurrentOvervoltage`
  - `PDS-FE-RailBrownout`
  - `PDS-FE-LiIonUnsafeCondition`
  - Constraint `Enough for 6 hours of continuous operation in On mode`
  - Constraint `Probability < 1%`

## Source views read

- `PDS&ESS/MBSE/v0.3/PDS_v0.3_view1_physical.d2`
- `PDS&ESS/MBSE/v0.3/PDS_v0.3_view2_functional_allocation.d2`
- `PDS&ESS/MBSE/v0.3/PDS_v0.3_view3_power_and_protection_chain.d2`
- `PDS&ESS/MBSE/v0.3/PDS_v0.3_view4_battery_supervision_chain.d2`
- `PDS&ESS/MBSE/tests/README.md`
- `PM&SE/IVV.md`

## Baseline copies (read-only)

Created `baseline/` and copied source views + PNGs from `PDS&ESS/MBSE/v0.3/`:

- `PDS_v0.3_view1_physical.d2/.png`
- `PDS_v0.3_view2_functional_allocation.d2/.png`
- `PDS_v0.3_view3_power_and_protection_chain.d2/.png`
- `PDS_v0.3_view4_battery_supervision_chain.d2/.png`

No baseline copies were edited after copying.

## Coverage and modeling approach for v0.3 gate

The following requested scope is modeled:

- Physical components/links relevant to protection and supervision:
  - charger, PDS circuitboard, protection circuit, INA219, regulator, connector terminal, XIAO ESP32, 1S1P Li-Ion
  - USB-C cable, battery cable, PC Out trace, INA Out/GND, I2C cables, connector/XIAO power
- Protection behavior:
  - charger power, battery-charger regulation, store/provide power, regulator, restore power, detect overcurrent, detect overvoltage, cut-off power
- Supervision behavior:
  - init/read voltage and current, measure voltage/current, I2C response, process values, collect/log measurements
- Additional gates:
  - 6-hour On-mode endurance loop (rail/temperature/supervision evidence)
  - failure-probability interpretation modeling for protection-demand misses

## Model elements added for verification-only campaign

- External actors/equipment: bench operator, safety observer, current-limited bench supply, battery emulator/supervised cell, overcurrent fixture, overvoltage fixture, programmable load, calibrated DMM/DAQ, scope/logger, thermal probe, Serial0/I2C logger, ambient station, interlock panel, evidence repository.
- New verification functions and logic:
  - Safe setup/authorization, ambient read, demand selection, fault injection, cut-off/restore observation, endurance profile execution, supervision logging, trial classification/statistics, evidence packaging.
- New verification physical links and interfaces:
  - Fault-injection, load, measurement, thermal, and evidence links for on/off demand trials and endurance monitoring.
- New component exchanges (in allocation and chain logic):
  - Power/apply commands, fault-demand interfaces, load profile control, rail/thermal telemetry, I2C/Serial0 telemetry, evidence/export controls.

## Pass/fail constraints assigned to modeled elements

| Constraint ID | Constraint text / modeled location |
|---|---|
| `PDS-V03-GATE-001-C-PC-PL` | All listed v0.3 physical components and required physical links are present, identifiable, and safely connected. Modeled in `View1` presence note and physical links. |
| `PDS-V03-GATE-001-C-PROB` | Conservative source interpretation: `[C] Probability < 1%` = missed demanded unsafe protection-action probability per demanded mode (`overcurrent` and `overvoltage`). A formal claim requires 299 independent zero-miss demanded trials per mode. This campaign is conservative/advancement-gate evidence; otherwise classify screening. Modeled in `View3` and trace note. |
| `PDS-V03-GATE-001-C-ENERGY` | On-mode endurance: demonstrate 6h continuous operation against representative load with no brownout/uncontrolled restart and no unsafe thermal/rail anomalies. Modeled in `View4`; per-result evidence remains execution-driven. |
| `PDS-V03-GATE-001-C-CHAIN` | Overcurrent and overvoltage demanded scenarios: detect observable, cut-off-before-limit, hold-safe-state on demand, restore-inhibited-while-demanded, safe restore recovery after demand cleared, and evidence logging per trial. Modeled in `View3`. |
| `PDS-V03-GATE-001-C-SUP` | Supervision loop captures INA219 init/read/process/logging sequence and environmental readings at run cadence over the endurance campaign, including `Serial0` and temperature context. Modeled in `View4`. |

## Stat significance / fault-hardening viewpoint

- Conservative interpretation used by the model:
  - missed demanded unsafe protection action probability `< 1%` for each mode (`overcurrent`, `overvoltage`)
  - `299/299` zero-missed demanded trials are needed at 95% confidence for formal claim
  - fewer counts remain screening/characterization and must report exact one-sided bound rationale
- Fault-hardening checked in model:
  - overcurrent and overvoltage demand/restore behavior, inhibit-restore conditions, thermal excursions, rail brownout/reset indicators, evidence hold on miss or unsafe readout, and safe power-down sequencing.

## Environment and safety controls (verification means)

- Ambient temperature/conditions recorded before trial sets.
- Current/voltage limits configured before energized operation.
- Bench interlocks and E-stop are explicit control points.
- Battery fixture is supervised with non-abuse assumptions; flight pack may be used only for normal non-abusive profile testing under a controlled containment assumption.

## Assumptions and blockers

- No external parameters were provided by the issue; conservative values are documented here.
- Battery capacity model, precise allowed battery temperature envelope, and final campaign-specific ambient acceptance bands are model-input assumptions for execution (execution pending).
- This issue requires only modeled definition and controlled evidence placeholder; execution is pending.

## Models created in this issue

- `PDS_V03_GATE_001_view1_physical_protection_testbench.d2` (+ PNG)
- `PDS_V03_GATE_001_view2_functional_allocation_testbench.d2` (+ PNG)
- `PDS_V03_GATE_001_view3_protection_fault_chain.d2` (+ PNG)
- `PDS_V03_GATE_001_view4_endurance_supervision_chain.d2` (+ PNG)

## Evidence path

- `PDS&ESS/MBSE/tests/results/PDS-V03-GATE-001/`

## Status

Modeled definition ready for review; execution pending.
