
//I2C GPS Firmware
//By Ryan Walmsley
//(C) Nebra LTD. T/A Pi Supply
//V0.1


//Library inclusion
#include <Wire.h>
#include <SoftwareSerial.h> 
#include <TinyGPS++.h>


byte command = "";

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
  Wire.begin(66);
  Wire.onRequest(returnData);
  Wire.onReceive(getCommand);

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
        counter = 0;
      }
    
    }
    counter = counter+1;

    
  
}

void returnData() {
  //Respond to the host
  
  if(command == 0x00) {
      //Fix Status
      
      
    }
  
  else if(command == 0x01) {
    //Latitude
    
    
  }
  else if(command == 0x02) {
    //Longitude
    
  }
  else if(command == 0x03) {
    //Altitude
    
  }
  else if(command == 0x04) {
    //HDOP
    
  }
  else {
    //Bad Command
    Serial.println("Bad Command");
    
  }
}

void getCommand() {
  //Respond to the host
  if(Wire.available()) {
    command = Wire.read();
    Serial.println(command);
  }
}
  
