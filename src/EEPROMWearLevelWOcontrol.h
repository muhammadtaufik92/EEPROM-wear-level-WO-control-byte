/*
    Copyright 2016-2016 Peter Rosenberg

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
  This file is part of the EEPROMWearLevel library for Arduino.
*/

#ifndef EEPROM_WEAR_LEVEL_H
#define EEPROM_WEAR_LEVEL_H

#include <EEPROM.h>

/**
   uncomment to deactivate the range check of idx.
*/
//#define NO_RANGE_CHECK
/**
   uncomment to use an array instead of the real EEPROM for testing purpose
*/
//#define NO_EEPROM_WRITES
/**
   uncomment to write debug logs to Serial
*/
//#define DEBUG_LOG
/**
   the size of the fake eeprom if used
*/
#ifdef NO_EEPROM_WRITES
#define FAKE_EEPROM_SIZE 34
#endif

/*
   the index of the layoutVersion byte
*/
#define INDEX_VERSION 0
/**
   definition of no data, happens when no data has been written yet.
*/
#define NO_DATA -1

/**
   returned when an error occured, e.g. out of index if RANGE_CHECK is defined
*/
#define ERROR_CODE -2

class EEPROMWearLevelWOcontrol: EEPROMClass {
  public:
    /**
        Initialises EEPROMWearLevel. One of the begin() methods must be called
        before any other method.
        This method uses the whole EEPROM for wear leveling.
        @param layoutVersion your version of the EEPROM layout. When ever you change any value
        on the begin() method, the layoutVersion must be incremented. This will reset EEPROMWearLevel
        and initilize it and the EEPROM to the given values.
        @param amountOfIndexes the amount of indexes you want to use.
    */
    void begin(MSN_eepromwl *address[], uint16_t partition_length);

    /**
      Returns the amount of indexes that can be used. This value is defined by the begin() method.
    */
    //unsigned int length();

    /**
       returns the maximum size a single element can be. If the element is larger than half of
       the maximum size, no wear levelling will be possible.
    */
    //int getMaxDataLength(const int idx) const;

    /**
       reads one byte from idx
    */
    uint8_t read(uint16_t var_n, MSN_eepromwl *address[], uint8_t val);

    /**
       writes one byte if it is not the same as the last one.
    */
    void update(uint16_t var_n, MSN_eepromwl *address[], uint8_t val);

    /**
       reads the last written value of idx or leaves t unchanged if no
       value written yet.
    */
    template< typename T > T &get(const int idx, T &t) {
      return getImpl(idx, t);
    }

    /**
        returns the first index used to store data for this idx.
        This method can be called to use EEPROMWEarLevel as a ring buffer.
    */
    int getStartIndexEEPROM(const int idx);

    /**
       returns the current read index of this idx.
        This method can be called to use EEPROMWEarLevel as a ring buffer.
    */
    int getCurrentIndexEEPROM(const int idx, int dataLength) ;

    /**
       prints the EEPROMWearLevel status to print. Use Serial to
       print to the default serial port.
    */
    void printStatus(Print &print);

    /**
       prints content of the EEPROM to print
    */
    void printBinary(Print &print, int startIndex, int endIndex);

    /**
       Constructor of the EEPROMWearLevel. Do not call this method as there
       is only one instance of EEPROMWearLevel supported.
    */
    EEPROMWearLevel();

  private:
   uint16_t lengthPerVar;
   uint16_t numOfVar;
   void updateHeaderByte(uint16_t var_n, MSN_eepromwl *address[]);
   uint16_t getLengthAllocationPerVar(uint16_t partition_length);
};


/**
   the instance of EEPROMWearLevel
*/
extern EEPROMWearLevel EEPROMwl;

#endif // #ifndef EEPROM_WEAR_LEVEL_H
