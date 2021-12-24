#pragma once
#include <stddef.h>

struct FrameBuffer {
	void* BaseAddress; // Address of frame buffer in memory
	size_t BufferSize; // Size of the frame buffer
	unsigned int Width; // Width and height
	unsigned int Height;

	unsigned int PixelsPerScanline; // Actual pixels per line
};