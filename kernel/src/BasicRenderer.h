#pragma once
#include "Math.h"
#include "FrameBuffer.h"
#include "PSF1.h"


class BasicRenderer {
    public:
    BasicRenderer(FrameBuffer* targetFrameBuffer, PSF1_FONT* psf1_font); // Constructor

    // Class variables
    Point CursorPosition; // The position on screen
    FrameBuffer* TargetFrameBuffer; // The frame buffer
    PSF1_FONT* PSF1_Font; // The font
    unsigned int Colour; // The print color

    // Class functions
    void Print(const char* str); // Print a string at the cursor position

    private:
    void PutChar(char chr, unsigned int xOff, unsigned int yOff); // Print a single char at the given position
};