#include "PageFrameAllocator.h"

uint64_t FreeMemory = 0;
uint64_t ReservedMemory = 0;
uint64_t UsedMemory = 0;

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize) {
    if (Initialized) return;

    Initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescSize;

    // We want to find the largest memory segment to put the page bitmap in
    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type == 7) // EfiConventionalMemory
            if (desc->numPages * PAGE_SIZE > largestFreeMemSegSize) {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * PAGE_SIZE;
            }
    }

    // Get the total amount of memory in the system
    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    FreeMemory = memorySize; // total amount, we will subtract the used/reserved later
    
    // calculate the number of bits in the bitmap
    uint64_t bitmapSize = memorySize / PAGE_SIZE / BYTE_SIZE + 1;

    // create the bitmap at the start of the largest memory segment
    InitBitmap(bitmapSize, largestFreeMemSeg);

    // lock pages of bitmap
    LockPages(&PageBitmap, PageBitmap.Size / PAGE_SIZE + 1);
    
    // reserve pages of unsuable/reserved memory
    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type != 7) { // Not EfiConventionalMemory
            ReservePages(desc->physAddr, desc->numPages);
        }
    }


}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void* bufferAddress) {
    // set the bitmap properties
    PageBitmap.Size = bitmapSize;
    PageBitmap.Buffer = (uint8_t*)bufferAddress;
    
    // reset the whole bitmap 
    for (int i = 0; i < bitmapSize; i++)
        *(uint8_t*)(PageBitmap.Buffer + i) = 0;
}

void PageFrameAllocator::FreePage(void* address) {
    //  calculate the index of the page
    uint64_t index = (uint64_t)address / PAGE_SIZE;
    if (PageBitmap[index] == false) return; // page is already free

    // free the page and change the memory measures
    PageBitmap.Set(index, false);
    FreeMemory += PAGE_SIZE;
    UsedMemory -= PAGE_SIZE;
}

void PageFrameAllocator::FreePages(void* address, uint64_t count) {
    // Free each page
    for (int page = 0; page < count; page++)
        FreePage((void*)((uint64_t)address + (page * PAGE_SIZE)));   
}

void *PageFrameAllocator::RequestPage() {

    // find the first free page
    for (uint64_t index = 0; index < PageBitmap.Size * BYTE_SIZE; index++)
    {
        if(PageBitmap[index]) continue; // page is locked, continue to next
        
        void* pageAddress = (void *)(index * PAGE_SIZE); // calculate the physical address
        LockPage(pageAddress); // lock and return the page

        return pageAddress;
    }


    return NULL; // Page frame swap to file
}

void PageFrameAllocator::LockPage(void* address) {
    //  calculate the index of the page
    uint64_t index = (uint64_t)address / PAGE_SIZE;
    if (PageBitmap[index] == true) return; // page is already locked

    // lock the page
    PageBitmap.Set(index, true);
    FreeMemory -= PAGE_SIZE;
    UsedMemory += PAGE_SIZE;
}

void PageFrameAllocator::LockPages(void* address, uint64_t count) {
    // Free each page
    for (int page = 0; page < count; page++)
        LockPage((void*)((uint64_t)address + (page * PAGE_SIZE)));   
}

void PageFrameAllocator::UnreservePage(void* address) {
    //  calculate the index of the page
    uint64_t index = (uint64_t)address / PAGE_SIZE;
    if (PageBitmap[index] == false) return; // page is not reserved

    // unreserve the page
    PageBitmap.Set(index, true);
    FreeMemory += PAGE_SIZE;
    ReservedMemory -= PAGE_SIZE;
}

void PageFrameAllocator::UnreservePages(void* address, uint64_t count) {
    // Free each page
    for (int page = 0; page < count; page++)
        UnreservePage((void*)((uint64_t)address + (page * PAGE_SIZE)));   
}

void PageFrameAllocator::ReservePage(void* address) {
    //  calculate the index of the page
    uint64_t index = (uint64_t)address / PAGE_SIZE;
    if (PageBitmap[index] == true) return; // page is already reserved

    // reserve the page
    PageBitmap.Set(index, true);
    FreeMemory -= PAGE_SIZE;
    ReservedMemory += PAGE_SIZE;
}

void PageFrameAllocator::ReservePages(void* address, uint64_t count) {
    // Free each page
    for (int page = 0; page < count; page++)
        ReservePage((void*)((uint64_t)address + (page * PAGE_SIZE)));   
}

uint64_t PageFrameAllocator::GetFreeMemory() {
    return FreeMemory;
}

uint64_t PageFrameAllocator::GetReservedMemory() {
    return ReservedMemory;
}

uint64_t PageFrameAllocator::GetUsedMemory() {
    return UsedMemory;
}