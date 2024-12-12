#ifndef EEPROM_WEAR_LEVEL_H
#define EEPROM_WEAR_LEVEL_H

#include <EEPROM.h>

class MSN_EEPROMWearLevel{
  public:
  MSN_EEPROMWearLevel();
    class MSN_EEPROMwlAddr{
      public:
       uint16_t address_toRead;
       uint16_t address_toWrite;
    };
    void begin(MSN_EEPROMwlAddr* address[], uint16_t partition_length);
    uint8_t read(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint8_t val);
    void update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint8_t val);
  private:
   uint16_t lengthPerVar;
   uint16_t numOfVar;
   void updateHeaderByte(uint16_t var_n, MSN_EEPROMwlAddr* address[]);
   uint16_t getLengthAllocationPerVar(uint16_t partition_length);
};


/**
   the instance of EEPROMWearLevel
*/
extern MSN_EEPROMWearLevel EEPROMwl;
#endif
