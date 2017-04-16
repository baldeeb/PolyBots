#include "Adafruit_GFX_local.h"
#include "Adafruit_ILI9341_local.h"
#include "drivers/mss_uart/mss_uart.h"
#include "drivers/mss_spi/drivers/mss_spi/mss_spi.h"

void setup(struct Print * print);
void testLines(struct Print * print, uint16_t color);
void testFastLines(struct Print * print, uint16_t color1, uint16_t color2);
void testRects(struct Print * print, uint16_t color);
void testFilledRects(struct Print * print, uint16_t color1, uint16_t color2);
void testFilledCircles(struct Print * print, uint8_t radius, uint16_t color);
void testCircles(struct Print * print, uint8_t radius, uint16_t color);
void testTriangles(struct Print * print);
void testFilledTriangles(struct Print * print);
void testRoundRects(struct Print * print);
void testFilledRoundRects(struct Print * print);

struct Print * print;
#define min(a,b) (((a)<(b))?(a):(b))

int main()
{
	print = (struct Print *) malloc(sizeof(struct Print));
	print->HEIGHT = ILI9341_TFTHEIGHT;
	print->WIDTH = ILI9341_TFTWIDTH;

	MSS_SPI_init( &g_mss_spi1 );
	MSS_SPI_configure_master_mode
	(
	    &g_mss_spi1,
	    MSS_SPI_SLAVE_0,
	    MSS_SPI_MODE0,
	    MSS_SPI_PCLK_DIV_256,
	    MSS_SPI_BLOCK_TRANSFER_FRAME_SIZE
	);
	MSS_SPI_configure_master_mode
		(
		    &g_mss_spi1,
		    MSS_SPI_SLAVE_1,
		    MSS_SPI_MODE0,
		    MSS_SPI_PCLK_DIV_256,
		    MSS_SPI_BLOCK_TRANSFER_FRAME_SIZE
		);

	  MSS_SPI_configure_slave_mode
		(
			&g_mss_spi1,
			MSS_SPI_MODE0,
			MSS_SPI_PCLK_DIV_256,
			MSS_SPI_BLOCK_TRANSFER_FRAME_SIZE
		);
//	  MSS_SPI_set_frame_rx_handler( &g_mss_spi1, rx_handler );
//
	setup(print);

	while( 1 )
	{
		//printf("fill screen black\n\r");
		//begin(print);
		//fillScreen(print, ILI9341_BLACK);
//		uint8_t cmd = 0x11;
//		spiWrite(cmd);
//		delay(100);

	}

	free(print);
	return 0;
}

void testFillScreen(struct Print * print) {
  fillScreen(print, ILI9341_BLACK);
  fillScreen(print, ILI9341_RED);
  fillScreen(print, ILI9341_GREEN);
  fillScreen(print, ILI9341_BLUE);
  fillScreen(print, ILI9341_BLACK);
}

//void testText() {
//  fillScreen(ILI9341_BLACK);
//  setCursor(0, 0);
//  setTextColor(ILI9341_WHITE);  setTextSize(1);
//  println("Hello World!");
//  setTextColor(ILI9341_YELLOW); setTextSize(2);
//  println(1234.56);
//  setTextColor(ILI9341_RED);    setTextSize(3);
//  println(0xDEADBEEF, HEX);
//  println();
//  setTextColor(ILI9341_GREEN);
//  setTextSize(5);
//  println("Groop");
//  setTextSize(2);
//  println("I implore thee,");
//  setTextSize(1);
//  println("my foonting turlingdromes.");
//  println("And hooptiously drangle me");
//  println("with crinkly bindlewurdles,");
//  println("Or I will rend thee");
//  println("in the gobberwarts");
//  println("with my blurglecruncheon,");
//  println("see if I don't!");
//}

