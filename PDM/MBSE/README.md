# PDM MBSE D2 shared context

This directory will hold D2 reconstructions of the historical PDM Capella raster views. Do not treat this file as a converted diagram; it is shared context for the conversion work.

## Canonical target D2 outputs

The legacy raster exports may contain physical, logical, functional-allocation, and exchange overlays in the same image. Treat those rasters as full-context references only: conversion agents must split the content into the canonical views below and must not preserve mixed overlays in a single D2 view. For each version, the canonical D2 source set is exactly the four files listed here.

### PDM v0.1

| View | Primary legacy context | Target D2 path |
| --- | --- | --- |
| Physical | `PDM/PDM_v0.1_S.png` | `PDM/MBSE/v0.1/PDM_v0.1_view1_physical.d2` |
| Logical | `PDM/PDM_v0.1_S.png` | `PDM/MBSE/v0.1/PDM_v0.1_view2_logical.d2` |
| Functional allocation | `PDM/PDM_v0.1_S.png`, `PDM/PDM_v0.1_FC.png` | `PDM/MBSE/v0.1/PDM_v0.1_view3_functional_allocation.d2` |
| Fall-test functional chain | `PDM/PDM_v0.1_FC.png` | `PDM/MBSE/v0.1/PDM_v0.1_view4_fall_test_chain.d2` |

### PDM v0.2

| View | Primary legacy context | Target D2 path |
| --- | --- | --- |
| Physical | `PDM/PDM_v0.2_S.png` | `PDM/MBSE/v0.2/PDM_v0.2_view1_physical.d2` |
| Logical | `PDM/PDM_v0.2_S.png` | `PDM/MBSE/v0.2/PDM_v0.2_view2_logical.d2` |
| Functional allocation | `PDM/PDM_v0.2_S.png`, `PDM/PDM_v0.2_FC.jpg` | `PDM/MBSE/v0.2/PDM_v0.2_view3_functional_allocation.d2` |
| Parachute deployment functional chain | `PDM/PDM_v0.2_FC.jpg` | `PDM/MBSE/v0.2/PDM_v0.2_view4_parachute_deployment_chain.d2` |

Render each D2 file to a `.png` next to it with ELK tight spacing:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```

## Strict view separation rules

These rules are acceptance criteria for PDM D2 conversion. When a legacy raster shows content from multiple MBSE concerns, move each element or exchange into the appropriate canonical view instead of copying the mixed overlay.

### Physical view

Allowed:

- `[System]`, `[PC]`, `[EA]`, and physical `[C]` nodes.
- `[PL]` physical links.

Not allowed:

- `[LC]`, `[F]`, `[FE]`, `[CE]`.

### Logical view

Allowed:

- Physical context: `[System]`, `[PC]`, and `[EA]` as allocation/deployment context.
- `[LC]` logical components.
- `[CE]` component exchanges.
- Logical `[C]` constraints/notes.

Not allowed:

- `[F]`, `[FE]`, `[PL]`.

### Functional allocation view

Allowed:

- `[System]`, `[PC]`, `[EA]`, `[LC]`, `[F]`, and allocation `[C]` constraints/notes.
- Functions nested under their allocated logical component or external actor where possible.

Not allowed:

- `[FE]`, `[CE]`, `[PL]`.

### Functional chain view

Allowed:

- A chain container.
- Participating `[F]` function nodes.
- `[FE]` functional exchanges.
- Chain-specific `[C]` constraints/notes.

Not allowed:

- `[System]`, `[PC]`, `[LC]`, `[EA]`, `[CE]`, `[PL]`.

## Shared D2 style block

Copy this block at the top of each PDM D2 file, then choose `direction` per view and iterate from the rendered PNG. Physical views usually start `direction: down`; functional chain views usually start `direction: right`.

```d2
vars: {
  d2-config: {
    layout-engine: elk
  }
}

# Pick per view; iterate after rendering.
direction: down

