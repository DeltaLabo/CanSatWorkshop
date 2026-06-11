---
url: "https://www.hubs.com/knowledge-base/selecting-optimal-shell-and-infill-parameters-fdm-3d-printing/"
final_url: "https://www.hubs.com/knowledge-base/selecting-optimal-shell-and-infill-parameters-fdm-3d-printing/"
title: "What are the optimal shell and infill parameters for FDM 3D printing? | Protolabs Network"
extracted_at: "2026-06-11T22:04:20.554319+00:00"
parser: "trafilatura-markdown"
confidence: 0.860
content_type: "text/html"
http_status: 200
word_count: 1946
---

### Infill in 3D printing: definition, parts and types

[Read article](https://www.hubs.com/knowledge-base/infill-in-3d-printing-definition-parts-types/)

How it works

On-demand, custom manufacturing

Capabilities

Prototypes and production parts

Industries

Join thousands of industry leaders developing revolutionary products with Protolabs Network

Aerospace & aviation manufacturing

Go from development to launch faster

Automotive

Drive product development and speed up innovation

Industrial machinery

Power your machines with cutting-edge technologies

Consumer electronics

From prototype to production to homes around the world

Robotics & automation

Build the most complex automated systems with ease

Medical

Get the next healthcare innovation to market

All industries

Materials

Protoypes and production parts

CNC machining materials

3D printing materials

Injection molding materials

Sheet metal materials

Resources

All you need to know about digital manufacturing

Company

Learn about who we are and how it all started

About us

The Protolabs Network story

Become a partner

How joining our manufacturing network grows your business

Contact us

We have offices in the United States and Europe

Jobs

Join our team

Protolabs Network

Big news! We changed our name to Protolabs Network

Sustainability

Reducing emissions in manufacturing

Team

The people behind the platform

EN

Language

How do shell and infill properties impact the performance and cost of FDM 3D printing? It turns out these parameters have more of an effect than you may realize, so learning to optimize these features will improve the performance of your FDM custom parts while reducing manufacturing costs.

The majority of [FDM](https://www.hubs.com/knowledge-base/introduction-fdm-3d-printing/) 3D-printed parts are not printed solid. Printing solid parts requires high amounts of material and longer print times, resulting in high costs. To optimize the printing process most parts are printed with solid shells and filled with infill. Shells and infill play an important role on the quality, appearance and function of FDM printed parts.

This article will discuss the difference between shells and infill and how shells and infill can be employed to optimize a design. To level up your design skills for 3D printing, check out this [comprehensive one-pager with all of Protolabs Network's top design rules](https://www.hubs.com/get/3d-printing-design-rules/).

A standard FDM print can be broken down into 4 sections: shells, bottom layers, top layers and infill.

-
**Shells:**The walls of the print that are exposed to the outside of the model -
**Bottom layers (a type of shell):**The part of the print that is exposed to the outside of the model, facing the build plate -
**Top layers (a type of shell):**The parts of the print that is exposed to the outside of the model, facing upwards, towards the nozzle. Typically this surface will have the best surface finish -
**Infill:**The internal structure of the print

The parameters of these sections can each be altered to optimize a design.

Shells are the number of layers on the outside of a print. For FDM printing,Â shells are always the first areas to be printed per layer. Letâs unpack several key design considerations for optimizing shells.Â

-
Strength can be added by increasing the shell thickness. This allows for a slightly more robust print without having to increase the amount of material used for infill. Most slicer programs allow shell thickness to be adjusted even allowing areas of high stress to be customized with a high shell density offering localized areas of high strength.

-
If you plan on finishing a print by using sanding or chemical smoothing, increasing shell thickness is often necessary. This is because post-processing methods reduce the thickness of the surface of the model.

-
Any increase in the number of shells also increases the amount of time and material required to print the model. This will augment the overall cost of your custom parts.Â

Shells typically consist of a specified number of nozzle diameters. Itâs always good to design shells with multiple nozzle diameters to prevent forming voids in the print. Most shells are printed with a thickness of 2 nozzle diameters (usually this corresponds to 0.8 mm).

Designing walls with multiple nozzle diameters eliminate spacing in wall features, which makes your custom parts stronger.

Objects printed with [ prototyping FDM](https://www.hubs.com/knowledge-base/what-is-fdm-3d-printing/) technology are rarely completely solid. Typically, the inside of an FDM print is composed of infill, which have varying structures and shapes that can affect the print time, weight, strength and flexibility of 3D-printed components.Â

By default, most FDM slicer programs will produce parts with 18% to 20% infill, which is perfectly adequate for most [ 3D printing applications](https://www.hubs.com/guides/3d-printing/#applications) (using FDM). This infill percentage generally allows for faster and more affordable print runs.Â

The strength of a design is directly related to a 3D-printed partâs infill percentage. A part with 50% infill compared to 25% is typically 25% stronger while a shift from 50% to 75% increases part strength by around 10%.

Understanding the application of a final printed part allows a designer to specify the optimal infill percentage. A prototype where the form is important can be printed with very low infill, which results in significant cost and time savings, whereas a bracket that will experience loading will need a higher infill percentage.Â

As mentioned above, the standard 18% to 20% that most FDM printers use as a default should be acceptable for most applications, though feel free to speak with a Protolabs Network engineer for other potentially more robust infill options.

Infill also plays a critical role in how extended/protruding features are connected to a model. [Snap-fit connections](https://www.hubs.com/knowledge-base/how-design-snap-fit-joints-3d-printing) are a good example of this. The base of a snap-fit connection is often a weak point.

With a low infill density (20%), the cantilever is much more likely to break as the short extruded clip is only connected to the body of the print by a small cross-sectional area. Increasing the infill percentage means that more of the body of the print is connected to the cantilever, thereby increasing the strength of this connection.

An important factor to remember when choosing the infill percentage of your 3D-printed parts is whether youâll need to drill holes or place screws into the component.Â

Consider a print with low infill that is going to be drilled and then screwed to another surface. Often the drill holes will go through the top and bottom layers of the print and miss the infill of the model, creating a very weak connection. For these applications, a higher infill is desirable (50% minimum).

Connections that utilize clearance holes and bolts are better suited to parts with a low infill percentage. The shells, walls, and infill offer good compressive strength providing better anchoring of the part.

For a standard FDM print, the machine will add the infill structure as an angled hatch or a honeycomb shape. Let's look at the four most common infill geometries and their optimal uses.

**Rectangular**Â - This is the standard infill pattern for FDM 3D prints. It's strong in all directions and is reasonably fast to print, and requires the printer to do the least amount of bridging across the infill pattern.

**Triangular or diagonal**Â - This geometry is used when strength is needed in the direction of the walls. Triangles take a little longer to print.

**Wiggle**Â - This geometry allows the model to twist or compress, as well as be softer. It can be a good choice, particularly with a soft rubbery material or softer nylon.

**Honeycomb**Â - This is one of the more popular infills. It's quick to print and is very strong, providing strength in all directions.

New to 3D printing or need a comprehensive refresher?

Designing parts for FDM 3D printing involves a lot of steps, and it's easy to forget certain factors and features. Choosing the right infill percentages and geometries, and optimizing the use of shells, will definitely improve how your custom parts turn out.

-
Remember to take into account the application of the parts you're sourcing. This will affect the shell thickness and infill percentage you need to set. Increases in shell thickness and infill percentages lead to higher strength but also longer print times and augmented costs.

-
Design shells with multiple nozzle diameters.

-
If you need to place screws in a part, increase the shell thickness or infill percentage to improve anchoring. If this isn't feasible (or possible), consider using clearance holes and bolting with washers.

-
For cheaper rapid prints, rectangular infill is optimal thanks to its swifter print speed. Honeycomb or triangular infills boost part strength compared to rectangular geometries, so use either of these two if higher strength is critical to your part's functionality.

Curious about the cost of FDM 3D printing?

[Our online FDM 3D printing service](https://www.hubs.com/3d-printing/fdm/)
[Upload a CAD file for a free, instant quote](https://www.hubs.com/manufacture/)

Learn how infill density, pattern, and overlap affect 3D-printed part strength, weight and cost, with a comparison table and practical selection guide.

Simulation software helps you predict exactly how designs will perform long before hitting the build plate. This article covers how this powerful digital tool can transform your workflows, slash prototyping costs, and get you to market ahead of the pack.

Seeking consistency and predictability in your parts? Check out our guide on repeatability, which highlights the materials that will perform the same way time and time again.

How can you create a part or product thatâs ready to move from prototype to production? Check out our article, which offers tips and tricks for designing with scalability in mind.

What is Geometric Dimensioning and Tolerancing (GD&T) and how is it used? This article explores the basics of how and when to use GD&T to get the best results out of custom part manufacturing.

Multi Jet Fusion (MJF) 3D printing can create highly accurate, complex industrial parts more efficiently - and potentially more cost-effectively - than other industrial 3D printing processes. This article covers how to design parts for MJF, common applications of the technology and key best practices.

Design for manufacturing (DFM) means taking a design-first approach to manufacturing. In this article, we look at the overall DFM process, the necessary steps for a successful outcome, examples of DFM done right and how to get the most out of your own processes.

Learn how to avoid low quality 3D prints or unnecessarily large files by exporting your STL file in the correct resolution.

What are the different materials available for SLA 3D printing? This article compares the main printing resins, including standard, tough, durable, heat resistant, rubber-like, dental and castable, by material properties. Find the best material option for your application.

A comprehensive guide on designing parts for Binder Jetting, covering the printing process, design specifications and material options.

How does industrial 3D printing accelerate development in aerospace and aviation? This overview explains how engineers use additive manufacturing for prototypes, tooling, and flight-ready components, and how outsourced production with a vetted supplier network reduces lead time and supports repeatable end-use part manufacturing.

What are the most common STL file errors and how will they affect your ability to export models for 3D printing? Learn to identify the errors you may encounter when working with STL files and how to fix them so they don't delay your next 3D printing run.

Show more

Show less

×
