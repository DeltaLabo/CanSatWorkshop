---
url: "https://learn.andoyaspace.no/docs/cansat/arduino_uno/telemetry_system/"
final_url: "https://learn.andoyaspace.no/docs/cansat/arduino_uno/telemetry_system/"
title: "Telemetry system"
extracted_at: "2026-06-12T06:29:52.592306+00:00"
parser: "trafilatura-markdown"
confidence: 0.853
content_type: "text/html"
http_status: 200
word_count: 1471
---

# Telemetry system

## Using the radio

Telemetry is a technology that allows transmission of data from remote measurement devices. It is derived from the Greek words âteleâ, meaning remote, and âmetronâ, meaning measure. Telemetry is an essential part of rocketry and satellite technology. Information is transmitted wirelessly using radio waves. On the ground these signals are collected by radio receivers. Large space agencies have networks of these ground stations stretching all over the globe, tracking, monitoring and receiving telemetry from their satellites.

Telemetry data can be divided into two groups: data from internal sources and data from external sources. Rockets and satellites are equipped with countless sensors that measure internal parameters. The measurements they take may relate to temperature, pressure, attitude, power usage, and a wide variety of other measurements. The information from these sensors is called âhousekeeping dataâ. This is used to monitor the satellites health, and is necessary for the operation of the system.

Information from the external sources is mostly what interest scientists. This is the data collected from the payload. The payload of a research satellite typically takes the form of sensors or other equipment which measures and generates data about our planet, the space environment, the sun, the stars, or any number of other things depending on the mission. This information is called the âmission dataâ or âscientific dataâ. In your CanSat this would be the information from the sensor board. This data is sent to a ground station to be studied by scientists.

CanSat telemetry operations can be broken down into three distinct components: transmitting data, receiving data, and processing data.

The transmitter board inside the CanSat collects information and transmits it as a radio signal.

This signal is received by the ground station and sent to a laptop, where it is stored before being processed as experimental data.

## Transceiver APC220

A transceiver is a device comprising both a transmitter and a receiver which are combined and share common circuitry or a single housing. When no circuitry is common between transmit and receive functions, the device is a transmitter-receiver.

In the Arduino CanSat kit we are using APC220 which is a transceiver, with a highly versatile low power radio solution that is easy to setup and integrate into any project requiring a wireless RF link. It is perfect for robotic application which gives you wireless control. You can connect one of these modules with your microcontroller through TTL interface. And connect your PC with another APC220 module through a TTL/USB converter.

