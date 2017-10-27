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