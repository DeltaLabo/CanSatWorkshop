# AMS-VV-PL-001 — Physical link presence/absence inspection

- **SSIV / development version:** AMS v1.0 final acceptance.
- **IADT method:** Inspection.
- **Traceability:** AMS physical/electrical integration readiness; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` / intermittent interconnect.
- **References cited in diagram titles:** IVV, AMS-R2 (I2C physical/electrical intent), AMS-R6 (CanSat build/integration context).
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-VV-PL-001/`.
- **Scope boundary:** physical link presence and integrity between modeled endpoints. PC presence/identity is covered by `AMS-VV-PC-001`; component-exchange protocol/timing behavior is covered by CE/constraint activities.

## Baseline views copied

Untouched baseline copies of all AMS v1.0 D2/PNG views are in `baseline/`.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_PL_001_view1_physical_link_inspection_testbench.d2` | Physical-link inspection setup with ESD fixture, optical inspection, continuity/probe means, retention gauge, and PL-target constraints. |
| `AMS_VV_PL_001_view3_functional_allocation_inspection.d2` | Inspection operator, QA witness, equipment, evidence repository functions, and pass/fail constraints. |

No functional-chain view is created for this activity because the IADT method is **Inspection**; the inspection targets and pass/fail constraints are defined directly on the relevant physical links / inspection functions in the test-definition views.

## Physical links covered

The inspection is a 100% census of the 14 modeled UUT physical links:

1. AMS PCB ↔ AMS Module — `[PL] Screws`
2. OBCC PCB ↔ OBCC Module — `[PL] Screws`
3. AMS Module ↔ Backplane PCB — `[PL] Backplane Fixture`
4. OBCC Module ↔ Backplane PCB — `[PL] Backplane Fixture`
5. BME280 ↔ AMS PCB — `[PL] BME280 Footprint`
6. AMS-side Backplane Connector ↔ AMS PCB — `[PL] Connector footprint`
7. BME280 ↔ AMS-side Backplane Connector — `[PL] I2C + 3V3 traces`
8. AMS-side Backplane Connector ↔ 2mm 2x6 AMS Headers — `[PL] Parallel Connector`
9. XIAO ESP32-S3 ↔ OBCC PCB — `[PL] XIAO Footprint`
10. OBCC-side Backplane Connector ↔ OBCC PCB — `[PL] Connector footprint`
11. XIAO ESP32-S3 ↔ OBCC-side Backplane Connector — `[PL] I2C + 3V3 traces`
12. OBCC-side Backplane Connector ↔ 2mm 2x6 OBCC Headers — `[PL] Parallel Cable`
13. 2mm 2x6 AMS Headers ↔ Spine — `[PL] Footprint`
14. 2mm 2x6 OBCC Headers ↔ Spine — `[PL] Footprint`

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. The inspected article is the AMS v1.0 final-acceptance integrated article, not a protoflight, partial build, or disconnected subassembly.
2. Each of the 14 target PLs has an individual checklist entry and supporting visual, retention, continuity, or build-record evidence as applicable.
3. Each target PL is present, connects exactly the modeled endpoints, and has no unapproved reroute, bypass, temporary jumper, repair, or substitution.
4. Mechanical-retention PLs pass only if all modeled screws/fixtures are present and secure with no missing hardware, loose joint, cracked mount, excessive play, or failed retention check.
5. Footprint/interconnect PLs pass only if solder/mechanical contact is present and acceptable; connectors/cable are fully seated and correctly oriented; no bent pin, solder bridge, lifted pad, damage, contamination, or FOD affects the link.
6. Electrical I2C + 3V3 trace PLs pass only if modeled conductors are continuous endpoint-to-endpoint and no open circuit, short, or probe-induced damage is observed.
7. Physical-link evidence must use full endpoint paths to disambiguate duplicate labels such as `[PL] Screws`, `[PL] Footprint`, `[PL] Connector footprint`, and duplicate `[PC] Backplane Connector` endpoints.
8. PC presence/identity is not credited by this activity; missing endpoint PCs are recorded as dependencies/anomalies against `AMS-VV-PC-001`.
9. CE/I2C protocol, timeout, and data behavior are not credited by this activity.

## Statistical and fault-hardening viewpoints

- Statistical basis: 100% census inspection, `14/14` target PLs per final-acceptance article; no sampling or fleet reliability claim.
- Fault-hardening viewpoint: missing/loose link, wrong endpoint/route/cable, open, short, intermittent contact, connector/cable seating error, solder bridge, lifted pad, bent pin, FOD/contamination, unapproved bypass, and probe-induced damage.
