---
name: capella2graphviz
description: Generate and iteratively refine Graphviz diagrams that mimic Capella / Arcadia-style systems engineering views in a consistent manner.
---

# Capella to Graphviz

## Working method

When asked to create or improve a Capella-like diagram:

1. **Read the existing `.dot` file completely** if one exists.
2. If the source is an image **and a Capella project is available**, prefer extracting structure from:
   - `*.aird` for diagram membership and layout
   - `*.capella` for semantic structure
   See `CAPELLA_XML.md` in this skill folder.
3. **Render / re-render the diagram** (`dot -Tpng`, `dot -Tsvg`) early and often.
4. **Inspect the rendered image**, not just the source.
   - Do not assume the DOT layout will look good from code alone.
   - View the PNG or SVG and judge the actual visual result.
5. **Iterate on layout**.
   - Make one or a few targeted changes.
   - Re-render.
   - Inspect again.
6. Prefer **aesthetics and diagram legibility** over strict mechanical symmetry.
7. Keep the user informed, but stay concise.

The key lesson: **Capella-like Graphviz diagrams must be visually iterated**. Good structure in DOT does not guarantee a good rendered diagram.

When the input is an existing image (JPG/PNG/PDF screenshot), first treat it as a **layout to reconstruct**, not just semantics to restate.
The source image is a **reference and acceptance target**, not an asset to embed as the finished Graphviz result.
If exact reconstruction matters and the Capella model files are available, prefer XML-assisted reconstruction over image-only guessing.

### Forbidden shortcut: embedding the source image as the diagram
Do **not** "solve" an image-to-Graphviz task by placing the original screenshot, raster image, or PDF into the DOT as the main content.
This includes patterns such as:
- a single giant node whose label/image is the source screenshot,
- HTML-like labels that just display the source image,
- `image=...` on the main node or main structure,
- using the source screenshot as a background that replaces reconstruction.

Those approaches may visually match the input, but they are **not Graphviz reconstructions** and do not satisfy the task.
Use the source image only to infer structure, composition, labels, and layout quality; the final DOT must recreate the view with Graphviz nodes, clusters, and edges.

---

## Capella-style visual semantics

Use these visual conventions unless the user requests otherwise.

### External actors
External actors should be visually distinct from internal subsystem content.

- Represent as a cluster/subgraph if it contains functions.
- Typical style:
  - `fillcolor="#BFEAF4"`
  - `color="#5B65C9"`
  - `style="filled,rounded"`
  - `penwidth=2`
- Label example:
  - `User`

This is a **special color treatment** distinct from the internal physical architecture.

### Physical components / physical subsystems
Use Capella-like pale yellow containers.

- Typical style:
  - `fillcolor="#FFF8BF"`
  - `color="#D1B24A"`
  - `style="filled"` or `style="filled,rounded"`
  - `penwidth=2`

Examples:
- `PDS Circuitboard`
- `Protection Circuit`
- `Regulator`
- `1s1P Li-Ion`

### Functional blocks / logical behavior containers
Use light blue rounded containers.

- Typical style:
  - `fillcolor="#A9C7E6"`
  - `color="#5B65C9"`
  - `style="filled,rounded"`
  - `penwidth=2`

Examples:
- `Battery`
- `Power Protection`
- inner `Regulator`

### Functions
Use green function boxes.

- Typical style:
  - `fillcolor="#BDFB9B"`
  - `color="#166534"`

Examples:
- `Store energy`
- `Provide power`
- `Restore power`
- `Cut off power`
- `Regulate voltage`
- `Switch power on`
- `Switch power off`

### Constraints / non-functional requirement annotations
Use pale yellow note-like boxes.

- Typical style:
  - `fillcolor="#FFF5B0"`
  - `color="#D1B24A"`

Example:
- `{c} Screw terminal or crimped cables`

Constraints do **not** need to live inside the constrained subsystem. They may be placed outside if that improves readability, as long as they point to the element they constrain.

---

## Exchange / link semantics

### Functional exchanges
Use green arrows.

- Typical style:
  - `color="#1F7A4D"`
  - `fontcolor="#1F7A4D"`

These typically connect **function to function**.

Examples:
- actor function -> system function
- internal function -> internal function

