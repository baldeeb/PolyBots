#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

typedef int boolean;
enum { false, true };

#include "gfxfont.h"
#include <inttypes.h>

//*************ADAFRUIT_GFX PUBLIC PRINT CLASS *********//
struct Print {

  //Adafruit_GFX(int16_t w, int16_t h); // Constructor

   int16_t
    WIDTH, HEIGHT;   // This is the 'raw' display w/h - never changes
  int16_t
    widthe, heighte, // Display w/h as modified by current rotation
    cursor_x, cursor_y;
  uint16_t
    textcolor, textbgcolor;
  uint8_t
    textsize,
    rotation;
  int
    wrap,   // If set, 'wrap' text at right edge of display
    cp437; // If set, use correct CP437 charset (default is off)
  GFXfont
    *gfxFont;
};


  // This MUST be defined by the subclass:
  //void drawPixel(struct Print * print, int16_t x, int16_t y, uint16_t color);
  int16_t height(struct Print* print) ;
  int16_t width(struct Print* print) ;

  uint8_t getRotation(struct Print * print) ;

  // get current cursor position (get rotation safe maximum values, using: width() for x, height() for y)
  int16_t getCursorX(struct Print * print) ;
  int16_t getCursorY(struct Print * print) ;

  // TRANSACTION API / CORE DRAW API
   // These MAY be overridden by the subclass to provide device-specific
   // optimized code.  Otherwise 'generic' versions are used.
   void startWriteGFX(void);
   //void writePixel(int16_t x, int16_t y, uint16_t color);
   //void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
   //void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
   //void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
   void writeLine(struct Print * print, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
   //void endWrite(void);


   // CONTROL API
     // These MAY be overridden by the subclass to provide device-specific
     // optimized code.  Otherwise 'generic' versions are used.
      //void setRotation(struct Print * print,uint8_t r);
     // void invertDisplay(boolean i);

     // BASIC DRAW API
     // These MAY be overridden by the subclass to provide device-specific
     // optimized code.  Otherwise 'generic' versions are used.
      void
       // It's good to implement those, even if using transaction API
       //drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
       //drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
       //fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
       fillScreen(struct Print * print, uint16_t color),
       // Optional and probably not necessary to change
       drawLine(struct Print * print, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color),
       drawRect(struct Print * print, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

     // These exist only with Adafruit_GFX (no subclass overrides)
     void drawCircle(struct Print * print, int16_t x0, int16_t y0, int16_t r, uint16_t color);
     void drawCircleHelper(struct Print * print, int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
         uint16_t color);
     void fillCircle(struct Print * print, int16_t x0, int16_t y0, int16_t r, uint16_t color);
       void fillCircleHelper(struct Print * print, int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
         int16_t delta, uint16_t color);
     void drawTriangle(struct Print * print, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
         int16_t x2, int16_t y2, uint16_t color);
     void fillTriangle(struct Print * print, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
         int16_t x2, int16_t y2, uint16_t color);
     void drawRoundRect(struct Print * print, int16_t x0, int16_t y0, int16_t w, int16_t h,
         int16_t radius, uint16_t color);
     void fillRoundRect(struct Print * print, int16_t x0, int16_t y0, int16_t w, int16_t h,
         int16_t radius, uint16_t color);
//     void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
//         int16_t w, int16_t h, uint16_t color);
     void drawXBitmap(struct Print * print, int16_t x, int16_t y, const uint8_t *bitmap,
         int16_t w, int16_t h, uint16_t color);
     void drawChar(struct Print * print,int16_t x, int16_t y, unsigned char c, uint16_t color,
         uint16_t bg, uint8_t size);
     void setCursor(struct Print * print,int16_t x, int16_t y);
     void setTextColor(struct Print * print,uint16_t c);
     void setBGTextColor(struct Print * print,uint16_t c, uint16_t bg);
     void setTextSize(struct Print * print,uint8_t s);
     void setTextWrap(struct Print * print,boolean w);
     void cp437(struct Print * print, boolean x);
     void setFont(struct Print * print,GFXfont *f );
     void getTextBounds(struct Print * print,char *string, int16_t x, int16_t y,
         int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);


     void   write(struct Print * print,uint8_t c);


//***************ADAFRUIT_GFX CLASS*********///
//void drawPixel(int16_t x, int16_t y, uint16_t color);
void fillScreen(struct Print * print, uint16_t color);
  uint16_t *getBuffer(void);
struct Adafruit_GFX {
	  uint16_t *buffer;
};

#endif // _ADAFRUIT_GFX_H



//************ADAFRUIT_GFX_BUTTON CLASS *************//

void initButton(struct Adafruit_GFX *gfx, int16_t x, int16_t y,
   uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
   uint16_t textcolor, char *label, uint8_t textsize);
  // New/alt initButton() uses upper-left corner & size
  void initButtonUL(struct Adafruit_GFX *gfx, int16_t x1, int16_t y1,
   uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
   uint16_t textcolor, char *label, uint8_t textsize);
  void drawButton(boolean inverted);
  boolean contains(int16_t x, int16_t y);

  void press(boolean p);
  boolean isPressed();
  boolean justPressed();
  boolean justReleased();

//
//struct Adafruit_GFX_Button {
//
////  Adafruit_GFX_Button(void);
//  // "Classic" initButton() uses center & size
//
//  struct Adafruit_GFX *_gfx;
//  int16_t       _x1, _y1; // Coordinates of top-left corner
//  uint16_t      _w, _h;
//  uint8_t       _textsize;
//  uint16_t      _outlinecolor, _fillcolor, _textcolor;
//  char          _label[10];
//
//  boolean currstate, laststate;
//}Adafruit_GFX_Button_t;

