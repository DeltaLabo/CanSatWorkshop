# AMS-VV-PC-001 — Physical component presence/absence inspection

- **SSIV / development version:** AMS v1.0 final acceptance.
- **IADT method:** Inspection.
- **Traceability:** AMS physical integration/build readiness; `AMS-UC-MeasureAtmosphere`; modeled final-acceptance physical component baseline.
- **References cited in diagram titles:** IVV, AMS-R1 (BME280 identity), AMS-R6 (CanSat build/integration context).
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-VV-PC-001/`.
- **Scope boundary:** physical component presence, identity, containment, and gross condition. Physical links, continuity, retention, screws, traces, footprints, and cables are covered by `AMS-VV-PL-001`.

## Baseline views copied

Untouched baseline copies of all AMS v1.0 D2/PNG views are in `baseline/`.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_PC_001_view1_physical_inspection_testbench.d2` | Physical inspection setup with ESD fixture, camera/microscope, connector gauge, and PC-target constraints. |
| `AMS_VV_PC_001_view3_functional_allocation_inspection.d2` | Inspection operator, QA witness, equipment, evidence repository functions, and pass/fail constraints. |

No functional-chain view is created for this activity because the IADT method is **Inspection**; the inspection target and pass/fail constraints are defined directly on the relevant physical components/functions in the test-definition views.

## Physical components covered

The inspection is a 100% census of the 13 modeled UUT physical components:

1. `[PC] CanSat`
2. `[PC] AMS Module`
3. `[PC] AMS PCB`
4. `[PC] BME280`
5. AMS-side `[PC] Backplane Connector`
6. `[PC] Backplane PCB`
7. `[PC] 2mm 2x6 AMS Headers`
8. `[PC] Spine`
9. `[PC] 2mm 2x6 OBCC Headers`
10. `[PC] OBCC Module`
11. `[PC] OBCC PCB`
12. `[PC] XIAO ESP32-S3`
13. OBCC-side `[PC] Backplane Connector`

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. The inspected article is the AMS v1.0 final-acceptance integrated article, not a protoflight or partial build.
2. Each of the 13 target PCs has an individual checklist entry and supporting photo/build-record evidence.
3. Each target PC is physically present, identifiable, correct for the v1.0 baseline, and installed in its modeled containment.
4. The BME280 and XIAO ESP32-S3 identity/configuration evidence is recorded where visible or by controlled build record.
5. Duplicate-named components, especially the two `[PC] Backplane Connector` instances, are verified by full containment path and are not double-counted.
6. Any missing, wrong, ambiguous, damaged, contaminated, temporary/loose, or unapproved substituted PC fails unless dispositioned by controlled waiver/model update.
7. Physical-link integrity is not credited by this activity and remains pending under `AMS-VV-PL-001`.

## Statistical and fault-hardening viewpoints

- Statistical basis: 100% census inspection, `13/13` target PCs per final-acceptance article; no sampling or fleet reliability claim.
- Fault-hardening viewpoint: wrong variant, wrong side/location, duplicate-instance confusion, visible damage, FOD, contamination, and unapproved critical substitution.
