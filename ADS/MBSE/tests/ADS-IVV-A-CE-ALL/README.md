# ADS-IVV-A-CE-ALL — all-version component exchange analysis definition

**IADT method:** Analysis.

**IVV source category:** component exchange.

**Selected SSIV/development scope:** all ADS development versions currently present in the MBSE corpus: `v0.1`, `v0.2`, `v0.3`, and `v1.0`.

**Traceability targets:** `ADS-CAP-GPS`, `ADS-CAP-IMU`, `ADS-CAP-ATT`, `ADS-CAP-INIT`, `ADS-CAP-DELIVERY`, `ADS-CAP-PCB` for v0.3 N/A rationale, and feared events `ADS-FE-SILENT-SENSOR-FAIL`, `ADS-FE-STUCK-LOOP`, `ADS-FE-CORRUPT-MEASUREMENT`. Physical-link evidence may also reference `ADS-FE-OPEN-SHORT-LINK`.

**References cited in diagrams:** IVV minimum CE analysis rule, NASA-SE, GPS/UBX references, ICM20948/I2C references, SW/statistics references, workmanship references for physical path context, and the ADS MBSE IVV plan `../README.md`.

## Source-view copies

All Capella/D2 views for the selected all-version scope were copied under `source_views/`:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_A_CE_ALL_view1_logical_ce_inventory.d2/png` | PV2 inventory of modeled CEs across versions and analysis constraints; includes explicit v0.3 CE N/A rationale. |
| `definition_views/ADS_IVV_A_CE_ALL_view2_logical_analysis_interfaces.d2/png` | PV2 analysis record interfaces among IVV analyst, firmware/OBCC owner, quality/configuration authority, and selected-version CE analysis records. |
| `definition_views/ADS_IVV_A_CE_ALL_view3_functional_allocation.d2/png` | PV3 allocation of verification-only functions to the selected-version analysis interface, IVV analyst, firmware/static-analysis tools, runtime evidence tools, reference corpus, and quality authority. |
| `definition_views/ADS_IVV_A_CE_ALL_view4_analysis_sequence.d2/png` | Functional-chain style analysis sequence used as the modeled analysis procedure; IADT method remains Analysis. |

## Version CE coverage

| Version | Modeled component exchanges | Pass/fail constraints |
|---|---|---|
| `v0.1` | One CE: `[CE] UART`, `[LC] ADS GPS Sensing` → `[LC] Loop`. Supporting FEs in GPS chain show UART request/response behavior. | Pass if the implemented interface is UART between the modeled endpoints, carries model-consistent GPS payload/request-response semantics, has bounded UART read timeout behavior where modeled, and does not accept stale/corrupt GPS data as valid. Fail on missing CE evidence, wrong protocol, wrong endpoints, unbounded blocking, absent timeout/error state, or unresolved directionality/semantics mismatch. |
| `v0.2` | Two CEs: `[CE] UART`, `[LC] ADS GPS Sensing` → `[LC] Loop`; `[CE] I2C`, `[LC] ADS Kinematic Sensing` → `[LC] Loop`. | Pass if both modeled CEs are implemented with modeled protocols/endpoints, support the relevant chain FEs, preserve validity/freshness/error semantics, and do not violate no-blocking/timing constraints. Fail on missing CE, wrong endpoint, wrong protocol, stale/corrupt data accepted as valid, missing UART timeout, or unbounded I2C fault behavior. v0.2 I2C timeout is recorded as a modeling gap. |
| `v0.3` | No modeled CEs. The only source view is a PV1 physical PCB delivery view; UART/I2C are physical traces, not component exchanges. | Pass/N/A if all v0.3 D2 views are reviewed, zero `[CE]` / `class: ce` exchanges and no LC endpoints exist, and the PCB-only delivery rationale is recorded. Fail if any source view is omitted, a CE is found but not inventoried, or physical traces are credited as implemented CEs. |
| `v1.0` | Four CEs: `[CE] UART`, `[LC] ADS GPS Sensing` → `[LC] ADS Processing`; `[CE] I2C`, `[LC] ADS Kinematic Sensing` → `[LC] ADS Processing`; `[CE] Pointers` and `[CE] Returns`, `[LC] ADS Processing` → `[LC] OBCC`. | Pass if every modeled CE is present and implemented consistently with endpoint LCs, physical/software path, protocol/interface type, timeout/no-blocking constraints, and validity/freshness/error semantics. Fail on missing CE evidence, wrong protocol/interface, wrong endpoint, unbounded blocking, unhandled timeout/fault, unsafe pointer/return lifetime or ownership semantics, or unreviewed CE. |

## Viewpoints

- **Statistical significance:** complete enumeration, not sampling. CE presence/consistency analysis covers 100% of selected-version CEs. Runtime UART/I2C/log samples are supporting evidence only unless a separate chain/constraint test defines statistical acceptance criteria.
- **Fault hardening:** malformed/silent/no-fix GPS UART, wrong baud, swapped TX/RX, partial GPS payloads, stale lat/lon cache, I2C NACK, stuck bus, wrong address, swapped SDA/SCL, partial IMU reads, loop blocking, stale/null/dangling pointers, invalid returns, and OBCC consuming corrupt ADS data.
- **Constraint interaction:** no blocking except I2C/UART, UART timeout `<=5 ms`, v1.0 I2C timeout `<=5 ms`, Variable Getter semantics, and Process/Calculate `<5 ms` are treated as CE-consistency concerns where the CE implementation can violate or satisfy them. v0.2 I2C timeout absence is recorded as a modeling gap requiring follow-up.
- **Configuration control:** report identifies selected ADS version, source-view copy, hardware/software baseline, firmware commit, schematic/netlist or code references used, runtime captures/logs if used, analyst/reviewer, deviations, waivers, and retest status.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-A-CE-ALL/v0.1/`
- `../results/ADS-IVV-A-CE-ALL/v0.2/`
- `../results/ADS-IVV-A-CE-ALL/v0.3/`
- `../results/ADS-IVV-A-CE-ALL/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-analyzed implementation/configuration, evidence sources, actual deviations, anomalies, waivers, pass/fail or N/A rationale, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.
