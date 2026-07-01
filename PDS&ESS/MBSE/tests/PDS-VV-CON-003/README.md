# PDS-VV-CON-003 — Protection probability constraint test definition

Model-based verification definition for the PDS & ESS v1.0 constraint `[C] Probability < 1%` attached to `[F] Detect overcurrent` and `[F] Detect overvoltage`.

- **Activity ID:** `PDS-VV-CON-003`.
- **SSIV/version/campaign:** PDS & ESS **v1.0 final flight acceptance**. Earlier versions are protoflight/development baselines and are out of scope for this folder.
- **IADT method:** Testing with supporting Analysis.
- **IVV source category:** Constraint, with functional-chain/scenario coverage of demanded protection response; this definition provides the formal probability-demand-count evidence referenced by `PDS-VV-FC-001`.
- **Model elements:** `[C] Probability < 1%`; `[F] Detect overcurrent`; `[F] Detect overvoltage`; `[F] Cut off power`; `[F] Restore power`; `[LC] Power Protection`; `[PC] Protection Circuit`; protected output, regulator, PDS backplane connector, and backplane rail path.
- **Traceability:** source constraint; `PDS-VV-FC-001`; `PDS-FE-OvercurrentOvervoltage`; `PDS-FE-LiIonUnsafeCondition`; `PDS-FE-RailBrownout`; `PDS-UC-ProvideRegulatedPower`.
- **References cited in views:** IVV, PDS-R4, PDS-R5, PDS-R6, PDS-R7, PDS-R8; PDS-R2 may also support CanSat safety/master-switch context.

## Source-constraint interpretation

The source model states `[C] Probability < 1%` and attaches it to both detection functions without defining the probability event. For this verification definition, the constraint is interpreted conservatively as:

> The probability of a **missed demanded unsafe protection action** is `<1%` for each demanded protection mode: overcurrent/output-short-equivalent and overvoltage.

A demanded unsafe protection action is missed if a valid current-limited demand is applied and the protection path does not detect/actuate/cut off in time to keep rails, cell, PCB, and temperature within safe limits, or if unsafe restore occurs before the fault is cleared. If the intended meaning of the source constraint differs, the source model and this test definition must be updated before claiming verification.

## Baseline views

`baseline/` is a local report-by-reference copy of all PDS & ESS v1.0 source D2/PNG views used to derive this definition:

- `PDS_v1.0_view1_physical.d2/png`
- `PDS_v1.0_view2_logical.d2/png`
- `PDS_v1.0_view3_functional_allocation.d2/png`
- `PDS_v1.0_view4_power_and_protection_chain.d2/png`
- `PDS_v1.0_view5_battery_supervision_chain.d2/png`

## Definition views

| View | File | Purpose |
|---|---|---|
| PV1 physical probability testbench | `PDS_VV_CON_003_view1_physical_probability_testbench.d2/png` | UUT protection path, battery emulator/current-limited source, overcurrent/short-equivalent and overvoltage injection hardware, protected rail loads, measurement equipment, safety equipment, and evidence path. |
| PV2 logical trial interfaces | `PDS_VV_CON_003_view2_logical_trial_interfaces.d2/png` | Logical controls and observations for randomized/procedure-selected demand trials, safety approval, instrumentation, protection state, rail state, and evidence/statistics. |
| PV3 functional allocation | `PDS_VV_CON_003_view3_functional_allocation_testbench.d2/png` | Allocation of source protection functions and verification-only setup, injection, observation, classification, binomial, independence, and evidence functions. |
| Functional chain | `PDS_VV_CON_003_view4_overcurrent_probability_trial_chain.d2/png` | Overcurrent/output-short-equivalent demanded-protection trial chain and per-trial pass/fail constraints. |
| Functional chain | `PDS_VV_CON_003_view5_overvoltage_probability_trial_chain.d2/png` | Current-limited overvoltage demanded-protection trial chain and per-trial pass/fail constraints. |
| Functional chain | `PDS_VV_CON_003_view6_binomial_independence_analysis_chain.d2/png` | Exact one-sided binomial/Clopper-Pearson analysis, independence checks, and final classification as verification or screening. |

## Pass/fail constraints

Pass only if all applicable final-acceptance conditions below are satisfied and evidence is archived:

