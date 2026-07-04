# PCB General Rules

## Design Rules

- Minimum track width: 0.8 mm
- Minimum Via Diameter: 1.7 mm (can be 1.0 mm if a track provides enough space for soldering)
- Minimum Via Drill: 0.9 mm (creates a ~0.83 mm diameter hole)
- Minimum Pad Diameter: 70 mil
- Minimum Pad Drill Diameter: 35 mil

## Operations

- Place WCS Origin on the bottom left corner of the top stock surface. Set Top and Bottom stock to 0.083 mm each. Set Side Stock as needed but prefer to set symmetrical side stock for easier origin setting for double-sided PCBs.
- Use a Bore operation for mounting holes, set Top and Bottom heights to Stock Top and Bottom. This is the first operation to be done on either board face, to check for alignment. Use the `⌀3.175mm Spiral O 3.175*25mm` tool for this operation.
- Use a Bore operation for pin holes, set Top and Bottom heights to Stock Top and Bottom. Use the `⌀0.8 mm TiN Coating Corn Bit 0.8*5.5mm` tool.
- Use a 2D Contour operation for tracks, disable Lead-in, Lead-out and Chamfer. Use the lower outline of the track, with Bottom Height set to Selected Contours with zero offset. Do not use copper pour outlines. Use the `⌀3.175mm 45° Chamfering Bit - 1/8″ Shank` tool.
- Use a Ramp operation for the outer border. In the Geometry tab, select Body and then click on the top and bottom copper layers. Set Top and Bottom heights to Stock Top and Bottom. Use the `⌀3.175mm Spiral O 3.175*25mm` tool.

## Double-sided PCBs

- Remember that through-hole components can only be routes on the side opposite to where they are mounted. If you need to route on the same same they are mounted, draw a parallel track on the opposite layers and use vias.
- Create a new Setup for the bottom side operations with the zero set to the bottom left corner of the bottom stock surface. Adjust the coordinate axes so the Z axis points outward from the bottom stock surface.
- It is recommended to generate one NC Program per PCB side so that the Z leveling can be performed once per surface, and to allow time to flip the board.

## Stock Prework

- If the body of interest is not centered on the stock or if the stock has irregular edges, manual measurements will be required to reposition the origin point on the bottom surface. As a solution, it was proposed to prework the raw copper sheet into symmetric, custom-sized stocks. This solution can be found in Fusion 360 under `CanSatWorkshop > Module PCB > Stock Prework`. The design is fully parametric and considers the desired dimensions of the module PCB (42x48mm) plus a 3.5mm margin around the edges to allow the ramp tool (`⌀3.175mm Spiral O 3.175*25mm`) to pass without collisions. `Sketch2` contains a rectangular pattern that can be edited to fit more stocks if the raw sheet dimensions allow.