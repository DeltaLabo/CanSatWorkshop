# ADS-IVV-FC-OBCC-DELIVERY — v1.0 ADS-to-OBCC delivery verification definition

**IADT method:** Demonstration/Testing with supporting Analysis.

**IVV source category:** functional chain / scenario, with linked component-exchange and constraint coverage.

**Selected SSIV/development scope:** all ADS MBSE versions currently present (`v0.1`, `v0.2`, `v0.3`, `v1.0`). Execution applies to **`v1.0`**. `v0.1` and `v0.2` are explicitly N/A here because their delivery behavior is Serial0 logging to a PC, not ADS Processing → OBCC `Pointers`/`Returns`. `v0.3` is explicitly N/A because it is a PCB-only delivery with no LCs, CEs, allocations, or functional chains.

**Traceability targets:** `ADS-CAP-DELIVERY`, `ADS-FE-CORRUPT-MEASUREMENT`, `ADS-FE-STUCK-LOOP`, and linked source constraints: no blocking except I2C/UART, Variable Getter pattern, process/calculate `<5 ms`, UART read timeout `<=5 ms`, and I2C read timeout `<=5 ms` for `v1.0`.

**References cited in diagrams:** IVV, the ADS MBSE IVV plan `../README.md`, NASA-SE, and SW/statistics references from the ADS plan. No external research was performed for this definition.

**Shared freshness contract:** v1.0 ADS delivery uses `ADS-V10-DATA-FRESHNESS` as an alias/extension through this activity, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ`. The controlling contract is [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md): OBCC requests/responses at `5 Hz`, `2 s` LoRa telemetry packaging remains separate from internal `5 Hz` evidence, fresh age is `<=400 ms` only when status is `VALID`, and the exact enum is `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.

## Source-view copies

All currently present ADS MBSE source D2/PNG views were copied into this activity package so reports can reference a stable test-definition baseline:

- `source_views/v0.1/` — physical, logical, functional allocation, GPS position chain, Serial0 logging chain.
- `source_views/v0.2/` — physical, logical, functional allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial0 logging chain.
- `source_views/v0.3/` — PCB physical delivery view only.
- `source_views/v1.0/` — physical, logical, functional allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_OBCC_DELIVERY_view1_v10_source_interface_inventory.d2/png` | v1.0 source interface inventory: UART, I2C, `Pointers`, `Returns`, OBCC consumer, data-chain context, and N/A rationale for `v0.1`/`v0.2`/`v0.3`. The rendered view groups `Pointers` and `Returns` on one CE label for readability; the note and source copies identify them as separate source CEs. |
| `definition_views/ADS_IVV_FC_OBCC_DELIVERY_view2_physical_integration_setup.d2/png` | Physical integration setup with v1.0 integrated article, power supply, OBCC log harness, ADS stimulus/logger, pointer/freshness monitor or code-review workstation, ambient monitor, analysis workstation, temporary PLs, setup and environment constraints. |
| `definition_views/ADS_IVV_FC_OBCC_DELIVERY_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to ADS Processing, OBCC, delivery observation probe, human conductor, human software reviewer, log harness, stimulus/logger, pointer monitor, power/ambient equipment, analysis script, and quality reviewer. |
| `definition_views/ADS_IVV_FC_OBCC_DELIVERY_view4_pointers_returns_delivery_sequence.d2/png` | Functional-chain style test sequence covering nominal delivery plus null, dangling, stale, corrupt/invalid-return, and slow/stuck-call cases, with pass/fail constraints. |
| `definition_views/ADS_IVV_FC_OBCC_DELIVERY_view5_evidence_traceability.d2/png` | Evidence and traceability interface view linking logs, analysis, report store, configuration review, and trace targets. |

## Version coverage

| Version | Applicability | Coverage / rationale | Expected outcome |
|---|---|---|---|
| `v0.1` | N/A for this activity | Source views show GPS-only XIAO prototype with delivery through Serial0 logging to a PC, not ADS Processing → OBCC `Pointers`/`Returns`. | Record N/A if this activity is used for all-version closure; use a Serial0 delivery activity instead. |
| `v0.2` | N/A for this activity | Source views show GPS/IMU XIAO prototype with Serial0 logging to a PC. No OBCC LC or `Pointers`/`Returns` CE exists. | Record N/A if this activity is used for all-version closure; use a Serial0 delivery activity instead. |
| `v0.3` | N/A for this activity | PCB-only delivery: physical PCB, GPS, IMU, connector, footprints, UART/I2C/3V3 traces. No behavior, LC, CE, allocation, or functional chain exists. | Pass/N/A only after confirming source view is PV1-only and physical traces are not credited as OBCC delivery behavior. |
| `v1.0` | Applicable | ADS Processing and OBCC LCs are co-located on the OBCC XIAO. ADS Processing receives GPS/IMU data via UART/I2C, computes stored GPS, processed IMU, attitude, and init-state data, and exposes data/status to OBCC via modeled `Pointers` and `Returns` CEs. | Demonstration/testing with supporting analysis shall produce pass/fail evidence for the shared freshness contract, field coverage, fault rejection, and bounded/no-blocking behavior. |

## Pass/fail criteria

Pass for `v1.0` only if all criteria below are satisfied and evidenced:

