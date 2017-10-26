# Load the new project
This chapter will be interesting because you'll build a specific use case. Your WeMos will be connected to the Internet and publish sensor data to an IoT Platform. The following things need to be setup in order to do that.

1. Create an Adafruit Account
2. Connect your Door-Sensor
3. Create a new Project in your Adafruit IDE
4. Publish Sensor Data to Adafruit

# Create an Adafruit Account
Visit the Adafruit Website and create a free account https://io.adafruit.com/. Adafruit provides a free or charge IoT Service to get started easily with your project. To send and receive data between Adafruit and your WeMos it's best to define dedicated message Feeds. It's not mandatory but it makes sense because we're having two different use cases (send sensor data to Adafruit and receiving data to control your Wireless Switch). To so so Click on "Feeds" => "Acions" => and "Create a New Feed".

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_1_adafruit_create_sensor_feed.png" width="90%">

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_2_adafruit_create_sensor_feed.png" width="70%">

Adafruit uses the MQTT Protocol and provides an MQTT broker to exchange data. A Feed is an individual channel where devices can subscribe (receive) and publish (send) data. If you want to know more about MQTT you can read a brief introduction here (https://www.hivemq.com/blog/how-to-get-started-with-mqtt).

# Connect Door-Sensor
Connect your sensor to the following Pins on your WeMos Board. In the Arduino Sketch we're using Pin D3 + GND for the connection. You can use another digital input but you've to modify your Adruino Sketch accordingly. 

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_3_wemos_sensor_cabling.png" width="50%">

# Create a new Project in your Arduino IDE
Create an empty Sketch in your Arduino IDE and copy / paste the follwing code from here: https://github.com/cvolkmer/iot-hackathon/blob/master/4.%20Expand%20Hardware%20Setup%20and%20publish%20Sensor%20Data%20to%20Adafruit.io/esp8266_MQTT_sensor_rest_v2.ino

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

/************************* Other Setup Variables *****************************/
````
Upload your Sketch to your WeMos and open the serial console to debug the output. Your WeMos should have joined the local WLAN and established a connection with Adafuit. If you open or close the door sensor you should see appropriate values "0" and "1" logged in the serial console.

Screenshot Serial Console

If you login to Adafruit and navigate to your feed, you should see the same values published like in the serial console.

Screenshot Adafruit Feed



# Publish Sensor Data to Adafruit
Modify Code with WLAN, API Key, Feed, Serial Troubleshooting Sensor Data, Verify Data arrives at Adafruit