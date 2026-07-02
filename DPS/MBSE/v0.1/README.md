# DPS v0.1 MBSE Views

DPS v0.1 is functionally equivalent to DPS v1.0, with hardware-only downgrades:

- The datalogger-side XIAO and RFM96W LoRa sit directly on a circuitboard; there is no CanSat, OBCC module, OBCC PCB, or backplane connector.
- The datalogger-side XIAO contains one logical component: `[LC] Dummy Datalogger`, with the same functions as the v1.0 OBCC logical component.
- The ground station uses a `[PC] Ground Station Circuitboard`; there is no ground-station PCB.
- Functional chain views 4–9 keep the v1.0 chain content; only the version label was updated to v0.1.
