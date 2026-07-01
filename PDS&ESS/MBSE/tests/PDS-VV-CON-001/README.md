# PDS-VV-CON-001 — Normal charge constraint verification definition

Model-based verification definition for the PDS & ESS v1.0 constraint `[C] At 4.2 V, 0.5 A`.

- **Activity ID:** `PDS-VV-CON-001`.
- **SSIV/version/campaign:** PDS & ESS **v1.0 final flight acceptance**. Earlier PDS & ESS versions are protoflight/development baselines and are out of scope for this folder.
- **IADT method:** Testing with supporting Analysis and Inspection for safety documentation, calibration/status, and evidence review.
- **IVV source category:** Constraint, with functional-chain/scenario coverage of the normal charge path and traceability to `PDS-VV-FC-001`.
- **Model elements:** `[C] At 4.2 V, 0.5 A`; `[EA] Charger` / `[F] Provide power`; `[LC] Battery Charger` / `[F] Regulate voltage`; `[LC] Battery` / `[F] Store energy`; `[PC] 1S1P Li-Ion`; `[PC] Protection Circuit`; USB-C/charge path.
- **Traceability:** source constraint; `PDS-UC-ChargeESS`; `PDS-FE-LiIonUnsafeCondition`; `PDS-FE-OvercurrentOvervoltage`; `PDS-VV-FC-001`; `PDS-VV-SAFE-001`.
- **References cited in views:** IVV, PDS-R2, PDS-R4, PDS-R5, PDS-R6, PDS-R7.

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
| PV1 physical charge testbench | `PDS_VV_CON_001_view1_physical_charge_testbench.d2/png` | UUT charge path, certified current-limited charger/emulator, dry-run battery emulator, flight Li-ion pack containment, measurement equipment, environmental/safety equipment, and evidence path. |
| PV2 logical charge interfaces | `PDS_VV_CON_001_view2_logical_charge_interfaces.d2/png` | Logical charger, safety, measurement, ambient, documentation, hold/abort, and evidence interfaces for normal charge final acceptance. |
| PV3 functional allocation | `PDS_VV_CON_001_view3_functional_allocation_testbench.d2/png` | Allocation of source and verification-only functions to the charger, battery charger, battery, protection path, monitoring, test harness, instruments, humans, and evidence repository. |
| Functional chain | `PDS_VV_CON_001_view4_normal_charge_acceptance_chain.d2/png` | Supervised non-abuse normal charge acceptance sequence using a certified charger/emulator and, only when documentation permits, the flight Li-ion pack. |
| Functional chain | `PDS_VV_CON_001_view5_wrong_charger_safety_hold_chain.d2/png` | Wrong charger, reverse/ambiguous setup, missing documentation, unsafe cell, out-of-range ambient, or unresolved calibration/status issue causes hold/abort before energizing. |
| Functional chain | `PDS_VV_CON_001_view6_charge_evidence_analysis_chain.d2/png` | Evidence analysis for voltage/current/thermal logs, safety documents, uncertainty, traceability to `PDS-VV-FC-001`, and safety-document coverage via `PDS-VV-SAFE-001`. |

## Pass/fail constraints

Pass only if all applicable final-acceptance conditions below are satisfied and evidence is archived:

1. **Charge voltage:** charge voltage measured at the cell/protection charge path never exceeds the modeled `4.2 V` limit plus the declared measurement uncertainty/tolerance. If the certified charger terminates below `4.2 V`, record the actual termination; do not invent a tighter battery-chemistry requirement in this activity.
2. **Charge current:** charge current is limited to nominal `0.5 A`, with measurement uncertainty considered. Any uncontrolled current, unexpected overcurrent/protection event, reverse current, overvoltage, unexpected heating, smoke, swelling, cell anomaly, or unsafe connector/PCB temperature is fail/hold/anomaly.
3. **Safety-document prerequisite:** cell/pack identity, datasheet/SDS or equivalent safety documentation, charge/discharge/storage limits, and UN 38.3 / IEC 62133 or equivalent evidence when available shall be recorded before powered Li-ion charge. If evidence is absent, only supervised emulator/non-cell path checks are allowed and no final Li-ion charge acceptance claim is made.
4. **Hold before energizing:** wrong or uncertified charger, reverse polarity, ambiguous setup, unsafe ambient, unresolved calibration/status issue, missing safety limits, unsafe cell condition, or Safety Observer hold prevents energizing.
5. **Sampling/statistical basis:** continuous voltage/current/temperature data use `n ≥ 30` stable samples per relevant condition or a complete logged charge profile. Retain raw data, sample timing, charger settings, uncertainty, ambient conditions, and all anomalies.
6. **Trace closure:** evidence shall trace to the source charge constraint, the normal-charge portion of `PDS-VV-FC-001`, and the Li-ion safety-document record associated with `PDS-VV-SAFE-001`.

## Environmental and safety conditions

- Read and record ambient temperature/humidity before charge repetitions or dry-run path checks.
- Use calibrated or status-checked DMM/DAQ, USB power meter/current logger, oscilloscope/logger if used, thermal camera/thermocouples, ambient meter, and charger/source instruments; record equipment IDs or uncertainty assumptions.
- Verify charger certification/settings and current limit before connection or energization.
- Use a battery emulator/current-limited source for dry-run charge-path and measurement checks when Li-ion evidence is missing or when the campaign does not approve powered cell charging.
- Use the flight Li-ion pack only for supervised normal non-abuse charge in a fire-safe enclosure, with Safety Observer/Witness approval and E-stop/containment ready.
- Destructive Li-ion abuse, accredited safety certification, overcharge abuse, direct short-circuit abuse of the flight pack, and transport/safety-standard compliance claims are out of scope for this bench definition.

## Statistical significance and fault-hardening viewpoint

- **Statistical significance:** this activity verifies the inspected article and charge setup. Stable continuous measurements use at least `30` samples per condition or a complete charge profile; raw data and uncertainty are retained. Repeated charge runs on one article are characterization unless the report states a separate independence and confidence rationale.
- **Fault hardening:** the definition includes a specific safety-hold chain for wrong/uncertified charger, reverse or ambiguous connection, missing safety evidence, unsafe ambient, unresolved calibration/status issue, unsafe cell condition, or Safety Observer hold. The design and test procedure shall fail safe by not energizing, stopping the run, and recording an anomaly rather than continuing into an unsafe or ambiguous state.

## Evidence path

Store execution evidence under `PDS&ESS/MBSE/tests/results/PDS-VV-CON-001/` (`../results/PDS-VV-CON-001/` relative to this folder): raw voltage/current/temperature/ambient logs, charger settings and certification/status record, cell identity and safety documentation, datasheet/SDS/UN38.3/IEC62133 or equivalent records, calibration/status records, photos of setup/probe points, charge profiles, uncertainty budget, wrong-charger/hold records, Safety Observer approvals, anomalies/deviations, and the final report referencing this model definition and copied baseline.

## Assumptions and caveats

- The final flight acceptance campaign records the exact article ID, charger model/certification, cell/pack identity, ambient limits, current/voltage logger sampling configuration, campaign tolerance/uncertainty, and any approved normal-charge duration/profile.
- This activity verifies the modeled normal charge constraint; it is not a qualification, production-lot reliability, destructive abuse, UN 38.3, or IEC 62133 compliance test.
- If the required Li-ion safety evidence is absent, the modeled acceptance result shall be limited to supervised emulator/non-cell charge-path checks and shall explicitly state that final powered Li-ion charge acceptance was not claimed.
