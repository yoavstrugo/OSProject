#pragma once
#include <stddef.h>
#include <stdint.h>

/*
* This class represents a bitmap.
*
* Since C++ is using byte-sized booleans, it can waste large amount of memory
* to store boolean information on massive data (like pages).
* Therefore we use a bitmap for storing the boolean value, where every single
* bit repsents a boolean value.
*/
class Bitmap {
    public:
    size_t Size; // Size of the buffer
    uint8_t* Buffer; // The buffer, an array of bytes
    bool operator[](uint64_t index); // Get method (using operator overload, i.e Bitmap[2] - get the value at second index)
    void Set(uint64_t index, bool value); // Set method
};