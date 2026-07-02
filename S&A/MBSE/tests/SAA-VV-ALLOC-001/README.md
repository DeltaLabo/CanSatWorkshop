# SAA-VV-ALLOC-001 — S&A integration-function allocation and ownership analysis

Model-defined verification activity for S&A v1.0 integration-function allocation and ownership. Baseline S&A remains intentionally physical-only; the absence of source `[LC]`, `[F]`, `[FE]`, `[CE]`, or functional-chain views is an accepted modeling-scope decision, not an unresolved definition blocker. S&A owns physical integration constraints around structure, module retention, backplane fit, PCB accommodation, testpoint access, battery/connector retention, and deployment clearance. Strict execution credit may pass with controlled physical-constraint-only S&A responsibilities plus subsystem model references, provided the ownership/disposition matrix closes 100% of candidates.

- **IADT method:** Analysis
- **IVV source category:** Allocation / functional allocation to logical components
- **SSIV / development version:** `SAA-v1.0` flight-readiness / final-acceptance baseline. `v0.1` is copied for incremental context only.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-ALLOC-001/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-ALLOC-001/`
- **Primary traceability targets:** `SAA-UC-IntegratedAssembly`, `SAA-UC-BackplaneIntegration`, `SAA-UC-ParachuteClearance`, `SAA-FE-EnvelopeNonCompliance`, `SAA-FE-BackplaneMisMate`, `SAA-FE-StructuralLoosening`, `SAA-FE-LandingDamage`, and the v1.0 envelope, module, backplane, and assembly/printing constraints.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R1, SAA-R2, SAA-R3, SAA-R4, and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen v0.1 structural/module/backplane-volume context; not the focus of the v1.0 allocation analysis. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 PCs, PLs, and constraints used by this analysis. |
| Logical ownership analysis context | `SAA-VV-ALLOC-001_logical_ownership_analysis_context.d2` | `SAA-VV-ALLOC-001_logical_ownership_analysis_context.png` | Verification-only PV2 context with S&A reviewer, subsystem owners, configuration/evidence repository, candidate function register, ownership matrix, gap register, and hazard screen. |
| Functional allocation / ownership analysis | `SAA-VV-ALLOC-001_functional_allocation_analysis.d2` | `SAA-VV-ALLOC-001_functional_allocation_analysis.png` | Verification-only PV3 view mapping candidate functions to physical integration areas and requiring owner/disposition. |
| Analysis chain | `SAA-VV-ALLOC-001_analysis_chain.d2` | `SAA-VV-ALLOC-001_analysis_chain.png` | Functional-chain-style analysis scenario for enumerating candidate functions, collecting owner responses, assigning owner/disposition, screening gaps, and releasing the pass/hold/fail decision. |

The LCs, functions, CEs, and analysis chain in this folder are **verification-only**. They do not modify the baseline S&A design model. Because the physical-only baseline scope is accepted, explicit baseline S&A LC/F/allocation views are not required solely for definition-decision closure; execution/report credit still requires approved S&A allocation views, subsystem model cross-references, or controlled physical-constraint-only dispositions.

## Required ownership review census

The execution report shall include one row for every candidate S&A integration function and every foreign or ambiguous function discovered during the review. At minimum it shall cover the following candidates:

| Candidate ID | Candidate function / ownership question | Minimum analysis fields | Pass/hold/fail focus |
|---|---|---|---|
| ALLOC-CAND-01 | Maintain `355 ml` envelope and total mass constraint | S&A owner/disposition, related envelope/mass constraints, subsystem mass inputs or references, model/update need | No ambiguous physical-fit or mass/envelope ownership. |
| ALLOC-CAND-02 | Retain standard module stack with stack screws | S&A owner/disposition, PL references, inspection/test cross-links, environmental-screening owner | No unowned retention or post-screen responsibility. |
| ALLOC-CAND-03 | Accommodate ADS/AMS/OBCC/PDS `44 mm × 44 mm` PCBs | S&A physical accommodation owner, subsystem PCB owner refs, keep-out/tolerance evidence, model/update need | No ambiguous PCB fit or interface accommodation. |
| ALLOC-CAND-04 | Locate and mate perpendicular backplane / backplane spine | S&A physical owner, subsystem/backplane interface owner refs, connector/header ownership, model/update need | No unowned backplane physical integration or mismate hazard. |
| ALLOC-CAND-05 | Expose critical rail/signal testpoints | S&A physical/testpoint access owner, subsystem electrical/measurement owner refs, absence rationale where applicable | No missing or ambiguous testpoint-access responsibility. |
| ALLOC-CAND-06 | Maintain physical routing constraints for SPI/I2C/UART fast lines | S&A physical routing/SI responsibility, subsystem protocol owner refs, CE analysis cross-link | No unowned low-capacitance physical-routing responsibility. |
| ALLOC-CAND-07 | Retain ESS battery pack | S&A physical retention owner, ESS electrical/energy owner refs, environmental-screening owner | No ambiguous battery-retention or screening responsibility. |
| ALLOC-CAND-08 | Retain PDM servo connector and harness path | S&A physical retention/clearance owner, PDM behavior/electrical owner refs, CE analysis cross-link | No unowned connector/harness retention or servo-path ambiguity. |
| ALLOC-CAND-09 | Provide top-module, cap, servo, and backplane clearance | S&A physical clearance owner, PDM/OBCC deployment-behavior owner refs, scenario follow-up references | No ambiguous deployment-clearance ownership. |
| ALLOC-CAND-10 | Support parachute deployment clearance path | S&A physical path/clearance owner, deployment-control owner refs, FC follow-up references | No unowned physical deployment-support responsibility. |
| ALLOC-CAND-11 | Assign environmental screening responsibility for S&A physical constraints | S&A IVV owner, subsystem support refs, environmental level/status, model/update need | No ambiguous environmental-screening ownership for retention, backplane, clearance, or fit. |
| ALLOC-CAND-12 | Foreign behavior functions found in S&A context, e.g. sensing, command logic, rail regulation, bus protocols, mission decisions | subsystem owner, authoritative model reference or waiver, reason not allocated to S&A, impact if unresolved | No foreign or extra function remains unowned or silently allocated to S&A. |

## Analysis procedure definition

1. Open the v1.0 baseline copy, the S&A test plan, and the verification-only model views in this folder.
2. Enumerate the complete candidate integration-function set from v1.0 PCs, PLs, and constraints, including backplane, harness/connector, retention, deployment clearance, physical fit, testpoint access, and environmental screening responsibilities.
3. Collect controlled evidence: subsystem owner responses, subsystem model references, prior CE/PC/PL verification definitions, constraint references, and any proposed S&A model-change requests.
4. For every candidate and any additional foreign/ambiguous function, fill the ownership matrix with: owner, S&A-owned vs subsystem-owned vs foreign/out-of-scope disposition, model reference or required model update, affected PC/PL/constraint, traceability target, fault-hardening concern, evidence ID, and status.
5. Confirm each S&A-owned function is either explicitly allocated in an S&A `[LC]`/`[F]` view if the project elects to model it, or remains a physical constraint-only responsibility with controlled rationale.
6. Confirm subsystem-owned behaviors have authoritative model references or owner waivers, especially for sensing, deployment command logic, power regulation, SPI/I2C/UART operation, and servo electrical/control behavior.
7. Screen ownership gaps for hazards: backplane mislocation/mismate, harness or connector unseat, module/battery retention escape, blocked parachute clearance, physical-fit/mass/envelope noncompliance, and environmental-screening escape.
8. Classify each candidate and the overall activity as pass, hold, or fail.
9. Archive the completed matrix, owner responses, model references, waivers, and model-change requests under `S&A/MBSE/tests/results/SAA-VV-ALLOC-001/` and reference this model definition from the report.

## Pass/fail constraints

Pass only if **100%** of candidate S&A integration functions and foreign/ambiguous functions are reviewed and every row has:

- explicit owner or controlled disposition;
- S&A-owned integration functions allocated in an explicit S&A `[LC]`/`[F]` view **or** documented as physical constraint-only responsibilities with controlled rationale;
- subsystem-owned behaviors linked to authoritative subsystem model references or approved waivers;
- no ambiguous ownership for backplane, harness/connector, retention, deployment clearance, physical fit, testpoint access, or environmental screening;
- traceability to a mission/use-case/feared-event/constraint target listed above;
- fault-hardening rationale for ownership-related hazards;
- expected follow-up verification activity references where an allocation decision creates or updates CE, FC, CON, PC, or PL coverage; and
- controlled evidence sufficient for report-by-reference.

Hold the activity when owner responses, model references, baseline updates, or dispositions are missing, stale, or ambiguous but correctable before flight-readiness closure. Fail the activity when an integration function is deliberately unowned, incorrectly assigned, unsafe without mitigation, or allocated contrary to the physical constraints without approved waiver.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-ALLOC-001/` should reference this model definition and record only execution-specific information:

