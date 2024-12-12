
//uint16_t lengthOfPartition;

/*struct eepromwladdr{
    uint16_t address_toRead;
    uint16_t address_toWrite;
} typedef struct eepromwladdr MSN_EEPROMwlAddr;
*/
MSN_EEPROMWearLevel EEPROMwl;

MSN_EEPROMWearLevel::constructor(){
    numOfVar=0;
    lengthPerVar=0;
}

void MSN_EEPROMWearLevel::begin(MSN_EEPROMwlAddr* address[], uint16_t partition_length){
    numOfVar=(uint16_t)(sizeof(address)/sizeof(address[0]));
    lengthPerVar=getLengthAllocationPerVar(partition_length);
    for(uint8_t var_n=0;var_n<numOfVar;var_n++){
        uint16_t offset=lengthPerVar*var_n;
		for(int addr=0; addr<lengthPerVar; addr+=2){
			if(!EEPROM.read(addr+offset)){}
			else{
                address[var_n]->address_toRead=EEPROM.read(addr-1+offset);
                addr=partition_length;
            }
        }
        bool isFull=true;
        for(int addr=0; addr<lengthPerVar; addr+=2){
			if(!EEPROM.read(addr+offset)){}
			else{
                address[var_n]->address_toWrite=EEPROM.read(addr+offset);
                addr=partition_length;
                isFull=false;
            }
        }
        if(isFull){
            address[var_n]->address_toWrite=offset;
            EEPROM.write(offset,0b11111111);
        }
    }
}

uint16_t MSN_EEPROMWearLevel::getLengthAllocationPerVar(uint16_t partition_length){
    lengthPerVar=partition_length/numOfVar;
}

void MSN_EEPROMWearLevel::update(uint16_t var_n, MSN_EEPROMwlAddr* address[], uint8_t val){
    //eeprom update
    EEPROM.update(address[var_n]->address_toWrite, val);
    //header update
    updateHeaderByte(var_n, &address);
}

uint8_t MSN_EEPROMWearLevel::read(uint16_t var_n, MSN_EEPROMwlAddr* address[]){
    return EEPROM.read(address[var_n]->address_toRead);
}

void MSN_EEPROMWearLevel::updateHeaderByte(uint16_t var_n, MSN_EEPROMwlAddr* address[]){
    address[var_n]->address_toRead=address[var_n]->address_toWrite;
    bool isFull=true;
    for(int addr=0; addr<lengthPerVar; addr+=2){
		if(!EEPROM.read(addr+offset)){}
		else{
            address[var_n]->address_toWrite=EEPROM.read(addr+offset);
            addr=partition_length;
            isFull=false;
        }
    }
    if(isFull){
        address[var_n]->address_toWrite=offset;
        EEPROM.write(offset,0b11111111);
    }
}