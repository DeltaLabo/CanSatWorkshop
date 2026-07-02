# ADS-IVV-C-GETTER — Variable Getter template constraint verification definition

**IADT method:** Analysis with supporting Testing.

**IVV source category:** constraint.

**Selected SSIV/development scope:** all ADS MBSE versions currently present: `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Runtime Variable Getter verification applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is explicitly N/A because it is a PCB-only physical delivery model with no logical components, component exchanges, functional allocation, firmware functions, or functional chains.

**Traceability targets:** constraint `Read/process or read/calculate pairs use Variable Getter template`, feared event `ADS-FE-CORRUPT-MEASUREMENT`, and capabilities `ADS-CAP-GPS`, `ADS-CAP-IMU`, `ADS-CAP-ATT`, and `ADS-CAP-DELIVERY` where applicable. `ADS-FE-STUCK-LOOP` is supporting context through timeout/no-blocking behavior, especially when failed sensor reads are injected.

**References cited in diagrams:** IVV skill/minimum verification requirements, ADS MBSE IVV plan `../README.md`, copied source views under `source_views/`, and saved SW/statistics references named by the ADS plan. No external research was performed for this definition.

**Shared freshness contract:** for v1.0, `ADS-V10-DATA-FRESHNESS` extends this getter activity together with `ADS-IVV-FC-OBCC-DELIVERY` and `ADS-IVV-C-RATE-5HZ`. Use [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md): OBCC requests/responses at `5 Hz`, `2 s` LoRa telemetry remains separate, fresh data requires `status == VALID` and `age_ms <= 400 ms`, and the exact enum is `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.

## Source-view copies

All D2/PNG source views for the selected ADS versions were copied into this activity package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used only for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_GETTER_view1_source_constraint_function_inventory.d2/png` | Source constraint/function inventory across v0.1, v0.2, v0.3 N/A, and v1.0, including read/store functions, getters, process/calculate pairs, collected measurements, and v1.0 Pointer/Return implications. |
| `definition_views/ADS_IVV_C_GETTER_view2_analysis_test_setup.d2/png` | Physical analysis/test setup with code/model review station, deterministic firmware harness, fault/stale-data injector, PC/OBCC logger, human conductor, analysis workstation, ambient monitor, and evidence store. |
| `definition_views/ADS_IVV_C_GETTER_view3_verification_functional_allocation.d2/png` | Verification functional allocation and pass/fail constraints for UUT storage/accessor behavior, harness functions, review/analysis functions, human operator functions, logger functions, and environmental recording. |
| `definition_views/ADS_IVV_C_GETTER_view4_deterministic_getter_fault_sequence.d2/png` | Functional-chain style sequence for structural analysis, deterministic getter/process/calculate testing, fault/stale-data injection, v1.0 delivery checks, verdict, and evidence archiving. |
| `definition_views/ADS_IVV_C_GETTER_view5_evidence_traceability_view.d2/png` | Evidence and traceability interface view linking source views, firmware configuration, review records, harness/fault logs, PC/OBCC observations, analysis-script output, disposition, reports, and results repository. |

## Version coverage

| Version | Model element(s) covered | Pass/fail focus |
|---|---|---|
| `v0.1` | Variable Getter constraint on `Loop`; `Read and store lat, lon`; `Get lat`; `Get lon`; `Collect measurements`; supporting `Get UBX-G7020-KT init state` and Serial0 evidence. | Pass if latitude and longitude each have coherent backing storage, a single writer/update path, stable side-effect-light getters, failed/stale GPS reads do not corrupt prior valid values, and freshness/validity/error state is observable in return/status/log evidence. |
| `v0.2` | v0.1 GPS getter elements plus `Read angular velocities`/`Process angular velocities`, `Read accelerations`/`Process accelerations`, `Read field intensities` + `Calculate pitch, roll, yaw`, `Get UBX-G7020-KT init state`, `Get ICM20948 init state`, and `Collect measurements`. | Same as v0.1 plus angular-rate, acceleration, and PRY process/calculate pairs. Inject GPS and IMU stale/fault cases. v0.2 has no explicit I2C timeout constraint, so no timeout pass is claimed here; the getter/fault result must still show no corruption and observable degraded/error state. |
| `v0.3` | PCB-only PV1 source view with ADS PCB, GPS, IMU, backplane connector, footprints, UART/I2C/3V3 traces, and manufacturing note. | Pass/N/A if the source review confirms no runtime Variable Getter model elements exist. Fail if getter behavior is claimed from v0.3 without a modeled LC/function/chain/interface. |
| `v1.0` | v0.2-equivalent ADS Processing getter/process/calculate elements, `Collect measurements` and `Collect peripheral init states` in OBCC, and ADS Processing → OBCC `Pointers`/`Returns`. | Same as v0.2 plus Pointers/Returns shall preserve lifetime/ownership, validity, freshness, and error semantics; getter/API status shall map to `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, or `INIT_FAIL`; OBCC shall not consume stale, no-data, timeout, fault, init-fail, invalid, or corrupt ADS data as valid by bypassing the getter/status model. |

