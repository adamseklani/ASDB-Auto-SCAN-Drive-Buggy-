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

CODE
----------------
//Included Libararies
#include"led.h"
#include"buzzer.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <IRremote.h>

// CLASSES & OBJECTS  
LED_control  LED;
BUZ_control BUZ;
// controlling the SERVO by creating an object servo
Servo servo;  
//SETUP THE LED'S
const int yel_led=47;
const int gr_led=48;
const int red_led=49;
//SET THE IR TO PIN7 - IR SETUP
const int Rec_Pin = 7;
char *irmsg[] = {"FF38C7"};
//IR SETUP
IRrecv irrx(Rec_Pin);
decode_results results;
//SET THE BUZZER TO PIN8
int buzzer = 8;

//Ultrasonic setup
#define echoPin 4 // SET THE HC-SR04 ECHO TO PIN4
#define trigPin 5 // SET THE HC-SR04 TRIG TO PIN5

// VARIABLES FOR THE ULTRASONIC CALCULATION
long period; // VARIABLE FOR THE TIME PERIOD DURATION
int dist; // VARIABLE FOR THE DISTANCE 

void setup() {
  //put your setup code here, to run once:
  pinMode(yel_led, OUTPUT);
  pinMode(gr_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  //Buzzer
  pinMode(buzzer, OUTPUT);
  //ULTRASONIC
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  //LCD Setup
  Serial.begin(9600);// open the serial port
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  //
  Wire.begin();        // join i2c bus (address optional for master)
  servo.attach(10);  // attaches the servo on pin 10 to the servo object
  
  //Welcome Note
 Serial.print("ASDB (Auto SCAN Drive Buggy) Ready\n");
 Serial.print("Valid Command list : fscan rscan nstop estop");
}
void loop() {
 // RESET TRIG PIN CONDITION
  digitalWrite(trigPin, LOW);
  //ULTRASONIC
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  period = pulseIn(echoPin, HIGH);
  // DISTANCE CALCULATION
  dist = period * 0.033 / 2; // WE DVIDE THE RESULT BY TWO AS WE HAVE THE TRANSMITTED AND REFLECTED WAVE
  String msgs;
  //IF SERIAL IS AVAILABLE READ AND PRINT THE TYPED IN DATA
  if (Serial.available()>0){
  msgs=Serial.readString();
  Serial.print("You typed \n");
  Serial.print(msgs);
  //Serial.print("Valid Command list : fscan rscan nstop estop\n");
  }
  //OBSTACLE DETECTION (SAFETY)
   if (dist < 20){
  //Engage the brakes
  digitalWrite(9, HIGH);
  //Enable Sounder (SAFETY)
  BUZ.sound(8,30,10);
    
  Serial.print("Obstruction Detected at\n\r");
   // SERIAL PRINT THE DISTANCE
  Serial.print("APPROX DISTANCE (cm): ");
  Serial.print(dist);
  Serial.print("\n");
  Serial.print("5");//ESP32 SETUP to print a specific LCD message when it recieves 5
  //RED LED ACTIVATED
  LED.FLASH(red_led,100,10);
  delay(100); 
}
//IR FENCE
if (irrx.decode(&results)){
      int value = results.value;           
    irrx.resume(); // 
 if (value == 14535){
      //Engage the brakes
  digitalWrite(9, HIGH);
  //Enable Sounder (SAFETY)
  BUZ.sound(8,30,10);
  Serial.print("\n");
  Serial.print("5");//ESP32 SETUP to print a specific LCD message when it recieves 5
  //RED LED ACTIVATED
  LED.FLASH(red_led,100,10);
  }
}
//FORWARD SCAN
 if (msgs.substring(0,5) == "fscan"){
  //Move servo (Ultrasonice)to forward position
  servo.write(0);
  //Enable Sounder (Safety)
  BUZ.sound(8,100,10);
  //Green Light On
  LED.FLASH(gr_led,100,10);
  //Print Message 
  Serial.print("System is ready to scan \n\r");
  Serial.print("1");//ESP32 SETUP to print a specific LCD message when it recieves 1

 //move motors forward at low speed
 digitalWrite(12, HIGH); //Forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage Brake for Channel A
  analogWrite(3, 122);   //SPIN THE MOTOR AT HALF SPEED
 }

//rscan
 if (msgs.substring(0,5) == "rscan"){
// move servo to forward position
   servo.write(180);              
  //Enable Sounder (Safety)
    BUZ.sound(8,100,10);
  //FLASH Green LED
   LED.ON(gr_led);
  //delay(1000);
  //LED.OFF(gr_led);
  //delay(1000);
  LED.FLASH(gr_led,100,10);
  //Print Message 
  Serial.print("System is ready to scan in reverse\n\r");
  Serial.print("1");
 
  //Move motors
 //Motor A Reverse @ half speed
  digitalWrite(12, LOW);  //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed 
  delay(10000);
 }
//nstop
  if (msgs.substring(0,5) == "nstop"){
  //Engage the brakes
  digitalWrite(9, HIGH);  
  //Flash Yellow LED
  LED.FLASH(yel_led,100,10);
  //Print Serial
  Serial.print("Vehicle Stopped \n\r");
  Serial.print("3");
  }
//ESTOP
  if (msgs.substring(0,5) == "estop"){
  //Engage the brakes
  digitalWrite(9, HIGH);  
  //Enable Sounder
   BUZ.sound(8,100,10);
  //Flash RedLED
  LED.FLASH(red_led,100,10);
  //Print Serial
  Serial.print("Emergency Stop \n\r");
  Serial.print("4");
  }
  }
ESP CODE
----------------
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define RXD2 16
#define TXD2 17
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  //LCD init
 lcd.init();
 //turn on LCD backlight                      
 lcd.backlight();
}

