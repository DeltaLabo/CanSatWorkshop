# Capella XML / AIRD extraction guidance

Use this companion document when a Capella project is available and screenshot-only reconstruction is not reliable enough.

## Files in a Capella project

Typical project files:
- `*.capella` — semantic model: components, functions, ports, exchanges, constraints
- `*.aird` — diagram representations and layout information
- `*.afm` — metadata / viewpoint references

For Graphviz reconstruction:
- use `*.capella` for **what exists semantically**,
- use `*.aird` for **what is shown in the diagram and how it is arranged**.

## What to read first

1. In `*.aird`, locate the `viewpoint:DRepresentationDescriptor` for the target diagram name.
2. Follow its `repPath="#..."` to the corresponding `diagram:DSemanticDiagram`.
3. Inspect nested `ownedDiagramElements`, `ownedBorderedNodes`, and edge elements.
4. Resolve semantic references in `*.capella` to determine component/function/exchange/constraint meaning.

## Useful AIRD element types

### `diagram:DNodeContainer`
Usually a visible container such as:
- subsystem,
- physical component,
- nested component,
- grouped diagram block.

Useful fields:
- `name`
- `target`
- `semanticElements`
- nested `ownedDiagramElements`
- nested `ownedBorderedNodes`
- `ownedStyle`

### `diagram:DNode`
Usually a visible node such as:
- function,
- note,
- constraint,
- small diagram symbol,
- port-like visible element.

### `ownedBorderedNodes`
Often used for:
- physical ports,
- function ports,
- small terminal-like nodes.

### diagram edge elements
Use these to discover visible exchanges and relationships in the rendered view.
Resolve their semantic targets in `*.capella`.

## Useful semantic types in `*.capella`

Common examples:
- `org.polarsys.capella.core.data.pa:PhysicalComponent`
- `org.polarsys.capella.core.data.pa:PhysicalFunction`
- `org.polarsys.capella.core.data.cs:Part`
- `org.polarsys.capella.core.data.cs:PhysicalPort`
- `org.polarsys.capella.core.data.fa:FunctionInputPort`
- `org.polarsys.capella.core.data.fa:FunctionOutputPort`
- `org.polarsys.capella.core.data.fa:FunctionalExchange`
- `org.polarsys.capella.core.data.fa:ComponentExchange`
- `org.polarsys.capella.core.data.capellacore:Constraint`

## How to map XML into Graphviz

1. Recreate nested `ownedDiagramElements` as nested Graphviz clusters.
2. Use AIRD names for visible labels unless semantic names are clearly better.
3. Preserve major placement from AIRD composition before fine edge routing.
4. Resolve exchange semantics in `*.capella` and apply the matching Graphviz color/style.
5. Render, inspect, and then make small readability adjustments.

## Recommended XML-assisted workflow

1. Find the diagram descriptor in `*.aird`.
2. Jump to the referenced `diagram:DSemanticDiagram`.
3. Build a tree of visible containers, nodes, ports, and notes.
4. Collect visible edges and their semantic ids.
5. Resolve those ids in `*.capella`.
6. Build the Graphviz cluster hierarchy.
7. Render and compare against the screenshot or expected view.

## Practical advice

- Use XML when image-only reading leaves ambiguity about ports, exchange names, or diagram membership.
- Even with XML, use the screenshot as the final visual acceptance test.
- A semantically correct graph that loses the original visible container hierarchy is still not a good reconstruction.
