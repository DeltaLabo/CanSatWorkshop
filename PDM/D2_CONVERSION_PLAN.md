# PDM Capella Diagram D2 Conversion Plan

Goal: convert the Capella diagram images in `PDM/` into D2 **while strictly separating the MBSE views**. The raster exports provide historical context, but the committed D2 set must follow the repository convention used by other subsystems:

1. physical view,
2. logical view,
3. functional allocation view,
4. functional chain view(s).

This replaces the earlier hybrid transcriptions: do not keep physical/logical/function/exchange overlays mixed in one D2 view just because the legacy raster did so.

## Source inventory

Current legacy PDM raster exports:

| Image | Caption in `PDM/README.md` | How to use it |
| --- | --- | --- |
| `PDM/PDM_v0.1_S.png` | PDM v0.1 structure. The dummy CanSat is S&A v0.1. | Context for v0.1 physical, logical, and functional allocation views. |
| `PDM/PDM_v0.1_FC.png` | PDM v0.1 fall test functional chain. | Context for the v0.1 fall-test functional chain and allocation. |
| `PDM/PDM_v0.2_S.png` | PDM v0.2 structure. | Context for v0.2 physical, logical, and functional allocation views. |
| `PDM/PDM_v0.2_FC.jpg` | PDM v0.2 parachute deployment test functional chain. | Context for the v0.2 deployment functional chain and allocation. |

Capella XML source:

- Project directory: `PM&SE/capella`
- Relevant current diagram for name/semantic normalization: `PDM v1.0` in the Physical Architecture viewpoint.

Extraction command:

```sh
uv run ~/agent-tools/syseng/skills/capella-xml-extractor/scripts/extract_capella_diagram.py \
  'PM&SE/capella' \
  --diagram 'PDM v1.0'
```

Use current XML names where they clearly correspond to legacy elements, but preserve historical names where the raster is explicitly different (`Dummy CanSat`, `Top module`, `XIAO ESP32-C3`, `Parachute trigger`, etc.). Document historical/XML drift in D2 comments.

## Strict target D2 set

For each `.d2`, commit a rendered `.png` next to it.

### PDM v0.1

| View | Target D2 path |
| --- | --- |
| Physical | `PDM/MBSE/v0.1/PDM_v0.1_view1_physical.d2` |
| Logical | `PDM/MBSE/v0.1/PDM_v0.1_view2_logical.d2` |
| Functional allocation | `PDM/MBSE/v0.1/PDM_v0.1_view3_functional_allocation.d2` |
| Fall-test functional chain | `PDM/MBSE/v0.1/PDM_v0.1_view4_fall_test_chain.d2` |

### PDM v0.2

| View | Target D2 path |
| --- | --- |
| Physical | `PDM/MBSE/v0.2/PDM_v0.2_view1_physical.d2` |
| Logical | `PDM/MBSE/v0.2/PDM_v0.2_view2_logical.d2` |
| Functional allocation | `PDM/MBSE/v0.2/PDM_v0.2_view3_functional_allocation.d2` |
| Parachute deployment functional chain | `PDM/MBSE/v0.2/PDM_v0.2_view4_parachute_deployment_chain.d2` |

Remove or rename old non-canonical files such as `*_view2_*chain.d2` so the final `PDM/MBSE` tree does not present hybrid/incorrect numbering.

## Separation rules

These rules are the acceptance criteria for the converted D2 files.

### Physical view

Allowed:

- `[System]`, `[PC]`, `[EA]` containers/nodes when physically relevant.
- `[PL]` physical links.
- physical constraints/notes `[C]` with `shape: page`.

Not allowed:

- `[LC]`, `[F]`, `[FE]`, `[CE]`.

### Logical view

Allowed:

- physical containment context (`[System]`, `[PC]`, `[EA]`) as allocation/deployment context;
- `[LC]` logical components;
- `[CE]` component exchanges;
- logical constraints/notes `[C]`.

Not allowed:

- `[F]`, `[FE]`, `[PL]`.

### Functional allocation view

Allowed:

- `[System]`, `[PC]`, `[EA]`, `[LC]`, `[F]`, and constraints `[C]`.
- Nest functions under their allocated logical/actor component.

Not allowed:

- `[FE]`, `[CE]`, `[PL]`.

### Functional chain views

Allowed:

- a chain container;
- participating `[F]` function nodes;
- `[FE]` functional exchanges;
- chain-specific constraints/notes `[C]`.

Not allowed:

- `[System]`, `[PC]`, `[LC]`, `[EA]` owner/context containers;
- `[CE]`, `[PL]`.

If the legacy raster shows actors, components, physical links, or component exchanges in a functional chain export, move that information into physical/logical/allocation views and keep the chain D2 focused on functions and FEs only.

## D2 style and rendering conventions

- Use the same class palette and label prefixes as the existing MBSE D2 files, especially `ADS/MBSE/v1.0/ADS_v1.0_view1_physical.d2`, `ADS/MBSE/v1.0/ADS_v1.0_view2_logical.d2`, `ADS/MBSE/v1.0/ADS_v1.0_view3_functional_allocation.d2`, and `ADS/MBSE/v1.0/ADS_v1.0_view4_gps_position_chain.d2`.
- Render with ELK and tight spacing:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```

- Inspect the rendered PNG, not just the D2 source.
- Avoid fake semantic nodes or invented exchanges. Invisible layout edges are allowed only if explicitly commented.

## Work breakdown

1. Update shared PDM MBSE context to describe the strict view separation and target file set.
2. Refactor PDM v0.1 into canonical physical/logical/functional-allocation/fall-chain D2 files and renders.
3. Refactor PDM v0.2 into canonical physical/logical/functional-allocation/deployment-chain D2 files and renders.
4. Run integration QA: render every PDM D2 file, verify separation rules, update `PDM/README.md`, and remove obsolete non-canonical generated files.

## Acceptance criteria

- Final `PDM/MBSE/v0.1` and `PDM/MBSE/v0.2` each contain exactly four canonical D2 sources and four matching rendered PNGs.
- No physical view contains `[LC]`, `[F]`, `[FE]`, or `[CE]`.
- No logical view contains `[F]`, `[FE]`, or `[PL]`.
- No functional allocation view contains `[FE]`, `[CE]`, or `[PL]`.
- No functional chain view contains `[System]`, `[PC]`, `[LC]`, `[EA]`, `[CE]`, or `[PL]`.
- All D2 files render successfully with the preferred ELK command.
- `PDM/README.md` references the D2-backed canonical views and preserves links to the legacy raster exports.
