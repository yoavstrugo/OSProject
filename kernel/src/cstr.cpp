#include "cstr.h"

char uintToStringOut[128]; // buffer for the string
const char* toString(uint64_t value) {
    // The actual size of the string
    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0) {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while (value / 10 > 0) {
        uint8_t rem = value % 10;
        value /= 10;

        uintToStringOut[size - index] = rem + '0';
        index++;
    }

    uint8_t rem = value % 10;
    uintToStringOut[size - index] = rem + '0';
    uintToStringOut[size + 1] = 0;

    return uintToStringOut;
}

char intToStringOut[128]; // buffer for the string
const char* toString(int64_t value) {
    uint8_t isNeg = 0;

    if (value < 0) {
        isNeg = 1;
        value *= -1;
        intToStringOut[0] = '-';
    }

    // The actual size of the string
    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0) {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while (value / 10 > 0) {
        uint8_t rem = value % 10;
        value /= 10;

        intToStringOut[size - index + isNeg] = rem + '0';
        index++;
    }

    uint8_t rem = value % 10;
    intToStringOut[size - index + isNeg] = rem + '0';
    intToStringOut[size + 1 + isNeg] = 0;

    return intToStringOut;
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

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;
    
    for (uint8_t i = 0; i < decimal_places; i++)
    {
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }
    

    *doublePtr = 0;
    return doubleToStringOut;
}

const char* toString(double value) {
    return toString(value, 2);
}

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
        hexToStringOut64[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 'A' : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOut64[size - (i * 2)] = tmp + (tmp > 9 ? 'A' : '0');
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