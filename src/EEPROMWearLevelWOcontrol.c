uint16_t lengthPerVar;
uint16_t numOfVar;

void begin(uint16_t *latestAddress[], uint16_t partition_length){
    numOfVar=(uint16_t)(sizeof(*latestAddress)/sizeof(uint16_t));
    lengthPerVar=getLengthAllocationPerVar(partition_length);
    for(uint8_t var_n=0;var_n<numOfVar;var_n++){
		for(int addr=0; addr<partition_length; addr+=2){
			if(!EEPROM.read(addr)){}
			else{
                *latestAddress[var_n]=EEPROM.read(addr);
                addr=partition_length;
            }
        }
    }
}

uint16_t lengthAllocationPerVar(uint16_t partition_length){
    //partition_length/numOfVar
}

void update(uint16_t var_n, uint16_t *latestAddress[]){
    
}