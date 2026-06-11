---
url: "https://learn.andoyaspace.no/docs/cansat/teensy/telemetry_system/"
final_url: "https://learn.andoyaspace.no/docs/cansat/teensy/telemetry_system/"
title: "Telemetry system"
extracted_at: "2026-06-11T20:36:15.252549+00:00"
parser: "trafilatura-markdown"
confidence: 0.860
content_type: "text/html"
http_status: 200
word_count: 2792
---

# Telemetry system

## Using the radio

Telemetry is a technology that allows transmission of data from remote measurement devices. It is derived from the Greek words *tele*, meaning remote, and *metron*, meaning measure. Telemetry is an essential part of rocketry and satellite technology. Information is transmitted wirelessly using radio waves. On the ground these signals are collected by radio receivers. Large space agencies have networks of these ground stations stretching all over the globe, tracking, monitoring and receiving telemetry from their satellites.

Telemetry data can be divided into two groups: data from internal sources and data from external sources. Rockets and satellites are equipped with countless sensors that measure internal parameters. The measurements they take may relate to temperature, pressure, attitude, power usage, and a wide variety of other measurements. The information from these sensors is called âhousekeeping dataâ. This is used to monitor the satellites health, and is necessary for the operation of the system.

Information from the external sources is mostly what interest scientists. This is the data collected from the payload. The payload of a research satellite typically takes the form of sensors or other equipment which measures and generates data about our planet, the space environment, the sun, the stars, or any number of other things depending on the mission. This information is called the âmission dataâ or âscientific dataâ. In your CanSat this would be the information from the sensor board. This data is sent to a ground station to be studied by scientists.

CanSat telemetry operations can be broken down into three distinct components: transmitting data, receiving data, and processing data.

The transmitter board inside the CanSat collects information and transmits it as a radio signal.

This signal is received by the ground station and sent to a laptop, where it is stored before being processed as experimental data.

## The RFM96 radio

The RFM96 is a radio for 433 MHz ISM band, which is free to use and perfect for CanSat use. The radio uses a proprietary protocol called LoRa (short for long range), patented by Semtech, that is perfect for low data rate, but long range and relatively low transmission power (+20 dBm, 100 mW maximum). You can read more about the protocol, with its advantages and disadvantages here.

AndÃ¸ya Space has used this radio in other activities than CanSats also, and actually we routinely use this radio in weather balloons which go up to 25 km altitude with a total distance between the ground station and the transmitter of 230 km! We do this, however, at a lower data rate than you will use, since you do such a long range.

The black IC/chip you can see on the board (with an H on it) are actually made for a very wide range of frequencies, and the passives on the board (most of what is not the black chip) are filters that limits it to 433 MHz frequencies. The communication between the radio and the microcontroller uses SPI, which is super fast. Your Cansat will use a 8 MHz SPI clock. The radio sends a large frame where the data that you as a user sends is a (large) part of it, but it sends also other things, so the data rate is not that straight forward to calculate. You will probably send approx. two frames each second, depending on the frame size. Frames is a whole data packet that you choose to send (most often one Â«lineÂ» that you can see in Arduinoâs Serial Monitor). Sending less data means that you can send more often, so limit the data to what you need, and not more.

One of the advantages with this radio compared to other CanSat radios is that you can check when the radio is ready to send more data, so you can make better use of the time when you send, because you can send a new data packet directly after the previous one has been sent. You will see how you can do this in a later article.

It is important that you do not use the same frequency as another CanSat team, and at the CanSat operation, use at least 100 kHz difference in frequencies. Another advantage of this radio compared to the previous radio is that the frequency used is set in software at runtime of your current sketch, so it does not need to be programmed before using it. AndÃ¸ya Space Education has written a custom library for this radio, which also includes writing to the local SD card at the same time, and it is good to know a little bit of how this library works. You as a user set the frequency, and the first two bytes of each package (hidden to the user) is a sync word. This sync word is unique for the frequency that you use. If another CanSat team sets approximately the same frequency as you have chosen, it might interfere with your transmission, but the library will only handle packets with the same sync word as you. So the library will discard anything that it received that has not exactly the same frequency as you, but it cannot do anything with interference, which is a physical phenomenon which software has nothing to do with.

### Testing the RFM96 radio

Now we are finally ready to send something over the air! In the Cansat_RFM96 library there are some examples that can be used for testing the radios.

First, connect only the Cansat board to the computer with USB and make sure that the antenna is connected properly. **Never use the radio without an external antenna connected!** The antenna can be either a small whip antenna or a Yagi antenna or any other 50 Ohm impedance antenna made for the 433 MHz frequency band. Locate the example sketch in Files -> Examples -> Cansat_RFM96 and select the sketch Â«Cansat_SendPressureWithRFM96Â» and upload it to the board. Open the Serial Monitor, and you should see the pressure measurements that are transmitted by the radio. Note, however, that the sketch is what outputs the data also to the Serial port, which is not what happens without explicitly programmed to do so. Now the Cansat will send data at a given rate as long as it is connected to power, and it does not need to be connected to a computer to do so.

Disconnect the Cansat board and connect the ground control board (GCB) to the USB. Now locate the example sketch Â«Cansat_RadioRecvTestÂ» in the same example folder as above and upload it to the GCB. Now, in principle you can also connect the Cansat board to the computer to power it up, but it will be simpler for you to not connect the GCB and Cansat boards to the same computer, so life is going to be easier for you if you find another power supply for the Cansat (like a wall charger or a USB battery pack). While the GCB is connected and Cansat board unconnected to power, open Serial Monitor and see that you will periodically get text from the GCB stating that it did not receive any data in a given time frame. Connect now the Cansat to power, and you should then see text and data from the Cansat streaming in on the Serial Monitor connected to the GCB. If this is not the case, look in the code and find out if the radio frequency is the same for both transmitter and receiver, change to the same frequency if necessary. Does it work now?

