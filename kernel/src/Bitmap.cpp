#include "Bitmap.h"

bool Bitmap::operator[](uint64_t index) {
    // Calculate the specific bit and byte indices
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;

    // Get the bit to the correct index
    uint8_t bitIndexer = 0b10000000 >> bitIndex;

    // Check the spceific bit in the specific byte
    return (Buffer[byteIndex] & bitIndexer) > 0;
}

void Bitmap::Set(uint64_t index, bool value) {
    // Calculate the specific bit and byte indices
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;

    // Get the bit to the correct index
    uint8_t bitIndexer = 0b10000000 >> bitIndex;

    // Reset the bit
    Buffer[byteIndex] &= ~bitIndexer;
    
    // Set the bit if neccessery
    if (value) Buffer[byteIndex] |= bitIndexer;
}