# DPS-V10-A-001 — Component-exchange presence/intent analysis definition

- **SSIV / version:** DPS-v1.0 (confirmed by user for current detailed definitions).
- **IADT method:** Analysis.
- **IVV source category:** component exchange.
- **Model elements covered:** all six DPS v1.0 component exchanges listed in `../README.md` §3.3.
- **Traceability target:** inferred telemetry and command paths; feared events include wrong protocol, hidden substitute interface, stale bytes, corrupt accepted payload, lost UART/SPI exchange and duplicate/stale command.
- **References cited in diagrams:** P0 (`PM&SE/IVV.md`), R1-R3 and R8-R13 from `../references/INDEX.md`.
- **Expected report/evidence folder:** `DPS/MBSE/tests/results/DPS-V10-A-001/`.

## Baseline views copied

The unmodified DPS v1.0 Capella/D2 source views and rendered PNGs are copied under [`baseline/`](./baseline/) for traceability. The verification-specific analysis views in this folder extend the copied baseline with IVV analyst/reviewer actors, verification-only analysis record functions and pass/fail constraints.

## Verification-specific diagrams

| View | Purpose |
|---|---|
| [`DPS-V10-A-001_view1_component_exchange_analysis_context.d2`](./DPS-V10-A-001_view1_component_exchange_analysis_context.d2) | PV2 context showing all six modeled CEs, the verification-only CE Analysis Record LC, analyst/reviewer EAs and analysis constraints. |
| [`DPS-V10-A-001_view2_functional_allocation_analysis_context.d2`](./DPS-V10-A-001_view2_functional_allocation_analysis_context.d2) | PV3 allocation of analyst, reviewer, repository and verification-only evidence functions used to perform and control the analysis. |

Rendered PNGs are generated beside the D2 sources.

## Analysis pass/fail constraints

1. **Coverage:** 100% of modeled component exchanges are analyzed; no CE may be left as “not checked” without an explicit limitation in the report.
2. **Presence:** every modeled CE exists in the implementation evidence as an interface, software path, data structure, queue, protocol configuration, schematic/netlist connection or reviewed equivalent.
3. **Protocol/intent consistency:** implementation uses the modeled protocol or data interface intent. SPI exchanges shall not be silently implemented as UART/I2C or vice versa; Payload and Command exchanges shall preserve their modeled data semantics.
4. **Directionality:** data/control direction matches the modeled exchange, including Decoder fan-out to CSV Writer and Dashboard and Dashboard-to-Decoder command flow.
5. **Fault hardening:** analysis finds documented behavior for stale bytes, corrupt frames/payloads, lost UART/SPI exchanges, duplicate/stale commands and interface disconnection. Missing or ambiguous behavior is an analysis failure or limitation.
6. **Evidence baseline:** model baseline, schematic/netlist revision, firmware/source revision, PC software revision and any interface logs/configuration snippets are identified. Any mismatch is recorded as an anomaly/limitation.
7. **Statistics viewpoint:** statistical significance is not primary for this presence/intent analysis; the statistical basis is 100% checklist coverage. Any unresolved CE item prevents an unconditional pass.

## Component-exchange analysis checklist

| CE ID | Model exchange | Analysis viewpoint/rationale | Pass/fail constraint | Expected evidence |
|---|---|---|---|---|
| CE-01 | CanSat LoRa Transceiver → OBCC: SPI | Check that RFM96W/SX1276 radio-to-XIAO/OBCC implementation uses SPI semantics and supports receive/transmit/status paths implied by FC03/FC04. | SPI pins/configuration and direction intent present; chip select, clock/MOSI/MISO and interrupt/status handling are documented; no UART/I2C substitute; corrupt/no-frame status is detectable or logged. | OBCC PCB schematic/netlist, firmware SPI configuration, radio driver code, interface notes. |
| CE-02 | LoRa Forwarder → Ground LoRa Transceiver: SPI | Check that ground XIAO forwarder-to-radio implementation uses RFM96W/SX1276 SPI consistently with downlink/uplink chains. | SPI pins/configuration and direction intent present; chip select, clock/MOSI/MISO and interrupt/status handling documented; no UART/I2C substitute; radio not-ready/read errors detectable or logged. | Ground PCB schematic/netlist, forwarder firmware, radio driver configuration, logs/config snippets. |
| CE-03 | LoRa Forwarder → PC Decoder: UART | Check ground forwarder-to-PC path framing, baud/configuration and byte ownership across USB serial/UART bridge. | UART/USB-serial path exists and is unidirectional as modeled; baud/framing/message delimiter or packetization documented; stale bytes, corrupt frames and disconnects are rejected/logged. | Forwarder serial code, PC decoder serial code, baud/framing configuration, example logs. |
| CE-04 | PC Decoder → CSV Writer: Payload | Check decoded payload queue/interface from Decoder to CSV Writer. | Payload exchange exists with typed decoded payload plus timestamp/latency metadata as applicable; row count/order match accepted frames; malformed payloads are not written. | PC software source, queue/interface definition, CSV writer code, data schema. |
| CE-05 | PC Decoder → Dashboard: Payload | Check Decoder fan-out to Dashboard and consistency with CSV path. | Dashboard receives the same accepted payload semantics without starving CSV Writer; stale/invalid fields are handled; fan-out is explicit and not an unmodeled hidden interface. | PC software source, dashboard queue/interface code, data schema, UI update mapping. |
| CE-06 | Dashboard → PC Decoder: Command | Check command queue/interface from Dashboard to Decoder and onward to transceiver. | Command exchange exists in modeled direction; only valid state commands are accepted; duplicate/stale commands are rejected or controlled by cooldown policy; no bypass around Decoder. | Dashboard command code, Decoder command queue code, command schema, cooldown/validation evidence. |

## Constraint coverage disposition

- This activity directly covers component-exchange presence/intent requirements from the IVV minimum requirements.
- Constraints C05-C08 influence Payload/Command CE semantics but remain tested in their functional-chain/constraint activities; this analysis only checks that the relevant exchange paths exist and are semantically consistent.
- C01 range and C02 physical ground-PCB reuse are not component-exchange analysis targets and remain covered by their assigned activities.

## Evidence expected in report

The report in `tests/results/DPS-V10-A-001/` should reference these modeled diagrams and record: model baseline, implementation artifact versions, CE checklist result for each exchange, protocol/direction/data rationale, fault-hardening rationale, unresolved limitations, pass/fail decision, reviewer disposition, deviations, anomalies and waivers.
