#include "EEPROMWearLevelWOcontrol.h"
#include <Arduino.h>
MSN_EEPROMWearLevel EEPROMwl;
//cek alamat kosong tiap kali read dan write
//tanpa update update pada pointer
#define DEBUG
#define ELEMENT_MAX 10
#define VAR_N_FROM_0x41

MSN_EEPROMWearLevel::MSN_EEPROMWearLevel(){
    numOfVar=0;
    lengthPerVar=0;
}

uint16_t MSN_EEPROMWearLevel::read(uint16_t var_n, MSN_EEPROMwlAddr* address[]){
    return EEPROM.read(address[var_n]->address_toRead);
}

void MSN_EEPROMWearLevel::begin(MSN_EEPROMwlAddr* address[], uint16_t partition_length){
    #ifdef DEBUG
    Serial.println("begin func");
    #endif
    for(uint8_t i=0;i<ELEMENT_MAX;i++){
      if(address[i]==NULL){
        numOfVar=i;
        i=ELEMENT_MAX;
      }
    }
    //numOfVar=(uint16_t)(sizeof(address)/sizeof(MSN_EEPROMWearLevel::MSN_EEPROMwlAddr));
    #ifdef DEBUG
    //Serial.println("  sizeof(address): "+String(sizeof(address)));
    //Serial.println("  sizeof(address[0]): "+String(sizeof(MSN_EEPROMWearLevel::MSN_EEPROMwlAddr)));
    Serial.println("  numOfVar: "+String(numOfVar));
    #endif
    lengthPerVar=getLengthAllocationPerVar(partition_length);
    for(uint8_t var_n=0;var_n<numOfVar;var_n++){
      uint16_t base_address=lengthPerVar*var_n;
      #ifdef DEBUG
      Serial.println("  var_n: "+String(var_n));
      Serial.println("    base address: "+String(base_address));
      #endif
		for(int offset=0; offset<lengthPerVar; offset+=2){
			if(EEPROM.read(offset+base_address)){}
			else{
        address[var_n]->address_toRead=base_address+offset+1;
        address[var_n]->address_toWrite=base_address+offset+1+2;
        offset=lengthPerVar;
        #ifdef DEBUG
        Serial.println("    address_toRead: "+String(address[var_n]->address_toRead));
        Serial.println("    address_toRead: "+String(address[var_n]->address_toWrite));
        #endif
      }
      if(offset==lengthPerVar-2){
        address[var_n]->address_toRead=base_address+offset+1;
        address[var_n]->address_toWrite=base_address+offset+1+2;
      }
    }
    /*bool isFull=true;
    for(int offset=0; offset<lengthPerVar; offset+=2){
		  if(!EEPROM.read(offset+base_address)){}
		  else{
        address[var_n]->address_toWrite=offset+1+base_address;
        #ifdef DEBUG
        Serial.println("    address_toWrite: "+String(address[var_n]->address_toWrite));
        #endif
        offset=lengthPerVar;
        isFull=false;
      }
    }
    if(isFull){
        address[var_n]->address_toWrite=base_address+1;
        EEPROM.write(base_address,0b11111111);
    }*/
  }
}

uint16_t MSN_EEPROMWearLevel::getLengthAllocationPerVar(uint16_t partition_length){
  lengthPerVar=partition_length/numOfVar;
  lengthPerVar/=2;
  lengthPerVar*=2;
  #ifdef DEBUG
  Serial.println("  lengthPerVar: "+String(lengthPerVar));
  #endif
  return lengthPerVar;
}

void MSN_EEPROMWearLevel::updateHeaderByte(uint16_t var_n, MSN_EEPROMwlAddr* address[]){
  #ifdef DEBUG
  Serial.println("update header func");
  #endif
  uint16_t base_address=lengthPerVar*var_n;
  EEPROM.write(address[var_n]->address_toWrite-1, 0);
  address[var_n]->address_toRead=address[var_n]->address_toWrite;
  if((uint8_t)(address[var_n]->address_toRead)-2==254){
    EEPROM.write(lengthPerVar-1, 255);
  }
  else{
    EEPROM.write(address[var_n]->address_toRead-2, 255);
  }
  #ifdef DEBUG
  Serial.println("  base address: "+String(base_address));
  #endif
  if((address[var_n]->address_toRead-base_address)<(lengthPerVar-1)){
    address[var_n]->address_toWrite=address[var_n]->address_toRead+2;
    #ifdef DEBUG
    Serial.println("    address_toRead: "+String(address[var_n]->address_toRead));
    #endif
  }
  else{
    address[var_n]->address_toWrite=base_address+1;
    #ifdef DEBUG
    Serial.println("    address_toWrite: "+String(address[var_n]->address_toWrite));
    #endif
    //EEPROM.write(base_address,0b11111111);
  }
}

void MSN_EEPROMWearLevel::update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint8_t val){
  //eeprom update
  #ifdef VAR_N_FROM_0x41
  var_n-=0x41;
  #endif 
  #ifdef DEBUG
  Serial.println("update func");
  Serial.println("  val: "+String(val));
  #endif
  EEPROM.update(address[var_n]->address_toWrite, val);
  //header update
  updateHeaderByte(var_n, address);
}