1. **Modeled-interface use:** OBCC obtains ADS data/handles only through modeled `Pointers`/`Returns`; no unmodeled global/shared/private consumer path is used for GPS, IMU, attitude, or init-state delivery.
2. **Explicit semantics:** pointer ownership, pointer lifetime, data freshness, validity flags/status, and return/error behavior are explicit in the firmware/interface contract and observed in logs or supporting code-review evidence; ADS-specific return codes shall map to the shared enum without losing fault evidence.
3. **Data coverage:** nominal evidence covers GPS lat/lon/init state, IMU angular velocity/acceleration/field data, attitude pitch/roll/yaw, and OBCC collection fields present in the v1.0 source inventory.
4. **Shared freshness/status:** ADS-to-OBCC responses support `5 Hz` requests/responses and carry or trace timestamp/sequence/age/status evidence. Fresh data requires `status == VALID`, all required fields finite/in range, and `age_ms <= 400 ms`; `2 s` LoRa telemetry cadence is packaging evidence, not a substitute for internal `5 Hz` delivery evidence. The only accepted status vocabulary is `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`. Required report-level evidence fields are `contract_version`, `subsystem_id=ADS`, `sample_id`/sequence, `sample_time_ms`, request/consumer time, `age_ms`, `status`, finite/in-range field-validity flags, and fault/init indicators; implementation variable names are mapped in the report.
5. **Fault hardening:** null, dangling, out-of-lifetime, stale, no-data, timeout, sensor-fault, init-fail, corrupt, invalid-return, and slow/stuck-call cases are rejected or reported as non-`VALID` and are not consumed as valid measurements. Old ADS data shall not remain marked `VALID` after timeout, runtime fault, no-data, or init-fail conditions.
6. **Bounded/no-blocking behavior:** no unexpected blocking occurs outside modeled I2C/UART waits. Linked constraints remain applicable: Variable Getter pattern, process/calculate `<5 ms`, UART read timeout `<=5 ms`, and I2C read timeout `<=5 ms`. Delivery progress/freshness uses the selected shared threshold: no internal ADS-to-OBCC progress/freshness gap may exceed `400 ms`; no separate delivery-watchdog threshold is used.
7. **Evidence integrity:** raw logs, fault markers, firmware/build metadata, code-review notes, analysis settings, actual environmental/power conditions, deviations, anomalies, waivers, and retest status are preserved in the report package.

Fail on any unmodeled data path, missing or ambiguous ownership/lifetime/freshness/validity/error semantics, invalid/stale/corrupt data consumed as valid, unexpected blocking, missing required field/fault coverage, missing source baseline, or unreported execution deviation affecting interpretation.

## Statistical and fault-hardening viewpoints

- **Statistical significance:** this definition is an engineering demonstration/test unless a formal population or PDR claim is predeclared. Minimum nominal engineering evidence is `>=30` delivery observations spanning the modeled GPS, IMU, attitude, and init-state fields. Formal freshness/deadline claims use `n = 59` representative request/response observations with every observation meeting the `5 Hz` opportunity, `age_ms <= 400 ms`, exact-status, finite/in-range, and `400 ms` max-gap rules. PDR claims require a separate predeclared packet-delivery method.
- **Fault hardening:** explicitly execute or disposition null pointer, missing return, dangling/out-of-lifetime handle, stale freshness epoch, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, corrupt data, invalid return/status, slow/stuck call, recovery, and no-unmodeled-bypass cases.
- **Constraint coverage:** this activity directly covers delivery/no-corruption/no-blocking aspects of the source constraints. GPS position `<5 m` and angular-rate `<30 deg/s` accuracy are not re-verified here; they are preserved by non-corruption/validity checks and are verified by the GPS/ANG activities.

## Required execution conditions

- Select and record the `v1.0` source-view package, UUT serial/identifier, hardware revision, ADS/OBCC firmware commit/build, instrumentation configuration, and equipment IDs/calibration status.
- Configure current-limited power or battery simulation and record voltage/current limits, resets, brownouts, and current anomalies.
- Human conductor reads the ambient thermometer/hygrometer before repetitions and after fault cases; record temperature/humidity and calibration ID.
- Configure the OBCC firmware/log harness, ADS stimulus/logger, pointer lifetime/freshness monitor or code-review station, and analysis script without creating an unmodeled ADS data path to OBCC.
- Preserve raw OBCC delivery logs, ADS stimulus/fault markers, timing/heartbeat records, pointer/freshness observations, `contract_version` (`PMSE-SENSOR-OBCC-FRESHNESS-v1.0` or approved successor), `subsystem_id=ADS`, sample IDs/sequences, sample and request/consumer timestamps, `age_ms`, status values, finite/in-range field-validity flags, fault/init indicators, code-review notes, analysis scripts/settings, and generated plots/tables.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-OBCC-DELIVERY/v1.0/` for applicable demonstration/testing and supporting analysis.
- `../results/ADS-IVV-FC-OBCC-DELIVERY/v0.1/`, `v0.2/`, and `v0.3/` only if all-version closure records are created for N/A dispositions.

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested/as-analyzed configuration, raw evidence, actual conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.

## Assumptions and gaps

- Controlled SSIV/version identifiers remain inferred from folder names and D2 titles.
- Traceability targets are controlled IDs from the ADS-wide plan; no formal mission/capability/feared-event source-model nodes were found, and no pass/fail gate depends on unresolved trace-label naming.
- ADS-specific Pointers/Returns field names, implementation return codes, data schema names, timing instrumentation overhead, hardware revision, firmware commit, and equipment IDs are report-time mapping/configuration records. Freshness thresholds, status vocabulary, required evidence fields, `400 ms` delivery progress/freshness rule, and formal `n = 59` timing/freshness sample rule are fixed by this definition and the shared PM&SE contract.
- Definition views and reports shall reference the shared freshness/status contract; remaining work is execution evidence, not definition selection.
- This activity does not replace the all-version PC/PL inspection, CE analysis, allocation analysis, GPS, angular velocity, or attitude verification definitions.
