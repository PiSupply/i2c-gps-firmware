
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
  float speedMph;
  float speedKmph;
  float gpsTime;
  float gpsDate;
  int fix = 0;
  float gpshdop;
  byte command = 0x42;
  int counter = 0;

void setup() {
 
  // Setup on GPS Bus

  pinMode(LED_BUILTIN, OUTPUT);
  
  
  
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
          digitalWrite(LED_BUILTIN, HIGH);  
          latitude = gps.location.lat();
          longitude = gps.location.lng();
        
  
        }

      if (gps.altitude.isUpdated()) {
        gpsaltitude = gps.altitude.meters();
   
      }
      
      if (gps.hdop.isUpdated()) {
        gpshdop = gps.hdop.hdop();
       
      }

      if (gps.speed.isUpdated()) {
        speedKmph = gps.speed.kmph();
        speedMph = gps.speed.mph();
        
      
      }
      
      if (gps.time.isUpdated()) {
        gpsTime = gps.time.value();
      }
      if (gps.date.isUpdated()) {
        gpsDate = gps.date.value();
        
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
    floatAsBytes.fval = latitude;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
    
    
  }
  else if(command == 0x02) {
    //Longitude
    floatAsBytes.fval = longitude;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  else if(command == 0x03) {
    //Altitude
    floatAsBytes.fval = gpsaltitude;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  else if(command == 0x04) {
    //HDOP
    floatAsBytes.fval = gpshdop;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  
  else if(command == 0x05) {
    //speedKmph
    floatAsBytes.fval = speedKmph;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  
  else if(command == 0x06) {
    //speedMph
    floatAsBytes.fval = speedMph;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  
  else if(command == 0x07) {
    //time
    floatAsBytes.fval = gpsTime;
    Wire.write((byte *)floatAsBytes.bval, 4);
    
  }
  
  else if(command == 0x08) {
    //date
    floatAsBytes.fval = gpsDate;
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




  
