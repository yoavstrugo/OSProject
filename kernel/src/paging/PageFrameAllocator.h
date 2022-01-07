#pragma once
#include "../efiMemory.h"
#include <stdint.h>
#include "../Bitmap.h"
#include "../memory.h"
#include "../constants.h"

class PageFrameAllocator {
    public:
    void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap PageBitmap;
    void FreePage(void* address);
    void FreePages(void* address, uint64_t count);
    void* RequestPage();
    void LockPage(void* address);
    void LockPages(void* address, uint64_t count);

    uint64_t GetFreeMemory();
    uint64_t GetReservedMemory();
    uint64_t GetUsedMemory();

    private:
    void InitBitmap(size_t bitmapSize, void* bufferAddress); // create and initiallize bitmap at the given address
    void ReservePage(void* address);
    void ReservePages(void* address, uint64_t count);
    void UnreservePage(void* address); 
    void UnreservePages(void* address, uint64_t count); 



    bool Initialized = false;
};