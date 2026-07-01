# ADS-IVV-C-POS-5M — GPS position accuracy constraint verification definition

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint.

**Selected SSIV/development scope:** all ADS MBSE versions currently present: `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Execution applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is explicitly N/A because the source model is PCB-only and has no logical components, component exchanges, allocations, or behavior chains.

**Traceability targets:** constraint `<5 m` / `Accuracy < 5 m`, `ADS-CAP-GPS`, `ADS-FE-SILENT-SENSOR-FAIL`, and `ADS-FE-CORRUPT-MEASUREMENT`.

**Covered model elements:** GPS position chains; `Measure longitude`, `Measure latitude`, `Send payload`, `Read and store lat, lon`, `Get lat`, `Get lon`, `Collect measurements`; UART/GPS data validity and timeout handling; and the `v1.0` ADS/OBCC observation point.

**References cited in diagrams:** IVV skill requirements, `../README.md` ADS MBSE IVV plan, `../model_inventory.json`, GPS/UBX saved references, and SW/statistics saved references. No external research was performed.

## Source-view copies

The selected source D2/PNG views were copied into this activity package for stable report references:

- `source_views/v0.1/` — all five v0.1 views, including physical, logical, allocation, GPS position chain, and serial logging chain.
- `source_views/v0.2/` — all eight v0.2 views, including GPS position chain and supporting allocation/logging context.
- `source_views/v0.3/` — the PCB-only physical delivery view used for N/A rationale.
- `source_views/v1.0/` — all seven v1.0 views, including physical/logical/allocation, GPS chain, and related integrated ADS/OBCC context.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_POS_5M_view1_source_constraint_inventory.d2/png` | Source constraint inventory for `<5 m`, GPS-chain functions/getters, UART validity, v1.0 observation point, and v0.3 N/A rationale. |
| `definition_views/ADS_IVV_C_POS_5M_view2_physical_truth_reference_setup.d2/png` | Physical truth/reference setup with GNSS simulator or surveyed reference receiver, ADS UUT/version selector, PC/OBCC logger, timebase, condition monitor, power, and fault source. |
| `definition_views/ADS_IVV_C_POS_5M_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation across human operators, GNSS truth source, timebase, logger, statistical analysis tool, quality/configuration authority, and ADS UUT observation functions. |
| `definition_views/ADS_IVV_C_POS_5M_view4_sample_collection_analysis_sequence.d2/png` | Functional-chain style sample collection and analysis sequence, including nominal campaign and no-fix/stale/malformed/silent GPS cases. |
| `definition_views/ADS_IVV_C_POS_5M_view5_evidence_traceability.d2/png` | Evidence/report traceability closure for source views, model elements, trace targets, raw evidence, analysis, status, and master-plan coverage row. |

## Version coverage

| Version | Applicability and covered elements | Pass/fail criteria |
|---|---|---|
| `v0.1` | Applicable. Covers GPS position chain, getters, `Accuracy < 5 m`, UART payload validity, and Serial0/PC logging as evidence path. | Pass if `n >= 30` matched valid ADS/truth samples are collected, horizontal error plus truth/measurement uncertainty guard band or formal 95/95 bound where claimed is `<5 m`, and invalid/no-fix/stale/silent GPS data are not accepted as valid. Fail on bound `>=5 m`, missing truth/evidence, accepted invalid data, unhandled stale/silent GPS, or unreported deviation. |
| `v0.2` | Applicable. Same GPS accuracy coverage as `v0.1`, with concurrent IMU/Loop context as possible interference evidence. | Same as `v0.1`; additionally record whether concurrent v0.2 loop/IMU activity affects GPS validity, timestamps, or collection. |
| `v0.3` | N/A for this behavior constraint. Source model is PV1-only PCB delivery with physical GPS/UART traces but no behavior chain. | Pass/N/A if the v0.3 source view is reviewed and confirms no LC/CE/allocation/functional-chain behavior to verify for position accuracy. Fail if v0.3 behavior evidence is claimed from physical traces alone. |
| `v1.0` | Applicable. Covers GPS chain through ADS Processing and the ADS/OBCC collection observation point. | Pass if the `<5 m` verdict is proven at the ADS/OBCC observation point using `n >= 30` matched valid ADS/truth samples and invalid/no-fix/stale/silent GPS data are flagged or handled invalid before OBCC consumption. |

## Pass/fail criteria

- **Nominal accuracy:** each applicable campaign shall collect at least `n >= 30` matched valid ADS/truth samples. The accepted horizontal position error plus truth/reference uncertainty guard band shall be `<5 m`, or, when a formal statistical claim is made, the predeclared 95/95 bound shall be `<5 m`.
- **Truth/reference control:** use either a GNSS simulator or a surveyed/high-confidence reference receiver. Record calibration status, truth uncertainty, antenna placement, sky/multipath conditions, warm-up, power mode, and timebase.
- **Validity/fault handling:** invalid, no-fix, stale, malformed, or silent GPS samples may be excluded from the accuracy calculation only if ADS/OBCC visibly flags or handles them as invalid. They shall not be accepted as valid positions.
- **v1.0 observation:** v1.0 passes only when evidence is taken at the ADS/OBCC observation point, not solely at the GPS receiver or intermediate UART stream.
- **Supporting constraints:** UART timeout and no-blocking/validity behavior are supporting fault-hardening evidence for this activity; separate rate/timing constraint activities remain responsible for primary verdicts on `5 Hz` and timeout limits.

## Statistical and fault-hardening viewpoints

- **Statistical significance:** minimum `n >= 30` matched valid samples per campaign. If claiming formal 95/95 compliance, the report must name the selected tolerance/confidence method and guard-band calculation. Repeated samples from one article/environment are screening evidence unless independence or population inference is justified.
- **Fault hardening:** no-fix, stale, malformed, silent UART/GPS, timeout, and recovery cases shall show that corrupt or unavailable GPS data are not silently accepted as valid.
- **Environmental viewpoint:** record ambient thermometer/hygrometer readings, sky visibility, multipath/shielding, antenna placement, warm-up, power condition, and any GNSS simulator scenario before repetitions begin.

## Required execution conditions

- Record selected ADS version/SSIV, copied source-view baseline, hardware revision, UUT identifier, firmware commit/build, logger configuration, operator, and equipment IDs/calibration status.
- Select the truth method before execution: GNSS simulator or surveyed/high-confidence reference receiver.
- Synchronize or correlate ADS and truth timestamps with the modeled timebase.
- Preserve raw ADS logs, raw truth/reference logs, validity/fault markers, environmental records, analysis scripts/settings, generated plots/tables, deviations, anomalies, waivers, and retest status.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-POS-5M/v0.1/`
- `../results/ADS-IVV-C-POS-5M/v0.2/`
- `../results/ADS-IVV-C-POS-5M/v0.3/` for the N/A record
- `../results/ADS-IVV-C-POS-5M/v1.0/`

Each report shall identify referenced model views/elements, selected version, as-tested configuration, truth source, actual conditions, raw evidence, analysis method, pass/fail or N/A rationale, deviations, anomalies, limitations, waivers, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.

## Assumptions and gaps

- The orchestrator selected all current ADS MBSE versions; no user disambiguation was requested.
- `ADS-CAP-GPS`, `ADS-FE-SILENT-SENSOR-FAIL`, and `ADS-FE-CORRUPT-MEASUREMENT` are planning trace placeholders because explicit Capella mission/capability/feared-event elements are not modeled in the source views.
- Exact truth equipment model, surveyed coordinates or simulator scenario, guard-band method, and 95/95 method are TBD before execution.
- ADS/OBCC validity/freshness field names and log schema are TBD before execution.
- `v0.3` remains N/A for this constraint unless behavior chains are later added to that baseline.