### Physical links / component exchanges
Use red arrows.

- Typical style:
  - `color="#E11D28"`
  - `fontcolor="#E11D28"`

These are used to represent:
- physical links
- component exchanges
- named physical interfaces / carried items

Examples:
- `Battery Cable JST`
- `PC Out / GND`
- `5V / 3V3 / GND`

### Constraint links
Use dashed dark gray / black lines.

- Typical style:
  - `style=dashed`
  - `color="#333333"`
  - often `constraint=false`

These annotate rather than participate in system flow.

---

## What may connect to what

Use these rules unless the user wants a different modeling style.

### Functions connect to functions
Functional exchanges should usually connect:
- function -> function

Do not terminate functional exchanges on physical components when the source semantics are behavioral.

Examples:
- `Switch power on` -> `Restore power`
- `Provide power` -> `Regulate voltage`

### Physical/component exchanges connect physical things, but Graphviz often routes through representative nodes
Conceptually, physical links belong between:
- physical component <-> physical component
- physical subsystem <-> physical subsystem
- component/block <-> component/block
- terminal/port/connector anchor <-> terminal/port/connector anchor

**Explicit rule:** red physical/component exchanges must **not** start or end at green function boxes.
They must attach to physical elements or to representative physical anchor nodes that stand in for a component, subsystem, port, terminal, or connector.

However, in Graphviz, cluster-to-cluster links are usually implemented by connecting **invisible representative physical anchor nodes** and using:
- `ltail=cluster_*`
- `lhead=cluster_*`

This is often the best practical compromise.
Keep those representative nodes visually invisible whenever they exist only to support routing, and place them deliberately near the side/port/terminal where the exchange should appear to enter or leave the container.
If a red link seems to need to touch a function, introduce a nearby physical anchor node instead and connect the red link to that anchor.

### Constraints connect to constrained elements
Constraint notes should point to the element they constrain.
This can be:
- a component
- a terminal
- a function
- a subsystem/container

In practice, it is often easiest and clearest to point to a representative node.

---

## Preferred Graphviz defaults

For these Capella-like diagrams, start with:

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

### Why `splines=polyline`
Use `polyline` rather than `ortho` when label readability matters.

Observed result from iteration:
- `splines=ortho` made edge labels harder to place and triggered Graphviz warnings for normal edge labels.
- `splines=polyline` produced better overall readability.

### Why `xlabel=`
For exchange labels, prefer `xlabel=` over `label=` when the diagram is dense.

Observed result from iteration:
- `label=` with `ortho` was poor.
- `xlabel=` worked better and avoided the orthogonal-edge label warning.
- Best practical result in this task: **`xlabel=` + `splines=polyline`**.

---

## Image-to-Graphviz reconstruction playbook

When converting an existing Capella screenshot/image into Graphviz, follow this sequence before writing DOT:

0. **Reject source-image embedding shortcuts**
   - Do **not** embed the original screenshot/image/PDF as the output diagram's main content.
   - The deliverable must be a reconstructed Graphviz diagram, not a wrapper around the source asset.

1. **Read the image as a spatial composition**
   - Identify the outer subsystem container.
   - Identify every first-level block inside it.
   - Identify external actors/components outside it.
   - Identify which side each major block belongs to: left, right, top, bottom, center.

2. **Preserve the original topology first**
   - If the source image already has a clean arrangement, keep that arrangement.
   - Do **not** re-invent the layout unless the source is obviously messy.
   - Typical mistake: semantically correct but spatially very different reconstruction.

3. **Choose the graph direction from the source image, not by habit**
   - If the source stacks major elements vertically, prefer `rankdir=TB`.
   - If the source reads left-to-right, prefer `rankdir=LR`.
   - For Capella screenshots, `rankdir=TB` is often the safer default because subsystems and blocks are commonly stacked vertically.

4. **Sketch major lanes/ranks before details**
   - Define invisible ordering among major blocks first.
   - Then add inner functions and exchanges.
   - Then add constraints/annotations last.

5. **Render early before polishing labels**
   - First get major placement right.
   - Only then refine exchanges, labels, and note locations.

