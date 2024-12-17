#include "EEPROMWearLevelWOcontrol.h"

#define NUM_OF_VAR          3
#define PARTITION_LENGTH    20


MSN_EEPROMWearLevel::MSN_EEPROMwlAddr var_a,var_b,var_c;
MSN_EEPROMWearLevel::MSN_EEPROMwlAddr* address[]={&var_a,&var_b,&var_c,NULL};
#define IDX_VAR_A   0x41
#define IDX_VAR_B   0x42
#define IDX_VAR_C   0x43

#define IDX_VAR_NTH    (uint16_t[]){IDX_VAR_A, IDX_VAR_B, IDX_VAR_C}

void setup() {
  TCCR0B = TCCR0B & B11111000 | B00000001;//64x faster than default
  TCCR1B = TCCR1B & B11111000 | B00000001;
  TCCR2B = TCCR2B & B11111000 | B00000001;
  TCCR3B = TCCR3B & B11111000 | B00000001;
  TCCR4B = TCCR4B & B11111000 | B00000001;
  TCCR5B = TCCR5B & B11111000 | B00000001;
  Serial.begin(115200);
  delay(500);
  EEPROMwl.begin(address, PARTITION_LENGTH);
  for(uint8_t i=0;i<NUM_OF_VAR;i++){
    if(address[i]->address_toRead!=NULL){
      Serial.print("VAR "+String(i)+": ");
      Serial.println(EEPROMwl.read(IDX_VAR_NTH[i]-0x41,address));
    }
    else{
      Serial.println("VAR "+String(i)+": NULL");
    }
  }
  /*for(uint8_t i=0;i<18;i++){
    Serial.println("EEPROM Address "+String(i)+": "+String(EEPROM.read(i)));
  }*/
  Serial.println("Enter values for the next startup sequence");
  Serial.println("the values printed in the next startup sequence will be the value stored in this session");
}

void loop() {
  cmd();
}

void cmd(){
  if(Serial.available() > 0){
    String str = Serial.readString();
    uint8_t cmd_available = 0;
    if(str[0]==0x21){
      if (str[1]==IDX_VAR_A) {
        EEPROMwl.update(IDX_VAR_A, address, (uint8_t)str[2]);
        Serial.println((uint8_t)str[2]);
        Serial.println("VAR "+String(IDX_VAR_A-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_A-0x41, address)));
        cmd_available=1;
      }
      if (str[1]==IDX_VAR_B) {
        EEPROMwl.update(IDX_VAR_B, address, (uint8_t)str[2]);
        Serial.println("VAR "+String(IDX_VAR_B-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_B-0x41, address)));
        cmd_available=1;
      }
      if (str[1]==IDX_VAR_C) {
        EEPROMwl.update(IDX_VAR_C, address, (uint8_t)str[2]);
        Serial.println("VAR "+String(IDX_VAR_C-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_C-0x41, address)));
        cmd_available=1;
      }
      if (!cmd_available) {
        Serial.println("Var not found");
      }
    }
    else if(str[0]==0x22){
      for (int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0xff);
      }
      Serial.println("EEPROM erased");
    }
    else{
      Serial.println("command should start with 0x21 (!), then 1 byte of var index, then 1 byte of value");
    }
  }
}

