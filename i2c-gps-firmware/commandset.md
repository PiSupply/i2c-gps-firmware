#Command Set

Here's a list of all of the I2C Commands

### Get Fix Status 0x00
This command requests to check if the Module has a valid fix. This is recommended to be used to check if there's a fix before continuing on.

**Response**
01 = fix
00 = No Fix

### Get Latitude 0x01
This command requests the current Latitude.

**Response**
33194EC = 51.103660

### Get Longitude 0x02
This command requests the current Longitude.

**Response**
0049462 = 0.300130

### Get Altitude 0x03
This command requests the current Altitude (In Meters)

**Response**

### Get HDOP 0x04
This command requests the current HDOP value, this is the accuracy of the latitude & longitude.

**Response**

### Get Speed in KMPH 0x05
This command requests the current speed that the GPS is moving and returns the value in KMPH.

**Response**

### Get Speed in MPH 0x06
This command requests the current speed that the GPS is moving and returns the value in the MPH.

**Response**

### Get Time 0x07

This command get's the current time from the GPS module and returns it in (GMT/BST?) in Hours, Minutes, Seconds,

**Response**

### Get Date 0x08
This command gets the current date in D M Y form.

**Response**
