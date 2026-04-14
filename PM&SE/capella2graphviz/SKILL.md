---
name: capella2graphviz
description: Generate and iteratively refine Graphviz diagrams that mimic Capella / Arcadia-style systems engineering views in a consistent manner.
---

# Capella to Graphviz

This skill is the reusable entry point for converting Capella-style diagrams and screenshots into Graphviz diagrams.

Use it to:
- reconstruct Capella / Arcadia views from screenshots,
- refine existing `.dot` diagrams,
- extract structure from Capella model files when available,
- keep output visually recognisable as a systems-engineering diagram rather than a generic node-link graph.

## Skill structure

- `SKILL.md` — index, workflow, and reusable best practices
- `PHYSICAL_ARCHITECTURE_BLANK.md` — diagram-type guidance for Physical Architecture Blank views
- `CAPELLA_XML.md` — XML / AIRD extraction workflow when Capella project files are available

When working a task, start here, then follow the complementary document that matches the diagram type.

## Working method

When asked to create or improve a Capella-like diagram:

1. **Read the existing `.dot` file completely** if one exists.
2. If the source is an image **and a Capella project is available**, use `*.aird` for diagram membership/layout and `*.capella` for semantic structure. See `CAPELLA_XML.md`.
3. **Render early and often** with Graphviz (`dot -Tpng`, `dot -Tsvg`).
4. **Inspect the rendered image**, not just the DOT source.
5. **Iterate visually**:
   - identify the most obvious layout problems,
   - make a few targeted changes,
   - render again,
   - inspect again.
6. Prefer **legibility and recognisable Capella composition** over rigid mechanical symmetry.
7. Keep the user informed, but stay concise.

The core rule: **a Capella-like DOT file is only good when the rendered image looks good**.

## Reconstruction principles

### Reconstruct the diagram, do not embed the source image
If the input is a screenshot, PDF, or raster image:
- treat it as a reference and acceptance target,
- infer structure, labels, composition, and routing from it,
- recreate the view with Graphviz nodes, clusters, and edges.

Do **not** solve the task by embedding the source screenshot as:
- a giant image-backed node,
- an HTML label that simply shows the screenshot,
- a background image that replaces reconstruction.

### Preserve composition before polishing details
First recover the large-scale layout:
- outer container,
- first-level internal blocks,
- external actors/components,
- note or constraint lanes,
- top/bottom/left/right reading order.

Do not spend time polishing labels or edge routing before the major composition matches the source.

### Use the source diagram's reading direction
Choose `rankdir` from the source image, not by habit:
- vertically stacked architecture → usually `rankdir=TB`
- strongly left-to-right flow → usually `rankdir=LR`

## Reusable Capella-style conventions

Use these defaults unless the source diagram or user asks for something else.

### Visual semantics

#### External actors
- visually distinct from internal subsystem content
- often blue rounded containers
- typical style:
  - `fillcolor="#BFEAF4"`
  - `color="#5B65C9"`
  - `style="filled,rounded"`
  - `penwidth=2`
- often modeled functionally, but may also be **hybrid participants**:
  - green functional exchanges may connect to the actor's functions/behaviors
  - red physical/component exchanges may connect to the actor's physical container/component level or representative physical anchor when the actor is also a real physical participant/device/interface

#### Physical components / physical subsystems
- pale yellow containers
- typical style:
  - `fillcolor="#FFF8BF"`
  - `color="#D1B24A"`
  - `style="filled"` or `style="filled,rounded"`
  - `penwidth=2`

#### Functional blocks / logical behavior containers
- light blue rounded containers
- typical style:
  - `fillcolor="#A9C7E6"`
  - `color="#5B65C9"`
  - `style="filled,rounded"`
  - `penwidth=2`

#### Functions
- green function boxes
- typical style:
  - `fillcolor="#BDFB9B"`
  - `color="#166534"`

#### Constraints / annotation notes
- pale yellow note-like boxes
- typical style:
  - `fillcolor="#FFF5B0"`
  - `color="#D1B24A"`

### Exchange semantics

#### Functional exchanges
- usually **function -> function**
- green arrows
- typical style:
  - `color="#1F7A4D"`
  - `fontcolor="#1F7A4D"`

#### Physical / component exchanges
- red arrows
- represent physical links, component exchanges, interfaces, carried items
- typical style:
  - `color="#E11D28"`
  - `fontcolor="#E11D28"`

#### Constraint links
- dashed dark gray lines
- usually annotative rather than flow-driving
- typical style:
  - `style=dashed`
  - `color="#333333"`
  - `constraint=false`

## What may connect to what

