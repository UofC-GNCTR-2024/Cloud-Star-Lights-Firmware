#include <Arduino.h>
#include <Wire.h>

#if 1

const int ledPin0 = 17;
const int ledPin1 = 23;
const int ledPin2 = 33;

int redVal;
int blueVal;
int greenVal;
int delayTime = 20;

// setting PWM properties
const int freq = 1000;
const int ledChannel0 = 0;
const int ledChannel1 = 1;
const int ledChannel2 = 2;
const int resolution = 8;
 
void setup(){
  Serial.begin(115200);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel0, freq, resolution);
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin0, ledChannel0);
  ledcAttachPin(ledPin1, ledChannel1);
  ledcAttachPin(ledPin2, ledChannel2);
}

void changeColor(int redVal, int greenVal, int blueVal){
  ledcWrite(ledChannel0, 255 - greenVal);
  ledcWrite(ledChannel1, 255 - redVal);
  ledcWrite(ledChannel2, 255 - blueVal);

  Serial.print("Color: 0x");
  Serial.println(String(blueVal << 16 + greenVal << 8 + redVal, HEX));

  delay(delayTime);
}


void loop() {

  int redVal = 255;
  int blueVal = 0;
  int greenVal = 0;
  for( int i = 0 ; i < 255 ; i += 1 ){
    greenVal += 1;
    redVal -= 1;
    changeColor(redVal, greenVal, blueVal);
  }

  redVal = 0;
  blueVal = 0;
  greenVal = 255;
  for( int i = 0 ; i < 255 ; i += 1 ){
    blueVal += 1;
    greenVal -= 1;
    changeColor(redVal, greenVal, blueVal);
  }

  redVal = 0;
  blueVal = 255;
  greenVal = 0;
  for( int i = 0 ; i < 255 ; i += 1 ){
    redVal += 1;
    blueVal -= 1;
    changeColor(redVal, greenVal, blueVal);
  }
}

#else

// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// --------------------------------------

#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  WIRE.begin();

  Serial.begin(115200);
  while (!Serial)
     delay(10);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}

#endif