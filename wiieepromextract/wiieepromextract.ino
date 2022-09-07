/*
  Read and write settings and calibration data to an external I2C EEPROM
  By: Nathan Seidle
  SparkFun Electronics
  Date: December 11th, 2019
  License: This code is public domain but you buy me a beer if you use this 
  and we meet someday (Beerware license).
  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14764
  This example demonstrates how to read and write various variables to memory.
  The I2C EEPROM should have all its ADR pins set to GND (0). This is default
  on the Qwiic board.
  Hardware Connections:
  Plug the SparkFun Qwiic EEPROM to an Uno, Artemis, or other Qwiic equipped board
  Load this sketch
  Open output window at 115200bps
*/

#include <Wire.h>

#include "SparkFun_External_EEPROM.h"
ExternalEEPROM myMem;

void setup() {
  Serial.begin(115200);
  //Serial.println("Qwiic EEPROM example - for wii???");

  Wire.begin();

  if (myMem.begin() == false) {
    Serial.println("No memory detected. Freezing.");
    Serial.println("Take a crap");
    while (1)
      ;
  }
  //Serial.println("Memory detected!");

  myMem.setMemorySize(16384);

  //Serial.print("Mem size in bytes: ");
  //Serial.println(myMem.length());

  delay(5000);

  runJoj(0, 16384);

  
}

void runJoj(uint32_t eepLoc, uint32_t amount) {
  
  uint8_t *onEEPROM = (uint8_t *)malloc(myMem.getPageSize()); //Create a buffer to hold a page

  int j = eepLoc;
  uint32_t EEPROMLocation = j;
  
  while(j < amount) {
    EEPROMLocation = j;

    uint8_t bytesToRead = myMem.getPageSize();

    if (EEPROMLocation + bytesToRead > myMem.getMemorySize())
      bytesToRead = myMem.getMemorySize() - EEPROMLocation;
  
    //if (bytesToRead > binFile.available())
    //  bytesToRead = binFile.available();
  
    
    
    myMem.read(EEPROMLocation, onEEPROM, myMem.getPageSize()); //Location, data
  
    for (int x = 0; x < bytesToRead; x++) {
      //Serial.print(F("Verify failed at location 0x"));
      //Serial.print(EEPROMLocation + x, HEX);
      //Serial.print(F(". Read 0x"));
      //Serial.print(onEEPROM[x], HEX);
      //Serial.println(F("."));
      Serial.write(onEEPROM[x]);
    }

    j = j + 64;
  }
}

void loop() {
}
