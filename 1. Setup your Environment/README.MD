# Download Drivers and Connect your board via USB
The board we're going to use is a WeMos D1 mini with an ESP8266. You can find all technical details about your board here: https://wiki.wemos.cc/products:d1:d1_mini . In order to make your board acessible from your System, you need to download the driver for you OS (https://wiki.wemos.cc/downloads). Go ahead and download and install the drivers on your system.

# Driver setup on OSX
1. Double click the "CH34x_Install_V1.4.pkg" to start the installation
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_1_install_driver_osx.png" width="70%">

2. Click "Continue"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_2_install_driver_osx.png" width="70%">

3. Click "Continue"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_3_install_driver_osx.png" width="70%">

4. Click "Install"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_4_install_driver_osx.png" width="70%">

5. You need to restart your system twice in order to load the drivers and the system extension. For the first reboot click on "Restart".
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_5_install_driver_osx.png" width="70%">

6. After the reboot connect your board to your PC using a Micro USB cable. It will show up with a warning that OSX didn't allow the extenstion to be loaded. Go to "System Preferences" - "Security & Privacy" and click on "Allow".
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_6_install_driver_osx.png" width="70%">

7. Enable the extension from "jiangsu Qunheng Co., Ltd." an click "OK"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_7_install_driver_osx.png" width="70%">

8. Enabling this extension requires your system to reboot again. Click "Restart" to reboot your system for the second time.
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_8_install_driver_osx.png" width="70%">

9. After the reboot open your Terminal App and enter the following command in order to verify that your WeMos board has been recognized.
```bash
ls /dev/tty* | grep serial
```
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_9_install_driver_osx.png" width="70%">
 
 
# Driver setup on Windows
1. Double click the "CH341SER.exe" to start the driver installation

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_1_install_driver_win.png" width="50%">

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_2_install_driver_win.png" width="50%">

2. Use the device manager to find your ESP8266 board in Windows:
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_3_install_driver_win.png" width="50%">
 
 
# Install the Arduino IDE
Next thing you're goint to do is to Install the Arduino IDE. It's one possibility to develop code and run it on your WeMos (or any other Arduino compatible) board. Download and install the Arduino IDE for your Operating System (https://www.arduino.cc/en/Main/Software). You need to install the Board Firmware for your ESP8266 board in order to access and program it. 

1. Open "Arduino" - "Preferences"

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_10_arduino_ide_setup.png)

2. Under "Additional Boards Manager URLs:" enter the following URL (http://arduino.esp8266.com/versions/2.3.0/package_esp8266com_index.json) and click "OK"

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_11_arduino_ide_setup.png)

3. Click on "Tools" - "Board: …" - "Boards Manager"

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_12_arduino_ide_setup.png)

4. Enter "ESP" into the search field. Select and Install "esp8266 by ESP8266 Community".

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_13_arduino_ide_setup.png)

5. EGo back to "Tools" - "Board: …" and select "WeMos D1 R2 & mini". 

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_14_arduino_ide_setup.png)

6. Under "Tools" - "Port" select the device port from your WeMos board which we've figured out earlier.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_15_arduino_ide_setup.png)

Congratulations! Now you're ready to load your first Program (Sketch).