# DPS-V10-A-002 — Functional allocation analysis definition

- **SSIV / version:** DPS-v1.0 (confirmed by user for current detailed definitions).
- **IADT method:** Analysis.
- **IVV source category:** functional allocation.
- **Model elements covered:** all logical components and function allocations listed in `../README.md` §3.4, plus allocation-boundary consistency against the component exchanges in §3.3.
- **Traceability target:** correct responsibility partition and shared-load behavior; inferred feared events include missing function, foreign function in the wrong LC, command bypass, unbounded queue growth, stale command path and shared CanSat processing starvation.
- **References cited in diagrams:** P0 (`PM&SE/IVV.md`), R1-R5 and R8-R13 from `../references/INDEX.md`.
- **Expected report/evidence folder:** `DPS/MBSE/tests/results/DPS-V10-A-002/`.

## Baseline views copied

The unmodified DPS v1.0 Capella/D2 source views and rendered PNGs are copied under [`baseline/`](./baseline/) for traceability. The verification-specific analysis views in this folder extend the copied baseline with IVV analyst/reviewer actors, evidence/tool actors, verification-only allocation-analysis record functions and pass/fail constraints.

## Verification-specific diagrams

| View | Purpose |
|---|---|
| [`DPS-V10-A-002_view1_functional_allocation_analysis_context.d2`](./DPS-V10-A-002_view1_functional_allocation_analysis_context.d2) | PV3 context showing all DPS v1.0 LC/function allocations, analyst/reviewer/repository/trace functions, the verification-only Allocation Analysis Record LC, and analysis constraints. |
| [`DPS-V10-A-002_view2_allocation_boundary_analysis_context.d2`](./DPS-V10-A-002_view2_allocation_boundary_analysis_context.d2) | PV2 context showing LC boundaries and modeled CEs used to check that cross-LC functional responsibility is allocated through the correct components. |

Rendered PNGs are generated beside the D2 sources.

## Analysis pass/fail constraints

1. **Coverage:** 100% of logical components and allocated functions in `../README.md` §3.4 are analyzed. No LC/function pair may be left unchecked without a recorded limitation.
2. **Intended allocation:** every modeled DPS-owned function is implemented or deliberately dispositioned in the LC to which the v1.0 model allocates it.
3. **No foreign function:** no LC implements a DPS-owned function allocated to another LC unless the discrepancy is explicitly modeled, justified and dispositioned. Context LCs ESS/ADS/PDM/AMS shall remain free of DPS-owned functions.
4. **Boundary-flow consistency:** when functional responsibility crosses LC boundaries, the implementation uses the modeled CE/interface path or a documented local queue/protocol consistent with the model. Bypasses such as Dashboard-to-radio or Forwarder-to-CSV are failures unless waived.
5. **Shared-load/starvation:** ESS/ADS/PDM/AMS shared XIAO workload evidence shall not starve OBCC radio/command handling at the v1.0 2 s cadence. Missing trace/scheduling evidence makes the analysis limited, not an unconditional pass.
6. **Fault hardening:** analysis addresses missing functions, duplicate/foreign functions, direct command bypass, queue overload/backlog, stale command handling, init/error path ownership and shared-load starvation.
7. **Statistics viewpoint:** statistical inference is not primary for this allocation analysis. The statistical basis is 100% allocation-checklist coverage plus any cited runtime trace coverage; unresolved allocation items or missing shared-load evidence prevent an unconditional pass.
8. **Evidence baseline:** model baseline, implementation commit/build revision, firmware/software modules, static mapping evidence, trace/log identifiers and assumptions are identified in the report.

## LC/function allocation checklist

