# CON-003 Test Definition Closure Register

Assessment follow-up date: 2026-07-02

Purpose: close the former CON-003 candidate/blocker register by separating resolved definition work into (1) updates/fixes applied to baseline MBSE models, interface contracts, implementation, or existing tests and (2) formerly candidate tests that are now fully modeled. Updates were applied before new test-definition creation. System-level tests were defined last.

Status summary: **no active test remains a planning candidate**. Active subsystem and system verification activities are now either `Model-defined / not executed`, `Defined / execution pending`, `Covered by ...`, or controlled historical/deferred/N/A scope. Execution evidence, equipment IDs, calibration records, as-tested configuration, deviations, and reports remain future work.

## 1. Updates and fixes applied first

| Area | Applied update/fix | Controlled artifacts |
|---|---|---|
| Cross-cutting parachute status | Added `deployment_status` / Parachute Deployment Status as a one-byte OBCC-to-DPS telemetry enum. Only `OPEN_CONFIRMED` is deployed/success; `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, and unrecognized states are not success. DPS GUI/parser/docs preserve code, symbol, and category. | `OBCC/LoRa_Frame.md`; `PM&SE/contracts/obcc_dps_lora_telemetry_contract.md`; `OBCC/main/*`; `DPS/dashboard.py`; `DPS/README.md`; OBCC/DPS/PDM MBSE/test docs. |
| ADS | Existing ADS source models and tests now distinguish v0.2 Serial0-only development logging from v1.0 ADS-to-OBCC internal `Pointers`/`Returns` delivery; carry the shared 5 Hz freshness path, 2 s LoRa packaging separation, `age_ms <=400 ms` only with `VALID`, six-status enum, mission-window/rate/no-blocking/GPS/gyro truth updates, acceleration/heading delegation, and no stale/default/fault-as-`VALID` rule. | `ADS/README.md`; `ADS/MBSE/v0.2/`; `ADS/MBSE/v1.0/`; `ADS/MBSE/tests/README.md`; affected ADS test folders. |
| AMS | AMS source baseline and controlled README now align pressure/temperature/altitude constraints, OBCC `>=5 Hz` internal delivery vs `2 s` telemetry separation, shared freshness/status/no-stale-valid semantics, v1.0 use cases/feared events, and IVV statistics; existing AMS API/FC/CON test definitions retain the shared freshness/status, API/non-blocking evidence checklist, v0.2 PCB-only disposition, and provisional trace policy. | `AMS/README.md`; `AMS/MBSE/v0.1/`; `AMS/MBSE/v1.0/`; `AMS/MBSE/tests/README.md`; affected AMS test folders. |
| DPS | Existing DPS v1.0 source/test models now align with bidirectional UART intent, selected RF/PDR, concurrency, UI/CSV/latency/layout oracles, corrupt-frame hardening, and `deployment_status` display/storage. | `DPS/MBSE/v1.0/`; `DPS/MBSE/tests/`; `DPS/MBSE/tests/DPS-V10_*_Oracles.md`; `DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md`. |
| OBCC | Existing OBCC gate definitions now cite the telemetry/command/RF contract, deployment/fault policy, 2 s cadence, `N=300`/`k>=279` PDR rule, runtime-fault/deployment gates, and target-context caveats. | `OBCC/MBSE/tests/README.md`; `OBCC/MBSE/tests/OBCC-V03/V04/V05/V06/V09/V10*`; `OBCC/MBSE/v1.0/`. |
| PDS & ESS | Baseline source model now includes INA219 I2C CE and accessible master-switch/interface detail; existing PDS tests now include protection-probability, rail/endurance, DFM, Li-ion safety, and execution prerequisite criteria. | `PDS&ESS/MBSE/v1.0/`; `PDS&ESS/MBSE/tests/README.md`; affected PDS test folders. |
| PDM | Existing PDM source/test models now include the selected `<=11 m/s` terminal-speed linkage, OBCC-owned deployment policy boundary, PDM status/no-false-success semantics, v0.2 power validity, and v0.1 mass/video/wind criteria. | `PDM/MBSE/v1.0/`; `PDM/MBSE/v1.0/tests/PDM-VV-FC-001/`; `PDM/MBSE/v0.2/tests/`; `PDM/MBSE/v0.1/tests/`. |
| S&A | Existing S&A test definitions now include approved tailored environmental-screen criteria, confirmed `122 mm` height, mass guard band, Fusion 360 pinout authority, rail/I2C/SPI/UART/DFM criteria, PLA/print criteria, and movement thresholds. | `S&A/MBSE/tests/README.md`; affected S&A activity folders. |

## 2. Former subsystem candidates now model-defined

| Area | Former candidate(s) | Definition status and location |
|---|---|---|
| ADS | `ADS-IVV-C-ACCEL-3AXIS`; `ADS-IVV-C-HEADING-NORTH`; `ADS-V10-DATA-FRESHNESS` alias | Model-defined in `ADS/MBSE/tests/ADS-IVV-C-ACCEL-3AXIS/`, `ADS/MBSE/tests/ADS-IVV-C-HEADING-NORTH/`; freshness covered by updated ADS definitions and index. |
| AMS | `AMS-V10-TEMP-RESPONSE-60S`; `AMS-V10-DATA-FRESHNESS` | Model-defined in `AMS/MBSE/tests/AMS-V10-TEMP-RESPONSE-60S/` and `AMS/MBSE/tests/AMS-V10-DATA-FRESHNESS/`. |
| DPS v1.0 | `DPS-V10-T-004`, `T-005`, `T-006`, `C-001`, `C-003`, `C-004`, `C-005`, `C-006`, `C-008` | Model-defined in corresponding `DPS/MBSE/tests/<activity-id>/` folders. `DPS-V10-C-002` and `C-007` are retired as separate active rows and covered by `DPS-V10-I-001` and `DPS-V10-T-002`. Historical v0.1/v0.2 rows are deferred scope unless a future board promotes historical closure. |
| PDS & ESS | `PDS-VV-CON-010` regulator efficiency | Model-defined in `PDS&ESS/MBSE/tests/PDS-VV-CON-010/`. Other PDS rows are defined, covered, or execution-only prerequisites. |
| PDM v1.0 | `PDM-VV-PC-001`, `PDM-VV-PL-001`, `PDM-VV-CE-001`..`005`, `PDM-VV-ALLOC-001`..`003`, `PDM-VV-FC-002`, `PDM-VV-FC-003`, `PDM-VV-CON-001`..`007` | Model-defined in corresponding `PDM/MBSE/v1.0/tests/<activity-id>/` folders. |
| PDM v0.2 / v0.1 | `PDM-V02-INS-PC-PL-INVENTORY`, `PDM-V02-ANA-CE-INTENT`, `PDM-V02-ANA-LC-FUNC-ALLOC`, `PDM-V02-TEST-TERMINAL-SPEED`, `PDM-V02-ANA-CONSTRAINT-COVERAGE`, `PDM-V01-INSP-PC`, `PDM-V01-ALLOC-DSC` | Model-defined in corresponding `PDM/MBSE/v0.2/tests/` and `PDM/MBSE/v0.1/tests/` folders. `PDM-V01-GAP-PL` and `PDM-V01-GAP-CE` remain controlled non-executable source gaps, not executable test definitions. |
| OBCC | No new OBCC test definitions required | Existing gate definitions are the active model-defined list. Literal advancement/final-readiness gates remain execution/disposition gates, not open test definitions. |
| S&A | No S&A definition backlog | S&A activities remain model-defined; remaining work is execution/reporting. |

## 3. System-level definitions created last

System-level MBSE definitions are under `PM&SE/MBSE/tests/` and are indexed by `PM&SE/MBSE/tests/README.md`. Requirement closure is mapped in `PM&SE/MBSE/tests/requirements_to_test_matrix.md`.

| Activity ID | Purpose | Status |
|---|---|---|
| `SYS-FLIGHT-READINESS-CLOSURE` | Final board closure, requirement-to-test matrix, waivers/deviations, final configuration. | Model-defined / not executed |
| `SYS-MISSION-REHEARSAL` | Full assembled CanSat + DPS mission sequence with safe deployment branches. | Model-defined / not executed |
| `SYS-RF-RANGE-PDR` | Final-article 500 m RF/PDR or approved RF-equivalent with `N=300`, `k>=279`. | Model-defined / not executed |
| `SYS-END-TO-END-DATA` | Truth/reference payload through OBCC LoRa to DPS CSV/dashboard, including freshness/status and `deployment_status`. | Model-defined / not executed |
| `SYS-POWER-ENDURANCE-TRANSIENT` | Full-system power endurance and servo/RF/sensor transients. | Model-defined / not executed |
| `SYS-DEPLOYMENT-SAFE-LIVE` | ADS/OBCC/PDM/PDS/S&A/DPS deployment interaction with safe fixture/live policy. | Model-defined / not executed |
| `SYS-ENVIRONMENTAL-REGRESSION` | Critical functions after approved mechanical/environmental screens. | Model-defined / not executed |
| `SYS-WORKSHOP-READINESS` | Independent-user rebuild, guide/BOM/materials, and learning-readiness checks. | Model-defined / not executed |

## 4. Execution-only prerequisites still open

The following items are not definition blockers. They must be recorded before execution credit:

- as-tested hardware IDs, PCB/printed-part IDs, firmware/software commits, source/build maps, parser/dashboard versions, configuration deviations, and waiver records;
- equipment asset IDs, calibration/status, analysis-script versions, clock/timebase/synchronization methods, environmental limits, and safety controls;
- RF legal/site approval, antenna installation/orientation, weather/interference records, and PDR independence rationale;
- Li-ion cell/charger safety documents and powered-test authorization;
- final load profiles, thermal/current limits, protection setpoints, demanded-trial independence, terminal-speed mass/configuration/wind/video calibration, and environmental-screen event records;
- execution reports under each activity `results/<activity-id>/` path.

No pass/fail credit is claimed by this register. It only records that all active CON-003 definition work is now closed and ready for execution planning.