classes: {
  func: {
    shape: rectangle
    style: { fill: "#BDFB9B"; stroke: "#166534"; stroke-width: 2; font-size: 36 }
  }
  lc: {
    style: {
      fill: "#A9C7E6"; stroke: "#5B65C9"; stroke-width: 2
      border-radius: 20; font-size: 40
    }
  }
  pc: {
    style: { fill: "#FFF8BF"; stroke: "#D1B24A"; stroke-width: 2; font-size: 40 }
  }
  sys: {
    style: { fill: "#E6E6E6"; stroke: "#9A9A9A"; stroke-width: 2; font-size: 48 }
  }
  ea: {
    shape: rectangle
    style: {
      fill: "#BFEAF4"; stroke: "#5B65C9"; stroke-width: 2
      border-radius: 20; font-size: 40
    }
  }
  note: { style: { fill: "#FFF5B0"; stroke: "#D1B24A"; font-size: 32 } }
  chain: {
    style: {
      fill: "#FFFFFF"; stroke: "#D1B24A"; stroke-width: 2
      border-radius: 20; font-size: 36
    }
  }
  fe:   { style: { stroke: "#1F7A4D"; font-color: "#1F7A4D"; stroke-width: 2; font-size: 30 } }
  ce:   { style: { stroke: "#5B65C9"; font-color: "#5B65C9"; stroke-width: 2; font-size: 30 } }
  pl:   { style: { stroke: "#E11D28"; font-color: "#E11D28"; stroke-width: 2; font-size: 30 } }
  cstr: { style: { stroke: "#333333"; stroke-dash: 3; font-size: 26 } }
}
```

Use `shape: page` at the instance level for constraint notes, for example:

```d2
max_diameter_30cm: "[C] Max. diameter 30cm" { class: note; shape: page }
```

## Naming conventions

- Use stable lower-snake-case D2 IDs without semantic prefixes: `system`, `cansat`, `parachute_module`, `obcc_module`, `pdm_processing`, `set_servo_init_state`.
- Reflect Capella allocation with D2 nesting/path IDs: `system.cansat.parachute_module.servo.trigger.retain_position` for allocated physical/logical/function content.
- Disambiguate duplicate connector-like names by owner: `obcc_backplane_connector`, `backplane_obcc_headers`, `pdm_jst_connector`.
- Labels must carry the Capella prefix: `[System]`, `[PC]`, `[LC]`, `[EA]`, `[F]`, `[C]`, `[PL]`, `[CE]`, `[FE]`.
- Preserve Capella names and exchange payload brackets when known, e.g. `[FE] Close Signal [PWM]`; use line breaks only for readability.
- Physical links are undirected (`--`, class `pl`). Component exchanges and functional exchanges are directed (`->`, classes `ce` and `fe`). Constraint links use class `cstr` and no label.
- Do not copy a legacy raster's mixed overlays into one D2 file. Move `[PL]` content to the physical view, `[LC]`/`[CE]` content to the logical view, allocated `[F]` content to the functional allocation view, and `[FE]` sequences to the functional chain view.
- Functional chain views must remain focused on chain participation: the chain container, participating `[F]` functions, `[FE]` exchanges, and chain-specific `[C]` notes only. If a raster shows actors, components, physical links, or component exchanges around a chain, represent that context in the physical, logical, or functional allocation views instead.

## PDM v1.0 extraction summary

Extractor command used:

```sh
uv run ~/agent-tools/syseng/skills/capella-xml-extractor/scripts/extract_capella_diagram.py \
  'PM&SE/capella' \
  --diagram 'PDM v1.0'