1. **Zero missed unsafe actions:** any missed unsafe action in any valid demanded-protection trial is a fail/hold/anomaly. No waiver may convert a miss into a pass for the `<1%` statistical claim.
2. **Per-mode acceptance:** because the source constraint is attached to both `[F] Detect overcurrent` and `[F] Detect overvoltage`, formal acceptance requires **299 independent demanded-protection trials with zero missed unsafe actions per demanded protection mode** unless a project-approved allocation states otherwise.
3. **Confidence basis:** `299/299` zero misses supports a one-sided 95% exact binomial upper bound below 1% for missed-demand probability. If fewer trials are executed, report the exact one-sided Clopper-Pearson upper bound and classify the result as screening/characterization, not verification of `<1%`.
4. **Overcurrent/output-short-equivalent trials:** each trial shows the demand is applied inside a current-limited safe envelope; `[F] Detect overcurrent` is invoked/observable; `[F] Cut off power` reaches safe state before unsafe rail/cell/PCB/temperature limits; rails are de-energized or current-limited as applicable; restore is inhibited until the fault is cleared; controlled restore returns to nominal without reset or uncontrolled restart.
5. **Overvoltage trials:** each trial shows the overvoltage demand is current-limited and preconfigured; `[F] Detect overvoltage` is invoked/observable; `[F] Cut off power` reaches safe state before unsafe rail/cell/PCB/temperature limits; rails are safe; restore is inhibited until overvoltage is removed; controlled restore returns to nominal without reset or uncontrolled restart.
6. **Continuous observations:** rail voltage/current/thermal observations use calibrated or status-checked instruments and retain raw data. Reference accepted `PDS-VV-CON-004` rail evidence where continuous limits are reused, or collect at least `n ≥ 30` samples for each stable continuous condition claimed in this activity.
7. **Stop conditions:** unsafe current, heating, smoke, swelling, cell anomaly, uncontrolled restart, rail brownout/reset, instrument/status failure, unsafe ambient condition, or unresolved anomaly prevents pass until disposition and retest are complete.

## Environmental and safety conditions

- Read and record ambient temperature/humidity before each demanded-trial set.
- Verify calibration/status of source/load, DMM/DAQ, oscilloscope/logger, thermal instrument, and ambient instrument before use.
- Configure and record current limits before energizing or injecting any demand.
- Safety Observer/Witness approval is required before each trial set and after any anomaly.
- Use a battery emulator/current-limited source for all demanded protection trials by default.
- The flight Li-ion pack, if present, is contained and may only be used for normal non-abuse conditions; destructive Li-ion abuse, direct flight-pack short abuse, flight-pack overcharge abuse, and accredited safety-standard evidence are out of scope for this bench definition.
- Use relay/interlock/E-stop controls so fault energy can be removed independently of the UUT.

## Statistical significance and fault-hardening viewpoint

- **Statistical significance:** binary outcomes are analyzed with exact one-sided binomial/Clopper-Pearson bounds. The verification claim is per demanded mode: overcurrent/short-equivalent and overvoltage. Repeated trials must be documented as independent enough for the claim: reset/thermal conditions controlled, demand sequence randomized or procedure-selected, source/load limits verified, and instrumentation triggers independent of the UUT response. If independence is not defensible, report the evidence as screening only.
- **Fault hardening:** trials cover overcurrent, output short-equivalent, overvoltage, cut-off failure, unsafe restore, rail brownout/reset, overheating, high-current path stress, and Li-ion unsafe-condition precursors. The design must fail safe: hold/abort rather than continue after any ambiguous or unsafe protection behavior.

## Evidence path

Store execution evidence under `PDS&ESS/MBSE/tests/results/PDS-VV-CON-003/` (`../results/PDS-VV-CON-003/` relative to this folder): raw rail/current/thermal logs, source/load settings, current-limit records, ambient records, calibration/status records, randomized/procedure-selected trial list, demand waveform files, cut-off/restore waveforms, photos of setup/probe points, safety observer approvals, trial classification sheet, exact binomial calculation, independence analysis, anomalies/deviations, and the final report referencing this model definition and copied baseline.

## Assumptions and caveats

- The campaign defines final article ID, safe rail/cell/temperature thresholds, fault-demand setpoints, reset/restart observation method, cooldown/spacing between trials, and independence rationale.
- This activity verifies the source constraint under the conservative missed-demand interpretation above; a different project interpretation requires a source-model/test update.
- This folder defines final flight acceptance evidence for the inspected article. It is not a qualification, production-lot reliability, destructive abuse, UN 38.3, or IEC 62133 compliance test.
