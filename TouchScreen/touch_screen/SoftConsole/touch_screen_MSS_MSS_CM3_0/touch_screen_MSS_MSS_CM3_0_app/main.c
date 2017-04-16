#include "GFX/Adafruit_GFX_local.h"
#include "Adafruit_ILI9341_local.h"
#include "drivers/mss_uart/mss_uart.h"

void setup();


int main()
{
	struct Print * print = {};
	while( 1 )
	{

	}

	return 0;
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

void testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = width(print),
                h = height(print);

  fillScreen(print, ILI9341_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);


  fillScreen(print,ILI9341_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  fillScreen(print,ILI9341_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);

  fillScreen(print,ILI9341_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(print, x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(print, x1, y1, x2, y2, color);

}

void testFastLines(uint16_t color1, uint16_t color2) {
  int x, y, w = width(print), h = height(print);

  fillScreen(print,ILI9341_BLACK);

  for(y=0; y<h; y+=5) drawFastHLine(print,0, y, w, color1);
  for(x=0; x<w; x+=5) drawFastVLine(print,x, 0, h, color2);

}

void testRects(uint16_t color) {
  int           n, i, i2,
                cx = width(print)  / 2,
                cy = height(print) / 2;

  fillScreen(print,ILI9341_BLACK);
  n     = min(width(print), height(print));
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    drawRect(cx-i2, cy-i2, i, i, color);
  }

}

void testFilledRects(uint16_t color1, uint16_t color2) {
  int           n, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    fillRect(cx-i2, cy-i2, i, i, color1);
    // Outlines are not included in timing results
    drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

void testFilledCircles(uint8_t radius, uint16_t color) {
  int x, y, w = width(), h = height(), r2 = radius * 2;

  fillScreen(ILI9341_BLACK);
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      fillCircle(x, y, radius, color);
    }
  }

}

void testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = width() + radius,
                h = height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      drawCircle(x, y, radius, color);
    }
  }

}

void testTriangles() {
  int           n, i, cx = width()  / 2 - 1,
                      cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  for(i=0; i<n; i+=5) {
    drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      color565(i, i, i));
  }

}

void testFilledTriangles() {
  int           i, cx = width()  / 2 - 1,
                   cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  for(i=min(cx,cy); i>10; i-=5) {
    fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(0, i*10, i*10));
    drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(i*10, i*10, 0));
  }

}

void testRoundRects() {
  int           w, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  w     = min(width(), height());
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    drawRoundRect(cx-i2, cy-i2, i, i, i/8, color565(i, 0, 0));
  }

}

void testFilledRoundRects() {
  int           i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9341_BLACK);
  for(i=min(width(), height()); i>20; i-=6) {
    i2 = i / 2;
    fillRoundRect(cx-i2, cy-i2, i, i, i/8, color565(0, i, 0));
  }

  return micros() - start;
}

void setup() {
  printf("ILI9341 Test!\n");

  begin(8);

  // read diagnostics (optional but can help debug problems)
  uint8_t x = readcommand8(ILI9341_RDMODE, 0);
  printf("Display Power Mode: %ud"PRIu8"\n\r", x);
  x = readcommand8(ILI9341_RDMADCTL, 0);
  printf("MADCTL Mode: %ud"PRIu8"\n\r", x);
  x = readcommand8(ILI9341_RDPIXFMT, 0);
  printf("Pixel Format: %ud"PRIu8"\n\r", x);
  x = readcommand8(ILI9341_RDIMGFMT, 0);
  printf("Image Format: %ud"PRIu8"\n\r", x);
  x = readcommand8(ILI9341_RDSELFDIAG, 0);
  printf("Self Diagnostic: %ud"PRIu8"\n\r", x);

  printf("Benchmark                Time (microseconds)\n");
  delay(10);
  printf("Screen fill              ");
  printf("%ul\n", testFillScreen());
  delay(500);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);

  Serial.print(F("Lines                    "));
  Serial.println(testLines(ILI9341_CYAN));
  delay(500);

  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(ILI9341_RED, ILI9341_BLUE));
  delay(500);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(ILI9341_GREEN));
  delay(500);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA));
  delay(500);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, ILI9341_MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, ILI9341_WHITE));
  delay(500);

  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));

}


void loop(void) {
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);
  }
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  return micros() - start;
}

