---
url: "https://learn.andoyaspace.no/docs/cansat/recovery_system/parachute/"
final_url: "https://learn.andoyaspace.no/docs/cansat/recovery_system/parachute/"
title: "Parachute design"
extracted_at: "2026-06-11T22:09:40.868220+00:00"
parser: "trafilatura-markdown"
confidence: 0.825
content_type: "text/html"
http_status: 200
word_count: 1356
---

# Parachute design

Satellites normally do not return to Earth in a parachute. At the end of their useful life, a satellite will be put in a different orbit. For satellites orbiting at a low altitude this could mean they will burn up in the atmosphere. Satellites further away will end up in a much more distant parking orbit and will circle our planet forever.

Sometimes however the spacecraft has to return to earth with samples or astronauts. One of the solutions is then to descend in a parachute.

When the CanSat is deployed it must have a device to slow it down, otherwise it will crash into the surface. The parachute also helps ensure that the CanSat stays in an upright position. This is particularly important because it helps to maintain proper antenna orientation, which maximises the chances of receiving telemetry. These pages will guide you through the different steps needed to design and built your parachute.

## Required Descent Parameters

The values listed below are preliminary and can change in advance of a CanSat competition and launch campaign. However, they can be used as a temporary guideline. Uncertainties in the Launch Campaign could lead to a different value for the eventual descent velocities.

| Parameter | Value |
|---|---|
| Minimal descent Velocity | 8 m/s |
| Maximal descent Velocity | 11 m/s |
| Allowed mass | 300 â 350 g |
| Drag coefficients | |
| Semi Spherical | 1.5 |
| Cross Shaped | 0.8 |
| Parapent | depends on the design (can be determined by tests) |
| Flat, hexagon | 0.8 |

## Parachute Production

When the design of the parachute is finished you can start the production process. There are however a few important issues to keep in mind during this process. Deployment of the parachute will be relatively violent, so the fabric and fibres you use need to be strong. Most often you can get nylon cord and ripstop fabric at a kite shop. These materials are ideally suited for the parachute.

When cutting the fabric keep in mind that some of the fabrics need to be cast double in order to sew it.

More handy tips on parachute production can be found here: [https://www.nakka-rocketry.net/paracon.html](https://www.nakka-rocketry.net/paracon.html)

When the parachute is done, the best way to check if it works is to actually test it.

## Parachute Design Calculations

The following calculations can be performed when working on the parachute design. You may need to read the following sections on descent physics and parachute designs in order to do these calculation.

- Calculate the impact speed of the can without a parachute (when released from 1 kilometre altitude). (The answer to this question gives you an idea of why a parachute is nescessary!)
- Calculate the minimum required area for your parachute when you use a cross shaped parachute. What size should the squares be on the parachute?
- Perform the same calculation for a semi spherical parachute. What is the radius?
- Test the descent velocity of your parachute with a soda can with same mass as your CanSat.
- Try out different solutions for the parachute. A parachute with some holes in it or perhaps multiple small parachutes? Both will enhance the stability of the CanSat.

## Descent Physics

Before we can start making the parachute we will have to figure out how big it should be. More specifically, we need to calculate how much surface area the parachute will need in order to fulfil the requirements.

Logic suggests that the bigger the parachute the slower the objectâs descent velocity. Later on this principle is shown with some basic equations.

Although it would be very beneficial for the CanSat to have a very low descent rate, a limit has been set to ensure that the CanSat will land near the launch area. If the descent rate is too slow the CanSat may drift kilometres away along with the wind, which is neither allowed nor desired. For safety reasons there has also been set a maximum descent rate.

To design the parachute weâll use some simple physics. We use a simplified model to estimate the area of the parachute, after which we can start on the construction.

During the descent two forces will be acting on the CanSat as illustrated in the figure to the right. Gravity will pull on the can and accelerate it towards the ground, and the drag force on the parachute will act on the CanSat in the opposite direction and slows down the descent rate. The two forces are shown in the figure to the right.

When the CanSat is deployed, the force of gravity will cause it to accelerate. The drag force depends on the velocity of the CanSat and when the velocity is low, the drag force is smaller that the force of gravity. When the velocity grows, the drag force becomes larger and after a few seconds the drag force from the parachute will reach equilibrium with the force of gravity. From that point on, the acceleration will be zero and the CanSat will descend at a constant velocity. This constant velocity has to be larger than the minimum descent velocity specified in the requirements. For the following calculations we can use this minimum value as the constant velocity of the CanSat.

The gravity force \(F_g\) is equal to: \(F_g = m \cdot g\)

In this equation:

| Symbol | Description |
|---|---|
| \(m\) | Mass of the CanSat |
| \(g\) | Acceleration of gravity, equal to \(9.81 m/s^2\) |

The drag force \(F_D\) of the parachute is equal to:

In this equation:

| Symbol | Description |
|---|---|
| \(A\) | Total area of the parachute (not just the frontal area) |
| \(C_D\) | Drag coefficient of the parachute. This value depends on the shape of the parachute |
| \(\rho\) | Local density of the air, assumed to be constant at \(0.001225 \frac{g}{cm^3}\) |
| \(V\) | Descent velocity of the CanSat |

When the acceleration is zero, the two forces are of equal size and we can write:

or

You can rewrite this equation to calculate the area (\(A\)) needed for the parachute to achieve a desired velocity:

If you have a parachute already, you can rewrite the equation and find the terminal velocity (\(V\)) for it:

## Semi-spherical Parachute Design

A semi-spherical appearance is the most common shape of a parachute.

Although it is not hard to make one, it can be quite time-consuming to get the right shape. The figure to the right should help out. In the figure two parameters are used:

| Symbol | Description |
|---|---|
| n | stands for the number of needed parts |
| r | stands for the radius of the parachute |

## Cross Parachute Design

Instead of using a semi spherical shaped parachute you can also choose a cross shape. The advantage of this shape is that itâs easy to make. If you want to know more about cross shaped parachutes you can check this following link: [https://www.nakka-rocketry.net/xchute1.html](https://www.nakka-rocketry.net/xchute1.html)

## Parapent shaped parachute

A parapent shaped parachute acts a bit like a wing. Because of its shape you can use it to steer.

The design of a parapent is more complex than that of the other shapes mentioned.

You will have to do some more research if you wish to use this type of parachute.

## Flat parachute design

Most commonly available parachutes are in fact created from standard two-dimensional flat geometric figures, such as hexagons or octagons.

The figure to the right shows a sketch of a plat parachute which consists of 8 equal triangles.

Hence the total area for the parachute would be

where the area of one triangle is

By combining these two equations we get

You can read more about how to calculate the area of a flat parachute here: [https://www.sunward1.com/imagespara/The%20Mathematics%20of%20Parachutes%28Rev2%29.pdf](https://www.sunward1.com/imagespara/The%20Mathematics%20of%20Parachutes%28Rev2%29.pdf)

As soon as you know the total area (\(A\)) together with the drag coefficient (\(C_D\)) you can easily determine the descent rate for your CanSat.

If you do not know the drag coefficient for your parachute, you can do drop tests of the CanSat to find the terminal velocity.