| LC ID | Logical component | Modeled allocated functions | Analysis viewpoint/rationale | Pass/fail constraint | Expected evidence |
|---|---|---|---|---|---|
| LC-01 | CanSat LoRa Transceiver | Receive incoming data; Transmit outgoing data | Radio LC owns raw LoRa radio RX/TX behavior. | Radio RX/TX implemented in radio driver/abstraction; no OBCC command parsing, CSV, dashboard or forwarding logic assigned here. | CanSat radio driver/source mapping, board/radio configuration. |
| LC-02 | OBCC | Receive LoRa RX Interrupt; Send LoRa packet; Read command | OBCC owns CanSat-side radio interrupt response, packet send request and command extraction. | These functions are in OBCC firmware/module; no ground forwarder/PC UI behavior is assigned to OBCC; command read path is not bypassed. | OBCC firmware modules, interrupt/callback mapping, command handler mapping. |
| LC-03 | ESS Processing | No DPS-owned functions | Context LC present on shared XIAO; ensure DPS model does not hide ESS ownership. | No DPS-owned receive/transmit/forward/decode/store/UI function is implemented in ESS; ESS execution does not starve OBCC DPS handling. | Code ownership map, scheduler/task map, shared-load trace. |
| LC-04 | ADS Processing | No DPS-owned functions | Context LC present on shared XIAO; ensure no foreign DPS allocation and no starvation. | Same no-DPS-owned-function and no-starvation criteria as LC-03. | Code ownership map, scheduler/task map, shared-load trace. |
| LC-05 | PDM Processing | No DPS-owned functions | Context LC present on shared XIAO; ensure no foreign DPS allocation and no starvation. | Same no-DPS-owned-function and no-starvation criteria as LC-03. | Code ownership map, scheduler/task map, shared-load trace. |
| LC-06 | AMS Processing | No DPS-owned functions | Context LC present on shared XIAO; ensure no foreign DPS allocation and no starvation. | Same no-DPS-owned-function and no-starvation criteria as LC-03. | Code ownership map, scheduler/task map, shared-load trace. |
| LC-07 | Ground LoRa Transceiver | Store incoming data; Transmit outgoing data | Ground radio LC owns raw LoRa frame storage/transmission and not PC decoding/UI. | Raw LoRa RX/TX behavior allocated to radio driver/abstraction; decoder, dashboard and CSV logic not implemented here. | Ground radio driver/source mapping, firmware configuration. |
| LC-08 | LoRa Forwarder | Init Serial0 with interrupts; Init SPI with interrupts; Log error; Receive LoRa RX Interrupt; Read payload; Forward to PC; Store incoming UART data; Receive Serial0 RX Interrupt; Read command; Generate frame; Write to LoRa Radio | Ground microcontroller owns radio/serial bridging, init/error handling and command frame generation. | All 11 functions map to forwarder firmware; no PC decode/CSV/dashboard behavior is embedded; init/error path has an owner; UART and SPI responsibilities do not bypass the Decoder. | Forwarder firmware modules, serial/SPI config, error logging code, command frame code. |
| LC-09 | Decoder | Check if data is available; Read and decode frame; Push to payload queue; Get RX timestamp; Calculate latency; Forward to transceiver; Consume command queue | PC Decoder owns serial intake, decode/timestamp/latency, payload fan-out source and command forwarding. | All seven functions map to Decoder module; CSV writer does not decode frames; Dashboard does not bypass Decoder for command forwarding; malformed/stale data handling owner is defined. | PC decoder source, serial interface code, queue definitions, command consumer code. |
| LC-10 | CSV Writer | Consume payload queue; Append to CSV | CSV Writer owns storage-side queue consumption and CSV append only. | CSV Writer does not decode raw UART frames or update dashboard plots; CSV append is fed only by accepted payload queue. | CSV writer source, data schema, queue interface evidence. |
| LC-11 | Dashboard | Consume payload queue; Update orientation 3D plot; Update relative-humidity 2D plot; Push to command queue; Update temperature 2D plot; Update altitude 2D plot; Catch State toggle; Update latency alert; Disable toggle; Enable toggle; Cooldown; Create plots | Dashboard owns visualization, browser UI and state-toggle enqueue/debounce behavior. | All 12 UI functions map to Dashboard module; Dashboard does not directly write radio/serial; relative-humidity model/telemetry mismatch is recorded as a limitation or requirement disposition. | Dashboard source, UI routing, plot/alert/toggle code, command queue interface. |
| LC-12 | USB Power | Provide power | USB Power owns the power-provision function only. | Power provision is modeled/implemented separately from UART data responsibility; no data-processing function is assigned to USB Power. | Hardware/power interface notes, schematic or integration evidence. |

## Allocation-boundary checklist

| Boundary | Related modeled CEs | Allocation-analysis rationale | Pass/fail constraint |
|---|---|---|---|
| CanSat radio ↔ OBCC | CE-01 SPI | Raw radio receive/transmit belongs to CanSat LoRa Transceiver; interrupt, send request and command read belong to OBCC. | Implementation keeps radio-driver and OBCC command responsibilities separated and connected through SPI/driver boundary evidence. |
| Ground forwarder ↔ ground radio | CE-02 SPI | Forwarder owns SPI init, payload read/write and frame generation; ground radio LC owns raw frame store/transmit. | No PC decoder/UI logic on radio LC; no bypass around forwarder for radio read/write. |
| Ground forwarder ↔ Decoder | CE-03 UART | Forwarder owns serial output/input bridging; Decoder owns PC-side availability check, read/decode/timestamp/latency. | Raw UART bytes enter Decoder before CSV/Dashboard; direct Forwarder-to-CSV/Dashboard path is absent or dispositioned. |
| Decoder ↔ CSV Writer | CE-04 Payload | Decoder owns accepted timestamped payload production; CSV Writer owns consuming and appending. | CSV Writer only stores accepted decoded payloads and does not own frame decode or timestamp calculation. |
| Decoder ↔ Dashboard | CE-05 Payload | Decoder owns accepted timestamped payload source; Dashboard owns UI consumption and plotting. | Dashboard receives accepted payload semantics from Decoder and does not own raw serial decode. |
| Dashboard ↔ Decoder | CE-06 Command | Dashboard owns user toggle/cooldown and command queue push; Decoder owns command consumption and forwarding to transceiver. | Dashboard does not directly write the UART/radio path; duplicate/stale command handling owner is assigned. |

## Constraint coverage disposition

- This activity directly covers the IVV minimum requirement for **functional allocation to logical components**.
- C03 concurrent execution influences the shared-load/starvation review but remains tested in its dedicated concurrency/load activity.
- C05-C08 UI/storage constraints are checked here only for correct ownership; their behavioral pass/fail criteria remain in the relevant testing/demonstration activities.
- C01 range and C02 physical PCB reuse are not allocation-analysis targets and remain covered by their assigned activities.

## Evidence expected in report

The report in `tests/results/DPS-V10-A-002/` should reference these modeled diagrams and record: model baseline, implementation artifact versions, LC/function checklist result for every row, static code/module mapping, CE/boundary-flow rationale, representative runtime trace summary for shared-load/starvation, unresolved allocation discrepancies, relative-humidity model/telemetry disposition, pass/fail decision, reviewer disposition, deviations, anomalies, waivers and limitations.