## Pass/fail criteria

Pass requires all applicable criteria below for the selected runtime version:

1. **Complete trace:** every applicable source function/pair and the Variable Getter constraint are traced to analysis and, where runtime behavior exists, deterministic test evidence.
2. **Single writer:** each measured value has exactly one modeled backing-store update path. Getters, processors, calculators, collectors, and v1.0 OBCC consumers do not write measured-value storage except through that update path.
3. **Side-effect-light accessors:** getters/processors/calculators return coherent stored or derived values without hidden sensor reads, unrelated storage mutation, or freshness/validity bypass.
4. **Failed-read preservation:** GPS no-fix/malformed/silent/stale and IMU NACK/stuck/partial/stale cases, where applicable, do not corrupt prior valid stored values.
5. **Observable state:** freshness, validity, and error state are observable in return values, status fields, logs, or analysis evidence and are mappable to the shared enum `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
6. **Age/status rule:** when a getter result is claimed fresh for v1.0 OBCC use, the ADS-to-OBCC observation has `status == VALID`, all required fields are finite/in range, and `age_ms <= 400 ms`; otherwise the result is explicitly non-`VALID`. Report-level evidence includes `contract_version`, `subsystem_id=ADS`, `sample_id`/sequence, `sample_time_ms`, request/consumer time, `age_ms`, `status`, field-validity flags, and fault/init indicators. `2 s` LoRa telemetry cadence is not accepted as proof of the internal `5 Hz` getter freshness path.
7. **Repeated-call stability:** repeated calls remain stable and coherent until a successful modeled update; after success, related outputs transition coherently.
8. **v1.0 delivery protection:** Pointers/Returns do not bypass lifetime, ownership, freshness, validity, or error semantics.

Fail on missing trace, multiple writers for a value, hidden side effects, old valid data overwritten by failed reads, stale/no-data/timeout/fault/init-fail/invalid data reported as `VALID`, unstable repeated getter results without an intervening successful update, unsafe pointer/return exposure, missing evidence, or unreported deviations.

## Statistics and fault-hardening viewpoints

- **Statistical significance:** this activity is structural analysis plus deterministic vector/fault coverage over all modeled getter/value/fault classes. It supports verification coverage, not population reliability or sensor accuracy. Any later reliability claim needs a separate sample-size and independence plan.
- **Fault hardening:** cover GPS no-fix, malformed payload, silent UART, stale/no-data GPS data, IMU NACK/stuck/partial/stale/no-data responses where IMU is modeled, timeout/sensor-fault/init-fail mappings, prior-value preservation without stale-as-`VALID`, explicit invalid/degraded state, recovery after subsequent successful update, and v1.0 pointer/return lifetime/ownership errors.
- **Completeness:** v0.1/v0.2/v1.0 require 100% enumeration of applicable source getter/process/calculate pairs. v0.3 requires explicit N/A evidence from its 1/1 physical-only source view.

## Required execution conditions

- Record selected ADS version, copied source-view package, model baseline, UUT or host-harness configuration, hardware revision/serial if hardware is used, firmware commit, compiler/build flags, and test-harness version.
- Record equipment IDs/calibration status for the review station, deterministic firmware harness, fault/stale-data injector, PC/OBCC logger, and ambient thermometer/hygrometer.
- Before repetitions, a human conductor reads and records ambient temperature/humidity from the modeled ambient monitor. No fixed environmental acceptance limit is claimed unless a later controlled requirement adds one.
- Preserve source review notes, pair inventory, seed values, nominal vectors, fault schedule, raw call/return/status logs, timestamp/sequence/age/status evidence, PC/OBCC observations, analysis scripts/settings, generated verdicts, deviations, anomalies, waivers, and retest status.
- If execution uses a host-only firmware harness rather than physical hardware, record that limitation and do not claim hardware-interface fault coverage beyond the modeled/injected cases.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-GETTER/v0.1/`
- `../results/ADS-IVV-C-GETTER/v0.2/`
- `../results/ADS-IVV-C-GETTER/v0.3/`
- `../results/ADS-IVV-C-GETTER/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested/as-analyzed configuration, raw evidence, analysis settings, environmental/equipment conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status, assumptions, and gaps

- **Status:** modeled definition ready for review; execution pending.
- **Traceability note:** capability and feared-event IDs are controlled ADS-plan labels until formal mission/capability/feared-event elements exist in the source model.
- **v0.3 N/A:** no runtime behavior is modeled, so only N/A source-review evidence is expected for this activity.
- **v0.2 modeling gap:** no explicit I2C timeout constraint is modeled; this activity checks getter preservation/observability for IMU faults but does not close the timeout gap.
- **Report-time mapping:** ADS-specific validity/freshness/error field names and implementation return-code names are recorded in the execution report as a mapping to the required evidence fields and shared enum; they are not open pass/fail gates. The stale-data threshold, finite/in-range rule, status vocabulary, and `400 ms` freshness limit are fixed by the shared PM&SE contract.
