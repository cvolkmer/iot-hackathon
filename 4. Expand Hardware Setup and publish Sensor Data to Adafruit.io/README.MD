# Load the new project
After your first experience with Arduino, you'll build a specific use case. Your WeMos will be connected to the Internet and publish sensor data to the Adafruit IoT Platform. The following things need to be setup in order to do that.

1. Create an Adafruit Account
2. Connect your Door-Sensor
3. Create a new Project in your Adafruit IDE
4. Publish Sensor Data to Adafruit

# Create an Adafruit Account
Visit the Adafruit Website and create a free account https://io.adafruit.com/. Adafruit provides a free or charge IoT Service to get started easily with your project. To send and receive data between Adafruit and your WeMos it's best to define dedicated message Feeds. It's not mandatory but it makes sense because we're having two different use cases (send sensor data to Adafruit and receiving data to control your Wireless Switch). To so so Click on "Feeds" => "Acions" => and "Create a New Feed".

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_1_adafruit_create_sensor_feed.png" width="90%">

The two feeds ("doorsensor" and "wifiswitch" are used in code examples. Create these two feeds now. You can choose different feed names, but you've to modify your code accordingly to make it work.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_2_adafruit_create_sensor_feed.png" width="50%">

# Connect Door-Sensor
Connect your sensor to the following Pins on your WeMos Board. In the Arduino Sketch we're using Pin D3 + GND for the connection. You can use another digital input but you've to modify your Adruino Sketch accordingly. 

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_3_wemos_sensor_cabling.png" width="40%">

# Create a new Project in your Arduino IDE
Create an empty sketch in your Arduino IDE and copy / paste the follwing code provided in this section (esp8266_MQTT_sensor.ino) 

You need to adjust the values in the "Variable Setup" Section:

````
/************************* Variable Setup ************************************/

#define WLAN_SSID       "<YOURWLANSSID>"        // Insert your WLAN SSID
#define WLAN_PASS       "<YOURWLANPASSWORD>"    // Insert your WLAN Password

#define AIO_SERVER      "io.adafruit.com"       // Adafruit Service 
#define AIO_SERVERPORT  1883                    // use 8883 for SSL
#define AIO_USERNAME    "<YOURAIOUSER>"         // Insert your AIO Username
#define AIO_KEY         "<YOURAIOAPIKEY>"       // Insert your AIO API Key

````
# Publish Sensor Data to Adafruit via MQTT
Upload your Sketch to your WeMos and open the serial console to debug the output. Your WeMos should have joined the local WLAN and established a connection with Adafuit. If you open or close the door sensor you should see appropriate values "0" and "1" logged in the serial console.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_4_sketch_serial_output.png" width="70%">

If you login to Adafruit and navigate to your feed, you should see the same values published like in the serial console.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_5_adafruit_feed_log.png" width="90%">

You have now successfully published states from your door sensor to Adafruit via MQTT. This used case covered the publish portion when using MQTT. In the next chapter, you will use code which does the opposite. Your WeMo will subscribe to a message feed and wait for input to be executed.

# Connect with an MQTT client to the door feed
MQTT clients like mqttool can be used to subscribe to the door feed. Find the details <a href="https://learn.adafruit.com/adafruit-io/mqtt-api">here</a>.

Use your username and AIO-Key as password to connect. The feeds at io.adafruit.com are starting with the username.

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_6_mqttclient1.png" width="40%">
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/4_6_mqttclient2.png" width="40%">