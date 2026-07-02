# DPS-V10-I-001 — Physical component and physical-link inspection definition

- **SSIV / version:** DPS-v1.0 (confirmed by user for this session).
- **IADT method:** Inspection.
- **IVV source category:** component/link.
- **Model elements covered:** all physical components and physical links listed in the DPS v1.0 planning inventory (`../README.md` §3.2), plus constraint C02 ground-station PCB reuse/no backplane connector.
- **Traceability target:** assembled v1.0 DPS/CanSat interface; ground-station integration safety constraint C02. Formal mission/capability/use-case IDs are absent from the source model.
- **References cited in diagrams:** P0 (`PM&SE/IVV.md`), R1-R3, R8, R11-R13 from `../references/INDEX.md`.
- **Expected report/evidence folder:** `DPS/MBSE/tests/results/DPS-V10-I-001/`.

## Baseline views copied

The unmodified DPS v1.0 Capella/D2 source views and rendered PNGs are copied under [`baseline/`](./baseline/) for traceability. This satisfies the requirement to preserve all source views before defining the verification activity.

## Verification-specific diagrams

| View | Purpose |
|---|---|
| [`DPS-V10-I-001_view1_physical_inspection_context.d2`](./DPS-V10-I-001_view1_physical_inspection_context.d2) | PV1 physical inspection context with all modeled PCs/PLs, inspection equipment EAs, physical probe/fixture links, and pass/fail constraints. |
| [`DPS-V10-I-001_view2_logical_inspection_context.d2`](./DPS-V10-I-001_view2_logical_inspection_context.d2) | PV2 logical/evidence context connecting the IVV Inspector and IVV Reviewer to the verification-only Inspection Evidence Record LC. |
| [`DPS-V10-I-001_view3_functional_allocation_inspection_context.d2`](./DPS-V10-I-001_view3_functional_allocation_inspection_context.d2) | PV3 allocation of human, equipment, and verification-only evidence functions used to perform and record the inspection. |

Rendered PNGs are generated beside the D2 sources.

## Inspection pass/fail constraints

1. **Coverage:** 100% of modeled PCs and PLs below are inspected; any absent item requires an explicit disposition/waiver in the report.
2. **Presence/variant:** each physical component is present, identifiable, correct variant/revision, correctly placed, and not visibly damaged.
3. **Physical-link implementation:** screws, footprints, solder joints, traces, 5 V power traces, and USB-C cable are present and continuous as applicable.
4. **Safety/fault hardening:** UUT is unpowered during resistance/continuity checks; no 5 V/GND short; polarity verified; antenna fitted before any later radio power-up.
5. **C02 ground-station reuse:** ground-station PCB reuse passes only if the Backplane Connector is absent/not soldered and no unintended backplane continuity/load is measured.
6. **Environment/evidence:** ESD mat/strap connected; PCB illumination ≥500 lx; photos are in focus; article IDs, board revisions, inspection equipment IDs, readings and deviations are recorded.

## Inspection checklist coverage

### Physical components

| Item ID | Model element | Inspection target | Pass/fail constraint | Evidence |
|---|---|---|---|---|
| PC-01 | CanSat | CanSat assembly present for the v1.0 DPS/CanSat interface. | Present, identifiable, no visible damage affecting DPS integration. | Photo + checklist. |
| PC-02 | OBCC Module | OBCC module present inside CanSat. | Present and mechanically seated; screws interface available. | Photo + checklist. |
| PC-03 | OBCC PCB | OBCC PCB present inside OBCC Module. | Correct PCB/revision; no visible damage/contamination. | Photo + article ID. |
| PC-04 | CanSat RFM96W LoRa | RFM96W LoRa present on OBCC PCB. | Correct radio variant, soldered to modeled footprint, antenna readiness noted. | Photo + marking check. |
| PC-05 | CanSat XIAO ESP32-S3 | XIAO ESP32-S3 present on OBCC PCB. | Correct variant, soldered/installed to modeled footprint. | Photo + marking check. |
| PC-06 | Backplane Connector | Backplane Connector present on CanSat OBCC PCB. | Present on CanSat OBCC PCB as modeled. | Photo + checklist. |
| PC-07 | Ground Station PCB | Ground station PCB present. | Reuses OBCC PCB as modeled; no ground backplane connector soldered. | Photo + C02 check. |
| PC-08 | Ground RFM96W LoRa | RFM96W LoRa present on ground-station PCB. | Correct radio variant, soldered to modeled footprint, antenna readiness noted. | Photo + marking check. |
| PC-09 | Ground XIAO ESP32 | XIAO ESP32 present on ground-station PCB. | Correct variant, soldered/installed to modeled footprint. | Photo + marking check. |
| PC-10 | PC | Ground-station PC present for USB connection and evidence record. | Identified as test/as-inspected PC if used. | Checklist. |
| PC-11 | PC USB Port | USB port used for ground-station connection present. | Physically available and not visibly damaged. | Photo/checklist. |

### Physical links

| Item ID | Model element | Inspection target | Pass/fail constraint | Evidence |
|---|---|---|---|---|
| PL-01 | OBCC Module ↔ OBCC PCB screws | Mechanical screw link. | Screws present/tightened or dispositioned; PCB mechanically retained. | Photo + checklist. |
| PL-02 | CanSat RFM Footprint | Radio-to-OBCC PCB footprint. | Footprint populated/soldered; no lifted pads/bridges. | Close-up photo. |
| PL-03 | CanSat XIAO Footprint | XIAO-to-OBCC PCB footprint. | Footprint populated/soldered; no lifted pads/bridges. | Close-up photo. |
| PL-04 | CanSat Backplane Footprint | Backplane connector footprint on OBCC PCB. | Footprint/link present for CanSat OBCC PCB. | Close-up photo. |
| PL-05 | CanSat RFM96W ↔ XIAO SPI traces | SPI traces on OBCC PCB. | Continuity/resistance acceptable; no shorts found. | DMM readings. |
| PL-06 | Ground RFM Footprint | Ground radio-to-PCB footprint. | Footprint populated/soldered; no lifted pads/bridges. | Close-up photo. |
| PL-07 | Ground XIAO Footprint | Ground XIAO-to-PCB footprint. | Footprint populated/soldered; no lifted pads/bridges. | Close-up photo. |
| PL-08 | Ground RFM96W ↔ XIAO SPI traces | SPI traces on ground-station PCB. | Continuity/resistance acceptable; no shorts found. | DMM readings. |
| PL-09 | Ground RFM96W ↔ XIAO 5 V power traces | 5 V/GND power traces. | 5 V continuity and polarity pass; no 5 V/GND short. | DMM readings. |
| PL-10 | Ground XIAO ↔ PC USB-C cable | USB-C cable/endpoint link. | Cable present; continuity/short check passes; endpoints fit without visible damage. | Cable tester/DMM + photo. |

## Constraint coverage disposition

- **C02** is directly assigned to this inspection as a pass/fail constraint.
- **C01** 500 m separation is not a presence/absence inspection target; it remains assigned to `DPS-V10-C-001`.
- Software/UI constraints C03-C08 are not component/link inspection targets and remain covered by the relevant analysis/testing/demonstration activities in the master table.

## Evidence expected in report

The report in `tests/results/DPS-V10-I-001/` should reference these modeled diagrams and record: model baseline, as-inspected configuration, article IDs, board revisions, equipment IDs/calibration status where applicable, checklist results for every PC/PL, photos, DMM/cable-tester readings, environmental readings, pass/fail rationale, deviations, anomalies, waivers and limitations.
