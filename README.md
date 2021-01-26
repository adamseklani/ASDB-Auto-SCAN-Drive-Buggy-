# SOFT546
## Introduction
Welcome to ASDB (AutoScanDriveBuggy) 
Code takes into account:
•	Safety Pre-warning Lights and Sounders 
•	Auto obstacle detection feature 
•	Emergency Stop (Wired + Wireless)
•	Scan Direction
## Setup 
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
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Starting the Buggy
 * Arduino to ESP32 Communication
 * Code
 * ESP CODE
 * Classes

Introduction
----------------
ASDB (AutoScanDriveBuggy), Project aim is tocontrol a vehicle autonomously, the system should be designed to take into account:
•	Safety Pre-warning Lights and Sounders 
•	Auto obstacle detection feature 
•	Emergency Stop (Wired + Wireless)
•	Scan Direction

Starting the Buggy
----------------
Connect the Buggy to the IDE Via the correct communication ports and power the motor shield.
Next upload the program and monitior the serial (CTRL + M) and the welcome screen will appear with the command list.
Valid Command list : fscan rscan stop estop

ARDUINO TO ESP COMMUNICATION
----------------
We will use the serial port U2UXD to establish communcation between the ESP and arduihno via the RX and TX pins.
