# Setup MyStrom Outlet
bla

# Control myStrom Switch over HTTP Rest

The myStrom WiFi Switch offers a REST API (REST = representational State Transfer).
The interface allows you to access/control the switch directly from your local network independently from myStrom Cloud/App - you don’t need a myStrom account or the myStrom app.
With those rules you can integrate the switch in almost any environment.

Important Note
The interface is transparent and has no authentication. If someone has access to your local network, they will be able to control your switch.
Please apply strong security mechanisms to protect your network.

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

You can use your browser or command line utililty to test the API.

