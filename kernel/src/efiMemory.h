#pragma once
#include <stdint.h>

// The EFI memory descriptor
// Reference: https://uefi.org/sites/default/files/resources/UEFI_Spec_2_9_2021_03_18.pdf, Page 170
struct EFI_MEMORY_DESCRIPTOR {
    uint32_t type;
    void* physAddr;
    void* virtAddr;
    uint64_t numPages;
    uint64_t attribs;
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];