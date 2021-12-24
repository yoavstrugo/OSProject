#pragma once
#include <stdint.h>

// Signed / Unsigned to string 
const char* toString(uint64_t value);
const char* toString(int64_t value);

// Double to string
const char* toString(double value, uint8_t decimal_places);
const char* toString(double value); // With default of 2 decimal places

// To hex string for 8/16/32/64 bit value
const char* toHexString(uint64_t value);
const char* toHexString(uint32_t value);
const char* toHexString(uint16_t value);
const char* toHexString(uint8_t value);
