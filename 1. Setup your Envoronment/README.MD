# Setup your environment
The board we're going to use is a WeMos D1 mini with an ESP8266. You can find all technical details about your board here: https://wiki.wemos.cc/products:d1:d1_mini . In order to make your board acessible from your System, you need to download the driver for you OS (https://wiki.wemos.cc/downloads). Go ahead and download and install the drivers on your system.

1. Double click the "CH34x_Install_V1.4.pkg" in order to start the installation
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_1_install_driver_osx.png "Double Click on CH34x_Install_V1.4.pkg")

2. Click "Continue"
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_2_install_driver_osx.png "Click Continue")

3. Click "Continue"
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_3_install_driver_osx.png "Click Continue")

4. Click "Install"
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_4_install_driver_osx.png "Click Install")

5. You need to restart your system twice in order to load the drivers and the system extension. For the first reboot click on "Restart".
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_5_install_driver_osx.png "Click Restart")

6. After the reboot connect your board to your PC using a Micro USB cable. It will show up with a warning that OSX didn't allow the extenstion to be loaded. Go to "System Preferences" - "Security & Privacy" and click on "Allow".
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_6_install_driver_osx.png "")

7. Enable the extension from "jiangsu Qunheng Co., Ltd." an click "OK"
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_7_install_driver_osx.png "Allow the extension")

8. Enabling this extension requires your system to reboot again. Click "Restart" to reboot your system for the second time.
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_8_install_driver_osx.png "Allow the extension")

9. After the reboot open your Terminal App and enter the following command in order to verify that your WeMos board has been recognized.
```bash
ls /dev/tty* | grep serial
```
![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_8_install_driver_osx.png "Allow the extension")