6. **Do a composition-first acceptance check before detailed routing**
   - Compare the render against the source image side by side.
   - Reject the render immediately if the major composition is wrong, even if many labels and exchanges are already present.
   - Also reject any result that merely displays the source image instead of reconstructing it.
   - Only continue into detailed exchange cleanup once the big blocks are in the right regions of the page.

### Strong recommendation for screenshots with many cross-boundary edges
Prefer **clusters with ordinary nodes** over a single giant HTML-table node when many external edges must attach to internal elements.
If the AIRD already exposes a nested container hierarchy, mirror that directly into Graphviz clusters.

Why:
- giant HTML-table nodes often cause huge looping edges
- port routing becomes visually brittle
- labels end up far from the meaningful segment
- the result may be semantically rich but aesthetically poor

Use HTML-like labels only when:
- the block is mostly self-contained, or
- there are few external edges to its internals

If a block has many incoming/outgoing exchanges to internal functions, prefer:
- nested `cluster_*` containers
- explicit function nodes
- invisible ordering edges for alignment

### Placement rules for reconstructed images

If the source image shows these relative positions, preserve them:
- external actors/components on the left stay on the left
- constraints on the right stay on the right
- top battery/source blocks stay at the top
- bottom software/controller blocks stay at the bottom
- internal hardware board blocks stay central

For the PDS v0.2 image specifically, the source composition is roughly:
- top: `1S1P Li-Ion`
- middle: `PDS Circuitboard`
- bottom: `XIAO ESP32-S3`
- left exterior: `Charger`, `User`
- right exterior: constraint notes

A one-shot reconstruction should preserve that broad composition.

### Common failure modes to avoid

1. **Huge looping red or green edges**
   - Usually caused by poor major-block ordering or giant HTML-table ports.

2. **External actors/components placed on the wrong side**
   - If the source has `User` and `Charger` on the left, keep them there.

3. **Constraint notes competing with the core architecture**
   - Keep them in a separate annotation lane, usually on the right.

4. **Too many parallel exchanges around one regulator/monitoring block**
   - Merge labels where semantically acceptable.
   - Or spread them across distinct anchor points.

5. **Trying to force too much with rank constraints**
   - Overconstraint can break the layout.
   - Use a few invisible edges rather than many rigid same-rank declarations.

## Layout strategy learned from the PDS task

### Source-faithful reading order comes before generic neatness
Do **not** apply a generic "clean" layout pattern from a different diagram version if the screenshot you are reconstructing has a different composition.

For screenshot reconstruction, the source image wins over reusable habits.
In particular:
- do **not** move the battery pack to the right just because another PDS layout looked cleaner that way,
- do **not** move software/controller blocks upward if the source clearly places them at the bottom,
- do **not** center external actors just to shorten edges if the source clearly keeps them in a left-side lane.

### PDS v0.2 target reading order
For `PDS_v0.2`, the source image should read approximately as:
- top: `1S1P Li-Ion`
- center: `PDS Circuitboard`
- bottom: `XIAO ESP32-S3`
- left exterior lane: `Charger`, `User`
- right exterior lane: constraint notes
- inside the board: `Protection Circuit` left, `Regulator` upper-right, `INA219` lower-left/center, connector terminal near the regulator

### Why this matters
Matching this composition first reduces:
- long diagonal functional arrows
- large detouring physical links
- accidental horizontal sprawl
- note boxes competing with the main architecture
- semantically correct but visually unfaithful reconstructions

---

## Iteration strategies that worked well

### 1. Inspect the rendered diagram and name what looks wrong
Do not just tweak blindly. Explicitly identify problems such as:
- a component ended up in the wrong region of the page
- a physical link makes an enormous detour
- labels bunch up or overlap
- the conceptual flow does not read naturally
- a constraint note competes with system structure

### 2. Simplify crowded exchanges
When multiple parallel exchanges between the same two elements create clutter, combine them if semantically acceptable.

Examples that improved the PDS diagram:
- combine `5V`, `3V3`, `GND` into one red exchange label:
  - `5V / 3V3 / GND`
- combine `PC Out` and `GND` into one red exchange label:
  - `PC Out / GND`

This greatly improved readability around the regulator.

### 3. Move constraints away from the system core
If a constraint note sits inside the subsystem and increases visual clutter, move it outside.
The dashed annotation line can still point to the constrained element.

