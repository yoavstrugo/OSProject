#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"
#include "PageFrameAllocator.h"
#include "constants.h"

struct BootInfo {
	FrameBuffer* framebuffer;
	PSF1_FONT* PSF1_Font;	
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

uint64_t test[60000];

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo) {
	BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->PSF1_Font);

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	PageFrameAllocator pageFrameAllocator;
	pageFrameAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

	// Lock kernel pages
	uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
	uint64_t kernelPages = kernelSize / PAGE_SIZE + 1;

	pageFrameAllocator.LockPages(&_KernelStart, kernelPages);

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Free RAM: ");
	newRenderer.Print(toString(pageFrameAllocator.GetFreeMemory() / KiB_SIZE));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Reserved RAM: ");
	newRenderer.Print(toString(pageFrameAllocator.GetReservedMemory() / KiB_SIZE));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Used RAM: ");
	newRenderer.Print(toString(pageFrameAllocator.GetUsedMemory() / KiB_SIZE));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};


	for (int t = 0; t < 20; t++)
	{
		void* address = pageFrameAllocator.RequestPage();
		newRenderer.Print(toHexString((uint64_t)address));
		newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	}
	
	return;
}