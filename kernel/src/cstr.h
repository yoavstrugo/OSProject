#pragma once
#include <stdint.h>


const char* toString(uint64_t value);
const char* toString(int64_t value);
const char* toHexString(uint64_t value);
const char* toHexString(uint32_t value);
const char* toHexString(uint16_t value);
const char* toHexString(uint8_t value);
const char* toString(double value, uint8_t decimal_places);
const char* toString(double value);