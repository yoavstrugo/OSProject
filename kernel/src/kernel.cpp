#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"

struct BootInfo {
	FrameBuffer* framebuffer;
	PSF1_FONT* PSF1_Font;	
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

uint8_t testBuffer[20];

extern "C" void _start(BootInfo* bootInfo) {
	BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->PSF1_Font);

	// newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	Bitmap testBitmap;
	testBitmap.Buffer = testBuffer;
	testBitmap.Set(0, false);
	testBitmap.Set(1, true);
	testBitmap.Set(2, false);
	testBitmap.Set(3, false);
	testBitmap.Set(4, true);

	for (int i = 0; i < 20; i++)
	{
		newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
		newRenderer.Print(testBitmap[i] ? "true" : "false");
	}
	


	// newRenderer.Print(toString(GetMemorySize((EFI_MEMORY_DESCRIPTOR*)bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize)));

	return;
}