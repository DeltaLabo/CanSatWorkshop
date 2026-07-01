# AMS-VV-CE-001 — I2C component-exchange presence/absence analysis

- **SSIV / development version:** AMS v1.0 final acceptance.
- **IADT method:** Analysis.
- **Traceability:** `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault`.
- **References cited in diagram titles:** IVV, AMS-R1 (BME280), AMS-R2 (I2C).
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-VV-CE-001/`.
- **Scope boundary:** component-exchange presence and implementation consistency for the modeled `[CE] I2C` only. VV-only analysis records, analysis actors, and evidence CEs are not flight/UUT functionality and are excluded from the `1/1` target count. Physical-link integrity is covered by `AMS-VV-PL-001`; detailed `≤5 ms` timing and fault-recovery proof is covered by `AMS-VV-CON-003`; `[CE] Pointers` and `[CE] Returns` remain `AMS-VV-CE-002` / `AMS-VV-CE-003`.

## Baseline views copied

Untouched baseline copies of all AMS v1.0 D2/PNG views are in `baseline/`.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_CE_001_view2_logical_ce_analysis_testbench.d2` | PV2 logical analysis testbench showing the target `[CE] I2C`, context CEs, VV-only analysis record LC, analysis actors, evidence CEs, and pass/fail constraints. |
| `AMS_VV_CE_001_view3_functional_allocation_ce_analysis.d2` | PV3 allocation view with operator, workstation, repository, QA, evidence, and VV-only analysis functions; no CEs/FEs/PLs. |
| `AMS_VV_CE_001_view4_i2c_ce_presence_absence_analysis_chain.d2` | Analysis chain defining the CE presence/absence analysis workflow and constraints. |

## Target CE covered

The activity is a 100% analysis of the single modeled I2C component exchange:

1. `system.cansat.ams_module.ams_pcb.bme280.ams_sensing` ↔/to `system.cansat.obcc_module.obcc_pcb.xiao.ams_processing` — `[CE] I2C`.

The CE analysis is checked against all modeled I2C functional crossings from the v1.0 chains:

1. `[F] Read pressure` → `[F] Respond to I2C Requests` — pressure request.
2. `[F] Respond to I2C Requests` → `[F] Read pressure` — pressure response.
3. `[F] Read temperature` → `[F] Respond to I2C Requests` — temperature request.
4. `[F] Respond to I2C Requests` → `[F] Read temperature` — temperature response.
5. `[F] Get BME280 init state` → `[F] Respond to I2C Requests` — init-state request.
6. `[F] Respond to I2C Requests` → `[F] Get BME280 init state` — state-info response.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. The analysis matrix covers `1/1` target CE with the full endpoint paths above and is tied to the AMS v1.0 final-acceptance baseline/configuration evidence.
2. The implementation uses I2C for the target exchange; UART, SPI, GPIO bit-bang, analog, proxy, or other protocol substitutions fail unless covered by controlled model update/waiver.
3. The implemented exchange maps to the modeled AMS Processing ↔ AMS Sensing/BME280 relationship with no unmodeled bypass, bridge, substitute endpoint, or foreign LC carrying the modeled I2C exchange.
4. AMS Processing / XIAO is evidenced as the I2C requester/master for modeled reads; BME280 / AMS Sensing is evidenced as the addressed responder/slave.
5. Bus instance, BME280 address, request/response direction, 3V3 compatibility, and pullup/topology design intent are unambiguous and consistent with AMS-R1/AMS-R2 and the model.
6. Interface-level evidence defines bounded error/status behavior for NACK/absent device, stuck SDA/SCL, clock-stretch/no-response, and address/configuration mismatch; detailed `≤5 ms` proof is not credited here and is referenced to `AMS-VV-CON-003`.
7. Missing, ambiguous, inconsistent, or unauditable evidence fails unless a controlled waiver/model update exists.
8. Open PC/PL anomalies do not count as CE failures by themselves, but they are recorded as dependencies/anomalies if they invalidate the CE analysis basis.

## Statistical and fault-hardening viewpoints

- Statistical basis: 100% design/interface analysis of the target CE (`1/1`) and all six modeled I2C functional crossings; no sampling or fleet reliability claim.
- Fault-hardening viewpoint: wrong protocol, wrong endpoint, wrong direction/role, address conflict, bus-instance mismatch, pullup/voltage-level design mismatch, unmodeled bypass/proxy, NACK, absent BME280, stuck SDA/SCL, clock-stretch/no-response, and missing bounded error/status policy.
