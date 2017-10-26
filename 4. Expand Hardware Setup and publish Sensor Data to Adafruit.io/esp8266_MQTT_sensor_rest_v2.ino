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
 *****************************************************************************/

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

#define MYSTROM         "<YOURMYSTROMIP"        // Insert the IP Adress of your myStrom WiFi Switch

/************************* Other Setup Variables *****************************/

int inputPin = D3;                              // pushbutton connected to digital pin D3
int state = HIGH;                               // the current state of the output pin

long timestamp = 0;                             // the last time something has been published via MQTT 

boolean interruptstate = false;                 // flag for interrupt by button

unsigned long lastDebounceTime = 0;             //last time the pin was toggled, used to keep track of time
unsigned long debounceDelay = 50;               //the debounce time which user sets prior to run

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

HTTPClient http;

/****************************** Feeds ***************************************/

// Setup a feed called 'button' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish button = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/button", MQTT_QOS_1);
Adafruit_MQTT_Publish esp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/esp", MQTT_QOS_1);

// Setup a feed called 'relay' for subscribing to changes.
Adafruit_MQTT_Subscribe relay = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay", MQTT_QOS_1);

/*************************** Sketch Code ************************************/

void buttonChange() {  // function to be executed on interrupt (button on Pin D3)
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 300ms, assume it's a bounce and ignore. (what is switch bounce? see: https://www.allaboutcircuits.com/technical-articles/switch-bounce-how-to-deal-with-it/)
  if (interrupt_time - last_interrupt_time > 300)
  {
    Serial.print(F("\n Button pressed "));
    interruptstate = true; // setting flag to invoke MQTT publish in main loop
  }
  last_interrupt_time = interrupt_time;
}

void interruptAction() {
  interruptstate = false; // resetting interrupt flag
  Serial.print(F("\nSending button state "));
  if (! button.publish("1")) {  // Now we can publish stuff!
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT);  // set onboard LED as output (will be used for successful MQTT connection)
  pinMode(inputPin, INPUT_PULLUP);  // set pin as input
  attachInterrupt(digitalPinToInterrupt(inputPin), buttonChange, FALLING); // trigger interrupt on button click. Function buttonChange will be invoked.

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
  mqtt.subscribe(&relay);
  
  Serial.println();
  Serial.println("subscribing to MQTT relay feed");
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // checking if returning from interrupt (buttonChange function)
  if (interruptstate == true) {
    interruptAction();
  }

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {  // this is our 'wait for incoming subscription packets' busy subloop
    if (subscription == &relay) {
      Serial.print(F("\nGot: "));
      Serial.println((char *)relay.lastread);

      if (strcmp((char *)relay.lastread, "ON") == 0)
      {
        http.begin(MYSTROM, 80, "/relay?state=1");
        http.addHeader("Content-Type", "text/plain");
        auto httpCode = http.GET();
        Serial.print(F("\n Switching Relay ON"));
      }

      if (strcmp((char *)relay.lastread, "OFF") == 0)
      {
        http.begin(MYSTROM, 80, "/relay?state=0");
        http.addHeader("Content-Type", "text/plain");
        auto httpCode = http.GET();
        Serial.print(F("\n Switching Relay OFF"));
      }

      if (strcmp((char *)relay.lastread, "TOGGLE") == 0)
      {
        http.begin(MYSTROM, 80, "/toggle");
        http.addHeader("Content-Type", "text/plain");
        auto httpCode = http.GET();
        Serial.print(F("\n Toggle Relay"));
      }
    }
  }

 // ping the server to keep the mqtt connection alive
 // NOT required if you are publishing once every KEEPALIVE (300) seconds
 // millis() = number of milliseconds since the program started 

  if (millis() - timestamp > 240000)
  {
    Serial.print("\nSending MQTT ping");
    if(! mqtt.ping()) {
      mqtt.disconnect(); // disconnect from MQTT. Will connect automatically in the beginning of the loop
      digitalWrite(LED_BUILTIN, HIGH);  // sets the LED if MQTT is connected
  }
    if (! esp.publish("ping")) {  // Now we can publish stuff!
    Serial.println(F("Updating ESP state on MQTT"));
  }
    timestamp = millis();
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
  if (! esp.publish("connected")) {  // Now we can publish stuff!
    Serial.println(F("Updating ESP state on MQTT"));
  }
  digitalWrite(LED_BUILTIN, LOW);  // sets the LED if MQTT is connected
}
