# SAA-VV-CE-001 — Backplane/interface component-exchange presence/absence analysis

Model-defined verification activity for the S&A v1.0 backplane/interface component-exchange gap. The baseline S&A views are physical-only and contain no `[CE]` elements, so this activity defines a verification-only analysis bench that confirms traceable ownership in subsystem models or records hold/fail for S&A-owned missing or ambiguous exchanges.

- **IADT method:** Analysis
- **IVV source category:** Component exchange
- **SSIV / development version:** `SAA-v1.0` flight-readiness / final-acceptance baseline. `v0.1` is copied for context only.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-CE-001/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-CE-001/`
- **Primary traceability targets:** `SAA-UC-BackplaneIntegration`, `SAA-FE-BackplaneMisMate`, and the v1.0 Backplane PCB constraints for defined pin interface, `5.0 ±0.1 V`, `3.3 ±0.1 V`, testpoints, low-capacitance SPI/I2C/UART, and ERC + DRC clean.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R4, SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen historical/transition context; not the focus of this CE analysis. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for v1.0 Backplane PCB constraints and physical endpoints. |
| Physical evidence access | `SAA-VV-CE-001_physical_evidence_access.d2` | `SAA-VV-CE-001_physical_evidence_access.png` | Verification-only PV1 view showing temporary evidence-access physical links to the backplane, rails, testpoints, fast lines, and servo connector. |
| Logical interface analysis context | `SAA-VV-CE-001_logical_interface_analysis_context.d2` | `SAA-VV-CE-001_logical_interface_analysis_context.png` | Verification-only PV2 view for review actors, subsystem owners, netlist/pinout, ERC/DRC, measurements, and CE ownership/disposition records. |
| Functional allocation / analysis | `SAA-VV-CE-001_functional_allocation_analysis.d2` | `SAA-VV-CE-001_functional_allocation_analysis.png` | Verification-only PV3 view allocating analysis functions to reviewer, owners, tools, evidence packages, and UUT interface-analysis elements. |
| Analysis chain | `SAA-VV-CE-001_analysis_chain.d2` | `SAA-VV-CE-001_analysis_chain.png` | Functional-chain-style analysis scenario: collect evidence, compare to constraints, check ownership/power/fast-lines/servo path, and classify pass/hold/fail. |

The LCs, functions, CEs, PLs, and functional chain in this folder are **verification-only**. They do not add baseline S&A design exchanges and must not be treated as closing the baseline modeling gap until the execution report references actual subsystem CE definitions or approved S&A model updates.

## Required interface review census

The execution report shall include one row for every released net/pin/interface instance in the evidence package and, at minimum, cover these implied interface candidates:

| Candidate ID | Implied interface candidate | Minimum analysis fields | Pass/hold/fail focus |
|---|---|---|---|
| CE-CAND-01 | `5.0 ±0.1 V` rail over the backplane | owner/source, all sink endpoints, voltage level, current/load assumption if available, testpoint, return path, continuity/isolation evidence, model reference | No absent owner, swapped pin, rail short/open, missing testpoint, or unapproved voltage mismatch. |
| CE-CAND-02 | `3.3 ±0.1 V` rail over the backplane | owner/source, all sink endpoints, voltage level, current/load assumption if available, testpoint, return path, continuity/isolation evidence, model reference | No absent owner, swapped pin, rail short/open, missing testpoint, or unapproved voltage mismatch. |
| CE-CAND-03 | ADS `2 mm 2×6` header pin interface | pin numbers, endpoint components, direction/protocol/rail intent per pin, owner, testpoint/access where applicable, CE or cross-reference | All pins reviewed; no swapped or unmodeled pins. |
| CE-CAND-04 | AMS `2 mm 2×6` header pin interface | pin numbers, endpoint components, direction/protocol/rail intent per pin, owner, testpoint/access where applicable, CE or cross-reference | All pins reviewed; no swapped or unmodeled pins. |
| CE-CAND-05 | OBCC `2 mm 2×6` header pin interface | pin numbers, endpoint components, direction/protocol/rail intent per pin, owner, testpoint/access where applicable, CE or cross-reference | All pins reviewed; no swapped or unmodeled pins. |
| CE-CAND-06 | PDS `2 mm 2×6` header pin interface | pin numbers, endpoint components, direction/protocol/rail intent per pin, owner, testpoint/access where applicable, CE or cross-reference | All pins reviewed; no swapped or unmodeled pins. |
| CE-CAND-07 | Critical rail/signal testpoints | linked net, physical accessibility, label/reference designator, intended measurement, owner | Required critical signals and rails have accessible, traceable testpoints or approved rationale. |
| CE-CAND-08 | SPI fast-line intent | endpoints, direction/chip-select intent, voltage level, owner, low-capacitance/rise-time rationale, testpoint/access | No wrong-protocol implementation, swapped direction, excessive capacitance/rise-time risk, or unowned net. |
| CE-CAND-09 | I2C fast-line intent | bus owner/master/slave intent, pullup/voltage level, endpoints, owner, capacitance/rise-time rationale, testpoint/access | No wrong-protocol implementation, excessive bus capacitance/rise-time risk, missing pullup ownership, or unowned net. |
| CE-CAND-10 | UART fast-line intent | TX/RX direction, endpoints, voltage level, owner, low-capacitance/rise-time rationale, testpoint/access | No TX/RX swap, voltage mismatch, wrong protocol, or unowned net. |
| CE-CAND-11 | PDM servo connector path | connector pins, polarity/ground/command/power path, endpoints, owner, continuity evidence, miswire controls | No servo connector miswire, wrong polarity, unowned endpoint, or missing evidence. |
| CE-CAND-12 | Extra implemented backplane nets or protocols not implied by the S&A constraint | net name, endpoints, intended owner, rationale, model reference or waiver | Extra unmodeled interfaces affecting the backplane are hold/fail until modeled, cross-referenced, or removed. |

## Analysis procedure definition

1. Open the v1.0 baseline copy and the verification-only model views in this folder.
2. Compile the complete implied-interface candidate list from the v1.0 Backplane PCB constraint and the released netlist/pinout evidence.
3. Collect controlled evidence: backplane netlist/pinout, connector pin tables, DRC/ERC report, continuity/rail measurements if available, and subsystem CE references or written owner responses.
4. For every candidate and every released pin/net, fill the ownership matrix with: owner, model reference or required S&A CE update, endpoints, direction/protocol intent, voltage level where applicable, testpoint access, low-capacitance/rise-time rationale where applicable, evidence ID, and disposition.
5. Compare the matrix against the v1.0 Backplane PCB constraints and SAA-R4/SAA-R5/IVV expectations.
6. Explicitly screen the fault-hardening cases: swapped pins, missing testpoints, excessive capacitance/rise time, rail short/open, wrong protocol on a multi-point link, ambiguous direction, unowned net, and PDM servo connector miswire.
7. Classify each candidate and the overall activity as pass, hold, or fail.
8. Archive the matrix and supporting evidence under `S&A/MBSE/tests/results/SAA-VV-CE-001/` and reference this model definition from the report.

## Pass/fail constraints

Pass only if **100%** of implied v1.0 backplane power, signal, testpoint, header-pin, and servo interfaces are reviewed and every row has:

- traceable ownership by an S&A `[CE]` or by a referenced subsystem CE/interface model;
- explicit endpoints and pin numbers where a connector/header is involved;
- direction/protocol intent for SPI, I2C, UART, servo command/control, and any other communication path;
- voltage level and return-path intent for rail and signal paths where applicable;
- testpoint access for critical rails/signals or approved rationale for absence;
- low-capacitance/rise-time rationale for SPI/I2C/UART fast lines;
- clean or formally dispositioned ERC/DRC evidence;
- no unmodeled wrong-protocol, swapped-pin, rail short/open, voltage mismatch, unowned-net, or servo-miswire implementation; and
- controlled evidence sufficient for report-by-reference.

Hold the activity when evidence or model ownership is missing, stale, ambiguous, or awaiting approved model update. Fail the activity when an implemented interface is demonstrably wrong, unsafe, incompatible with the modeled constraints, or deliberately unowned/unmodeled without approved waiver.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CE-001/` should reference this model definition and record only execution-specific information:

