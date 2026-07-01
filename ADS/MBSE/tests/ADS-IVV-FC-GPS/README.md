# ADS-IVV-FC-GPS — GPS functional-chain verification definition

**IADT method:** Testing with supporting Analysis.

**IVV source category:** functional chain / scenario and linked constraints.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. GPS functional-chain execution applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is a PCB-delivery N/A branch because no logical components, component exchanges, allocations, or functional chains are modeled.

**Traceability targets:** `ADS-CAP-GPS`, constraint `Accuracy < 5 m`, constraint `At 5 Hz` for `v0.1`/`v0.2` only, and feared events `ADS-FE-SILENT-SENSOR-FAIL`, `ADS-FE-STUCK-LOOP`, `ADS-FE-CORRUPT-MEASUREMENT`. The `v0.3` N/A rationale may also reference `ADS-CAP-PCB`, `ADS-CAP-DELIVERY`, and `ADS-FE-OPEN-SHORT-LINK`.

**References cited in diagrams:** IVV, NASA-SE, GPS/UBX, SW/statistics references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

## Source-view copies

All D2 views for the selected ADS versions were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used only for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_GPS_view1_source_chain_inventory.d2/png` | GPS functional-chain inventory for v0.1, v0.2, and v1.0, plus v0.3 N/A rationale and traceability. |
| `definition_views/ADS_IVV_FC_GPS_view2_physical_test_setup.d2/png` | Physical GPS test setup, including selected ADS UUT, human test conductor, GPS truth/stimulus source, fault injector, serial/OBCC loggers, power supply, temporary PLs/CEs, pass/fail, fault, and environment constraints. |
| `definition_views/ADS_IVV_FC_GPS_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to the selected ADS version, IVV conductor, GNSS truth source, data logger, statistical analysis tool, and quality/configuration authority. |
| `definition_views/ADS_IVV_FC_GPS_view4_test_chain_sequence.d2/png` | Functional-chain style verification sequence for nominal GPS accuracy/rate testing and no-fix/malformed/silent/stale GPS fault cases. |
| `definition_views/ADS_IVV_FC_GPS_view5_results_traceability_interfaces.d2/png` | Results and traceability interfaces for evidence, analysis, model targets, references, deviations, waivers, limitations, and retest status. |

## Version coverage and pass/fail rules

| Version | GPS-chain coverage | Pass/fail constraints |
|---|---|---|
| `v0.1` | GPS position chain: Measure longitude, Measure latitude, Send payload, Read and store lat/lon, Get lat, Get lon, Collect measurements. UART GPS payload and Serial logging are supporting evidence paths. | Pass if valid GPS data propagate through the modeled functions, at least 30 matched valid ADS/truth samples are analyzed, the accepted horizontal-error criterion including truth/instrument uncertainty or a 95/95 bound where claimed is `<5 m`, the modeled `At 5 Hz` rule is met for collection timestamps/gaps, and no-fix/malformed/silent/stale GPS data are not accepted as valid. Fail on missing chain evidence, position bound `>=5 m`, rate violation, invalid/stale data accepted as valid, unexpected blocking, or unreported deviations. |
| `v0.2` | Same GPS chain as v0.1, in the v0.2 model with GPS, IMU, Setup, Loop, and PC monitor context. IMU chains are out of GPS scope except as loop-interference/fault observations. | Same as v0.1: valid data propagation, `>=30` matched valid samples, accepted `<5 m` criterion, modeled `At 5 Hz` rule, and fault-hardening behavior. Also record whether concurrent IMU/Loop activity affects GPS collection timing or validity. |
| `v0.3` | No GPS functional chain is modeled. Source package is a PV1-only PCB delivery model with physical GPS/IMU/backplane elements and UART/I2C/3V3 traces. | Pass/N/A if 1/1 v0.3 source view is reviewed, no GPS LC/CE/allocation/functional-chain behavior exists, and physical UART traces are not credited as functional-chain behavior. Fail if behavior is claimed from v0.3 without a modeled logical/functional chain. |
| `v1.0` | GPS position chain: Measure longitude, Measure latitude, Send payload, Read and store lat/lon, Get lat, Get lon, Collect measurements. GPS data flow through ADS Processing and are delivered to OBCC through related Pointers/Returns interfaces. | Pass if valid GPS data propagate through the modeled chain to the ADS/OBCC observation point, `>=30` matched valid ADS/truth samples are analyzed, the accepted `<5 m` criterion passes, and no-fix/malformed/silent/stale GPS data are not accepted as valid by ADS Processing or OBCC. No ADS `5 Hz` pass/fail is applied unless a separate v1.0 rate constraint is added; report observed rate as information. |

## Required execution conditions

- Select and record ADS version, source-model package, hardware revision, firmware commit/build, UUT serial/identifier, and data-logging configuration.
- Select the GPS truth method before execution: GNSS simulator or surveyed open-sky reference receiver. Record truth location/scenario, timebase, uncertainty, antenna placement, sky/multipath/shielding conditions, ambient temperature/humidity, warm-up, power mode, and calibration status.
- Collect and preserve raw ADS GPS logs, raw truth/reference logs, timestamps, fault-injection markers, analysis scripts/settings, and any OBCC logs used for v1.0 delivery evidence.
- Minimum nominal accuracy evidence is `>=30` matched valid ADS/truth samples per campaign. If a formal 95/95 claim is made, record the selected tolerance/confidence method and uncertainty guard band.
- For `v0.1`/`v0.2`, record timing/rate/gap statistics against the modeled `At 5 Hz` constraint. The exact accepted timing tolerance must be fixed before execution; if it is not fixed, report the rate verdict as blocked/limited rather than silently passing.
- Execute or disposition fault-hardening cases: no-fix, malformed payload, silent GPS/UART timeout, stale position, and recovery. Invalid/no-fix samples shall be excluded from accuracy calculations only if the ADS marks or handles them as invalid; they shall not be accepted as valid positions.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-GPS/v0.1/`
- `../results/ADS-IVV-FC-GPS/v0.2/`
- `../results/ADS-IVV-FC-GPS/v0.3/`
- `../results/ADS-IVV-FC-GPS/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested configuration, GPS truth method, raw evidence, analysis settings, actual environmental conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.
