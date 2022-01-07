#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(FrameBuffer* targetFrameBuffer, PSF1_FONT* psf1_font) {
    TargetFrameBuffer = targetFrameBuffer;
    PSF1_Font = psf1_font;
    Colour = 0xffffffff;
    CursorPosition = {0, 0};
}

void BasicRenderer::AdvanceCursor() {
    if (CursorPosition.X + PSF1_CHAR_WIDTH > TargetFrameBuffer->Width) 
        NewLine();
    else
        CursorPosition.X += PSF1_CHAR_WIDTH;
}

void BasicRenderer::NewLine() {
    CursorPosition = {0, CursorPosition.Y + LINE_HEIGHT};
}

bool BasicRenderer::strequ(const char *str1, const char *str2, bool match_length) {
    if ((strlen(str1) != strlen(str2)) && match_length) return false;

    for (int i = 0; i < MIN(strlen(str1), strlen(str2)); i++) {
        if (str1[i] != str2[i]) return false;
    }

    return true;
}

void BasicRenderer::Printf(const char* format, ...) {
    
    int i;
    char *s;

    char *traverse = (char *)format;

    va_list arg;
    va_start(arg, format);

    
    for (char *traverse = (char *)format; *traverse != '\0'; traverse++) {
        // Print all chracters until we get a '%'
        while (*traverse != '%' && *traverse != '\0') {
            PutChar(*traverse);
            traverse++;
        }

        if (*traverse == '\0') break;

        traverse++;

        // After a '%', check the next character
        switch (*traverse) {
            case 'c':
                i = va_arg(arg, int); // char argument
                PutChar(i);
                break;
            case 'd':
                i = va_arg(arg, int);
                Print(toString((int64_t)i));
                break;
            case 's':
                s = va_arg(arg, char *);
                Print((const char *)s);
                break;
            case 'x':
                i = va_arg(arg, uint64_t);
                traverse++;
                if (*traverse == '8')
                    Print(toHexString((uint8_t)i));
                else  if (strequ((const char *)traverse, "16", false)) {
                    Print(toHexString((uint16_t)i));
                    traverse++;
                }
                else  if (strequ((const char *)traverse, "32", false)) {
                    Print(toHexString((uint32_t)i));
                    traverse++;;
                }
                else  if (strequ((const char *)traverse, "64", false)) {
                    Print(toHexString((uint64_t)i));
                    traverse++;
                }
                else 
                    traverse--;

                break;
            default:
                break;
        }
    }

    va_end(arg);
}

void BasicRenderer::Print(const char* str) {
    // get a pointer to the first char
    char* chr = (char*)str;
    while(*chr != 0) {
        // write the char and increase the cursor
        PutChar(*chr);
        chr++;
    }
}

char BasicRenderer::PutChar(char chr) {
    // get the pointer to the graphics address
	unsigned int* pixPtr = (unsigned int*) TargetFrameBuffer->BaseAddress;
    // get the pointer to the given char
	char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);

    if (chr == '\n') {
        NewLine();
        return chr;
    }


    // loop on the vertical pixels
	for (unsigned long y = CursorPosition.Y; y < CursorPosition.Y + 16; y++)
	{
        // loop on the horizontal pixels
		for (unsigned long x = CursorPosition.X; x < CursorPosition.X + 8; x++)
		{
            // get the (x,y) pixel and check if it's on or off
			if ((*fontPtr & (0b10000000 >> (x- CursorPosition.X))) > 0) {
                // if it's on write the pixel
				*(unsigned int*)(pixPtr + x + (y * TargetFrameBuffer->PixelsPerScanline)) = Colour;
			}
		}
        // next row
		fontPtr++;
	}

    AdvanceCursor(); // Set it ready for next character

    return chr;
}