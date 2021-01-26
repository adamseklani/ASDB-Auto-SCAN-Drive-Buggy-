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
