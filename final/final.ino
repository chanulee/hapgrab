/******************************************************************************
Chanwoo (chanu) Lee
Physical Computing (Prof. Sangwook Lee, 2022 Fall)
Dept. of Art & Technology at Sogang University

Flex Sensor, TFT LCD Display with SPI, 6DoF Sensor with I2C, Bluetooth Classic

References
6DoF LSM6DSO Library
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DSO_Arduino_Library
******************************************************************************/
#include <SparkFunLSM6DSO.h>

#include "BluetoothSerial.h"
#include <Wire.h>

//1123 freefontdemo
#include <TFT_eSPI.h>
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch

//hardware setup
TFT_eSPI tft = TFT_eSPI();

unsigned long drawTime = 0;
int xpos = 20;
int ypos = 10;

int tapState = 0;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

LSM6DSO myIMU;

//IO PINS
const int FLEX_PIN = 34; // Pin connected to voltage divider output
const int TAP_PIN = 32;
// GPIOs 34, 35, 36, 39 can only be used as inputs

// 5V and 47k resistor
const float VCC = 5;
const float R_DIV = 47500.0;

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 16000.0; // resistance when straight
const float BEND_RESISTANCE = 39000.0; // resistance at 90 deg

void setup(){

  //TFT
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  //PINS
  pinMode(FLEX_PIN, INPUT);
  pinMode(TAP_PIN, OUTPUT); //taptic

  Serial.begin(9600);

  //SERIAL (Testing)
  // Serial.println("The device started, now you can pair it with bluetooth!");
  // Serial.setTimeout(200);

  //SerialBT (Demo)
  SerialBT.begin("sunnyAlpha"); //Bluetooth device name
  SerialBT.setTimeout(200);

  //Wire I2C for 6DoF begin
  Wire.begin();
  delay(10);
  if( myIMU.begin() )
    Serial.println("Ready.");
  else { 
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
  }

  if( myIMU.initialize(BASIC_SETTINGS) )
    Serial.println("Loaded Settings.");

}

void loop(){

  //read flex data
  int flexADC = analogRead(FLEX_PIN);
  //calculate angle
  float flexV = flexADC * VCC / 1023.0;
  int flexR = R_DIV * (VCC / flexV);
  int angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 180);  // bend angle
  
  // pipe("Cable for power delivery");

  //haptic feedback when pressed only
  if(angle>90){
    if(tapState==0){
      tap(400);
      tapState=1;
    }
  } else {
    tapState=0;
  }

  //Send to oF
  // Serial.print(myIMU.readFloatAccelX()*10, 2); // 0 -10 10 
  // Serial.print(",");
  // Serial.print(myIMU.readFloatAccelY()*10, 2);
  // Serial.print(",");
  // Serial.print(myIMU.readFloatAccelZ()*10, 2);
  // Serial.print(",");

  // Serial.print(myIMU.readFloatGyroX()*2, 0);
  // Serial.print(",");
  // Serial.print(myIMU.readFloatGyroY()*2, 0);
  // Serial.print(",");
  // Serial.print(myIMU.readFloatGyroZ()*2, 0);
  // Serial.print(",");

  // Serial.print(angle, 0);
  // Serial.println(",");

  //BT to oF

  SerialBT.print(myIMU.readFloatAccelX()*10, 2); // 0 -10 10 
  SerialBT.print(",");
  SerialBT.print(myIMU.readFloatAccelY()*10, 2);
  SerialBT.print(",");
  SerialBT.print(myIMU.readFloatAccelZ()*10, 2);
  SerialBT.print(",");

  SerialBT.print(myIMU.readFloatGyroX()*2, 0);
  SerialBT.print(",");
  SerialBT.print(myIMU.readFloatGyroY()*2, 0);
  SerialBT.print(",");
  SerialBT.print(myIMU.readFloatGyroZ()*2, 0);
  SerialBT.print(",");

  SerialBT.print(angle, 0);
  SerialBT.println(",");

  delay(50);

}


void pipe(const char *string){
    tft.fillScreen(TFT_BLACK); 
    tft.setTextColor(TFT_LIGHTGREY);
    tft.setCursor(xpos, ypos);    // Set cursor near top left corner of screen

    tft.setFreeFont(FSB9);       // Select Free Serif 12 point font
    tft.println();   
    tft.print("NEEDED");

    tft.setTextColor(TFT_YELLOW);
    tft.setFreeFont(FSB18);       // Select Free Serif 12 point font
    tft.println();
    tft.print(string);

    tft.setCursor(xpos, 290-ypos);
    tft.setFreeFont(FSB9);       // Select Free Serif 12 point font
    tft.println();                // Move cursor down a line
    tft.print("Type: PIPE");
}

void disReset() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(xpos, 130);    // Set cursor near top left corner of screen

    tft.setFreeFont(FSB18);       // Select Free Serif 12 point font
    tft.println();                // Move cursor down a line
    tft.print("Hello");
}
  
void tap(int time){
    digitalWrite(TAP_PIN, HIGH);
    delay(time);
    digitalWrite(TAP_PIN, LOW);
}