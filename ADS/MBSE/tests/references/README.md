# ADS MBSE-wide references

This directory contains additional references for the ADS-wide corpus in `../ADS_MBSE_CORPUS.md`.

## Reused version-specific corpus

Most ADS behavioral references are already saved in:

- `../../v0.2/tests/references/`

That corpus includes:

- ESA CanSat guidance/book and CanSat literature.
- NASA Systems Engineering Handbook.
- NASA GEVS GSFC-STD-7000B.
- GPS SPS Performance Standard 2020.
- u-blox G7020 product summary and u-blox receiver protocol material.
- TDK ICM-20948 datasheet and product page.
- NXP UM10204 I2C-bus specification.
- ISO/IEC/IEEE 29119 software testing overview.
- NIST tolerance interval pages and binomial reliability demonstration reference.

## Additional ADS-wide sources

Saved in `sources/`:

| Local source | Use in ADS-wide tests |
|---|---|
| `nasa_std_8739_3_soldered_electrical_connections.pdf`, `.txt` | Soldered electrical connection workmanship, visual inspection, cleanliness, ESD, and solder-joint acceptance context for ADS PCB assembly. |
| `nasa_std_8739_4a_crimping_cables_harnesses.pdf`, `.txt` | Crimping/interconnecting cable/harness/connector workmanship context for backplane fixtures, parallel cables, headers, strain relief, and connector inspection. |
| `nasa_std_8739_4_cables_harnesses_page.md` | NASA official standards page for NASA-STD-8739.4. |
| `ipc_a_610_overview_wevolver.md`, `ipc_a_610_overview_nextpcb.md` | Public overview context for IPC-A-610 as electronic-assembly acceptability/inspection guidance; not a substitute for the controlled IPC standard. |
| `ipc_a_610j_official_overview.diagnostics/*` | Diagnostics from the official IPC store page fetch; static extraction returned an access shell, but the search record preserves the official description. |

Saved in `searches/`:

- `nasa-std-8739-3-soldered-electrical-connections.json`
- `nasa-std-8739-4-cables-harnesses.json`
- `ipc-a-610-pcb-assembly-inspection.json`
- `ipc-official-a-610.json`

## Notes

- IPC-A-610 itself is a controlled/commercial standard; only public overview/search artifacts are saved here.
- For flight or competition acceptance, use the actual project/competition workmanship criteria when they differ from these references.
