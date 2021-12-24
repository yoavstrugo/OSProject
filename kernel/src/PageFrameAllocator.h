#pragma once
#include "efiMemory.h"
#include <stdint.h>
#include "Bitmap.h"
#include "memory.h"

class PageFrameAllocator {
    public:
    void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap PageBitmap;
    void FreePage(void* address);
    void LockPage(void* address);

    private:
    void InitBitmap(size_t bitmapSize, void* bufferAddress);
    void ReservePage(void* address);
    void UnreservePage(void* address); 
};