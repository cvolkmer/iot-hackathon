# NetApp IoT Hackathon
Resources and Sources for an IoT Hackathon with an Arduino Based ESP8266 WeMos D1 mini board, Door sensor, myStrom WLAN Power Outlet, Adafruit MQTT and IFTTT.

The goal of this Hackathon is to get familiar with different technologies and build a IoT Use Case. You'll start with some basic steps, setup the IDE, hardware environment and run some simple programs. After that, you'll expand your local setup and make it communicating with Adafruit's IoT Platform using MQTT. The next step is to link Adafruit with "If this then that" (IFTTT) in order to get access to the bright IoT Space and control or trigger further events. The following picture gives you a high-level overview about what you're going to build.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/iot_hackathon_usecase_1.png "High-Level Overview IoT Hackathon")

You'll perform these steps in order to complete the Hackathon:
1. Setup your environment (Hardware Setup, Drivers, Arduino IDE) and connect it to your PC
2. Get familiar with Arduino IDE and run a sample program
3. Install the MQTT library in your Arduino IDE
4. Expand your hardware setup, signup for an account at Adafruit IoT and publish your door sesor data via WLAN / MQTT to Adafruit
5. Install and configure your myStrom WLAN power outlet and explore it's API capabilities
6. Create a push button on Adaruit and extend your code in order to toggle the myStron WLAN power outlet
7. Optional: Connect Adafruit with IFTTT and use an external trigger to toggle your WLAN power outlet or get informed if the state of your door sensor changes
