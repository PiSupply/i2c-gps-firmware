//I2C GPS Firmware
//By Ryan Walmsley
//(C) Nebra LTD. T/A Pi Supply
//V0.1


//Library inclusion
#include <Wire.h>
#include <SoftwareSerial.h> 


void setup() {
 
  // Setup on GPS Bus
  Wire.begin(42);
  Wire.onRequest(returnData);

  // Setup the variables used to store Lat, Long, Altitude, fix and hdop
  float latitude = 0.0;
  float longitude = 0.0;
  float altitude = 0.0;
  boolean fix = false;
  float hdop = 0.0;
  
}

void loop() {
  //Loop and read GPS data
  

}

void returnData() {
  //Respond to the host
}
