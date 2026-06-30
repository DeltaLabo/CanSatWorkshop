# PDS-VV-FC-001 — Final flight acceptance full power/protection functional-chain definition

Activity **PDS-VV-FC-001** is the model-based verification definition for the PDS & ESS **v1.0 final flight acceptance** full power and protection functional chain. Earlier PDS & ESS versions are protoflight/development baselines and are out of scope for execution evidence in this folder.

- **IADT method:** Testing / Demonstration with supporting Analysis.
- **IVV source category:** Functional chain/scenario, with related constraint, component/link, exchange, and allocation evidence referenced by report.
- **Primary model elements:** charger provide power, battery-charger regulate voltage, battery store/provide power, regulator regulate voltage, user switch on/off, restore power, detect overcurrent, detect overvoltage, cut off power, and the protection/regulator/battery/backplane physical path.
- **Traceability:** `PDS-UC-ChargeESS`, `PDS-UC-ProvideRegulatedPower`, `PDS-FE-OvercurrentOvervoltage`, `PDS-FE-RailBrownout`, `PDS-FE-LiIonUnsafeCondition`.
- **References cited in views:** IVV, PDS-R2, PDS-R4, PDS-R5, PDS-R6, PDS-R7, PDS-R8.

## Baseline views

`baseline/` is a local report-by-reference copy of all PDS & ESS v1.0 D2/PNG source views used for this definition:

- `PDS_v1.0_view1_physical.d2/png`
- `PDS_v1.0_view2_logical.d2/png`
- `PDS_v1.0_view3_functional_allocation.d2/png`
- `PDS_v1.0_view4_power_and_protection_chain.d2/png`
- `PDS_v1.0_view5_battery_supervision_chain.d2/png`

## Definition views

| File | Purpose |
|---|---|
| `PDS_VV_FC_001_view1_physical_power_protection_testbench.d2/png` | PV1 physical final-acceptance testbench: UUT power path, battery/charger/fault/load/measurement equipment, safety equipment, and environmental constraints. |
| `PDS_VV_FC_001_view2_logical_power_protection_interfaces.d2/png` | PV2 logical interfaces for charger, battery/fault input, protection, rail loads, measurements, safety control, and evidence capture. |
| `PDS_VV_FC_001_view3_functional_allocation_testbench.d2/png` | PV3 allocation of source and verification-only functions to UUT LCs, test harness LCs, instruments, human actors, and evidence repository. |
| `PDS_VV_FC_001_view4_charge_and_nominal_power_chain.d2/png` | Nominal charge/store/provide/restore/regulate/load/measure/log sequence. |
| `PDS_VV_FC_001_view5_overcurrent_cutoff_restore_chain.d2/png` | Current-limited overcurrent or output-short-equivalent demand, cut-off, safe state, clear fault, and restore verification. |
| `PDS_VV_FC_001_view6_overvoltage_cutoff_restore_chain.d2/png` | Current-limited overvoltage demand, cut-off, safe state, clear fault, and restore verification. |
| `PDS_VV_FC_001_view7_power_off_safe_state_chain.d2/png` | Commanded power-off safe state, no unsafe restart, and controlled restore if required by the campaign. |

## Required pass/fail constraints

Pass only if all applicable final-acceptance conditions below are satisfied and evidence is archived:

1. The nominal chain completes: safe charger/emulator configuration, charge/store/provide power, switch on, restore power, regulate rails, command representative loads, measure/log rails/current/temperature, and verify no brownout/reset/uncontrolled restart.
2. When normal charge is exercised, charge behavior respects the modeled `4.2 V / 0.5 A` normal-charge constraint. Battery-emulator or certified charger evidence may support this; destructive Li-ion abuse is out of scope.
3. Regulated rails satisfy the v1.0 model: `5±0.1 V` and `3.3±0.1 V` at the modeled `1 A` condition, or the report explicitly references accepted numerical rail-load evidence from `PDS-VV-CON-004`.
4. No unsafe temperature, current, cell, connector, PCB, smoke, swelling, latch-up, rail brownout, reset, or uncontrolled restart occurs.
5. Every demanded overcurrent or short-equivalent protection event cuts off safely, reaches a safe state, and restores only after the fault is cleared and an explicit restore/on command is allowed.
6. Every demanded overvoltage protection event cuts off safely, reaches a safe state, and restores only after the fault is cleared and an explicit restore/on command is allowed.
7. Commanded power-off de-energizes the rails to the campaign-defined safe threshold and holds off without unsafe restart until a controlled restore is commanded or the campaign requires remaining safe-off.
8. Reverse/wrong charger setup, unsafe restore attempt while a fault remains, loose/high-resistance path indication, rail brownout, overheating, and Li-ion unsafe-condition precursors cause hold/abort/anomaly disposition rather than a pass.
9. No missed unsafe action is permitted in any demanded protection trial. If the report claims protection failure probability `<1%` at 95% confidence, it shall show **299 independent demanded-protection trials with zero missed unsafe actions**; smaller samples are final-acceptance functional screening only.

## Environmental and safety conditions

- Read and record ambient temperature/humidity before repetitions or demand sets.
- Use calibrated or status-checked DMM/DAQ, oscilloscope/logger, source/load, thermal, and timing instruments; record IDs or uncertainty assumptions.
- Prefer a battery emulator/current-limited source for fault injection. The flight Li-ion pack may be used only for normal, supervised, non-abuse charge/discharge in a fire-safe enclosure.
- ESD controls, fire-safe Li-ion container, E-stop/safety equipment, and Safety Observer/Witness approval are required before energizing the article.
- Current limits and safe source/load limits are set and recorded before applying power or injecting a fault.
- Destructive Li-ion abuse, transport certification, short-circuit abuse of the flight pack, overcharge abuse, and accredited safety-standard evidence must come from certified documentation or an accredited lab, not this bench activity.

## Statistical and fault-hardening viewpoints

- Continuous rail/current/thermal evidence uses `n ≥ 30` samples per stable condition, with raw data retained; `PDS-VV-CON-004` may provide the detailed numerical rail-load sample evidence.
- Binary protection and safe-state trials use exact one-sided binomial confidence bounds. A single article or repeated non-independent trials do not automatically support population reliability.
- Fault-hardening coverage includes overcurrent, output short-equivalent, overvoltage, reverse/wrong charger setup hold, unsafe restore prevention, loose/high-resistance path, rail brownout, overheating, and Li-ion unsafe condition.

## Evidence path

Store execution evidence under `PDS&ESS/MBSE/tests/results/PDS-VV-FC-001/` (`../results/PDS-VV-FC-001/` relative to this folder): raw logs, source/load profiles, current-limit settings, ambient records, calibration/status records, photos of setup/probe points, DMM/DAQ data, waveforms, thermal images, protection trial classification sheets, safety observer records, anomalies/deviations, and the final report referencing this model definition.

## Assumptions and caveats

- The final flight acceptance campaign defines the exact article ID, representative flight-load profile, safe off-voltage threshold, thermal limits, settling windows, and whether controlled restore after power-off is required.
- The source physical view does not expose a dedicated master-switch hardware PC; this definition treats switch on/off as a modeled user/operator command through the available approved interface and records the as-tested interface in the report.
- PDS-VV-FC-001 is a functional acceptance definition. Qualification, lot reliability, and destructive safety certification require separate campaign authority and evidence.
