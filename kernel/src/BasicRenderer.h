#pragma once
#include "Math.h"
#include "FrameBuffer.h"
#include "PSF1.h"


class BasicRenderer {
    public:
    BasicRenderer(FrameBuffer* targetFrameBuffer, PSF1_FONT* psf1_font); // Constructor

    // Class variables
    Point CursorPosition;
    FrameBuffer* TargetFrameBuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Colour;

    // Class functions
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
};