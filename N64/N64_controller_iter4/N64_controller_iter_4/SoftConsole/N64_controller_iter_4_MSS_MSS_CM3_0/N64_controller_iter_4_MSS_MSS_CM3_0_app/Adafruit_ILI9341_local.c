/*
 * Adafruit_ILI9341_local.c
 *
 *  Created on: Apr 15, 2017
 *      Author: mkothbau
 */


/*
 * Adafruit_ILI9341.c
 *
 *  Created on: Apr 15, 2017
 *      Author: mkothbau
 *      Adapted from Adafruit.cpp, their info is below
 *        This is our library for the Adafruit ILI9341 Breakout and Shield
		  ----> http://www.adafruit.com/products/1651

		  Check out the links above for our tutorials and wiring diagrams
		  These displays use SPI to communicate, 4 or 5 pins are required to
		  interface (RST is optional)
		  Adafruit invests time and resources providing this open source code,
		  please support Adafruit and open-source hardware by purchasing
		  products from Adafruit!

		  Written by Limor Fried/Ladyada for Adafruit Industries.
		  MIT license, all text above must be included in any redistribution
 */

#include "drivers/mss_spi/drivers/mss_spi/mss_spi.h"
#include "Adafruit_ILI9341_local.h"
#include "Adafruit_GFX_local.h"

#include <time.h>

static uint8_t g_rx_frame = 0;

void delay(int milliseconds) {
	long pause;
	clock_t now,then;

	pause = milliseconds*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while( (now-then) < pause )
		now = clock();
}

uint32_t * CD_REG = (uint32_t*)(FPGA_FABRIC_BASE + 4);

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04


// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

void startWrite(mss_spi_slave_t slave){
	MSS_SPI_set_slave_select( &g_mss_spi1, slave );
}

void spiWrite(uint8_t msg) {
	startWrite(MSS_SPI_SLAVE_0);
	MSS_SPI_transfer_frame(&g_mss_spi1, msg);
	endWrite(MSS_SPI_SLAVE_0);
}

void endWrite(mss_spi_slave_t slave) {
	MSS_SPI_clear_slave_select( &g_mss_spi1, slave );
}

uint8_t spiRead() {
	return g_rx_frame;
}

void rx_handler( uint32_t rx_frame ) {
	g_rx_frame = rx_frame;
}

#define SPI_WRITE16(s)         spiWrite((s) >> 8); spiWrite(s)
#define SPI_WRITE32(l)         spiWrite((l) >> 24); spiWrite((l) >> 16); spiWrite((l) >> 8); spiWrite(l)
//#define SPI_WRITE_PIXELS(c,l)  for(uint32_t i=0; i<(l); i+=2){ spiWrite(((uint8_t*)(c))[i+1]); spiWrite(((uint8_t*)(c))[i]); }

void SPI_WRITE_PIXELS(uint8_t*colors, uint8_t len) {
	uint32_t i;
	for( i=0; i<(len * 2); i+=2){
		spiWrite(((uint8_t*)((uint8_t*)colors))[i+1]);
		spiWrite(((uint8_t*)((uint8_t*)colors))[i]);
	}
}

void writeCommand(uint8_t cmd) {
	//*CD_REG = 0;
	startWrite(MSS_SPI_SLAVE_1);
	spiWrite(cmd);
	endWrite(MSS_SPI_SLAVE_1);
	//*CD_REG = 1;
}

