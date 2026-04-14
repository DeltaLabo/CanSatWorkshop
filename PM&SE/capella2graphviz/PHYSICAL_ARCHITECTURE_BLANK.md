# Physical Architecture Blank guidance

Use this companion document when reconstructing or refining a **Capella Physical Architecture Blank** view.

This diagram type typically shows:
- a visible physical subsystem or architecture container,
- nested physical components,
- functional or behavioral content inside those components,
- external actors/components outside the subsystem,
- physical/component exchanges crossing container boundaries,
- notes or constraints in a side lane.

## Recommended build order

For Physical Architecture Blank diagrams, build in this order:
1. outer subsystem container,
2. first-level physical components,
3. nested physical subcomponents,
4. functional blocks and functions inside those components,
5. external actors/components,
6. note/constraint lane,
7. exchanges.

If the visible container hierarchy is still weak or cluttered, do **not** keep adding exchanges yet.
Fix the architecture composition first.

## Composition rules

### Preserve the source layout
For screenshot reconstruction, the source image wins over generic neatness.
Preserve:
- left-side actor lanes,
- right-side note lanes,
- top/bottom component stacking,
- central hardware containers,
- relative placement of major subcomponents inside the main board/subsystem.

A semantically correct diagram that moves the big blocks to different regions of the page is still a poor reconstruction.

### Keep visible containers visible
Do **not** flatten a Physical Architecture Blank diagram into a function-only graph if the source clearly shows physical containers.

If the original diagram visibly includes components such as:
- a battery pack,
- a circuit board,
- a regulator,
- a protection circuit,
- controller/software blocks,
- backplanes, connectors, headers, or ports,

then the Graphviz reconstruction should preserve those visible containers with clusters.

### Prefer clusters with ordinary nodes
When many exchanges cross container boundaries, prefer:
- nested `cluster_*` containers,
- ordinary nodes for functions and visible content,
- a few invisible ordering hints.

Use giant HTML-table nodes only when a block is mostly self-contained and has very few external connections.

## Exchange rules for this diagram type

### Functional exchanges stay behavioral
Functional exchanges should usually connect function-to-function and stay green.
Do not make them terminate on physical containers just because those containers are visually convenient.

### Physical exchanges attach to physical things
Red physical/component exchanges must connect to:
- physical components,
- physical subsystems,
- ports,
- connector or terminal anchors,
- invisible representative anchors for those physical elements.

They must **not** start or end at green function boxes.

## Invisible-anchor placement technique

Physical Architecture Blank views often need container-to-container or container-to-port exchanges that Graphviz cannot route cleanly if you connect directly to visible content.

Use this reusable pattern:
1. create a representative anchor node inside each relevant physical container,
2. make the anchor visually invisible when it is only for routing,
3. place it near the side, border, terminal, or port where the exchange should appear,
4. connect anchor-to-anchor with the red exchange,
5. add `ltail=cluster_*` and `lhead=cluster_*` when the edge is conceptually between containers.

Why this helps:
- edges attach at visually meaningful borders,
- long looping detours are reduced,
- the diagram remains physically oriented,
- functions are not abused as routing endpoints.

Representative anchors are especially useful for:
- board-to-battery links,
- board-to-controller links,
- regulator/connector exits,
- external charger or user interactions with physical interfaces,
- any exchange that should visually enter a cluster from a specific side.

## Layout strategies that work well

### Use composition-first iteration
When a render looks wrong, first ask:
- is a major component on the wrong side of the page?
- is the diagram too wide when the source is vertically stacked?
- are note boxes mixed into the core architecture?
- are actor lanes missing?

Fix those first before fine-tuning individual links.

### Keep note boxes in an annotation lane
Constraint and note boxes often read best in a dedicated side lane, usually on the right.
Connect them with dashed non-constraining edges so they do not distort the main layout.

### Simplify crowded exchange sets
When several parallel physical exchanges create clutter, merge labels where semantically acceptable.
For example, grouped power rails are often clearer as one exchange label than as many parallel red edges.

### Use invisible ordering edges lightly
Invisible edges are useful for:
- preserving a vertical stack,
- keeping actors in a left lane,
- keeping notes in a right lane,
- aligning internal functions.

Use them as hints, not as a rigid cage.

## Common failure modes to avoid

1. **Flattened architecture**
   - The diagram loses visible physical containers and becomes an abstract function graph.

2. **Huge looping red edges**
   - Usually caused by poor major-block ordering or missing routing anchors.

3. **Actors/components on the wrong side**
   - Keep them where the source view places them unless there is a clear reason not to.

4. **Constraint notes competing with the core system**
   - Move them into a note lane.

5. **Over-constrained Graphviz layout**
   - Too many rank constraints can break otherwise good cluster structure.

## Physical Architecture Blank checklist

Before finalizing, verify that:
- the subsystem and major physical components are visibly nested,
- external actors/components sit outside the subsystem where expected,
- note/constraint boxes form a readable side lane,
- physical exchanges are local and legible,
- invisible anchors are used where container exchanges need routing help,
- the result still looks recognisably like a Capella physical architecture view.

## PDS-oriented examples of reusable lessons

These examples are reusable patterns, not one-off diary notes:
- if a source image uses a vertical stack, preserve that stack instead of spreading the diagram horizontally,
- if the source places actors on the left and constraints on the right, keep those lanes,
- if a regulator, connector, and monitoring block exchange several related items, merge exchange labels where that improves readability,
- if a controller block is visually below the board in the source, keep it below unless the source itself changes.
