# S&A MBSE views

The Structures & Assembly MBSE set is maintained as Capella-style D2 physical architecture views.

| Version | Scope | D2 source | Rendered PNG |
| --- | --- | --- | --- |
| v0.1 | Reusable structural module models and S&A constraints, before PCB mounting | [D2](v0.1/SAA_v0.1_view1_physical.d2) | [PNG](v0.1/SAA_v0.1_view1_physical.png) |
| v1.0 | Same module structure with subsystem PCBs, backplane PCB, battery pack, and parachute hardware mounted | [D2](v1.0/SAA_v1.0_view1_physical.d2) | [PNG](v1.0/SAA_v1.0_view1_physical.png) |

Render with:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```
