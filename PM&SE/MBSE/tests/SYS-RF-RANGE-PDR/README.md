# SYS-RF-RANGE-PDR — final-article RF range/PDR

**Status:** Model-defined / not executed. This is a system-level verification definition and must be executed after relevant subsystem tests are ready or explicitly dispositioned. No pass/fail credit is claimed here.

## Purpose
System-level RF range/PDR with final article or approved RF-equivalent setup.

## Controlled references
- PM&SE/IVV.md
- PM&SE/contracts/obcc_dps_lora_telemetry_contract.md
- PM&SE/contracts/sensor_obcc_freshness_contract.md
- OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md
- Subsystem MBSE/tests READMEs

## Verification definition

| Field | Controlled value |
|---|---|
| Item under verification | OBCC transmitter, DPS ground station receiver, final antennas/enclosure/orientation and payload schema |
| Verification means | Field test at 500 m horizontal LOS or approved RF-equivalent with RSSI/SNR, legal/site controls and exact-binomial PDR analysis |
| Stimulus / scenario | Transmit N=300 unique 2 s frames carrying OBCC-LORA-PAYLOAD-v1.0 including deployment_status |
| Environment / configuration | 915 MHz RFM96W, matching 22 AWG 81.4 mm monopoles, SF7/BW125/CR4/5 unless waived, legal/EIRP/site/weather/interference recorded |
| Statistical method | Exact binomial N=300/k>=279 |
| Fault-hardening cases | antenna orientation, interference, duplicate frame, invalid CRC/schema, weather/site deviation |
| Pass/fail oracle | PASS iff k>=279 valid unique frames out of N=300, one-sided 95% exact-binomial lower PDR bound >=0.90, schema/status preserved, RSSI/SNR retained, and no illegal/site deviation. |
| Required evidence | scheduled/transmitted/received logs, RSSI/SNR, site/legal evidence, PDR calculation, photos |

## Reporting rules

Predeclare assembled CanSat article ID, subsystem hardware revisions, firmware/software commits, wiring/configuration state, equipment/calibration IDs, environment/site/safety authorization, deviations/waivers, and exact evidence archive path before execution. A missing required subsystem definition/report/disposition is **HOLD**. An unsafe condition, false deployment success, unapproved waiver, schema mismatch, or unbounded fault response is **FAIL** unless explicitly classified as a controlled non-execution limitation by the final review board.

## Definition views

| View | Source | Rendered |
|---|---|---|
| System verification chain | [`definition_views/SYS-RF-RANGE-PDR_view1_system_verification_chain.d2`](definition_views/SYS-RF-RANGE-PDR_view1_system_verification_chain.d2) | [`definition_views/SYS-RF-RANGE-PDR_view1_system_verification_chain.png`](definition_views/SYS-RF-RANGE-PDR_view1_system_verification_chain.png) |
