# AMS-V02-BRINGUP-001 — Powered bring-up and I2C reachability

- **SSIV / development version:** AMS `v0.2` advancement gate from delivered PCB to `v1.0` integrated flight-readiness build.
- **IADT method:** Demonstration / Testing.
- **Traceability targets:** `AMS-v0.2-to-v1.0-readiness`, `AMS-UC-MeasureAtmosphere`, `AMS-UC-InitializePeripheral`, `AMS-FE-SensorBusFault`.
- **References cited in diagram titles:** IVV, AMS-R1 (BME280), AMS-R2 (I2C), AMS-R5 (statistics).
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-V02-BRINGUP-001/report.md`.
- **Scope boundary:** powered bring-up, current-limited 3V3/GND checks, I2C scan/read reachability, and readiness evidence before integration. Visual/manufacturing inspection of the delivered PCB remains `AMS-V02-PCB-001` and is not credited here.

## Baseline views copied

Untouched copies of the v0.2 physical baseline are in `baseline/`:

- `baseline/AMS_v0.2_view1_physical.d2`
- `baseline/AMS_v0.2_view1_physical.png`

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_V02_BRINGUP_001_view1_physical_powered_bringup_testbench.d2` | Physical powered-bring-up testbench with UUT, current-limited supply, DMM, fixture controller, logic analyzer, host logger, ESD fixture, ambient meter, and operator. |
| `AMS_V02_BRINGUP_001_view2_logical_i2c_bringup_testbench.d2` | VV-only logical/component-exchange view for fixture I2C stimulus, BME280 response, waveform/log evidence, and readiness record. |
| `AMS_V02_BRINGUP_001_view3_functional_allocation_bringup.d2` | Function allocation for test means, observed BME280 responder behavior, connector access, and readiness gate functions. |
| `AMS_V02_BRINGUP_001_view4_power_i2c_bringup_chain.d2` | Functional-chain sequence: safe setup, current-limited power, voltage checks, I2C scan, chip-ID/status/register read, waveform capture, logging, power-cycle, and repeat. |

Rendered PNGs with matching names are generated beside each D2 file.

## Model elements covered

- **Physical components:** `[PC] AMS PCB`, `[PC] BME280`, `[PC] Backplane Connector`.
- **Physical links:** `[PL] I2C + 3V3 traces`, `[PL] BME280 Footprint`, `[PL] Connector footprint`.
- **Component exchange / observed behavior:** VV-only fixture I2C stimulus/response through the modeled connector and trace path; BME280 address, ACK, chip ID, status/register response.
- **Functional allocation:** VV-only test functions allocated to operator, ESD fixture, bench supply, DMM, fixture controller, logic analyzer, host logger, ambient meter, QA witness, connector test access, and bring-up readiness record.
- **Functional chain/scenario:** powered bring-up and I2C reachability sequence in view 4.
- **Constraint context:** manufacturable/solderable PCB delivery is a precondition handled by `AMS-V02-PCB-001`; this activity verifies safe powered behavior and I2C continuity before v1.0 integration.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. Current-limited 3V3/GND power-up has no short, overcurrent/current-limit trip, reversed power, abnormal heating, smoke, smell, visible damage, or operator safety concern.
2. DMM confirms correct polarity and `3.3 V ±5%` at the Backplane Connector and BME280 pads before I2C scanning is credited.
3. The fixture enters through the modeled Backplane Connector and PCB `[PL] I2C + 3V3 traces`; any direct sensor clip, fixture-only jumper, or unmodeled bypass fails the attempt.
4. I2C scan finds the BME280 at the expected build-record address (`0x76` or `0x77`), and chip ID/status/register evidence is logged. Chip ID pass value is `0x60`.
5. Logic analyzer evidence shows nominal 3V3 I2C signaling with START/STOP activity, ACK for the BME280 transaction, and no stuck SDA/SCL.
6. At least `3/3` complete power-cycle/read attempts pass and are logged.
7. Any no-response, wrong address, NACK-only behavior, overcurrent, reversed power, stuck SDA/SCL, damaged UUT, uncontrolled fixture configuration, missing evidence, or bypass fails unless controlled as a deviation in the report.

## Statistical and fault-hardening viewpoints

- **Statistical basis:** `3/3` passing cycles are required as a bring-up demonstration for one v0.2 PCB article. This is not a reliability claim and does not substitute for later v1.0 acceptance statistics.
- **Fault-hardening viewpoint:** fail-fast handling for overcurrent, reversed power, no-response/wrong-address, NACK-only behavior, stuck SDA/SCL, unmodeled bypass, and uncontrolled fixture configuration.
- **Environmental/safety viewpoint:** ESD-safe fixture and ambient lab temperature/humidity record are required before repetitions begin.

## Assumptions recorded

- The exact BME280 I2C address is not specified in the v0.2 physical view; the activity accepts the expected address from build/schematic evidence (`0x76` or `0x77`) and requires it to be recorded.
- Current limit threshold is fixture-specific and must be recorded in the report; pass/fail is based on no current-limit trip/overcurrent and correct 3V3 measurements.
- Manufacturing/visual acceptance of footprints/traces is assumed to be performed by `AMS-V02-PCB-001`; this activity does not duplicate that inspection.
