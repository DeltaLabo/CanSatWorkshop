# AMS-V02-PCB-001 — v0.2 PCB delivery/manufacturability inspection

- **SSIV / development gate:** AMS `v0.2` PCB delivery advancing to the `v1.0` integrated flight-readiness build.
- **IADT method:** Inspection with supporting Analysis.
- **Purpose:** verify before powered bring-up/integration that the delivered AMS PCB contains the modeled physical components, footprints, trace/link implementation, connector interface, and manufacturability evidence.
- **Traceability targets:** `AMS-v0.2-to-v1.0-readiness`, `AMS-UC-MeasureAtmosphere`, `AMS-FE-BadManufacturing`, `AMS-FE-SensorBusFault`.
- **References cited in diagram titles:** IVV, AMS-R1 (BME280), AMS-R2 (I2C), AMS v0.2 PA baseline, fabrication/rework traveler.
- **Expected report path:** `AMS/MBSE/tests/results/AMS-V02-PCB-001/report.md`.
- **Scope boundary:** unpowered visual/records/fit/continuity-support inspection only. Powered 3V3 application, I2C address scan, BME280 chip-ID/status read, logic-analyzer ACK evidence, and power-cycle repetition are explicitly reserved for `AMS-V02-BRINGUP-001`.

## Baseline views copied

Untouched copies of the AMS v0.2 baseline physical view are in `baseline/`:

- `baseline/AMS_v0.2_view1_physical.d2`
- `baseline/AMS_v0.2_view1_physical.png`

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_V02_PCB_001_view1_physical_inspection_testbench.d2` | Physical inspection testbench with the v0.2 PCB, BME280, connector, modeled PLs, and external inspection equipment/records actors. |
| `AMS_V02_PCB_001_view3_functional_allocation_inspection_analysis.d2` | Verification-only functions allocated to inspector, QA/manufacturing reviewer, microscope/camera, connector gauge, DMM, ESD fixture, and evidence repository. |
| `AMS_V02_PCB_001_view4_manufacturability_physical_link_analysis_chain.d2` | Supporting analysis chain for Carvera CNC manufacturability, soldering evidence, footprint correctness, trace/pad continuity support, connector fit, waivers, and readiness classification. |

Rendered PNGs with matching names are generated beside each D2 file.

## Model coverage

This activity is a 100% census inspection/analysis of all explicit v0.2 physical-model targets:

- Physical system: `[System] AMS v0.2 PCB Delivery`.
- Physical components: `[PC] AMS PCB`, `[PC] BME280`, `[PC] Backplane Connector`.
- Physical links: `[PL] BME280 Footprint`, `[PL] Connector footprint`, `[PL] I2C + 3V3 traces`.
- Constraint: `[C] Can be manufactured in a Carvera Air CNC, and soldered via reflux or manually`.

The v0.2 baseline contains no logical components, component exchanges, or functional chains; therefore this activity covers the physical component/link and manufacturing-constraint portion of the v0.2 readiness gate only.

## Pass/fail constraints

Pass only if the modeled constraints in the D2 views are satisfied, including:

1. The inspected AMS PCB article is the v0.2 delivery baseline and is traceable to fabrication, inspection, and rework records.
2. The BME280 component/footprint is present, correctly oriented, the correct pitch/variant, and free from visible damage, FOD, solder bridges, opens, lifted pads, or ambiguous rework.
3. The backplane connector component/footprint is present, correctly oriented, the correct pitch/variant, mechanically compatible with the v1.0 interface intent, and free from visible damage/FOD/bridges.
4. The I2C + 3V3 traces/pads between BME280 and connector are present and have no visible opens, shorts, lifted pads, or unapproved jumper/bypass routes; DMM continuity is unpowered inspection support only.
5. Board outline, clearances, drill/edge features, and the selected soldering method remain compatible with Carvera Air CNC manufacturing and reflux or manual soldering evidence.
6. Any missing, wrong, ambiguous component, footprint, route, manufacturing deviation, uncontrolled rework, or evidence gap fails unless a controlled waiver/model update exists before v1.0 integration.

## Statistical and fault-hardening viewpoints

- **Statistical basis:** 100% census review of the single delivered v0.2 PCB article; `3/3` modeled PCs, `3/3` modeled PLs, and `1/1` manufacturing constraint. No sampling, lot-acceptance, powered-function, or fleet-reliability claim is made.
- **Fault-hardening viewpoint:** bad manufacturing, wrong component variant/orientation, pitch mismatch, solder bridge, lifted pad, FOD/contamination, open trace, shorted I2C/3V3, hidden jumper/bypass, manufacturing-traveler mismatch, and uncontrolled rework that could mask a sensor-bus fault.

## Conservative assumptions

- The manufacturing traveler/evidence repository is treated as the controlled record source for fabrication, rework, inspection photos, waivers, and model updates.
- Connector fit is limited to unpowered mechanical/pitch/interface inspection; electrical bring-up evidence is not credited here.
- If Carvera-specific numerical fabrication limits are not present in the model, the report must bind the actual fabrication evidence and any applicable shop/tool constraints as execution evidence rather than silently passing the constraint.
