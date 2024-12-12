#include "EEPROMWearLevelWOcontrol.h"

#define NUM_OF_VAR          3
#define PARTITION_LENGTH    1024


//MSN_EEPROMwlAddr var_a,var_b,var_c;
//MSN_EEPROMwlAddr* address[NUM_OF_VAR]={&var_a,&var_b,&var_c};
#define IDX_VAR_A   0
#define IDX_VAR_B   1
#define IDX_VAR_C   2

#define IDX_VAR_NTH    (uint16_t[]){IDX_VAR_A, IDX_VAR_B, IDX_VAR_C}

void setup() {
  Serial.begin(115200);
  /*delay(500);
  EEPROMwl.begin(address, PARTITION_LENGTH);
  for(uint8_t i=0;i<NUM_OF_VAR;i++){
    Serial.print("VAR "+String(i)+": ");
    Serial.println(EEPROMwl.read(IDX_VAR_NTH[i],address));
  }
  Serial.println("Enter values for the next startup sequence");
  Serial.println("the values printed in the next startup sequence will be the value stored in this session");
*/}

void loop() {
  cmd();
}

void cmd(){
  /*if(Serial.available() > 0){
    String str = Serial.readString();
    cmd_available = 0;
    if(str[0]=0x21){
      if (str[1]==IDX_VAR_A) {
        EEPROMwl.update(IDX_VAR_A, (uint8_t)str[3]);
        Serial.println("VAR "+String(IDX_VAR_A)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_A, address)));
        cmd_available=1;
      }
      if (str[1]==IDX_VAR_B) {
        EEPROMwl.update(IDX_VAR_B, (uint8_t)str[3]);
        Serial.println("VAR "+String(IDX_VAR_B)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_B, address)));
        cmd_available=1;
      }
      if (str[1]==IDX_VAR_C) {
        EEPROMwl.update(IDX_VAR_C, (uint8_t)str[3]);
        Serial.println("VAR "+String(IDX_VAR_C)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_C, address)));
        cmd_available=1;
      }
      if (!cmd_available) {
        Serial.println("Var not found");
      }
    }
    else{
      Serial.println("command should start with 0x21 (!), then 1 byte of var index, then 1 byte of value");
    }
  }
*/}

