#include "cstr.h"

// TODO: change the toString functions to be more 'moudlar' and 'smartly handeled'
char strOut[128];


char uintToStringOut[128]; // buffer for the string
const char* toString(uint64_t value) {
    // Calculate the size of the string
    uint8_t size;
    {
        uint64_t sizeTest = value;
        while (sizeTest / 10 > 0) {
            sizeTest /= 10;
            size++;
        }
    }

    // build the string
    uint8_t index = 0;
    while (value / 10 > 0) {
        uint8_t rem = value % 10; // get the digit
        value /= 10; // remove the digit from the number

        uintToStringOut[size - index] = rem + '0';  // put the digit in the correct place,
                                                    // it starts from the end (the ascii for 
                                                    // number starts at '0')
        index++;
    }

    // Last digit
    uint8_t rem = value % 10;
    uintToStringOut[size - index] = rem + '0';

    uintToStringOut[size + 1] = 0; // terminate string

    return uintToStringOut;
}

char intToStringOut[128]; // buffer for the string
const char* toString(int64_t value) {
    uint8_t isNeg = 0;

    // First check if the number is negative
    if (value < 0) {
        isNeg = 1;
        value *= -1;
        strOut[0] = '-';
    }

    // Calculate the size of the string
    uint8_t size = 0;
    {
        uint64_t sizeTest = value;
        while (sizeTest / 10 > 0) {
            sizeTest /= 10;
            size++;
        }
    }

    // build the string
    uint8_t index = 0;
    while (value / 10 > 0) {
        uint8_t rem = value % 10; // get the digit
        value /= 10; // remove the digit from the number

        strOut[size - index + isNeg] = rem + '0';  // put the digit in the correct place,
                                                            // it starts from the end (the ascii for 
                                                            // number starts at '0'). If the number is
                                                            // negative, we start add 1 to the index.
        index++;
    }


    // Last char and terminate the string
    uint8_t rem = value % 10;
    strOut[size - index + isNeg] = rem + '0';
    strOut[size + 1 + isNeg] = 0;

    return strOut;
}

char doubleToStringOut[128];
const char* toString(double value, uint8_t decimal_places) {

    if (decimal_places > 20) decimal_places = 20; // limit the decimal places

    char* intPtr = (char*)toString((int64_t)value); // convert the int portion into string
    char* doublePtr = doubleToStringOut;

    if (value < 0) value *= -1;

    // copy the int portion into the double string
    while (*intPtr != 0) {
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    // TODO: Maybe change it to *doublePtr++ or something similar
    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value; // keep only the double portion
    
    // Add the decimal portion
    for (uint8_t i = 0; i < decimal_places; i++)
    {
        newValue *= 10; // promote the largest decimal digit to the units place
        *doublePtr = (int)newValue + '0'; // put it in the string
        newValue -= (int)newValue; // remove the int portion
        doublePtr++;
    }
    

    *doublePtr = 0; // terminate
    return doubleToStringOut;
}

// By default, we keep only 2 decimal places
const char* toString(double value) {
    return toString(value, 2);
}

// TODO: document
char hexToStringOut64[128];
const char* toHexString(uint64_t value) {
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOut64[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOut64[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToStringOut64[size + 1] = 0;
    return hexToStringOut64;
}

char hexToStringOut32[128];
const char* toHexString(uint32_t value) {
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOut32[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOut32[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToStringOut32[size + 1] = 0;
    return hexToStringOut32;
}

char hexToStringOut16[128];
const char* toHexString(uint16_t value) {
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 * 2 - 1;
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOut16[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOut16[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToStringOut16[size + 1] = 0;
    return hexToStringOut16;
}

char hexToStringOut8[128];
const char* toHexString(uint8_t value) {
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 1 * 2 - 1;
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOut32[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOut32[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToStringOut32[size + 1] = 0;
    return hexToStringOut32;
}

int strlen(const char *str) {
    int count = 0;
    while (str[count++] != '\0');
    return --count;
}