- model definition revision and v1.0 baseline copy used;
- released netlist/pinout, DRC/ERC, measurement, and subsystem model/evidence revisions;
- completed ownership/disposition matrix for all candidate interfaces and all released pins/nets;
- pass/hold/fail status for each row and for the overall activity;
- evidence IDs and file paths for netlists, pin tables, reports, measurements, screenshots, owner responses, waivers, and model-change requests;
- deviations from this model definition, anomalies, assumptions, waivers, and rationale.

## Viewpoints

- **Statistical significance:** 100% design/interface review of every implied v1.0 backplane interface and every released evidence source. This analysis makes no sampling, packet-delivery, or reliability-population claim; continuity/rail/capacitance/rise-time evidence is supporting design evidence only unless a separate test activity claims statistics.
- **Fault hardening:** The analysis intentionally screens for swapped header pins, missing or inaccessible testpoints, excessive capacitance or rise-time risk on SPI/I2C/UART paths, rail short/open, voltage mismatch, wrong protocol on multi-point or point-to-point links, ambiguous direction, unowned net, extra unmodeled interface, and PDM servo connector miswire.

## Constraint coverage note

This activity covers the component-exchange presence/absence and consistency portion of the S&A backplane constraints: defined pin interface, `5.0 ±0.1 V`, `3.3 ±0.1 V`, testpoints for critical signals, low-capacitance SPI/I2C/UART, PDM servo connector path, and clean/dispositioned ERC/DRC. Quantitative electrical performance or reliability demonstrations remain with separate constraint/test activities unless an execution report explicitly invokes this analysis as supporting evidence.

## Assumptions and blockers

- The baseline S&A v1.0 source view contains no `[CE]`, `[LC]`, `[F]`, `[FE]`, or functional-chain elements; this folder adds verification-only definitions rather than editing the baseline.
- The analysis can pass by cross-referencing subsystem-owned CE/interface models if S&A is only the physical/backplane owner; it must hold/fail if S&A-owned component exchanges remain absent or ambiguous.
- PDM/servo ownership is assumed to be external to the S&A physical view unless a subsystem owner identifies the authoritative model reference during execution.
- The gate may be placed on hold rather than failed when a discrepancy is correctable by approved model/evidence update before flight readiness closure.
