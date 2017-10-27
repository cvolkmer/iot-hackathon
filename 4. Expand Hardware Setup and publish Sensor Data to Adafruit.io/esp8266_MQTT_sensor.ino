/***************************************************
  Door sensor publish over MQTT
  based on Adafruit MQTT Library ESP8266 Example

  Door sensor is between GND and D3

  Written by Christian Volkmer and Christoph Schnidrig

  See https://learn.adafruit.com/mqtt-adafruit-io-and-you/overview for details.

  The MQTT broker from Adafruit is being used:
  https://io.adafruit.com
  The following feeds need to be created on Adafruit IO portal:
  door --> for door sensor
  switch --> for MyStrom switch
  esp --> for ESP connection log

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Adafruit Example written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* Variable Setup ************************************/

#define WLAN_SSID       "<YOURWLANSSID>"        // Insert your WLAN SSID
#define WLAN_PASS       "<YOURWLANPASSWORD>"    // Insert your WLAN Password

#define AIO_SERVER      "io.adafruit.com"       // Adafruit Service 
#define AIO_SERVERPORT  1883                    // use 8883 for SSL
#define AIO_USERNAME    "<YOURAIOUSER>"         // Insert your AIO Username
#define AIO_KEY         "<YOURAIOAPIKEY>"       // Insert your AIO API Key

/************************* Other Setup Variables *****************************/

/************************* Variable Setup *********************************/

int inputPin = D3;        // door sensor connected to digital pin D3
bool isOpen = false;      // flag for State change

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'button' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish door = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/doorsensor", MQTT_QOS_1);
Adafruit_MQTT_Publish wifiswitch = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/wifiswitch", MQTT_QOS_1);

/*************************** Sketch Code ************************************/


void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT);  // set onboard LED as output (will be used for successful MQTT connection)
  pinMode(inputPin, INPUT_PULLUP);  // set pin as input

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  //grab the current door state
  bool doorState = digitalRead(inputPin);    //LOW is closed HIGH is open

  if (!doorState && !isOpen) { //if door is open and the state closed, publish
    if (! door.publish("1")) {  // send closed
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK - sent door closed"));
    }
    isOpen = true;
    delay(500);
  }
  else if (doorState && isOpen) { //if door is closed and the state is open, publish
    if (! door.publish("0")) {  // send opened
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK - sent door opened"));
    }
    isOpen = false;
    delay(500);
  }
}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    digitalWrite(LED_BUILTIN, LOW);  // sets the LED if MQTT is connected
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  if (! wifiswitch.publish("connected")) {  // Now we can publish stuff!
    Serial.println(F("Updating Wifi Switch state on MQTT"));
  }
}
