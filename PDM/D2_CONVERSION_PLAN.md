# PDM Capella Diagram D2 Conversion Plan

Goal: convert every Capella diagram image currently referenced from `PDM/README.md` into D2 source, using `PM&SE/capella` as the semantic source where applicable, and keep the resulting PDM diagrams visually/semantically consistent with the existing MBSE D2 diagrams in the repository.

## Source inventory

Current PDM diagram images:

| Image | Caption in `PDM/README.md` | Target D2 location |
| --- | --- | --- |
| `PDM/PDM_v0.1_S.png` | PDM v0.1 structure. The dummy CanSat is S&A v0.1. | `PDM/MBSE/v0.1/PDM_v0.1_view1_physical.d2` |
| `PDM/PDM_v0.1_FC.png` | PDM v0.1 fall test functional chain. | `PDM/MBSE/v0.1/PDM_v0.1_view2_fall_test_chain.d2` |
| `PDM/PDM_v0.2_S.png` | PDM v0.2 structure. | `PDM/MBSE/v0.2/PDM_v0.2_view1_physical.d2` |
| `PDM/PDM_v0.2_FC.jpg` | PDM v0.2 parachute deployment test functional chain. | `PDM/MBSE/v0.2/PDM_v0.2_view2_parachute_deployment_chain.d2` |

For each `.d2`, commit a rendered `.png` next to it, following the convention used by `ADS/MBSE`, `AMS/MBSE`, `DPS/MBSE`, and `PDS&ESS/MBSE`.

## Semantic source of truth

- Capella XML project: `PM&SE/capella`.
- Relevant current Capella diagram: `PDM v1.0` in the Physical Architecture viewpoint.
- Extraction command:

```sh
uv run ~/agent-tools/syseng/skills/capella-xml-extractor/scripts/extract_capella_diagram.py \
  'PM&SE/capella' \
  --diagram 'PDM v1.0'
```

Use the extracted elements/exchanges to normalize names and semantics when old raster images are ambiguous. The old images remain the view-specific source of which version/view must be represented. If an old image contains content not present in the current XML, reproduce the image faithfully but use Capella-style labels (`[PC]`, `[LC]`, `[F]`, `[FE]`, `[CE]`, `[PL]`, `[C]`) and document any known drift in D2 comments.

## D2 style and rendering conventions

- Use the same class palette and label prefixes as the existing MBSE D2 files, especially `ADS/MBSE/v1.0/ADS_v1.0_view1_physical.d2` and related chain views.
- Render with ELK and tight spacing:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```

- Inspect the rendered PNG, not just the source. Iterate until labels are readable, semantic prefixes are correct, and obvious crossings/overlaps are removed.
- Avoid inventing fake semantics to force layout. Invisible edges are allowed only as explicitly commented layout-only aids.
- Notes/constraints use `shape: page` at the instance level.

## Work breakdown

1. Create a shared PDM MBSE D2 style/reference file and extraction summary.
2. Convert `PDM_v0.1_S.png` to `PDM/MBSE/v0.1/PDM_v0.1_view1_physical.d2` plus render.
3. Convert `PDM_v0.1_FC.png` to `PDM/MBSE/v0.1/PDM_v0.1_view2_fall_test_chain.d2` plus render.
4. Convert `PDM_v0.2_S.png` to `PDM/MBSE/v0.2/PDM_v0.2_view1_physical.d2` plus render.
5. Convert `PDM_v0.2_FC.jpg` to `PDM/MBSE/v0.2/PDM_v0.2_view2_parachute_deployment_chain.d2` plus render.
6. Run integration QA: render every PDM D2 file, compare against source images and Capella extraction, fix consistency drift, and update `PDM/README.md` to reference the new MBSE renders/source files while preserving old raster images as historical inputs.

## Acceptance criteria

- Every PDM Capella diagram image has a corresponding `.d2` source and rendered `.png` in `PDM/MBSE/...`.
- All generated D2 files parse and render successfully with the preferred ELK command.
- Diagrams use consistent labels, colors, prefixes, and hierarchy with the rest of the repo.
- Diagrams are semantically consistent with `PM&SE/capella` where the model contains the same elements.
- `PDM/README.md` points readers to the D2-backed diagrams.
- Temporary orchestration issue files are removed before completion.