Configuring the transceiver is done directly from the Arduino board using a pre-programmed script found in the [Downloads](https://learn.andoyaspace.no#downloads) section below.

## Ground station

### Installing drivers

The transceiver at the ground station will be connected to the computer trough a USB-TTL converter. This module needs a driver to work properly. The latest VCP (Virtual Com Port) drivers for the USB-TTL module can be downloaded using the link in the [Downloads](https://learn.andoyaspace.no#downloads) section below. Download the driver according to your platform.

## Programming the radio

Connect the Arduino board to the computer and upload (and unzip) the program *apc220cfg.ino* which can be found [Downloads](https://learn.andoyaspace.no#downloads) section below.

Make sure you upload the program before you try to connect the transceiver to the Arduino board. Disconnect the USB cable (and battery) from the Arduino board and connect the transceiver to the Arduino as shown in the following image.

Note

The transceiver will be connected to the pins labelled GND, 8, 9, 10, 11, 12 and 13 on the Arduino Board.

Reconnect the Arduino board trough the USB cable and open the Serial Monitor. In the command line at the top, type in **m** and hit enter. This will bring up the menu shown in figure below.

If you type **r** and hit enter, the program will return the current configuration for the transceiver.

To reconfigure the radio, type **w** and the 5 parameters needed, with space between each parameter.

### Frequencies

For your CanSat you have been given a pre-set frequency. If not, a list of frequencies are listed here in the figure below. The bitrate should be set to 9600 bps.

| Frequencies (MHz) | Team | Frequencies (MHz) | Team |
|---|---|---|---|
| 433,050 | 433,950 | ||
| 433,100 | 434,000 | ||
| 433,150 | 434,050 | ||
| 433,200 | 434,100 | ||
| 433,250 | 434,150 | ||
| 433,300 | 434,200 | ||
| 433,350 | 434,250 | ||
| 433,400 | 434,300 | ||
| 433,450 | 434,350 | ||
| 433,500 | 434,400 | ||
| 433,550 | 434,450 | ||
| 433,600 | 434,500 | ||
| 433,650 | 434,550 | ||
| 433,700 | 434,600 | ||
| 433,750 | 434,650 | ||
| 433,800 | 434,700 | ||
| 433,850 | 434,750 | ||
| 433,900 | 434,800 |

Note

You have to configure both transceivers with the same settings to be able to use them together. Also, remember to set the jumbers correct on the CanSat sensor board to allow radio programming. See chapter on [Jumper settings](https://learn.andoyaspace.no/data_acquisition_and_final_testing/#jumper-settings).

### Testing the radio

When you are finished programming the CanSat kit you should test that the radio link is working properly. Place jumpers on J2 and J3, connect the receiver to the PC via the USB to UART Bridge (USB-converter) and open the Arduino software.

Change the COM-port from Arduino Uno R3 (COMxx) to Silicon Labs CP210x USB to UART Bridge (COMxx) in the Arduino software by going to Tools â Serial Port. If you donât remember which COM-port that is the correct one, go to the Device Manager.

Press the serial monitor to look at the data that is coming from the radio.

To store data we use Terminal v.1.9b by Br@y++.

Important notes

If you donât see any data in the Arduino serial monitor, the reason could be that the âenableâ pin on the radio module connected to the USB-to-Serial bridge is set to âoffâ. If this is the reason, the storing program Terminal will still work, but you can do the following to enable passage through the bridge and get the data on to the Arduino serial monitor:

Disconnect the radio module from the USB-to-Serial bridge and lift/bend or isolate the EN pin on the radio module so it isnât connected to the RTS port of the bridge. Do not remove or destroy the pin, you might need it later. Reconnect to the pc/bridge and open the serial monitor again.

## Antenna Design

The antenna that is included with the APC220 radio is a 433MHz Rubber Duck antenna. This antenna is robust and great for testing, but wonât usually fit inside a soda can.

A good alternative is the simple thread antennas that can be attached to a SMA-Connector or alternatively soldered directly on to the transmitter output. Normally such antennas will be a quarter-wavelength. The thickness is not critical; the most important is the flexibility and durability.

Antenna length can be calculated from equation below when the frequency (\(f\)), and velocity of light (\(c\)) is known:

If we have a frequency \(f\)Â of 434 MHz, then the equation for calculating the length of a quarter wavelength is:

By this calculation we find that the antenna should be 17.3 cm long.

We can build this antenna by using a coaxial cable. Remove 17.3 cm of the plastic jacket and the metallic shield from the cable, leaving the centre core and dielectric insulator. Make sure that the shielded part of the cable reaches all the way out of the can before it is stripped.

## Terminal logging software

Terminal v1.9b by Br@y++ is a free software application that can read and store data coming from the serial ports. You can download the latest version in the [Downloads](https://learn.andoyaspace.no#downloads) section below.

Choose the correct Com-port and click connect in the top left corner in the program. If you have an Arduino (or radio) connected you should receive data in the terminal.

If you want to store the data you can find a button labelled **StartLog**. A popup will appear asking you where to store the log-file. Choose your folder and file name and press **Open**. The terminal will now write all the data coming in from this point and until you press **StopLog**.

After you are done logging data, you can open the text-file in any text editor. If the data is plain numbers with commas between it is easy to copy into a spreadsheet or other mathematical programs or programming languages like Python.

## Downloads

[APC220 Data sheet](https://learn.andoyaspace.no/assets/GY91.zip)
[APC220 configuration program](https://learn.andoyaspace.no/assets/apc220Cfg.zip)
[APC220 USB driver](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
[Terminal software](https://sites.google.com/site/terminalbpp/)