void loop() { //Choose Serial1 or Serial2 as required
  while (Serial2.available()) {
    //Serial.print(char(Serial2.read()));
    char test;
    test = Serial2.read();
    Serial.print(test);
    //fscan
    if (test = 1){
      // Set the cursor to (0,0) Column Line
  lcd.setCursor(0, 0);
  // print message
  lcd.print("SCANNING!");
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // Set the cursor to (0,1) Column Line
  lcd.setCursor(0,1);
  lcd.print("In Progress");
  delay(1000);
  lcd.clear(); 
    }
    //rscan
  if (test = 2){
        // Set the cursor to (0,0) Column Line
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Object Detected!");
  delay(1000);
  // clears the display to print new message
  //lcd.clear();
  // Set the cursor to (0,1) Column Line
  lcd.setCursor(0,1);
  lcd.print("Clear Scan Area");
  delay(1000);
  lcd.clear(); 
    }
//stop
  if (test = 3){
          // Set the cursor to (0,0) Column Line
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Normal Stop");
  delay(1000);
  // clears the display to print new message
  //lcd.clear();
 // Set the cursor to (0,1) Column Line
  lcd.setCursor(0,1);
  lcd.print("Clear Scan Area");
  delay(1000);
  lcd.clear(); 
    }
    //estop
  if (test = 4){
          // Set the cursor to (0,0) Column Line
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Emergency Stop!");
  delay(1000);
  // clears the display to print new message
  //lcd.clear();
  // Set the cursor to (0,1) Column Line
  lcd.setCursor(0,1);
  lcd.print("Clear Scan Area");
  delay(1000);
  lcd.clear(); 
    }
    //Ultrasonic
    if (test = 5){
          // Set the cursor to (0,0) Column Line
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Object Detected!");
  delay(1000);
  // clears the display to print new message
  //lcd.clear();
  // Set the cursor to (0,1) Column Line
  lcd.setCursor(0,1);
  lcd.print("Clear Scan Area");
  delay(1000);
  lcd.clear(); 
    }
    }
  }

Classes
----------------

1-Buzzer.h
class BUZ_control{
  public:

  void Begin(byte GPIO_pin){
    pinMode(GPIO_pin, OUTPUT);
  }

  void ON(byte GPIO_pin){
    for (int a = 0; a < 80; a++){
    //digitalWrite(GPIO_pin, HIGH);
    delay(1);
    //digitalWrite(GPIO_pin, LOW);
    delay(1);}
    delay(50);
    for (int b = 0; b < 100; b++) { 
    digitalWrite(GPIO_pin, HIGH);
    delay(2);
    digitalWrite(GPIO_pin, LOW);
    delay(2);}
    }
    void OFF(byte GPIO_pin){
   digitalWrite(GPIO_pin, LOW);
    }
    void sound(byte GPIO_pin, int flash_speed, int flashes){
      for (int i=0; i<flashes; i=i+1){
        ON(GPIO_pin);
        delay(flash_speed);
        OFF(GPIO_pin);
        delay(flash_speed);
      }
    }
};

2-led.h
class LED_control{
  public:

  void Begin(byte GPIO_pin){
    pinMode(GPIO_pin, OUTPUT);
  }

  void ON(byte GPIO_pin){
    digitalWrite(GPIO_pin, HIGH);
  }
    void OFF(byte GPIO_pin){
    digitalWrite(GPIO_pin, LOW);
    }
    void FLASH(byte GPIO_pin, int FLASHSPD, int FLASHES){
      for (int i=0; i<FLASHES; i=i+1){
        ON(GPIO_pin);
        delay(FLASHSPD);
        OFF(GPIO_pin);
        delay(FLASHSPD);
      }
    }
};

