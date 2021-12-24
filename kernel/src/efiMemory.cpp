#include "efiMemory.h"

// TODO: Read about the memory types

// Array of the efi memory type strings, ordered by their index
// Reference: https://uefi.org/sites/default/files/resources/UEFI_Spec_2_9_2021_03_18.pdf, Page 164
const char* EFI_MEMORY_TYPE_STRINGS[] {
    "EfiReserveMemoryType",
    "EfiLoaderCode",
    "EfiLoaderData",
    "EfiBootServicesCode",
    "EfiBootServicesData",
    "EfiRuntimeServicesCode",
    "EfiRuntimeServicesData",
    "EfiConventionalMemory",
    "EfiUnsuableMemory",
    "EfiACPIReclaimMemory",
    "EfiACPIMemoryNVS",
    "EfiMemoryMappedIO",
    "EfiMemoryMappedIOPortSpace",
    "EfiPalCode",
    
};