# System Requirement-to-Test Closure Matrix

Status: model-defined matrix; execution evidence pending.

| Requirement / closure theme | Primary system test(s) | Subsystem evidence references | Closure rule |
|---|---|---|---|
| Final CanSat readiness | `SYS-FLIGHT-READINESS-CLOSURE` | All subsystem test reports and waivers | 100% required reports pass or are dispositioned |
| Mission sequence | `SYS-MISSION-REHEARSAL` | ADS/AMS/OBCC/PDM/PDS/DPS/S&A definitions | Nominal and branch rehearsal pass with raw `deployment_status` code/symbol/category preserved and no false deployment success |
| RF range/PDR | `SYS-RF-RANGE-PDR` | OBCC-V03, DPS-V10-C-001 | `N=300/k>=279`; 500 m horizontal LOS or approved RF-equivalent; legal/site/weather/interference and RSSI/SNR evidence retained |
| End-to-end data/schema | `SYS-END-TO-END-DATA` | ADS/AMS freshness, OBCC LoRa, DPS parser/UI/CSV | `OBCC-LORA-PAYLOAD-v1.0` canonical values/status preserved; ADS/AMS `>=5 Hz` freshness evidence remains separate from `2 s` LoRa packaging; fresh requires `VALID` and `age_ms <= 400 ms`; no stale/default/fault-as-`VALID`; `deployment_status` code/symbol/category preserved in DPS UI/CSV columns |
| Power endurance/transients | `SYS-POWER-ENDURANCE-TRANSIENT` | PDS/ESS rail/endurance/protection, PDM servo branch | 6 h and transient criteria pass |
| Deployment safety | `SYS-DEPLOYMENT-SAFE-LIVE` | ADS freshness, OBCC policy, PDM status, S&A clearance, PDS rails, DPS UI | Stand-by inhibits; On trigger/emergency succeeds only with `OPEN_CONFIRMED` plus PDM/actuator evidence or reports fault; command/in-progress/inhibited/no-open/timeout/jam/fault/unknown/missing/unrecognized statuses are non-success |
| Environmental robustness | `SYS-ENVIRONMENTAL-REGRESSION` | S&A screens plus critical subsystem regression | Post-screen inspection and regression pass |
| Workshop readiness | `SYS-WORKSHOP-READINESS` | README/BOM/guide/subsystem smoke tests | Independent-user checklist passes |
