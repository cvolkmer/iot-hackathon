# Install the MQTT Library
You'll install additional libraries that are needed in order to send and receive MQTT Messages to/from an MQTT Message Broker.

1. Open "Sketch" - "Include Library" - "Manage Libraries" in your Arduino IDE.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/3_1_mqtt_library.png" width="60%">

2. Search for "adafruit mqtt" and install the "Adafruit MQTT Library".

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/3_2_mqtt_library.png)


# What is MQTT?

MQTT is the defacto standard the exchange information for IOT devices. It uses a message broker, where multiple clients can publish information. Everything interested in this information can subscribe for a so-called topic and gets then automatically informed. Therfore MQTT is bidirectional, and maintains stateful session awareness. HTTP Calls in contrast are stateless - a client has to ask for the same thing all over again.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/3_0_1_mqtt_library.png">

A very good explanation why MQTT is needed can be found <a href="https://learn.adafruit.com/mqtt-adafruit-io-and-you/why-mqtt?view=all#why-mqtt">here</a>.