- model definition revision and v1.0 baseline copy used;
- completed ownership/disposition matrix for all candidates and discovered foreign/ambiguous functions;
- owner responses, subsystem model references, waivers, and evidence IDs;
- pass/hold/fail result for each row and the overall activity;
- required S&A or subsystem model-change requests and follow-up verification activities;
- deviations from this model definition, anomalies, assumptions, and rationale.

## Viewpoints

- **Statistical significance:** 100% model/ownership census review of the v1.0 candidate allocation set, relevant constraints, and owner responses. This analysis makes no sampling, packet-delivery, or reliability-population claim.
- **Fault hardening:** The analysis intentionally treats missed ownership as a hazard source for unverified backplane mating, harness/connector retention, module or battery retention, blocked deployment clearance, physical-fit/mass/envelope noncompliance, and environmental-screening escapes.

## Constraint coverage note

This activity covers the allocation/ownership aspect of the S&A envelope, module, backplane, battery/connector, deployment-clearance, and assembly/printing constraints. Quantitative inspections, demonstrations, environmental tests, and electrical interface analyses remain with the corresponding PC, PL, CE, FC, and CON activities unless an execution report explicitly invokes this allocation analysis as supporting evidence.

## Assumptions and blockers

- The baseline S&A v1.0 source view intentionally contains no `[LC]`, `[F]`, `[FE]`, `[CE]`, or functional-chain source elements as an accepted physical-only scope decision; this folder adds verification-only definitions rather than editing the baseline, and no forced LC/F/allocation source-model update is required for definition-decision closure.
- The analysis may pass with a decision that S&A owns only physical constraints while subsystem models own behavior, provided all functions have explicit owner/disposition and traceable references.
- PDM/servo behavior, OBCC deployment command logic, subsystem sensing, power regulation, and bus protocol operation are assumed foreign to S&A unless the execution report identifies an approved S&A ownership decision.
- The gate may be placed on hold rather than failed when a discrepancy is correctable by approved model/evidence update before flight-readiness closure.
