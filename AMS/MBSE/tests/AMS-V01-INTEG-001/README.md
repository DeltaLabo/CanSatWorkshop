# AMS-V01-INTEG-001 — v0.1 breadboard to v0.2 PCB readiness inspection

- **SSIV / development version:** AMS `v0.1`, advancement gate from breadboard/subsystem delivery to `v0.2` PCB delivery.
- **IADT method:** Inspection with supporting Analysis.
- **Traceability:** `AMS-v0.1-to-v0.2-readiness`; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault`.
- **References cited in diagram titles:** IVV, AMS-R1 (BME280), AMS-R2 (I2C), AMS-R6 (CanSat build environment).
- **Expected report path:** `AMS/MBSE/tests/results/AMS-V01-INTEG-001/report.md`.

## Scope

This activity verifies that the v0.1 breadboard is complete and consistent enough to start the v0.2 PCB implementation. It covers:

- physical components/actors: `[PC] BME280`, `[PC] XIAO ESP32`, external `[EA] PC`;
- physical links: `[PL] I2C Cables`, `[PL] 3V3`, `[PL] GND`, `[PL] USB-C Cable`;
- logical components: `[LC] AMS Sensing`, `[LC] AMS Processing`;
- target component exchange: `[CE] I2C`;
- all v0.1 allocated functions and the model constraints visible in the baseline functional allocation and chain views.

Performance, timing, and accuracy constraints are reviewed here for coverage and non-contradiction only against the fixed source baseline (`±1 hPa`, `±0.5 °C` over `10–40 °C`, altitude `≤10 m` using `13 Pa/m = 130 Pa`, temperature response `≤60 s`, I2C timeout `≤5 ms`, process/calculate `<5 ms`, and no unbounded blocking). Full statistical, temperature-response, and I2C fault-timeout closure remains assigned to the explicit test definitions or derivation paths (`AMS-V01-FC-001`, `AMS-V10-TEMP-RESPONSE-60S`, and `AMS-VV-CON-003` as applicable).

## Baseline views copied

Untouched copies of all AMS v0.1 `.d2` and `.png` views are in `baseline/`.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_V01_INTEG_001_view1_physical_inspection_testbench.d2` | Physical inspection testbench with test operator, ESD bench, bench power, DMM/continuity meter, host PC/serial terminal, I2C scanner/logic analyzer, camera/checklist station, target PLs, and inspection constraints. |
| `AMS_V01_INTEG_001_view2_logical_ce_analysis.d2` | Logical/component-exchange analysis view for the target `[CE] I2C`, VV-only readiness-analysis record, evidence actors, and CE/allocation pass/fail constraints. |
| `AMS_V01_INTEG_001_view3_functional_allocation_readiness_analysis.d2` | Functional allocation/readiness analysis view with UUT functions, human/equipment/repository review functions, existing constraints, and pass/fail constraints for PC/PL/CE/allocation coverage. |

Rendered `.png` files with matching names are generated beside each `.d2` file.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. BME280, XIAO ESP32, and host PC/serial terminal are present, identifiable, correct for v0.1, undamaged, and not substituted without waiver/model update.
2. I2C SDA/SCL, 3V3, and GND wiring connects the modeled BME280/XIAO endpoints with correct pin identity, polarity, and documented route.
3. No open conductor, short, reversed SDA/SCL, reversed 3V3/GND, loose jumper, intermittent contact, or unaudited bypass is present.
4. USB-C serial link to the host PC is present and can provide init and measurement log evidence.
5. `[CE] I2C` implementation is consistent with modeled endpoints, protocol, direction/intent, XIAO requester/master role, BME280 addressed-responder role, and no UART/SPI/GPIO/proxy substitute.
6. All v0.1 functions remain allocated to `[LC] AMS Sensing` or `[LC] AMS Processing` as modeled; no foreign sensing, processing, collection, or serial function is allocated to the wrong LC.
7. Breadboard wiring, evidence, and analysis are sufficiently unambiguous to translate I2C, 3V3, GND, and USB links into v0.2 PCB traces/connectors.
8. Constraint-status evidence records the fixed v0.1 source limits and does not claim full accuracy, altitude, temperature-response, or fault-timeout closure without the explicit downstream derivation path.
9. Inspection environment is ESD-controlled; breadboard is strain-free; bench power is current-limited; continuity checks are power-off unless scan/log capture is active.

## Statistical and fault-hardening viewpoints

- **Statistical significance:** 100% census review of the v0.1 readiness items: 3 PCs/actors (`BME280`, `XIAO ESP32`, host `PC`), 4 PLs, 1 CE, 2 LCs, and all modeled v0.1 allocated functions. No sampling or fleet reliability claim is made.
- **Fault hardening:** explicit failure modes include wrong item, wrong pin, open/short/reversal, intermittent/loose jumper, wrong I2C protocol/role/address, missing timeout/non-blocking policy evidence, unmodeled proxy/bypass, and insufficient PCB-conversion evidence.

## Reporting

The execution report should reference these model-defined views, identify the actual breadboard configuration inspected, record checklist/photo/meter/serial/I2C-scan evidence, document anomalies or waivers, and conclude pass/fail for the v0.1-to-v0.2 advancement gate.