void begin(struct Print * print) {
    writeCommand(0xEF);
    spiWrite(0x03);
    spiWrite(0x80);
    spiWrite(0x02);

    writeCommand(0xCF);
    spiWrite(0x00);
    spiWrite(0XC1);
    spiWrite(0X30);

    writeCommand(0xED);
    spiWrite(0x64);
    spiWrite(0x03);
    spiWrite(0X12);
    spiWrite(0X81);

    writeCommand(0xE8);
    spiWrite(0x85);
    spiWrite(0x00);
    spiWrite(0x78);

    writeCommand(0xCB);
    spiWrite(0x39);
    spiWrite(0x2C);
    spiWrite(0x00);
    spiWrite(0x34);
    spiWrite(0x02);

    writeCommand(0xF7);
    spiWrite(0x20);

    writeCommand(0xEA);
    spiWrite(0x00);
    spiWrite(0x00);

    writeCommand(ILI9341_PWCTR1);    //Power control
    spiWrite(0x23);   //VRH[5:0]

    writeCommand(ILI9341_PWCTR2);    //Power control
    spiWrite(0x10);   //SAP[2:0];BT[3:0]

    writeCommand(ILI9341_VMCTR1);    //VCM control
    spiWrite(0x3e);
    spiWrite(0x28);

    writeCommand(ILI9341_VMCTR2);    //VCM control2
    spiWrite(0x86);  //--

    writeCommand(ILI9341_MADCTL);    // Memory Access Control
    spiWrite(0x48);

    writeCommand(ILI9341_VSCRSADD); // Vertical scroll
	spiWrite(0x00);
	spiWrite(0x00);

    writeCommand(ILI9341_PIXFMT);
    spiWrite(0x55);

    writeCommand(ILI9341_FRMCTR1);
    spiWrite(0x00);
    spiWrite(0x18);

    writeCommand(ILI9341_DFUNCTR);    // Display Function Control
    spiWrite(0x08);
    spiWrite(0x82);
    spiWrite(0x27);

    writeCommand(0xF2);    // 3Gamma Function Disable
    spiWrite(0x00);

    writeCommand(ILI9341_GAMMASET);    //Gamma curve selected
    spiWrite(0x01);

    writeCommand(ILI9341_GMCTRP1);    //Set Gamma
    spiWrite(0x0F);
    spiWrite(0x31);
    spiWrite(0x2B);
    spiWrite(0x0C);
    spiWrite(0x0E);
    spiWrite(0x08);
    spiWrite(0x4E);
    spiWrite(0xF1);
    spiWrite(0x37);
    spiWrite(0x07);
    spiWrite(0x10);
    spiWrite(0x03);
    spiWrite(0x0E);
    spiWrite(0x09);
    spiWrite(0x00);

    writeCommand(ILI9341_GMCTRN1);    //Set Gamma
    spiWrite(0x00);
    spiWrite(0x0E);
    spiWrite(0x14);
    spiWrite(0x03);
    spiWrite(0x11);
    spiWrite(0x07);
    spiWrite(0x31);
    spiWrite(0xC1);
    spiWrite(0x48);
    spiWrite(0x08);
    spiWrite(0x0F);
    spiWrite(0x0C);
    spiWrite(0x31);
    spiWrite(0x36);
    spiWrite(0x0F);

    writeCommand(ILI9341_SLPOUT);    //Exit Sleep
    delay(120);
    writeCommand(ILI9341_DISPON);    //Display on
    delay(120);

    print->widthe = ILI9341_TFTWIDTH;
    print->heighte = ILI9341_TFTHEIGHT;
}

void setRotation(struct Print * print, uint8_t m) {
    print->rotation = m % 4; // can't be higher than 3
    switch (print->rotation) {
        case 0:
            m = (MADCTL_MX | MADCTL_BGR);
            print->widthe  = ILI9341_TFTWIDTH;
            print->heighte = ILI9341_TFTHEIGHT;
            break;
        case 1:
            m = (MADCTL_MV | MADCTL_BGR);
            print->widthe  = ILI9341_TFTHEIGHT;
            print->heighte = ILI9341_TFTWIDTH;
            break;
        case 2:
            m = (MADCTL_MY | MADCTL_BGR);
            print->widthe  = ILI9341_TFTWIDTH;
            print->heighte = ILI9341_TFTHEIGHT;
            break;
        case 3:
            m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
            print->widthe  = ILI9341_TFTHEIGHT;
            print->heighte = ILI9341_TFTWIDTH;
            break;
    }

    writeCommand(ILI9341_MADCTL);
    spiWrite(m);
}

void invertDisplay(boolean i) {
    writeCommand(i ? ILI9341_INVON : ILI9341_INVOFF);
}

void scrollTo(uint16_t y) {
    writeCommand(ILI9341_VSCRSADD);
    spiWrite((y>>8) & 0x0011);
    spiWrite(y & 0x0011);
}
void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
    uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
    writeCommand(ILI9341_CASET); // Column addr set
    //SPI_WRITE32(xa);
    spiWrite((xa) >> 24);
    spiWrite((xa) >> 16);
    spiWrite((xa) >> 8);
    spiWrite(xa);

    writeCommand(ILI9341_PASET); // Row addr set
    //SPI_WRITE32(ya);
    spiWrite((ya) >> 24);
    spiWrite((ya) >> 16);
    spiWrite((ya) >> 8);
    spiWrite(ya);

    writeCommand(ILI9341_RAMWR); // write to RAM
}