```

The extractor reported `validation.ok: true` with counts: 1 system, 1 external actor, 13 physical components, 5 logical components, 14 functions, 1 constraint, 15 physical links, 3 component exchanges, 12 functional exchanges, and 1 constraint link.

### Visible structure and allocations

- `[System] Physical System`
  - `[PC] CanSat`
    - `[PC] Parachute Module`
      - `[PC] Cap`
        - `[LC] Parachute Holder`: `[F] Separate from Module`, `[F] Stay shut`
      - `[PC] Parachute`
        - `[LC] Descent speed control`: `[F] Unfold`, `[F] Limit terminal speed`, `[F] Fold`
      - `[PC] Servo`
        - `[LC] Trigger`: `[F] Retain position`, `[F] Reach closed position`, `[F] Reach open position`
    - `[PC] Backplane PCB`
      - `[PC] 1x3 PDM JST Connector`
      - `[PC] Spine`
      - `[PC] 2mm 2x6 OBCC Headers`
    - `[PC] OBCC Module`
      - `[PC] OBCC PCB`
        - `[PC] XIAO ESP32-S3`
          - `[LC] PDM Processing`: `[F] Set Servo init state`
          - `[LC] OBCC`: `[F] Send close signal to Servo`, `[F] Send open signal to Servo`, `[F] Collect peripheral init states`
        - `[PC] Backplane Connector`
- `[EA] User`: `[F] Place cap`, `[F] Reintroduce parachute`
- `[C] Max. diameter 30cm` is attached to `[PC] Parachute`.

### Physical links

- `[PL] 3V3 Power traces`: OBCC PCB -- OBCC PCB
- `[PL] Backplane Fixture`: OBCC Module -- Backplane PCB
- `[PL] Backplane Fixture`: Backplane PCB -- Parachute Module
- `[PL] Cap Fixture`: Cap -- Parachute Module
- `[PL] Footprint`: 1x3 PDM JST Connector -- Spine
- `[PL] Footprint`: 2mm 2x6 OBCC Headers -- Spine
- `[PL] Footprint`: Backplane Connector -- OBCC PCB
- `[PL] Nylon thread`: Parachute -- Parachute Module
- `[PL] PWM trace`: OBCC PCB -- OBCC PCB
- `[PL] Parallel Cable`: Backplane Connector -- 2mm 2x6 OBCC Headers
- `[PL] Rotating link`: Cap -- Servo
- `[PL] Screws`: OBCC Module -- OBCC PCB
- `[PL] Servo cable`: Servo -- 1x3 PDM JST Connector
- `[PL] Servo fixture`: Servo -- Parachute Module
- `[PL] XIAO Footprint`: XIAO ESP32-S3 -- OBCC PCB

### Component exchanges

- `[CE] PWM`: OBCC -> Trigger
- `[CE] PWM`: Trigger -> PDM Processing
- `[CE] Torque`: Trigger -> Parachute Holder

### Functional exchanges

- `[FE] Cap placed []`: Place cap -> Stay shut
- `[FE] Close Signal [PWM]`: Send close signal to Servo -> Reach closed position
- `[FE] Close signal [PWM]`: Set Servo init state -> Reach closed position
- `[FE] Holder open []`: Separate from Module -> Unfold
- `[FE] Init state [Result]`: Set Servo init state -> Collect peripheral init states
- `[FE] Open signal [PWM]`: Send open signal to Servo -> Reach open position
- `[FE] Parachute deployed []`: Unfold -> Limit terminal speed
- `[FE] Parachute reintroduced []`: Reintroduce parachute -> Fold
- `[FE] Servo closed []`: Retain position -> Stay shut
- `[FE] Servo open []`: Retain position -> Separate from Module
- `[FE] Servo reached closed position []`: Reach closed position -> Retain position
- `[FE] Servo reached open position []`: Reach open position -> Retain position

## Historical raster vs current XML

The old v0.1/v0.2 raster images remain the source context for historical content, but not for view boundaries. Reproduce the components, functions, exchanges, and omissions shown in those images in the appropriate canonical view according to the strict separation rules above. Use the current `PDM v1.0` XML extraction above only to normalize names and semantics when applicable. If a raster contains content not present in `PDM v1.0`, keep that historical content faithful and document the drift in comments in the relevant D2 file.
