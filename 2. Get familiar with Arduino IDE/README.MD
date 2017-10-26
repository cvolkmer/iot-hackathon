# Load your first Sketch
Arduino IDE ships with many example projects in order to help you to get started.

1. Click on "File" - "Examples" - "01.Basics" and select the "Blink" Sketch. This will open a simple code which, once deployed, will blink the onboard LED on your WeMos board.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_1_arduino_ide_first_sketch.png)

Have a look at the code to understand how it is structured.

2. Click on "Verify" in order to syntax-check and compile your code.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_2_arduino_ide_first_sketch.png)

3. Once checking your code is successfully compiled, click on "Upload"

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_3_arduino_ide_first_sketch.png)

4. Once the Sketch is loaded, the LED on your WeMos board should blink!

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_4_arduino_ide_first_sketch.png" width="50%">

Try to change the values in the delay funtion and see what happens.

# Debugging your code

The Arduino IDE has a feature that can be a great help in debugging sketches or controlling Arduino from your computer's keyboard.

The Serial Monitor is a separate pop-up window that acts as a separate terminal that communicates by receiving and sending Serial Data. The serial monitor is available in the Arduino IDE under the tools menu. Set the baud rate in the serial console according your code!

1. You must have an Arduino connected by USB to your computer to be able to activate the Serial Monitor
2. You need to begin Serial Communications and set the Baud Rate (speed) that data will be transferred at in the setup function of your sketch.
```
Serial.begin(9600); // Other baud rates can be used... For ESP8266 115200 is working fine.
```
3. In your code use the following command to print out stuff
```
Serial.println("Output of my variable: ");
Serial.println(MYVAR);
```

Here an example to do some testing with the serial monitor:
```
int x = 0;

void  setup()
{
  Serial.begin(115200);
  Serial.println("Hello world");
  delay(2000);// Give reader a chance to see the output.
}


void loop()
{
  Serial.println(x);
  delay(500);
  x=x+1;
}
```

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_5_arduino_ide_serial_monitor.png">

# Arduino Language Reference

The Arduino programming language is merely a set of C/C++ functions that can be called from your code. The Arduino environment can be extended through the use of libraries, just like most programming platforms. Libraries provide extra functionality for use in sketches, e.g. working with hardware or manipulating data. To use a library in a sketch, select it from Sketch > Import Library. 

The language reference can be found <a href="https://www.arduino.cc/en/Reference/HomePage">here</a> or by clicking Help-Reference in the Arduino IDE.
