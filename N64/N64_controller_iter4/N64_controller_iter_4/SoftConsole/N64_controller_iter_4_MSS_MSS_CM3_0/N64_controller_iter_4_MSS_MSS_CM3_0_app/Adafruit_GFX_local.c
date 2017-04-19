/*
 * Adafruit_GFX_local.c
 *
 *  Created on: Apr 15, 2017
 *      Author: mkothbau
 *      This driver is adapted from Adafruits GFX library
 *
 *     Below is Adafruit's copyright info
 *
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!

Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
 */

#include "Adafruit_GFX_local.h"
#include "Adafruit_ILI9341_local.h"
#include "glcdfont.c"
#include <stdlib.h>

// Many (but maybe not all) non-AVR board installs define macros
// for compatibility with existing PROGMEM-reading AVR code.
// Do our own checks and defines here for good measure...

#ifndef pgm_read_byte
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
 #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
 #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif


// Bresenham's algorithm - thx wikpedia
void writeLine(struct Print * print, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
        	writePixelCoordinates(print, y0, x0, color);
        } else {
        	writePixelCoordinates(print, x0, y0, color);
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
        }
    }
}


void fillScreen(struct Print * print, uint16_t color) {
    // Update in subclasses if desired!
    fillRect(print, 0, 0, print->widthe, print->heighte, color);
}

void drawLine(struct Print * print, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
        uint16_t color) {
    // Update in subclasses if desired!
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t(y0, y1);
        drawFastVLine(print, x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t(x0, x1);
        drawFastHLine(print, x0, y0, x1 - x0 + 1, color);
    } else {

        writeLine(print, x0, y0, x1, y1, color);

    }
}


// Draw a circle outline
void drawCircle(struct Print * print, int16_t x0, int16_t y0, int16_t r,
        uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;


    writePixelCoordinates(print,x0  , y0+r, color);
    writePixelCoordinates(print,x0  , y0-r, color);
    writePixelCoordinates(print, x0+r, y0  , color);
    writePixelCoordinates(print, x0-r, y0  , color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        writePixelCoordinates(print,x0 + x, y0 + y, color);
        writePixelCoordinates(print,x0 - x, y0 + y, color);
        writePixelCoordinates(print,x0 + x, y0 - y, color);
        writePixelCoordinates(print, x0 - x, y0 - y, color);
        writePixelCoordinates(print,x0 + y, y0 + x, color);
        writePixelCoordinates(print,x0 - y, y0 + x, color);
        writePixelCoordinates(print,x0 + y, y0 - x, color);
        writePixelCoordinates(print, x0 - y, y0 - x, color);
    }

}

void drawCircleHelper(struct Print * print, int16_t x0, int16_t y0,
        int16_t r, uint8_t cornername, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
        	writePixelCoordinates(print, x0 + x, y0 + y, color);
        	writePixelCoordinates(print, x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
        	writePixelCoordinates(print, x0 + x, y0 - y, color);
        	writePixelCoordinates(print, x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
        	writePixelCoordinates(print, x0 - y, y0 + x, color);
        	writePixelCoordinates(print, x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
        	writePixelCoordinates(print, x0 - y, y0 - x, color);
        	writePixelCoordinates(print, x0 - x, y0 - y, color);
        }
    }
}

void fillCircle(struct Print * print, int16_t x0, int16_t y0, int16_t r,
        uint16_t color) {

    writeFastVLine(print, x0, y0-r, 2*r+1, color);
    fillCircleHelper(print, x0, y0, r, 3, 0, color);

}

// Used to do circles and roundrects
void fillCircleHelper(struct Print * print, int16_t x0, int16_t y0, int16_t r,
        uint8_t cornername, int16_t delta, uint16_t color) {

    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        if (cornername & 0x1) {
            writeFastVLine(print, x0+x, y0-y, 2*y+1+delta, color);
            writeFastVLine(print, x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2) {
            writeFastVLine(print, x0-x, y0-y, 2*y+1+delta, color);
            writeFastVLine(print, x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}

// Draw a rectangle
void drawRect(struct Print * print, int16_t x, int16_t y, int16_t w, int16_t h,
        uint16_t color) {

    writeFastHLine(print, x, y, w, color);
    writeFastHLine(print, x, y+h-1, w, color);
    writeFastVLine(print, x, y, h, color);
    writeFastVLine(print, x+w-1, y, h, color);

}

// Draw a rounded rectangle
void drawRoundRect(struct Print * print, int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint16_t color) {
    // smarter version

    writeFastHLine(print, x+r  , y    , w-2*r, color); // Top
    writeFastHLine(print, x+r  , y+h-1, w-2*r, color); // Bottom
    writeFastVLine(print, x    , y+r  , h-2*r, color); // Left
    writeFastVLine(print, x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    drawCircleHelper(print, x+r    , y+r    , r, 1, color);
    drawCircleHelper(print, x+w-r-1, y+r    , r, 2, color);
    drawCircleHelper(print, x+w-r-1, y+h-r-1, r, 4, color);
    drawCircleHelper(print, x+r    , y+h-r-1, r, 8, color);

}

// Fill a rounded rectangle
void fillRoundRect(struct Print * print, int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint16_t color) {
    // smarter version

    writeFillRect(print, x+r, y, w-2*r, h, color);

    // draw four corners
    fillCircleHelper(print, x+w-r-1, y+r, r, 1, h-2*r-1, color);
    fillCircleHelper(print, x+r    , y+r, r, 2, h-2*r-1, color);

}


// Draw a character
void drawChar(struct Print * print, int16_t x, int16_t y, unsigned char c,
        uint16_t color, uint16_t bg, uint8_t size) {
	int8_t j, i;
//    if(!print->gfxFont) { // 'Classic' built-in font

        if((x >= print->widthe)            || // Clip right
                (y >= print->heighte)           || // Clip bottom
                ((x + 6 * size - 1) < 0) || // Clip left
                ((y + 8 * size - 1) < 0))   // Clip top
            return;

        if(!print->cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior


        for(i=0; i<6; i++ ) {
            uint8_t line;
            if(i < 5) line = pgm_read_byte(font+(c*5)+i);
            else      line = 0x0;
            for( j=0; j<8; j++, line >>= 1) {
                if(line & 0x1) {
                    if(size == 1) writePixelCoordinates(print, x+i, y+j, color);
                    else          writeFillRect(print, x+(i*size), y+(j*size), size, size, color);
                } else if(bg != color) {
                    if(size == 1) writePixelCoordinates(print, x+i, y+j, bg);
                    else          writeFillRect(print, x+i*size, y+j*size, size, size, bg);
                }
            }
        }


}



// Return the size of the display (per current rotation)
int16_t width(struct Print* print)  {
    return print->widthe;
}

int16_t height(struct Print* print)  {
    return print->heighte;
}

