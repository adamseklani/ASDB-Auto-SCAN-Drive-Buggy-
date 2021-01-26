# SOFT546
## Introduction
Welcome to ASDB (AutoScanDriveBuggy) 
Code takes into account:
•	Safety Pre-warning Lights and Sounders 
•	Auto obstacle detection feature 
•	Emergency Stop (Wired + Wireless)
•	Scan Direction

Project setup
----------------
Project Setup 
Steps needed to run the project 
Materials/Tools used for this project:
•	Arduihno Mega 
•	Arduino Motor Shield
•	LED Sensors
•	Buzzer
•	Ultrasonic (HC-SR04)
•	DC Motors
•	Servo motors
•	Infra-Red Sensor
•	LCD Display
•	Computer (IDE)
•	ESP32

Starting the Buggy
----------------
Connect the Buggy to the IDE Via the correct communication ports and power the motor shield.
Next upload the program and monitior the serial (CTRL + M) and the welcome screen will appear with the command list.
Valid Command list : fscan rscan stop estop

ARDUINO TO ESP COMMUNICATION
----------------
We will use the serial port U2UXD to establish communcation between the ESP and arduihno via the RX and TX pins.

Code
----------------
Folder attached are :
2 way distributed system code
3 way distributed system code
