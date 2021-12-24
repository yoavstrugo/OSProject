#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(FrameBuffer* targetFrameBuffer, PSF1_FONT* psf1_font) {
    TargetFrameBuffer = targetFrameBuffer;
    PSF1_Font = psf1_font;
    Colour = 0xffffffff;
    CursorPosition = {50, 50};
}

void BasicRenderer::Print(const char* str) {
    // get a pointer to the first char
    char* chr = (char*)str;
    while(*chr != 0) {
        // write the char and increase the cursor
        PutChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X += 8;
        // if the cursor reaches the end of the line move it down an reset the x offset
        if (CursorPosition.X + 8 > TargetFrameBuffer->Width) {
            CursorPosition.X = 0;
            CursorPosition.Y += PSF1_Font->psf1_Header->charsize;
        }
        chr++;
    }
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff) {
    // get the pointer to the graphics address
	unsigned int* pixPtr = (unsigned int*) TargetFrameBuffer->BaseAddress;
    // get the pointer to the given char
	char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    // loop on the vertical pixels
	for (unsigned long y = yOff; y < yOff + 16; y++)
	{
        // loop on the horizontal pixels
		for (unsigned long x = xOff; x < xOff + 8; x++)
		{
            // get the (x,y) pixel and check if it's on or off
			if ((*fontPtr & (0b10000000 >> (x- xOff))) > 0) {
                // if it's on write the pixel
				*(unsigned int*)(pixPtr + x + (y * TargetFrameBuffer->PixelsPerScanline)) = Colour;
			}
		}
        // next row
		fontPtr++;
	}
}