### 4. Use invisible edges as layout hints
Use invisible edges with weights to encourage ordering, but keep them modest.
These are hints, not guarantees.

Typical tricks:
- invisible edges between representative nodes to influence left-right or top-bottom order
- invisible edges inside clusters to keep vertically stacked functions aligned
- invisible chains among major blocks to preserve the source image's vertical composition
- invisible chains for left annotation lane and right annotation lane

### 5. Match the source image's annotation lanes
If the source image has notes/constraints arranged in a vertical lane on the right, reproduce that as a separate lane.
If it has external actors stacked on the left, reproduce that as a separate lane.
This usually makes the result look much closer to Capella.

### 6. Avoid over-constraining Graphviz
Too many rank constraints or aggressive same-rank rules can break cluster layout or even crash Graphviz.
Use a light touch.

### 7. Reconsider diagram semantics if the visual result is poor
Sometimes the cleanest fix is not micro-positioning but changing the representation, e.g.:
- merge parallel links
- move note/constraint nodes outside the subsystem
- route via a different representative node

### 8. Use a render-compare-edit loop, not a one-shot coding loop
For each iteration:
1. render the DOT,
2. inspect the rendered image,
3. compare it against the source screenshot,
4. name the top 2-4 visible mismatches,
5. edit only what addresses those mismatches,
6. render again.

Do **not** keep adding detail to a render that is still wrong at the composition level.
Fix placement before polish.

---

## Practical Graphviz advice for Capella-like diagrams

### Clusters as components
Use `subgraph cluster_*` for:
- physical subsystems
- physical components
- actor containers
- software/controller blocks
- annotation grouping lanes when useful

When reconstructing a screenshot, nested clusters are usually the best default.

### Representative nodes for cluster links
When a physical/component exchange is really between containers, implement it through **invisible representative nodes** and add:
- `ltail=cluster_name`
- `lhead=cluster_name`

Recommended pattern:
- place one representative node inside each physical container,
- make those nodes invisible if they are only routing anchors,
- position them deliberately near the intended border/port side,
- connect anchor node to anchor node, while `ltail` / `lhead` makes the edge visually terminate on the container borders.

This gives cleaner routing than trying to connect red exchanges directly to functions or to arbitrary visible content inside the clusters.

### Internal ordering
Use invisible edges like:

```dot
restore_power -> cut_off_power [style=invis, weight=10];
store_energy -> provide_power [style=invis, weight=10];
```

This helps preserve sensible ordering inside a block.

### Constraint links
Constraint links should usually have:

```dot
[style=dashed, color="#333333", constraint=false]
```

This prevents them from distorting the main architecture.

---

## XML-assisted reconstruction guidance

When `PM&SE/capella/*.capella` and `PM&SE/capella/*.aird` exist, use them.

Minimum procedure:
- locate the diagram by name in `*.aird`
- find the referenced `diagram:DSemanticDiagram`
- inspect nested `ownedDiagramElements` and `ownedBorderedNodes`
- map nested containers to Graphviz clusters
- resolve semantic ids in `*.capella` for component/function/exchange/constraint meaning
- only then use the raster image as a visual sanity check

This is especially important for more complex diagrams like `PDS v0.3` and `PDS v1.0`.

Supporting file:
- `CAPELLA_XML.md`

## PDS v0.2-specific lessons

The first subagent attempt at `PDS_v0.2.jpg` exposed additional rules that should be followed in future one-shot conversions:

- Do **not** place `Charger` and `User` on the right if the source image puts them on the left.
- Do **not** replace a vertically layered architecture with one giant monolithic HTML-table composition unless that still preserves clean routing.
- Avoid edge routes that wrap around half the diagram; if this appears, revisit major block ordering first.
- For architecture with many internal links (`INA219`, `XIAO ESP32-S3`, regulator/protection), use explicit nested clusters and ordinary nodes so edges can attach locally.
- Keep the major vertical stack faithful to the source:
  - battery top
  - board middle
  - controller/software bottom
- Keep the annotation/constraint notes in a clean right-side column.
- Preserve the source title/subsystem label exactly where practical.

