
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
  byte command = "";
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
     
    
    }

    
  
}

void returnData() {
    union {
    float fval;
    byte bval[4];
} floatAsBytes;


  //Respond to the host
  
  //if(command == 0x00) {
      //Fix Status
      //Serial.println("fix");
      
      
  //  }
  
  if(command == 0x01) {
    //Latitude
    //Serial.println("latitude");
    floatAsBytes.fval = latitude;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
    
    
  }
  else if(command == 0x02) {
    //Longitude
    //Serial.println("longitude");
    floatAsBytes.fval = longitude;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  else if(command == 0x03) {
    //Altitude
    //Serial.println("alt");
    floatAsBytes.fval = gpsaltitude;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  else if(command == 0x04) {
    //HDOP
    //Serial.println("hdop");
    floatAsBytes.fval = gpshdop;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  else {
    //Bad Command
    Serial.println("Bad Command");
    
  }
}

void getCommand(int bytesReceived) {
    
  command = Wire.read();
  Serial.println(command);
  Wire.read();  
}




  
