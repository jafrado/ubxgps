/*
 * uBlox via HW Serial (Serial1) for 32u4, debug output via USB (Serial)
 *
  Reading lat and long via UBX binary commands using UART @38400 baud - free from I2C
  By: Nathan Seidle, Adapted from Example3_GetPosition by Thorsten von Eicken
  SparkFun Electronics
  Date: January 28rd, 2019
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to configure the library and U-Blox for serial port use as well as
  switching the module from the default 9600 baud to 38400.

  Note: Long/lat are large numbers because they are * 10^7. To convert lat/long
  to something google maps understands simply divide the numbers by 10,000,000. We 
  do this so that we don't have to use floating point numbers.

  Leave NMEA parsing behind. Now you can simply ask the module for the datums you want!

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  ZED-F9P RTK2: https://www.sparkfun.com/products/15136
  NEO-M8P RTK: https://www.sparkfun.com/products/15005
  SAM-M8Q: https://www.sparkfun.com/products/15106

  Hardware Connections:
  Connect the U-Blox serial TX pin to Uno pin 10
  Connect the U-Blox serial RX pin to Uno pin 11
  Open the serial monitor at 115200 baud to see the output
*/

#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS
SFE_UBLOX_GPS GPS;

long lastTime = 0; //Simple local timer. Limits amount of I2C traffic to Ublox module.

void setup()
{
  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal
  Serial.println("SparkFun Ublox Example");

  //Assume that the U-Blox GPS is running at 9600 baud (the default) or at 38400 baud.
  //Loop until we're in sync and then ensure it's at 38400 baud.
  do {
    Serial.println("GPS: trying 38400 baud");
    Serial1.begin(38400);
    if (GPS.begin(Serial1) == true) break;

    delay(100);
    Serial.println("GPS: trying 9600 baud");
    Serial1.begin(9600);
    if (GPS.begin(Serial1) == true) {
        Serial.println("GPS: connected at 9600 baud, switching to 38400");
        GPS.setSerialRate(38400);
        delay(100);
    } else {
        //GPS.factoryReset();
        delay(2000); //Wait a bit before trying again to limit the Serial output
    }
  } while(1);
  Serial.println("GPS serial connected");

  GPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  GPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  GPS.saveConfiguration(); //Save the current settings to flash and BBR
  delay(2000);

  //GPS.setNavigationFrequency(10); //Set output to 10 times a second
  GPS.setNavigationFrequency(1); //Set output to 1x a second
  byte rate = GPS.getNavigationFrequency(); //Get the update rate of this module
  Serial.print("Current update rate:");
  Serial.println(rate);


  //This will pipe all NMEA sentences to the serial port so we can see them
  //GPS.setNMEAOutputPort(Serial);
  //GPS.enableDebugging(Serial);
  
}

void loop()
{
  //Query module only every second. Doing it more often will just cause I2C traffic.
  //The module only responds when a new position is available
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer

    long latitude = GPS.getLatitude();
    Serial.print(F("Lat: "));
    Serial.print(latitude);

    long longitude = GPS.getLongitude();
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees * 10^-7)"));

    long altitude = GPS.getAltitude();
    Serial.print(F(" Alt: "));
    Serial.print(altitude);
    Serial.print(F(" (mm)"));

    byte SIV = GPS.getSIV();
    Serial.print(F(" SIV: "));
    Serial.print(SIV);

    byte fixType = GPS.getFixType();
    Serial.print(F(" Fix: "));
    if(fixType == 0) Serial.print(F("No fix"));
    else if(fixType == 1) Serial.print(F("Dead reckoning"));
    else if(fixType == 2) Serial.print(F("2D"));
    else if(fixType == 3) Serial.print(F("3D"));
    else if(fixType == 4) Serial.print(F("GNSS+Dead reckoning"));

    byte RTK = GPS.getCarrierSolutionType();
    Serial.print(" RTK: ");
    Serial.print(RTK);
    if (RTK == 1) Serial.print(F("High precision float fix!"));
    if (RTK == 2) Serial.print(F("High precision fix!"));


    long speed = GPS.getGroundSpeed();
    Serial.print(F(" Speed: "));
    Serial.print(speed);
    Serial.print(F(" (mm/s)"));

    long heading = GPS.getHeading();
    Serial.print(F(" Heading: "));
    Serial.print(heading);
    Serial.print(F(" (degrees * 10^-5)"));

    int pDOP = GPS.getPDOP();
    Serial.print(F(" pDOP: "));
    Serial.print(pDOP / 100.0, 2);


    Serial.println();
  }
}
