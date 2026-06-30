---
url: "https://learn.andoyaspace.no/ebook/the-cansat-book/v2018/testing-and-using-the-rfm96-radio/"
final_url: "https://learn.andoyaspace.no/ebook/the-cansat-book/v2018/testing-and-using-the-rfm96-radio/"
title: "Testing and using the RFM96 radio"
extracted_at: "2026-06-11T22:24:23.205145+00:00"
parser: "trafilatura-markdown"
confidence: 0.599
content_type: "text/html; charset=UTF-8"
http_status: 200
word_count: 413
---

# Testing and using the RFM96 radio

Now we are finally ready to send something over the air! In the Cansat_RFM96 library there are some examples that can be used for testing the radios.

First, connect only the Cansat board to the computer with USB and make sure that the antenna is connected properly. **Never use the radio without an external antenna connected!** The antenna can be either a small whip antenna or a Yagi antenna or any other 50 Ohm impedance antenna made for the 433 MHz frequency band. Locate the example sketch in Files -> Examples -> Cansat_RFM96 and select the sketch «Cansat_SendPressureWithRFM96» and upload it to the board. Open the Serial Monitor, and you should see the pressure measurements that are transmitted by the radio. Note, however, that the sketch is what outputs the data also to the Serial port, which is not what happens without explicitly programmed to do so. Now the Cansat will send data at a given rate as long as it is connected to power, and it does not need to be connected to a computer to do so.

Disconnect the Cansat board and connect the ground control board (GCB) to the USB. Now locate the example sketch «Cansat_RadioRecvTest» in the same example folder as above and upload it to the GCB. Now, in principle you can also connect the Cansat board to the computer to power it up, but it will be simpler for you to not connect the GCB and Cansat boards to the same computer, so life is going to be easier for you if you find another power supply for the Cansat (like a wall charger or a USB battery pack). While the GCB is connected and Cansat board unconnected to power, open Serial Monitor and see that you will periodically get text from the GCB stating that it did not receive any data in a given time frame. Connect now the Cansat to power, and you should then see text and data from the Cansat streaming in on the Serial Monitor connected to the GCB. If this is not the case, look in the code and find out if the radio frequency is the same for both transmitter and receiver, change to the same frequency if necessary. Does it work now?

Congratulations, you have transmitted your first data packets!

Now spend some time on trying to understand how the transmitting sketch and the GCB receive sketch work, and to play around with it to learn how to use the radio.
