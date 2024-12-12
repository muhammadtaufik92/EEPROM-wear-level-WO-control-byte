
//uint16_t lengthOfPartition;

/*struct eepromwladdr{
    uint16_t address_toRead;
    uint16_t address_toWrite;
} typedef struct eepromwladdr MSN_EEPROMwlAddr;
*/
#include "EEPROMWearLevelWOcontrol.h"
MSN_EEPROMWearLevel EEPROMwl;

MSN_EEPROMWearLevel::MSN_EEPROMWearLevel(){
    numOfVar=0;
    lengthPerVar=0;
}

void MSN_EEPROMWearLevel::begin(MSN_EEPROMwlAddr* address[], uint16_t partition_length){
    numOfVar=(uint16_t)(sizeof(address)/sizeof(address[0]));
    lengthPerVar=getLengthAllocationPerVar(partition_length);
    for(uint8_t var_n=0;var_n<numOfVar;var_n++){
      uint16_t base_address=lengthPerVar*var_n;
		for(int offset=0; offset<lengthPerVar; offset+=2){
			if(!EEPROM.read(offset+base_address)){}
			else{
        address[var_n]->address_toRead=EEPROM.read(offset-1+base_address);
        offset=lengthPerVar;
      }
    }
    bool isFull=true;
    for(int offset=0; offset<lengthPerVar; offset+=2){
		  if(!EEPROM.read(offset+base_address)){}
		  else{
        address[var_n]->address_toWrite=EEPROM.read(offset+1+base_address);
        offset=lengthPerVar;
        isFull=false;
      }
    }
    if(isFull){
        address[var_n]->address_toWrite=base_address+1;
        EEPROM.write(base_address,0b11111111);
    }
  }
}

uint16_t MSN_EEPROMWearLevel::getLengthAllocationPerVar(uint16_t partition_length){
  lengthPerVar=partition_length/numOfVar;
}

void MSN_EEPROMWearLevel::updateHeaderByte(uint16_t var_n, MSN_EEPROMwlAddr* address[]){
    address[var_n]->address_toRead=address[var_n]->address_toWrite;
    bool isFull=true;
    for(int offset=0; offset<lengthPerVar; offset+=2){
		if(!EEPROM.read(offset+base_address)){}
		else{
            address[var_n]->address_toWrite=EEPROM.read(offset+base_address);
            offset=partition_length;
            isFull=false;
        }
    }
    if(isFull){
        address[var_n]->address_toWrite=base_address;
        EEPROM.write(base_address,0b11111111);
    }
}

void MSN_EEPROMWearLevel::update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint8_t val){
    //eeprom update
    EEPROM.update((address[var_n]->address_toWrite)+1, val);
    //header update
    updateHeaderByte(var_n, &address);
}

uint8_t MSN_EEPROMWearLevel::read(uint16_t var_n, MSN_EEPROMwlAddr* address[]){
    return EEPROM.read(address[var_n]->address_toRead);
}