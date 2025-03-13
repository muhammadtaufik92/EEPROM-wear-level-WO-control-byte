#include "EEPROMWearLevelWOcontrol.h"

#define NUM_OF_VAR          20
uint16_t  PARTITION_LENGTH =   1024;


MSN_EEPROMWearLevel::MSN_EEPROMwlAddr var_a,var_b,var_c,var_d,var_e,var_f,var_g,var_h,var_i,var_j,var_k,var_l,var_m,var_n,var_o,var_p,var_q,var_r,var_s,var_u;
MSN_EEPROMWearLevel::MSN_EEPROMwlAddr* address[]={&var_a,&var_b,&var_c,&var_d,&var_e,&var_f,&var_g,&var_h,&var_i,&var_j,&var_k,&var_l,&var_m,&var_n,&var_o,&var_p,&var_q,&var_r,&var_s,&var_u,NULL};

#define IDX_VAR_A   0x41
#define IDX_VAR_B   0x42
#define IDX_VAR_C   0x43
#define IDX_VAR_D   0x44
#define IDX_VAR_E   0x45
#define IDX_VAR_F   0x46
#define IDX_VAR_G   0x47
#define IDX_VAR_H   0x48
#define IDX_VAR_I   0x49
#define IDX_VAR_J   0x4A
#define IDX_VAR_K   0x4B
#define IDX_VAR_L   0x4C
#define IDX_VAR_M   0x4D
#define IDX_VAR_N   0x4E
#define IDX_VAR_O   0x4F
#define IDX_VAR_P   0x50
#define IDX_VAR_Q   0x51
#define IDX_VAR_R   0x52
#define IDX_VAR_S   0x53
#define IDX_VAR_U   0x54

#define IDX_VAR_NTH    (uint16_t[]){IDX_VAR_A,IDX_VAR_B,IDX_VAR_C,IDX_VAR_D,IDX_VAR_E,IDX_VAR_F,IDX_VAR_G,IDX_VAR_H,IDX_VAR_I,IDX_VAR_J,IDX_VAR_K,IDX_VAR_L,IDX_VAR_M,IDX_VAR_N,IDX_VAR_O,IDX_VAR_P,IDX_VAR_Q,IDX_VAR_R,IDX_VAR_S,IDX_VAR_U}

void setup() {
  var_a.size=WORD;
  var_b.size=WORD;
  var_c.size=WORD;
  var_d.size=WORD;
  var_e.size=WORD;
  var_f.size=WORD;
  var_g.size=WORD;
  var_h.size=WORD;
  var_i.size=WORD;
  var_j.size=WORD;
  var_k.size=WORD;
  var_l.size=WORD;
  var_m.size=WORD;
  var_n.size=WORD;
  var_o.size=WORD;
  var_p.size=WORD;
  var_q.size=WORD;
  var_r.size=WORD;
  var_s.size=WORD;
  var_u.size=WORD;
  
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
      Serial.print("	address_toRead: ");Serial.println(address[i]->address_toRead);
    }
    else{
      Serial.println("VAR "+String(i)+": NULL");
    }
  }
  EEPROM_print();
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
      uint8_t chara=str[1];
      uint16_t val_16=(uint16_t)(str[2]<<8);
      val_16+=(uint16_t)str[3];
      switch (chara){
        case IDX_VAR_A: {
          EEPROMwl.update(IDX_VAR_A, address, val_16);
          Serial.print((uint8_t)str[2]);
          Serial.println((uint8_t)str[3]);
          Serial.println("VAR "+String(IDX_VAR_A-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_A-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_B: {
          EEPROMwl.update(IDX_VAR_B, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_B-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_B-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_C: {
          EEPROMwl.update(IDX_VAR_C, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_C-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_C-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_D: {
          EEPROMwl.update(IDX_VAR_D, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_D-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_D-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_E: {
          EEPROMwl.update(IDX_VAR_E, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_E-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_E-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_F: {
          EEPROMwl.update(IDX_VAR_F, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_F-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_F-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_G: {
          EEPROMwl.update(IDX_VAR_G, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_G-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_G-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_H: {
          EEPROMwl.update(IDX_VAR_H, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_H-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_H-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_I: {
          EEPROMwl.update(IDX_VAR_I, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_I-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_I-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_J: {
          EEPROMwl.update(IDX_VAR_J, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_J-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_J-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_K: {
          EEPROMwl.update(IDX_VAR_K, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_K-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_K-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_L: {
          EEPROMwl.update(IDX_VAR_L, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_L-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_L-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_M: {
          EEPROMwl.update(IDX_VAR_M, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_M-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_M-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_N: {
          EEPROMwl.update(IDX_VAR_N, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_N-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_N-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_O: {
          EEPROMwl.update(IDX_VAR_O, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_O-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_O-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_P: {
          EEPROMwl.update(IDX_VAR_P, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_P-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_P-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_Q: {
          EEPROMwl.update(IDX_VAR_Q, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_Q-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_Q-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_R: {
          EEPROMwl.update(IDX_VAR_R, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_R-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_R-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_S: {
          EEPROMwl.update(IDX_VAR_S, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_S-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_S-0x41, address)));
          cmd_available=1;
          break;
        }
        case IDX_VAR_U: {
          EEPROMwl.update(IDX_VAR_U, address, (uint8_t)str[2]);
          Serial.println("VAR "+String(IDX_VAR_U-0x41)+" is successfully updated to "+String(EEPROMwl.read(IDX_VAR_U-0x41, address)));
          cmd_available=1;
          break;
        }

      }
      if(cmd_available){
        //EEPROM_print();
      }
      else{
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

void EEPROM_print(){
  Serial.println("\nEEPROM CONTENT:");
  for(uint16_t i=0;i<1024;i++){
    Serial.println("  Address "+String(i)+": "+String(EEPROM.read(i)));
    if((i+1)%10==0){
      Serial.println();
    }
  }
}

