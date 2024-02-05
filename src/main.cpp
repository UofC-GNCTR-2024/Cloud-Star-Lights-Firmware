#include <Arduino.h>
#include <Wire.h>

#if 1

// CLOUD STUFF //

struct cloudGroup {
  // Values
  int redVal;
  int blueVal;
  int greenVal;

  int redLedChannel;
  int greenLedChannel;
  int blueLedChannel;
} cloudGroup1, cloudGroup2, cloudGroup3, cloudGroup4, cloudGroup5;

// Pins for controlling the clouds
const int cloudRed1   = 2;
const int cloudRed2   = 4;
const int cloudRed3   = 17;
const int cloudRed4   = 12;
const int cloudRed5   = 13;
const int cloudGreen1 = 14;
const int cloudGreen2 = 15;
const int cloudGreen3 = 23;
const int cloudGreen4 = 25;
const int cloudGreen5 = 26;
const int cloudBlue1  = 27;
const int cloudBlue2  = 32;
const int cloudBlue3  = 33;
const int cloudBlue4  = 18;
const int cloudBlue5  = 19;

// setting PWM properties
int delayTime = 20;
const int freq = 1000;
const int resolution = 8;

// Set up LED PWM Channels
const int ledChannel1  = 1;
const int ledChannel2  = 2;
const int ledChannel3  = 3;
const int ledChannel4  = 4;
const int ledChannel5  = 5;
const int ledChannel6  = 6;
const int ledChannel7  = 7;
const int ledChannel8  = 8;
const int ledChannel9  = 9;
const int ledChannel10 = 10;
const int ledChannel11 = 11;
const int ledChannel12 = 12;
const int ledChannel13 = 13;
const int ledChannel14 = 14;
const int ledChannel15 = 15;


// STAR STUFF //

 
void setup(){
  Serial.begin(115200);


  // CLOUD STUFF //

  // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
  ledcSetup(ledChannel5, freq, resolution);
  ledcSetup(ledChannel6, freq, resolution);
  ledcSetup(ledChannel7, freq, resolution);
  ledcSetup(ledChannel8, freq, resolution);
  ledcSetup(ledChannel9, freq, resolution);
  ledcSetup(ledChannel10, freq, resolution);
  ledcSetup(ledChannel11, freq, resolution);
  ledcSetup(ledChannel12, freq, resolution);
  ledcSetup(ledChannel13, freq, resolution);
  ledcSetup(ledChannel14, freq, resolution);
  ledcSetup(ledChannel15, freq, resolution);

  // Group one
  cloudGroup1.redVal = 0;
  cloudGroup1.greenVal = 0;
  cloudGroup1.blueVal = 0;
  cloudGroup1.redLedChannel = ledChannel1;
  cloudGroup1.greenLedChannel = ledChannel2;
  cloudGroup1.blueLedChannel = ledChannel3;
  ledcAttachPin(cloudRed1, cloudGroup1.redLedChannel);
  ledcAttachPin(cloudGreen1, cloudGroup1.greenLedChannel);
  ledcAttachPin(cloudBlue1, cloudGroup1.blueLedChannel);

  // Group two
  cloudGroup2.redVal = 0;
  cloudGroup2.greenVal = 0;
  cloudGroup2.blueVal = 0;
  cloudGroup2.redLedChannel = ledChannel4;
  cloudGroup2.greenLedChannel = ledChannel5;
  cloudGroup2.blueLedChannel = ledChannel6;
  ledcAttachPin(cloudRed2, cloudGroup2.redLedChannel);
  ledcAttachPin(cloudGreen2, cloudGroup2.greenLedChannel);
  ledcAttachPin(cloudBlue2, cloudGroup2.blueLedChannel);

  // Group three
  cloudGroup3.redVal = 0;
  cloudGroup3.greenVal = 0;
  cloudGroup3.blueVal = 0;
  cloudGroup3.redLedChannel = ledChannel7;
  cloudGroup3.greenLedChannel = ledChannel8;
  cloudGroup3.blueLedChannel = ledChannel9;
  ledcAttachPin(cloudRed3, cloudGroup3.redLedChannel);
  ledcAttachPin(cloudGreen3, cloudGroup3.greenLedChannel);
  ledcAttachPin(cloudBlue3, cloudGroup3.blueLedChannel);

  // Group four
  cloudGroup4.redVal = 0;
  cloudGroup4.greenVal = 0;
  cloudGroup4.blueVal = 0;
  cloudGroup4.redLedChannel = ledChannel10;
  cloudGroup4.greenLedChannel = ledChannel11;
  cloudGroup4.blueLedChannel = ledChannel12;
  ledcAttachPin(cloudRed4, cloudGroup4.redLedChannel);
  ledcAttachPin(cloudGreen4, cloudGroup4.greenLedChannel);
  ledcAttachPin(cloudBlue4, cloudGroup4.blueLedChannel);

  // Group five
  cloudGroup5.redVal = 0;
  cloudGroup5.greenVal = 0;
  cloudGroup5.blueVal = 0;
  cloudGroup5.redLedChannel = ledChannel13;
  cloudGroup5.greenLedChannel = ledChannel14;
  cloudGroup5.blueLedChannel = ledChannel15;
  ledcAttachPin(cloudRed1, cloudGroup5.redLedChannel);
  ledcAttachPin(cloudGreen1, cloudGroup5.greenLedChannel);
  ledcAttachPin(cloudBlue1, cloudGroup5.blueLedChannel);
}

void changeColor(cloudGroup *cloudGroupN, bool increment, int redVal, int greenVal, int blueVal){
  
  if (increment==true){
    cloudGroupN->redVal = (cloudGroupN->redVal + redVal) % 256;
    cloudGroupN->greenVal = (cloudGroupN->greenVal + greenVal) % 256;
    cloudGroupN->blueVal = (cloudGroupN->blueVal + blueVal) % 256;
  } else {
    cloudGroupN->redVal = redVal;
    cloudGroupN->greenVal = greenVal;
    cloudGroupN->blueVal = blueVal;
  }
  
  ledcWrite(cloudGroupN->redLedChannel, redVal);
  ledcWrite(cloudGroupN->greenLedChannel, greenVal);
  ledcWrite(cloudGroupN->blueLedChannel, blueVal);
}


void loop() {

  // CLOUD STUFF //

  for( int i = 0 ; i < 255 ; i += 1 ){
    changeColor(&cloudGroup1, true, -1, 1, 0);
    changeColor(&cloudGroup2, true, 0, -1, 1);
    changeColor(&cloudGroup3, true, 1, 0, -1);
    changeColor(&cloudGroup4, true, 1, 1, 0);
    changeColor(&cloudGroup5, true, 0, -1, -1);
    delay(delayTime);
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