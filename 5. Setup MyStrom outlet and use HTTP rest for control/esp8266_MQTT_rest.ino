/***************************************************
  Door sensor publish and Mystrom subscribe over MQTT
  based on Adafruit MQTT Library ESP8266 Example
  Button is between GND and D3
  Button is triggering an interrupt in order to leave enough time
  in main loop for MQTT to listen for messages (Mystrom subscribe).
  Mystrom Switch is in the local network: https://mystrom.ch/wp-content/uploads/REST_API_SWI.txt
  Good Interrupt intro for ESP8266: https://techtutorialsx.com/2016/12/11/esp8266-external-interrupts/
  Fix for problems with MQTT publishing in the interrupt function: https://github.com/knolleary/pubsubclient/issues/99
  Written by Christian Volkmer and Christoph Schnidrig
  See https://learn.adafruit.com/mqtt-adafruit-io-and-you/overview for details.
  The MQTT broker from Adafruit is being used:
  https://io.adafruit.com
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
 #include <ESP8266HTTPClient.h>
 #include "Adafruit_MQTT.h"
 #include "Adafruit_MQTT_Client.h"
 
 /************************* Variable Setup ************************************/
 
 #define WLAN_SSID       "<YOURWLANSSID>"        // Insert your WLAN SSID
 #define WLAN_PASS       "<YOURWLANPASSWORD>"    // Insert your WLAN Password
 
 #define AIO_SERVER      "io.adafruit.com"       // Adafruit Service 
 #define AIO_SERVERPORT  1883                    // use 8883 for SSL
 #define AIO_USERNAME    "<YOURAIOUSER>"         // Insert your AIO Username
 #define AIO_KEY         "<YOURAIOAPIKEY>"       // Insert your AIO API Key
 
 #define MYSTROM         "<YOURMYSTROMIP>"        // Insert the IP Adress of your myStrom WiFi Switch
 
 /************************* Other Setup Variables *****************************/
 
 /************ Global State (you don't need to change this!) ******************/
 
 // Create an ESP8266 WiFiClient class to connect to the MQTT server.
 WiFiClient client;
 // or... use WiFiFlientSecure for SSL
 //WiFiClientSecure client;
 
 // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
 Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
 
 HTTPClient http;
 
 /****************************** Feeds ***************************************/
  
 // Setup a feed called 'wifiswitch' for subscribing to changes.
 Adafruit_MQTT_Subscribe wifiswitch = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/wifiswitch", MQTT_QOS_1);
 
 /*************************** Sketch Code ************************************/
 
 void setup() {
   Serial.begin(115200);
   delay(10);
 
   pinMode(LED_BUILTIN, OUTPUT);  // set onboard LED as output (will be used for successful MQTT connection)
   digitalWrite(LED_BUILTIN, HIGH);  // sets the LED if MQTT is connected
   
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
 
   // Setup MQTT subscription for onoff feed.
   mqtt.subscribe(&wifiswitch);
   
   Serial.println();
   Serial.println("subscribing to MQTT switch feed");
 }
 
 void loop() {
   // Ensure the connection to the MQTT server is alive (this will make the first
   // connection and automatically reconnect when disconnected).  See the MQTT_connect
   // function definition further below.
   MQTT_connect();
 
   Adafruit_MQTT_Subscribe *subscription;
   while ((subscription = mqtt.readSubscription(5000))) {  // this is our 'wait for incoming subscription packets' busy subloop
     if (subscription == &wifiswitch) {
       Serial.print(F("\nGot: "));
       Serial.println((char *)wifiswitch.lastread);
 
       if (strcmp((char *)wifiswitch.lastread, "ON") == 0)
       {
         String url = "http://";
         url += MYSTROM;
         url += "/relay?state=1";
         
         http.begin(url);
         http.addHeader("Content-Type", "text/plain");
         int httpCode = http.GET();
         http.end();
         Serial.print(F("\n Switching Relay ON"));
       }
 
       if (strcmp((char *)wifiswitch.lastread, "OFF") == 0)
       {
         String url = "http://";
         url += MYSTROM;
         url += "/relay?state=0";
         
         http.begin(url);
         http.addHeader("Content-Type", "text/plain");
         int httpCode = http.GET();
         http.end();
         Serial.print(F("\n Switching Relay OFF"));
       }
     }
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
        digitalWrite(LED_BUILTIN, HIGH);
        delay(5000);  // wait 5 seconds
        retries--;
        if (retries == 0) {
          // basically die and wait for WDT to reset me
          while (1);
        }
   }
   Serial.println("MQTT Connected!");
   digitalWrite(LED_BUILTIN, LOW);  // sets the LED if MQTT is connected
 }