A good one-shot result for PDS v0.2 should prioritize:
1. major block placement matching the source image,
2. short local edge routes,
3. right-side note column,
4. left-side external actor column,
5. explicit visible container hierarchy,
6. only then fine label polish.

## PDS v0.3 / v1.0 lessons

The first XML-assisted one-shot attempts for `PDS v0.3` and `PDS v1.0` still showed failure modes that must be explicitly avoided:

### Do not flatten the architecture into a function-only graph
If the source diagram visibly contains components/containers like:
- battery pack
- circuitboard
- protection circuit
- regulator
- INA219
- XIAO / software blocks
- backplane / connectors / headers / spine

then the Graphviz output must preserve those visible containers.

A function-only graph with labels floating in open space is **not acceptable** for Capella-style reconstruction when the original image clearly shows nested components.

### Keep edges local to their containing architecture
If an exchange belongs inside a component hierarchy, route it through the corresponding local area of the diagram.
Avoid long red diagonals jumping across the whole figure unless the source diagram itself does so.

### Preserve container hierarchy before adding every exchange
For complex diagrams, build in this order:
1. outer subsystem container
2. first-level components
3. nested subcomponents
4. functions inside subcomponents
5. external actors/components
6. note column
7. exchanges

If the container hierarchy is not visible and aesthetically clean, do **not** continue adding more exchanges yet.

### Use the image as a visual acceptance test even when using XML
XML gives semantics and membership, but the raster image still defines the look of the target view.
A result that is semantically correct but visually flattened is still wrong.

### One-shot acceptance criteria for complex PDS diagrams
Before considering `v0.3` or `v1.0` successful, verify that:
- major visible component boxes are present
- nested containers are visible and readable
- external actors/components are outside the subsystem where expected
- note/constraint boxes form a readable annotation lane
- physical links do not dominate the whole page with long criss-cross diagonals
- the graph still looks recognizably like a Capella physical architecture diagram

If these are not satisfied, revise the Graphviz structure, not just labels.

## PDS-specific result worth reusing

The durable design direction from this task was:
- use `splines=polyline`
- use `xlabel=` for red physical/component exchange labels
- keep functional exchanges green
- keep physical/component exchanges red
- keep constraints dashed dark gray
- preserve the screenshot's major composition before optimizing edge lengths
- for `PDS_v0.2`, keep battery top, board middle, XIAO bottom, actor lane left, note lane right
- keep board internals in visibly separate nested containers
- place the connector terminal near/below the regulator as in the source
- move constraints outside the subsystem if necessary
- merge multiple parallel red links where possible

Most importantly: **reuse styling tricks, but do not reuse a different diagram version's composition when the screenshot disagrees.**

---

## Quality checklist before finalizing a diagram

Before declaring the diagram done, render and verify:

1. **Major composition matches the source image**
   - Top/bottom/left/right placement of the big blocks is recognizably correct.
   - Reject horizontally sprawled layouts when the source is a vertical stack.

2. **Reading order is intuitive**
   - Actor -> system -> source/output makes sense visually.

3. **Physical links are short and legible**
   - No huge avoidable detours.
   - Reject routes that wrap around large portions of the diagram unless the source genuinely does that.

4. **Labels are readable**
   - No severe overlap or bunching.

5. **Constraint notes do not clutter the core**
   - Move them if needed.

6. **Parallel exchanges are simplified when appropriate**
   - Merge labels if it improves readability.

7. **Cluster nesting remains visually clear**
   - subsystem > component > behavior > function should still be readable.
   - Reject renders that flatten visible containers from the source image.

8. **The rendered image, not just the DOT file, looks good**
   - Always inspect the PNG or SVG.

---

## Tooling workflow

Typical workflow inside the coding agent:

1. `read` the `.dot` file
2. `edit` the file in targeted replacements
3. `bash`:
   - `dot -Tpng file.dot -o file.png`
   - `dot -Tsvg file.dot -o file.svg`
4. `read` the rendered PNG to inspect visual quality
5. iterate until aesthetically clean

---

## Notes

- Favor **clarity over strict fidelity** when Graphviz layout constraints make exact Capella mimicry difficult.
- Keep the semantics recognizable first, then optimize aesthetics.
- If the user says a diagram still looks wrong, inspect the rendering again and continue iterating rather than defending the current layout.
