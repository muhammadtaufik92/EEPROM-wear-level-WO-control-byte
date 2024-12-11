/*
    Copyright 2016-2016 Peter Rosenberg

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
  This file is part of the EEPROMWearLevel library for Arduino.
*/

#ifndef EEPROM_WEAR_LEVEL_H
#define EEPROM_WEAR_LEVEL_H

#include <EEPROM.h>

class EEPROMWearLevelWOcontrol: EEPROMClass {
  public:
    void begin(MSN_EEPROMwlAddr *address[], uint16_t partition_length);
    uint8_t read(uint16_t var_n, MSN_EEPROMwlAddr *address[], uint8_t val);
    void update(uint16_t var_n, MSN_EEPROMwlAddr *address[], uint8_t val);
    class MSN_EEPROMwlAddr{
      public:
       uint16_t address_toRead;
       uint16_t address_toWrite;
    };
    constructor();
    int x;
  private:
   uint16_t lengthPerVar;
   uint16_t numOfVar;
   void updateHeaderByte(uint16_t var_n, MSN_EEPROMwlAddr *address[]);
   uint16_t getLengthAllocationPerVar(uint16_t partition_length);
};


/**
   the instance of EEPROMWearLevel
*/
extern MSN_EEPROMWearLevel EEPROMwl;
