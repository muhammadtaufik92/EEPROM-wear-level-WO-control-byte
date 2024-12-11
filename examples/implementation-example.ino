#include <EEPROMWearLevelWOcontrol.h>

#define NUM_OF_VAR          3
#define PARTITION_LENGTH    1024

MSN_EEPROMwlAddr address[NUM_OF_VAR];
#define IDX_VAR_A   0
#define IDX_VAR_B   1
#define IDX_VAR_C   2

void setup() {
  Serial.begin(9600);
  while (!Serial);

  EEPROMwl.begin(&address, PARTITION_LENGTH);

  EEPROMwl.read
  readConfiguration();
}

void loop() {
}

void writeConfiguration() {
  // write a byte
  EEPROMwl.update(INDEX_CONFIGURATION_VAR1, 12);

  long var2 = 33333;
  EEPROMwl.put(INDEX_CONFIGURATION_VAR2, var2);
}

void readConfiguration() {
  byte var1 = EEPROMwl.read(INDEX_CONFIGURATION_VAR1);
  Serial.print(F("var1: "));
  Serial.println(var1);

  long var2 = -1;
  EEPROMwl.get(INDEX_CONFIGURATION_VAR2, var2);
  Serial.print(F("var2: "));
  Serial.println(var2);
}

