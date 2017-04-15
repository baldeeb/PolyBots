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

#include <time.h>

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

void startWrite(void){
	MSS_SPI_set_slave_select( &g_mss_spi1, MSS_SPI_SLAVE_0 );
}

void spiWrite(uint8_t msg) {
	MSS_SPI_transfer_frame(&g_mss_spi1, msg);
}

void writeCommand(uint8_t cmd) {
	*CD_REG = 0;
	spiWrite(cmd);
	*CD_REG = 1;
}

void begin(uint8_t frame_size) {
	MSS_SPI_configure_master_mode
	(
	    &g_mss_spi1,
	    MSS_SPI_SLAVE_0,
	    MSS_SPI_MODE0,
	    MSS_SPI_PCLK_DIV_256,
	    frame_size
	);

    startWrite();

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
}

