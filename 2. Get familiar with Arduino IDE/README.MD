# Load your first Sketch
Arduino IDE ships with many example projects in order to help you to get started.

1. Click on "File" - "Examples" - "01.Basics" and select the "Blink" Sketch. This will open a simple code which, once deployed, will blink the onboard LED on your WeMos board.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_1_arduino_ide_first_sketch.png)

Have a look at the code to understand how it is structured.

2. Click on "Verify" in order to check your code.

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_2_arduino_ide_first_sketch.png)

3. Once checking your code is finished, click on "Upload"

![alt text](https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_3_arduino_ide_first_sketch.png)

4. Once the Sketch is loaded, the LED on your WeMos board should blink!

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/2_4_arduino_ide_first_sketch.png" width="50%">

Try to change the values in the delay funtion and see what happens.

# Debugging your code

The Arduino IDE has a feature that can be a great help in debugging sketches or controlling Arduino from your computer's keyboard.

The Serial Monitor is a separate pop-up window that acts as a separate terminal that communicates by receiving and sending Serial Data.

1. You must have an Arduino connected by USB to your computer to be able to activate the Serial Monitor
2. In Setup you need to begin Serial Communications and set the Baud Rate (speed) that data will be transferred at.
```
Serial.begin(9600); // Other baud rates can be used...
```
3. In your code use the following command to print out stuff
```
Serial.println("My Sketch has started");
```
