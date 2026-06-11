---
url: "https://learn.andoyaspace.no/docs/cansat/cansat_competition_requirements/"
final_url: "https://learn.andoyaspace.no/docs/cansat/cansat_competition_requirements/"
title: "CanSat competition requirements"
extracted_at: "2026-06-11T22:03:17.874627+00:00"
parser: "trafilatura-markdown"
confidence: 0.626
content_type: "text/html"
http_status: 200
word_count: 526
---

# CanSat competition requirements

AndÃ¸ya Space has since 2009 held national and nordic CanSat competitions and European competitions in cooperation with the European Space Agency.

AndÃ¸ya Space uses the following set of CanSat requirements that are compatible with the Intruder rocket used for launching the CanSatÂ´s:

- All the components of the CanSat, with the exception of parachute, antenna and GPS, must fit inside a European soda can: 115 mm high and 66 mm diameter.
- The mass of the CanSat must be between 300 and 350 grams. CanSats that are lighter must take additional ballast with them to reach the 300 grams minimum mass limit required.
- The CanSat should have a recovery system, such as a parachute, capable of being reused after launch. It is recommended to use bright coloured fabric, which will facilitate recovery of the CanSat after landing.
- The antennas, transducers and other elements of the CanSat cannot extend beyond the canâs diameter until it has left the launch vehicle.
- For recovery reasons, a maximum flight time of 120 seconds is recommended. If attempting a directed landing, then a maximum of 170 seconds flight time is recommended.
- The descent rate is recommended to be between 8 m/s and 11m/s (If not other agreements or requirements have been made).
- Explosives, detonators, pyrotechnics, flammable materials, dangerous materials and biological payloads are strictly forbidden. All materials used must be safe for personnel, equipment and the environment. Material Safety Data Sheets (MSDS) will be requested in case of doubt.
- The CanSat shall operate with a battery or solar panels. It must be possible for the systems to be powered on for four continuous hours.
- The CanSat must be able to withstand an acceleration of up to 20G.
- The battery must be easily accessible, in case it has to be replaced or recharged in the Field.
- The CanSat must have an easily accessible master power switch.
- Inclusion of a retrieval system (beeper, radio beacon, GPS, etc.) is recommended.
- The total budget of the CanSat should not exceed â¬500.

Note

These requirements are just temporary guidelines. In the event of a competition the requirements will be announced.

Note

The rocket payload area usually has 4.5 cm of space per CanSat available, along the canâs axial dimension (i.e. height), which must accommodate all external elements including: parachute, parachute attachment hardware, and any antennas.

## Primary mission

For the primary mission we need to measure temperature and pressure as a function of time during the descent of the CanSat.

## Secondary mission

Examples of CanSat secondary missions and sensors are:

- Implement an airbag-system for safe landing
- accelerometer
- data logging on onboard MicroSD card
- GPS
- Advancet telemetry (two-way communication)
- Magnetometer for orientation measurements
- Gass-sensors (CO2 or other gases)
- Photo- or video camera (or 2 for 3D pictures)

A 9-DOF GY-91 multi sensor package and a on-board datalogger (openlogger) are already a part of the basic Arduino CanSat kit.

As an example of a GPD module suitable for CanSat and Arduino-programming, we use the GY-GPS6MV2-module (U-blox NEO-6M-0-001) which is treated on another page in this CanSat book.
