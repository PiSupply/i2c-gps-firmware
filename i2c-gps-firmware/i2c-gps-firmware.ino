//I2C GPS Firmware
//By Ryan Walmsley
//(C) Nebra LTD. T/A Pi Supply
//V0.1


//Library inclusion
#include <Wire.h>
#include <SoftwareSerial.h> 
#include <TinyGPS++.h>

//GPS Serial
SoftwareSerial gpsSerial(10,11);

//GPS Library
TinyGPSPlus gps;


  // Setup the variables used to store Lat, Long, Altitude, fix and hdop
 float latitude;
  float longitude;
  float gpsaltitude;
  int fix = 0;
  float gpshdop;
int counter = 0;

void setup() {
 
  // Setup on GPS Bus
  Wire.begin(42);
  Wire.onRequest(returnData);

  //Setup the Serial Ports
  gpsSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Starting Up"); 

 

  Serial.println("All Setup"); 
  
}

void loop() {
  //Loop and read GPS data
    while (gpsSerial.available() > 0){
      gps.encode(gpsSerial.read());
      
      if (gps.location.isValid())
        {
          latitude = gps.location.lat();
          longitude = gps.location.lng();
            //returnData();
  
        }

      if (gps.altitude.isUpdated()) {
        gpsaltitude = gps.altitude.meters();
        //Serial.print(gps.altitude.meters());
        //returnData();
      }
      if (gps.hdop.isUpdated()) {
        gpshdop = gps.hdop.hdop();
        //Serial.print(gps.altitude.meters());
        //returnData();
      }
      if (counter>5000) {
        returnData();
        counter = 0;
      }
    
    }
    counter = counter+1;

    
  
}

void returnData() {
  //Respond to the host
  Serial.print(latitude,6); 
  Serial.print(","); 
  Serial.print(longitude,6); 
  Serial.print(","); 
  Serial.print(gpsaltitude); 
  Serial.print(","); 
  Serial.println(gpshdop); 
}