### Functional exchanges
Functional exchanges should usually connect **function to function**.

Do not terminate behavioral exchanges on physical containers when the semantics are clearly functional.

#### Mediated service-function pattern
When a component contains an internal chain such as:
- measurement / sensing,
- processing / calculation / validation,
- service / response / reporting,

prefer to model the **service/respond/report function as the visible interaction boundary** for external consumers.

Use this reusable pattern:
- internal measurement or sensing functions feed processing/calculation functions,
- processing/calculation functions feed a visible service/respond/report function,
- external read/request/query/get functions interact with that service/respond/report function,
- avoid drawing external read/request/query/get functions directly to internal measurement functions when a visible service/respond/report function is part of the intended behavior.

This helps preserve the diagram's behavioral layering:
- internal functions create or prepare the data,
- the service/respond/report function exposes it,
- external consumers interact with the exposed service, not with hidden internal measurement steps.

Direct external-to-measurement links are only appropriate when the measurement function is itself explicitly the exposed service boundary in the source semantics.

Typical reusable names for the mediating function include:
- `Respond to ... requests`
- `Provide ... data`
- `Serve ... value`
- `Report ... state`
- `Return ... measurement`

### Physical / component exchanges
Red physical exchanges should connect:
- physical component ↔ physical component,
- subsystem ↔ subsystem,
- component ↔ port/terminal/connector anchor,
- physically participating external actor ↔ physical component/subsystem.

Red physical/component exchanges should **not** start or end at green function boxes.

If a physical component contains an inner logical/functional block with the same or a similar name, a named physical link must terminate on the **physical container/component level** or on its representative physical anchor, not on the inner logical block.

When Graphviz needs help routing a container-to-container exchange, use **invisible representative anchor nodes**:
- place one anchor node inside each relevant container,
- keep it invisible if it only exists for routing,
- place it near the side/port where the exchange should visually attach,
- connect anchor to anchor,
- use `ltail=cluster_*` and `lhead=cluster_*` when appropriate.

This invisible-anchor placement technique is the standard reusable pattern for physical/container exchanges in this skill.

## Preferred Graphviz defaults

Start with:

```dot
graph [
  rankdir=TB,
  splines=polyline,
  nodesep=0.5,
  ranksep=0.85,
  pad=0.25,
  bgcolor="white",
  fontname="Helvetica",
  compound=true,
  forcelabels=true,
  newrank=true
];
node [shape=box, style="filled", fontname="Helvetica", fontsize=18, margin="0.18,0.12"];
edge [fontname="Helvetica", fontsize=16, penwidth=2.5, arrowsize=0.8];
```

### Default layout advice
- Prefer `splines=polyline` when label readability matters.
- Prefer `xlabel=` over `label=` for dense exchange labeling.
- Use clusters for visible Capella containers.
- Use a small number of invisible edges as layout hints.
- Avoid over-constraining the graph with too many rigid rank rules.

## Generic workflow for screenshot reconstruction

1. Identify the outer subsystem/container.
2. Identify first-level blocks and their relative positions.
3. Identify external actors/components and note lanes.
4. Build cluster hierarchy first.
5. Add functions/internal behavior.
6. When a component has an internal measurement/processing pipeline plus a visible service/respond function, keep that mediation explicit rather than shortcutting external reads into the internal pipeline.
7. Add exchanges using the correct semantic color/style.
8. Render and compare against the source.
9. Fix composition first, then routing, then labels.

## Generic workflow for XML-assisted reconstruction

When `*.aird` and `*.capella` exist:
1. locate the target diagram in `*.aird`,
2. read its nested containers/nodes/edges,
3. resolve semantic ids in `*.capella`,
4. map visible container hierarchy to Graphviz clusters,
5. render,
6. use the screenshot as the final visual acceptance check.

See `CAPELLA_XML.md` for extraction details.

## Diagram-type guidance

Use complementary files for diagram-type-specific practices:
- **Physical Architecture Blank** → `PHYSICAL_ARCHITECTURE_BLANK.md`

Add new complementary files beside this one as new Capella view types become relevant.

## Quality checklist before finalizing

Before declaring a diagram done, verify that:
1. the major composition matches the source image,
2. the reading order is intuitive,
3. physical links are reasonably short and legible,
4. labels are readable,
5. note/constraint boxes do not clutter the core architecture,
6. visible container hierarchy is still clear,
7. the **rendered image**, not just the DOT file, looks good.

## Tooling workflow

Typical workflow inside the coding agent:
1. `read` the `.dot` file
2. `edit` the file in targeted replacements
3. render with Graphviz
4. inspect the render
5. iterate until the image is clean and readable
