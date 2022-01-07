#pragma once
#include "Math.h"
#include "FrameBuffer.h"
#include "PSF1.h"
#include "cstr.h"
#include <stdarg.h>
#include <stddef.h>

#define LINE_HEIGHT 16


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
    void Printf(const char* str, ...);
    void NewLine();

    private:
    char PutChar(char chr); // Print a single char at the given position
    void AdvanceCursor(); 
    bool strequ(const char *str1, const char *str2, bool match_length);
};