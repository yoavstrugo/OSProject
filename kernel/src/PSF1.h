#pragma once

// Represnts the header of PSF1 font
struct PSF1_HEADER {
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
};

// Reprensnts a PSF1 font
struct PSF1_FONT {
	PSF1_HEADER* psf1_Header;
	void* glyphBuffer;
};