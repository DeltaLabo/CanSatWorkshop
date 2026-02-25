# Understanding Capella Physical Diagrams

Tags: Docs
Owner: Anthony Arguedas

This is a simple to guide to understand Capella diagrams at the Physical level. This guide doesn’t cover other levels of abstraction (Organizational, System, Logical) because they won’t be used in this project.

At the very beginning, we only know that we want to build a Physical System. The term Physical shouldn’t be taken literally, as both software and hardware count as Physical Systems. Instead, let’s think of a Physical System as something that’s *ready to use*.

![image.png](image.png)

The system is made out of Physical Components.

![image.png](image%201.png)

These components are not abstract. They must be something that be bought or built from scratch. Let’s rename them and add some more.

![image.png](image%202.png)

Physical Components have high-level functions, which is to say that they implement Logical Components.

![image.png](image%203.png)

Notice that an LED can’t directly provide a visual signal, this is only a high-level placeholder. To implement actual behaviors that the component can physically (or digitally) provide, we add one or more Functions per Logical Component.

![image.png](image%204.png)

Not only the Physical System has functions, the external entities that it interacts with do so too.

Let’s introduce an User that can interact with the Pushbutton. Let’s say that for safety reasons the user can only push or not push the button to enable/disable system behavior, and so the system is unable to work on its own.

![image.png](image%205.png)

A list of functions is not enough to describe system behavior, so we need to introduce Functional Exchanges to model the transitions between functions and the information (physical or digital) they carry.

![image.png](image%206.png)

Notice how some Functions involve more than one Functional Exchange. Some only receive exchanges, and others only emit them. Look for the green (*out ports*) and red (*in ports*) arrows that indicate the direction of the information flow.

Notice how new functions have been added and others have been renamed. This is to be expected during the design process, but it should be avoided when the system is already being developed, integrated, and tested. 

Just like Logical Components are high-level containers of Functions, Logical Exchanges are high-level containers of Functional Exchanges.

While it can seem obvious from the diagram, let’s add some Component Exchanges to indicate that this is a series circuit.

![image.png](image%207.png)

In a real system, both Functional and Component Exchanges need a means of transmission (again, physical or digital). We call this a Physical Link. Physical Links must be descriptive enough so that a specialized diagram (like an electronics schematic) can be generated from them.

As an example, let’s wire the components up.

![image.png](Understanding%20Capella%20Physical%20Diagrams/image%208.png)

We know that the Battery generates a voltage, but, at which level? To not only define *what* the system must do (the functional requirements) but also *how* it must do it (non-functional requirements) we use Constraints.

![image.png](image%209.png)

Notice how Constraints can be applied not only to Functions but actually to any diagram element (Physical/Logical Component, Functional/Component Exchange, etc.).

Physical Components can contain any number of Logical Components. To finish, let’s leverage this to turn the system into a Toaster.

![toaster.jpg](toaster.jpg)

Obviously, the above diagram could be made a lot more rigorous, but it’s just enough to understand how the system works. Feel free to download Capella and improve it yourself, if you want.
