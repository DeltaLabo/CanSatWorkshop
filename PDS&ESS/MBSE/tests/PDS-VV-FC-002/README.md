# PDS-VV-FC-002 — Battery supervision verification definition

Primary activity: **PDS-VV-FC-002**. SSIV/version: **PDS & ESS v1.0 final flight acceptance**. Earlier versions are protoflight/development baselines and are out of scope for this folder. IADT method: **Testing / Demonstration** with supporting **Analysis**.

This folder is an individual model-based verification definition for the PDS & ESS v1.0 battery-supervision functional chain and the related variable-getter, I2C, timing, blocking, exchange, and allocation constraints. The v1.0 source model now explicitly includes the INA219 I2C component exchange; baseline source views are copied in `baseline/` for report-by-reference traceability.

## Scope and traceability

- Functional chain/scenario under verification: v1.0 battery supervision chain.
- Primary trace targets: `PDS-UC-SuperviseBattery`, `PDS-FE-SensorBusFault`.
- Constraint coverage provided here: `PDS-VV-CON-005`, `PDS-VV-CON-006`, `PDS-VV-CON-007`, `PDS-VV-CON-008`.
- Supporting analysis context: `PDS-VV-CE-001`, `PDS-VV-CE-002`, `PDS-VV-ALLOC-002`.
- Explicit model constraints covered: `[C] Variable Getter template`, `[C] Process/Calculate functions < 5 ms`, `[C] I2C read timeout ≤ 5 ms`, `[C] No blocking operations besides I2C or UART comms`.
- References used in the diagrams: IVV, PDS-R9 (INA219), PDS-R10 (I2C).

## Views

| File | Purpose |
|---|---|
| `PDS_VV_FC_002_view1_physical_testbench.d2` | PV1 physical testbench: UUT, source components, test harness, external equipment, physical links, environment/setup constraints. |
| `PDS_VV_FC_002_view2_logical_test_interfaces.d2` | PV2 logical test interfaces: source LCs, verification LCs, getter API CEs, explicit INA219 I2C CE, evidence interfaces, and bus-evidence analysis note. |
| `PDS_VV_FC_002_view3_functional_allocation_testbench.d2` | PV3 functional allocation: UUT and verification-only functions allocated to source/test LCs and external actors. |
| `PDS_VV_FC_002_view4_nominal_measurement_timing_chain.d2` | Nominal measurement/timing chain for init, read, process, collect, timestamp, reference comparison, and logging. |
| `PDS_VV_FC_002_view5_i2c_fault_timeout_recovery_chain.d2` | Fault-hardening chain for absent INA219, NACK, stuck SDA, stuck SCL, delayed/no-response, timeout, recovery, and live logging. |
| `PDS_VV_FC_002_view6_api_allocation_analysis_chain.d2` | Supporting analysis chain for CE-001/CE-002/CE-003, ALLOC-002, getter coverage, blocking review, and residual execution evidence. |

Rendered PNGs with the same names plus `.png` are generated in this folder.

## Pass/fail constraints

A final PDS-VV-FC-002 claim is pass only if all applicable conditions below are satisfied and evidence is archived:

1. Nominal init/read/process/collect completes for the declared operating points.
2. At each operating point, collect **≥30 paired voltage/current samples** with matched reference readings, timestamps, ambient conditions, UUT configuration, INA219/shunt configuration, and raw logs.
3. Measurement evidence remains within the declared INA219/reference uncertainty budget. The exact budget is campaign-configurable and shall not be tightened beyond the model/datasheet claim without an approved campaign requirement.
4. INA219 I2C reads either succeed or timeout within **≤5 ms**.
5. Voltage and current process/calculate functions complete in **<5 ms**.
6. Deadline evidence for a 95/95 timing claim uses **59/59** representative in-limit samples per deadline; smaller timing sets are characterization only.
7. Each read/process pair implements the modeled Variable Getter template with documented ownership, units, freshness/age metadata, valid/stale distinction, and bounded status/result codes.
8. No unbounded blocking occurs except modeled I2C or UART communication waits; scheduler/logging remain live during nominal and injected-fault cases.
9. Fault cases cover absent INA219, NACK, stuck SDA, stuck SCL, and delayed/no response. Each trial returns a bounded error/result code, reports no stale data as valid, and preserves scheduler/logging liveness.
10. Supporting analysis confirms CE-001 pointer behavior, CE-002 return behavior, CE-003 INA219 I2C bus/interface consistency, and ALLOC-002 functional allocation intent.
11. CE-003 final credit requires predeclared execution evidence for implemented topology, endpoint pins/net names, INA219 7-bit address, pullup resistor values/locations, bus voltage levels, transaction direction, `≤5 ms` timeout policy, fault-status mapping, and raw logic-analyzer/serial logs plus source/build evidence.

## Environmental and setup conditions

- Ambient temperature/humidity are read before repetitions and recorded with the evidence.
- Supply/load conditions are stable before each operating point and fault trial.
- Precision DMM/current reference, logic analyzer, source/load, and any timing source have calibration or configuration identifiers recorded.
- I2C harness pullups, cable length, bus capacitance proxy/notes, injection method, and analyzer sample rate are recorded.
- Battery-emulator/current-limited source is preferred for repeatable bench testing. Any real Li-ion use is limited to supervised, documented, non-abuse conditions.

## Statistical and fault-hardening viewpoints

- Continuous measurement accuracy: `n ≥ 30` stable paired samples per operating point, with raw data retained and uncertainty reported.
- Timing/deadline: `59/59` in-limit samples are the planning basis for a 95/95 non-parametric one-sided deadline claim.
- Fault injection: each fault case is classified pass/fail; absent INA219, NACK, stuck SDA, stuck SCL, and delayed/no-response faults are mandatory for final execution evidence.

## Evidence path

Store execution evidence for the integrated campaign under:

`PDS&ESS/MBSE/tests/results/PDS-VV-FC-002/`

If constraint, exchange, or allocation activities covered by this model are reported as separate records, store them under their own `results/<activity-id>/` folder while referencing these same views. At minimum, archive raw serial logs, logic-analyzer captures, fault-injection scripts/configuration, reference DMM/source logs, ambient records, harness configuration, rendered diagrams, and the final report that references this definition.

## Assumptions and caveats

- The campaign is PDS & ESS v1.0 final flight acceptance; the report still identifies the exact article ID, firmware/software commit, harness configuration, and accepted deviations.
- The v1.0 source PV2 now includes explicit `[CE] I2C / INA219 bus` from ESS Processing/XIAO to Battery monitoring/INA219. Final CE completeness credit remains execution-only until the report records implemented topology, endpoint pins/net names, INA219 7-bit address, pullups, voltage levels, transaction direction, `≤5 ms` timeout policy, fault-status mapping, and raw logs/source/build evidence.
- This definition does not invent a tighter measurement-accuracy requirement than the INA219/reference uncertainty budget available to the campaign.
