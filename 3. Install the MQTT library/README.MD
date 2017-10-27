# What is MQTT?
MQTT is the defacto standard the exchange information for IOT devices. It uses a message broker, where multiple clients can publish information. Everything interested in this information can subscribe for a so-called topic and gets then automatically informed. Therfore MQTT is bidirectional, and maintains stateful session awareness. HTTP Calls in contrast are stateless - a client has to ask for the same thing all over again.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/3_0_1_mqtt_library.png">

A very good explanation why MQTT is needed can be found <a href="https://learn.adafruit.com/mqtt-adafruit-io-and-you/why-mqtt?view=all#why-mqtt">here</a>.

#What is Adafruit.io?
Adafruit in generall is a manufaturer / broker of microcontrollers. They've built an own IoT communications platform (Adafruit.io) to interact with devices over the internet. There are certainly a lot of great services out there for datalogging, or communicating with your microcontroller over the web, but Adafruit.io is very easy and simple to get started. It is free of charge with a basic plan (absolutely sufficient for your use case).

# Install the MQTT Library
By integrating additional libraries in your code, you're able to extend the functionality of your device. To send and receive messages to/from an MQTT message broker, we have to install that library.

1. Open "Sketch" - "Include Library" - "Manage Libraries" in your Arduino IDE.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/3_1_mqtt_library.png" width="60%">

2. Search for "adafruit mqtt" and install the "Adafruit MQTT" Library.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/3_2_mqtt_library.png)
