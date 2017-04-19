/*
 * Adafruit_FT6206.h
 *
 *  Created on: Apr 17, 2017
 *      Author: mkothbau
 */

#ifndef ADAFRUIT_FT6206_H_
#define ADAFRUIT_FT6206_H_

typedef int bool;
#define true 1
#define false 0

#define FT6206_ADDR           0x38
#define FT6206_G_FT5201ID     0xA8
#define FT6206_REG_NUMTOUCHES 0x02

#define FT6206_NUM_X             0x33
#define FT6206_NUM_Y             0x34

#define FT6206_REG_MODE 0x00
#define FT6206_REG_CALIBRATE 0x02
#define FT6206_REG_WORKMODE 0x00
#define FT6206_REG_FACTORYMODE 0x40
#define FT6206_REG_THRESHHOLD 0x80
#define FT6206_REG_POINTRATE 0x88
#define FT6206_REG_FIRMVERS 0xA6
#define FT6206_REG_CHIPID 0xA3
#define FT6206_REG_VENDID 0xA8

// calibrated for Adafruit 2.8" ctp screen
#define FT6206_DEFAULT_THRESSHOLD 128

struct TS_Point {
	  int16_t x, y, z;
};


struct Adafruit_FT6206 {
  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];
};

bool ts_begin(struct Adafruit_FT6206 * ts, uint8_t thresh);

 void writeRegister8(uint8_t reg, uint8_t val);
 uint8_t readRegister8(uint8_t reg);

 void readData(struct Adafruit_FT6206 * ts, uint16_t *x, uint16_t *y);

 bool touched(struct Adafruit_FT6206 * ts);
 struct TS_Point * getPoint(struct Adafruit_FT6206 * ts);

#endif /* ADAFRUIT_FT6206_H_ */