void testLines(struct Print * print, uint16_t color) {
  int           x1, y1, x2, y2,
                w = width(print),
                h = height(print);

  fillScreen(print, ILI9341_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  for(x2=0; x2<w; x2+=6) drawLine(print, x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(print, x1, y1, x2, y2, color);


  fillScreen(print,ILI9341_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;

  for(x2=0; x2<w; x2+=6) drawLine(print, x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(print, x1, y1, x2, y2, color);

  fillScreen(print,ILI9341_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  for(x2=0; x2<w; x2+=6) drawLine(print, x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(print, x1, y1, x2, y2, color);

  fillScreen(print,ILI9341_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  for(x2=0; x2<w; x2+=6) drawLine(print, x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(print, x1, y1, x2, y2, color);

}

void testFastLines(struct Print * print, uint16_t color1, uint16_t color2) {
  int x, y, w = width(print), h = height(print);

  fillScreen(print,ILI9341_BLACK);

  for(y=0; y<h; y+=5) drawFastHLine(print,0, y, w, color1);
  for(x=0; x<w; x+=5) drawFastVLine(print,x, 0, h, color2);

}

void testRects(struct Print * print, uint16_t color) {
  int           n, i, i2,
                cx = width(print)  / 2,
                cy = height(print) / 2;

  fillScreen(print,ILI9341_BLACK);
  n     = min(width(print), height(print));
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    drawRect(print, cx-i2, cy-i2, i, i, color);
  }

}

void testFilledRects(struct Print * print, uint16_t color1, uint16_t color2) {
  int           n, i, i2,
                cx = width(print)  / 2 - 1,
                cy = height(print) / 2 - 1;

  fillScreen(print, ILI9341_BLACK);
  n = min(width(print), height(print));
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    fillRect(print, cx-i2, cy-i2, i, i, color1);
    // Outlines are not included in timing results
    drawRect(print,cx-i2, cy-i2, i, i, color2);
  }

}

void testFilledCircles(struct Print * print, uint8_t radius, uint16_t color) {
  int x, y, w = width(print), h = height(print), r2 = radius * 2;

  fillScreen(print, ILI9341_BLACK);
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      fillCircle(print, x, y, radius, color);
    }
  }

}

void testCircles(struct Print * print, uint8_t radius, uint16_t color) {
  int           x, y, r2 = radius * 2,
                w = width(print) + radius,
                h = height(print) + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      drawCircle(print, x, y, radius, color);
    }
  }

}

void testTriangles(struct Print * print) {
  int           n, i, cx = width(print)  / 2 - 1,
                      cy = height(print) / 2 - 1;

  fillScreen(print, ILI9341_BLACK);
  n     = min(cx, cy);
  for(i=0; i<n; i+=5) {
    drawTriangle(print,
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      color565(i, i, i));
  }

}

void testFilledTriangles(struct Print * print) {
  int           i, cx = width(print)  / 2 - 1,
                   cy = height(print) / 2 - 1;

  fillScreen(print, ILI9341_BLACK);
  for(i=min(cx,cy); i>10; i-=5) {
    fillTriangle(print, cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(0, i*10, i*10));
    drawTriangle(print, cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(i*10, i*10, 0));
  }

}

void testRoundRects(struct Print * print) {
  int           w, i, i2,
                cx = width(print)  / 2 - 1,
                cy = height(print) / 2 - 1;

  fillScreen(print, ILI9341_BLACK);
  w     = min(width(print), height(print));
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    drawRoundRect(print, cx-i2, cy-i2, i, i, i/8, color565(i, 0, 0));
  }

}

void testFilledRoundRects(struct Print * print) {
  int           i, i2,
                cx = width(print)  / 2 - 1,
                cy = height(print) / 2 - 1;

  fillScreen(print, ILI9341_BLACK);
  for(i=min(width(print), height(print)); i>20; i-=6) {
    i2 = i / 2;
    fillRoundRect(print, cx-i2, cy-i2, i, i, i/8, color565(0, i, 0));
  }

}

void setup(struct Print * print) {
  printf("ILI9341 Test!\n\r");

  begin(print);

  // read diagnostics (optional but can help debug problems)
  uint8_t x = readcommand8(ILI9341_RDMODE, 0);
  printf("Display Power Mode: %d\n\r", x);
  x = readcommand8(ILI9341_RDMADCTL, 0);
  printf("MADCTL Mode: %d\n\r", x);
  x = readcommand8(ILI9341_RDPIXFMT, 0);
  printf("Pixel Format: %d\n\r", x);
  x = readcommand8(ILI9341_RDIMGFMT, 0);
  printf("Image Format: %d\n\r", x);
  x = readcommand8(ILI9341_RDSELFDIAG, 0);
  printf("Self Diagnostic: %d\n\r", x);

  printf("Screen fill              \n\r");
  testFillScreen(print);

//  Serial.print(F("Text                     "));
//  Serial.println(testText());
//  delay(3000);

  printf("Lines                    \n\r");
  testLines(print,ILI9341_CYAN);

  printf("Horiz/Vert Lines         \n\r");
  testFastLines(print, ILI9341_RED, ILI9341_BLUE);

  printf("Rectangles (outline)     \n\r");
  testRects(print, ILI9341_GREEN);

  printf("Rectangles (filled)      \n\r");
  testFilledRects(print, ILI9341_YELLOW, ILI9341_MAGENTA);

  printf("Circles (filled)         \n\r");
  testFilledCircles(print, 10, ILI9341_MAGENTA);

  printf("Circles (outline)        \n\r");
  testCircles(print, 10, ILI9341_WHITE);

  printf("Triangles (outline)      \n\r");
  testTriangles(print);

  printf("Triangles (filled)       \n\r");
  testFilledTriangles(print);

  printf("Rounded rects (outline)  \n\r");
  testRoundRects(print);

  printf("Rounded rects (filled)   \n\r");
  testFilledRoundRects(print);

  printf("Done!");

}


//void loop(print) {
//	uint8_t rotation;
//  for( rotation=0; rotation<4; rotation++) {
//    setRotation(print, rotation);
//    //testText();
//    delay(1000);
//  }
//}



