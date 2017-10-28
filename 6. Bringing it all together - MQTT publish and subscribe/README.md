First some explanations about code in the merged project.

# Non-blocking code with Interrupts
There is no multi-process, nor multi-threading, support on the Arduino. Using delay() has a (usually not intended) sideeffect - the Arduino does nothing for that while. The very same thing is true when MQTT is listening for published information. In the code below (used in the example above) Arduino is listening for 5000ms for new information published over MQTT. During this time, to other code can run.
```
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {  // this is our 'wait for incoming subscription packets' busy subloop
    if (subscription == &button) {
```
Interrupts can be used in order to be able to look for MQTT messages at the same time as reading the door sensor. Arduino supports Interrupts with digital pins. If then there is a state change on a digital pin (e.g. door sensor) Ardunio will leave the loop-function and will jump into a defined interrupt-handler-function. After completing the interrupt-handler-function, loop-function will kick in again.

<img src="https://techtutorialsx.files.wordpress.com/2016/12/esp8266-interrupts.png">

Check <a href="https://techtutorialsx.com/2016/12/11/esp8266-external-interrupts/">here</a> for details.

# Adressing switch bouncing
When you push a button, press a micro switch (e.g. door sensor) or flip a toggleswitch, two metal parts come together. It might seem that the contact is made instantly. That is not quite correct. Inside the switch there are moving parts. When you push the switch, it initially makes contact with the other metal part, but just in a brief split of a microsecond. Then it makes contact a little longer, and then again a little longer. In the end the switch is fully closed. This is called bouncing.
In the first example with the door sensor, the state of the sensor is read in the loop and then some other code is executed. Switch bouncing is no problem there because the state is read on demand. The case with interrupts is different - the interrupt handler function is triggered multiple times because of the bounce of the door sensor. There need to be code addressing this (software debounce).

Check <a href="https://www.allaboutcircuits.com/technical-articles/switch-bounce-how-to-deal-with-it/">here</a> for details.

# Merged project - MQTT subscribe to trigger a Mystrom outlet using rest *and* a MQTT publish with a door state

The sketch is basically the code from the two examples in chapter 4 and 5. It also includes switch boucing and the interrupt handler for the door sensor. One point to mention: because MQTT publishing takes some time and an interrupt is fired on change (on close *and* open) two short intrrupts could disrupt the MQTT publishing and therefore send nothing. Check the picture below with a long and a short "open/close". Potentially this should be changed that only one interrupt gets triggered on a door open/close (on falling or rising edge).

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/6_1_Serial_Console.png">

# Get the merged project in play
Create an empty sketch in your Arduino IDE and copy / paste the follwing code provided in this section (<a href="https://github.com/cvolkmer/iot-hackathon/blob/master/6.%20Bringing%20it%20all%20together%20-%20MQTT%20publish%20and%20subscribe/esp8266_MQTT_sensor_rest.ino">esp8266_MQTT_sensor_rest.ino</a>) 

You need to adjust the values in the "Variable Setup" Section:

````
/************************* Variable Setup ************************************/

#define WLAN_SSID       "<YOURWLANSSID>"        // Insert your WLAN SSID
#define WLAN_PASS       "<YOURWLANPASSWORD>"    // Insert your WLAN Password

#define AIO_SERVER      "io.adafruit.com"       // Adafruit Service 
#define AIO_SERVERPORT  1883                    // use 8883 for SSL
#define AIO_USERNAME    "<YOURAIOUSER>"         // Insert your AIO Username
#define AIO_KEY         "<YOURAIOAPIKEY>"       // Insert your AIO API Key

#define MYSTROM         "<YOURMYSTROMIP"        // Insert the IP Adress of your myStrom WiFi Switch

````




