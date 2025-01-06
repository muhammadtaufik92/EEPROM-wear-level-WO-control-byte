#ifndef EEPROM_WEAR_LEVEL_H
#define EEPROM_WEAR_LEVEL_H

#include <EEPROM.h>

#define WORD  3//sizeof(word)  +1
#define BYTE  2//sizeof(byte)  +1
#define DWORD 4//sizeof(dword) +1

class MSN_EEPROMWearLevel{
  public:
  MSN_EEPROMWearLevel();
    class MSN_EEPROMwlAddr{
      public:
       uint16_t size = BYTE;
       uint16_t address_base;
       uint16_t address_toRead;
       uint16_t address_toWrite;
    };
    void begin(MSN_EEPROMwlAddr* address[], uint16_t partition_length);
    uint32_t read(uint16_t var_n, MSN_EEPROMwlAddr* address[]);
    void update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint8_t val);
    void update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint16_t val);
    void update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint32_t val);
  private:
   uint16_t lengthPerVar;
   uint16_t numOfVar;
   uint16_t slot;
   uint16_t size_total;
   void updateHeaderByte(uint16_t var_n, MSN_EEPROMwlAddr* address[]);
   uint16_t getLengthAllocationPerVar(uint16_t partition_length);
};


/**
   the instance of EEPROMWearLevel
*/
extern MSN_EEPROMWearLevel EEPROMwl;
#endif