void pushColor(uint16_t color) {
  SPI_WRITE16(color);
}


void writePixel(uint16_t color){
    SPI_WRITE16(color);
}

void writePixels(uint16_t * colors, uint32_t len){
	 SPI_WRITE_PIXELS((uint8_t*)colors , len * 2);
}


void writePixelCoordinates(struct Print * print, int16_t x, int16_t y, uint16_t color) {
    if((x < 0) ||(x >= print->widthe) || (y < 0) || (y >= print->heighte)) return;
    setAddrWindow(x,y,1,1);
    writePixel(color);
}
void writeColor(struct Print * print, uint16_t color, uint32_t len){
	uint32_t t;
	uint8_t hi = color >> 8, lo = color;
	for ( t=len; t; t--){
		spiWrite(hi);
		spiWrite(lo);
	}

}

void writeFillRect(struct Print * print,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
    if((x >= print->widthe) || (y >= print->heighte)) return;
    int16_t x2 = x + w - 1, y2 = y + h - 1;
    if((x2 < 0) || (y2 < 0)) return;

    // Clip left/top
    if(x < 0) {
        x = 0;
        w = x2 + 1;
    }
    if(y < 0) {
        y = 0;
        h = y2 + 1;
    }

    // Clip right/bottom
    if(x2 >= print->widthe)  w = print->widthe  - x;
    if(y2 >= print->heighte) h = print->heighte - y;

    int32_t len = (int32_t)w * h;
    setAddrWindow(x, y, w, h);

    writeColor(print, color, len);
}

void writeFastVLine(struct Print * print,int16_t x, int16_t y, int16_t h, uint16_t color){
    writeFillRect(print, x, y, 1, h, color);
}

void writeFastHLine(struct Print * print,int16_t x, int16_t y, int16_t w, uint16_t color){
    writeFillRect(print, x, y, w, 1, color);
}

uint8_t readcommand8(uint8_t c, uint8_t index) {

    writeCommand(0xD9);  // woo sekret command?
    spiWrite(0x10 + index);
    writeCommand(c);
    uint8_t r = spiRead();
    return r;
}

void drawPixel(struct Print * print, int16_t x, int16_t y, uint16_t color){
    writePixelCoordinates(print, x, y, color);
}

void drawFastVLine(struct Print * print,int16_t x, int16_t y,
        int16_t h, uint16_t color) {
    writeFastVLine(print, x, y, h, color);
}

void drawFastHLine(struct Print * print,int16_t x, int16_t y,
        int16_t w, uint16_t color) {
    writeFastHLine(print, x, y, w, color);
}

void fillRect(struct Print * print, int16_t x, int16_t y, int16_t w, int16_t h,
        uint16_t color) {
    writeFillRect(print, x,y,w,h,color);
}

// This code was ported/adapted from https://github.com/PaulStoffregen/ILI9341_t3
// by Marc MERLIN. See examples/pictureEmbed to use this.
void drawBitmap(struct Print * print, int16_t x, int16_t y, int16_t w, int16_t h,
  const uint16_t *pcolors) {

    int16_t x2, y2; // Lower-right coord
    if(( x             >= print->widthe ) ||      // Off-edge right
       ( y             >= print->heighte) ||      // " top
       ((x2 = (x+w-1)) <  0      ) ||      // " left
       ((y2 = (y+h-1)) <  0)     ) return; // " bottom

    int16_t bx1=0, by1=0, // Clipped top-left within bitmap
            saveW=w;      // Save original bitmap widthe value
    if(x < 0) { // Clip left
        w  +=  x;
        bx1 = -x;
        x   =  0;
    }
    if(y < 0) { // Clip top
        h  +=  y;
        by1 = -y;
        y   =  0;
    }
    if(x2 >= print->widthe ) w = print->widthe  - x; // Clip right
    if(y2 >= print->heighte) h = print->heighte - y; // Clip bottom

    pcolors += by1 * saveW + bx1; // Offset bitmap ptr to clipped top-left
    setAddrWindow(x, y, w, h); // Clipped area
    while(h--) { // For each (clipped) scanline...
      writePixels((uint16_t*)pcolors, w); // Push one (clipped) row
      pcolors += saveW; // Advance pointer by one full (unclipped) line
    }
}