Congratulations, you have transmitted your first data packets!

Now spend some time on trying to understand how the transmitting sketch and the GCB receive sketch work, and to play around with it to learn how to use the radio.

### The RFM96 library command set

AndÃ¸ya Space has written an Arduino library for the RFM96 radio for use on CanSat activities. This page will list the different commands than can and should be used by the user. When you use the radio, make sure that you have included the radio by using this at or close to the top of you sketch:

Note that this is not all the commands that are available for the user, but the other commands will be very specific and is not documented. This is for instance to change the bandwidth, coding rate and spreading factors and other transceiver specific parameters (these are the parameters that we set when reaching 60 km of range). Also, there are some functions for debugging the radio that should not be necessary to use. Basic commands

This will make an object for the library named rfm96, with the frequency of 433500 kHz (433.500 MHz), so please use the frequency that your tutor tells you to if you have been given one. Using this object initialization will use SD card by default. This Â«commandÂ» (it is not strictly as command per se) or the one below must be used when using the radio, or else you will get an error.

These two commands will disable use of SD cards. You can still use the SD card commands stated below, but the library will just not execute the parts of the commands related to SD cards.

This will initialize the rfm96 object that you made above. It does not take any inputs, but it will give an output stating if the initialization was successful or not. The normal use of it is something like this:

rfm96.printToBuffer(1001);
rfm96.printToBuffer(this_is_a_variable_containg_numbers);
rfm96.printToBuffer("This is some text");
rfm96.printlnToBuffer(1001);
rfm96.printlnToBuffer(this_is_a_variable_containg_numbers);
rfm96.printlnToBuffer("This is some text");
rfm96.printlnToBuffer();

When you want to send something or write to the SD card (often both, but not always), you will first need to fill a buffer before actually using the send or writeToFile commands. This is how you can send numbers or text or lineshifts. The use of these commands is exactly the same as when using the Serial.print and Serial.println commands (if you are familiar with Arduino from before, this is something that you would have seen), and they behave exactly the same, except that they only writing it to a buffer and not actually sending it or writing to file. The printToBuffer and printlnToBuffer commands will convert whatever is not in readable ASCII (normal text) to ASCII. The difference between the commands with print and println is that the commands with println will do the same thing as print, but will also add a line shift after it.

This is the same as the print counterparts from above, but this does not convert anything to ASCII/readable text, it will just add it without doing anything with the data. This is not often used in Cansat, but it might be used for very advanced users which will try to compact the data that it sends to binary. It is not very user friendly to do this, so make sure you understand how to use it works.

This will mark anything in the buffer to transmit. It is a so-called blocking command, which means that if the radio is not ready for transmission it will wait (block anything else going on) before setting the buffer to transmit the data currently in the buffer. Note that this command also clears the buffer, so writing to file after using a send will not do anything, since the buffer will be empty.

This will write everything that is in the current buffer to the SD card. It will not clear the buffer, so you can use this before using the send command to send with the radio.

A combination of the send and writeToFile commands. The way this function works is that it will write everything in the buffer to the SD card, then check if the radio is ready to transmit, and if that is the case, it also send with the radio. However, if the radio is not ready to transmit, it will exit the function without sending anything. It will always clear the buffer, no matter if the radio was ready to transmit or not. This is a command that is very easy to use, but it leaves the user out of control of some things. To be clear of how it works, this is the entire function:

uint8_t Cansat_RFM96::sendAndWriteToFile() {
uint8_t tmp_length;
tmp_length = writeToFile(); // This is always ready,
// and will also flush every time
if (isTxReady())
tmp_length = send(); // IF we send, then this is the length we return
clear(); // We empty the buffer and are ready to fill it up again
return(tmp_length);
}

This will clear anything in the buffer, and do nothing else. This must be done if you use the writeToFile command without using the send command after it, as the writeToFile command does not clear the buffer.

With this command it is possible to get the content in the buffer without sending it by the radio and thereby clearing the buffer. It can be used f.ex. in the case where we want to use the serial monitor to control what is actually send by the radio:

The two above code lines can be replaced by the single command:

As the name suggest, this command will set the TX power, and the input is the transmit power in dBm. You can set it from +5 dBm (lowest) to +20 dBm.

This command returns the Received Signal Stength Indication (RSSI) value of the lastly received data package and store it in a variable called last_RSSI_value (you can change the variable name) in dBm power. The RSSI is an indicator of the received signal strength, and is an excellent indication of how Â«farÂ» you are from losing communication between the CanSat and the ground station. Normally the CanSSat starts dropping out at about -80 dBm. You can read more about RSSI in general here (which is not specific to the RFM96 radio).

## Ground station

For the ground Station, you will need another empty CanSat board and only equip it with:

- RFM96 radio module
- Teensy 4.1
- sma connector
- An antenna (for example an 1/4 Î»-wire antenna or a YAGI antenna)

When working as a ground station, the Teensy 4.1 will be connected and powered via an USB cable to your pc, and needs no voltage regulator or other components on the board, except the radio and sma connector.

The CanSat shield board is now ready to be tested.

## Antenna design

The antenna that is included with the RFM96 radio is a 433MHz Rubber Duck antenna. This antenna is robust and great for testing, but wonât usually fit inside a soda can.

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

[Terminal software](https://sites.google.com/site/terminalbpp/)
[Radio RFM96 library](https://learn.andoyaspace.no/assets/Cansat_RFM96.zip)
