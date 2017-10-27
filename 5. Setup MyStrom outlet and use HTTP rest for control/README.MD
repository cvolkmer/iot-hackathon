# Setup myStrom WiFi Switch
myStrom is a Company based in Switzerland which develops and builds wireless switches and buttons. You'll use their WiFi Switch which is simply a power outlet which can be controlled in your local network only (via IP from a browser, application or your WeMos) or via Internet (myStrom Portal and Mobile App). The WiFi Switch also provides power metering functionality if you want to know the consumption of a connected device. Follow the instructions on https://mystrom.ch/wp-content/uploads/2017/01/myStrom_WiFi_Switch_CH_EN.pdf to setup your myStrom Outlet. 

# Control myStrom WiFi Switch over HTTP Rest
The myStrom WiFi Switch offers a REST API (REST = representational State Transfer). It allows you to access/control the switch directly from your local network independently from myStrom Cloud/App - you don’t need a myStrom account or the myStrom app. With those rules you can integrate the switch in almost any environment.

Important Note
The interface is transparent and has no authentication. If someone has access to your local network, they will be able to control your switch.
Please apply strong security mechanisms to protect your network.

```
Set State
ON – http://[IP]/relay?state=1
OFF – http://[IP]/relay?state=0
TOGGLE – http://[IP]/toggle

Get Values
http://[IP]/report

Response
{
	"power":	0,
	"relay":	false
}

[IP] – IP Address of your Switch e.g. 192.168.1.99
```
Use your browser to test the API calls and discover their functionality.

# Create a new Project in your Arduino IDE
Create an empty sketch in your Arduino IDE and copy / paste the follwing code provided in this section (esp8266_MQTT_rest.ino) 

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

# Receive input from Adafruit via MQTT
We now want to send data to your WiFi Switch via Adafruit. The easiest way to do that is by creating a dashboard with an interactive switch. Navigate to "Dashboards" in your Adafruit console and cllick on "Actions" => "Create a new Dashboard". Provide a name and hit "Create".

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/5_1_create_new_dashboard.png" width="90%">

Open the empty dashboard and add a widget (block)
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/5_2_create_new_dashboard.png" width="90%">

Have a look at the widgets which are available. Since we want to control our WiFi Switch, select the switch (on-off) widget in the top left corner.
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/5_3_create_new_dashboard.png" width="90%">

Select the "wifiswitch" Feed.
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/5_4_create_new_dashboard.png" width="90%">

You can edit the title and click "Create block" to crete a switch item on your dashboard
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/5_5_create_new_dashboard.png" width="90%">

Toggle the widget on-off and see what happens with your WiFi Switch! For debugging purposes you can add aditional blocks like a text block. This allows you to see what data is being send to or from Adafruit. Add a text widget to your dashboard. Try out other widgets as well if you want.
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/5_6_create_new_dashboard.png" width="60%">
