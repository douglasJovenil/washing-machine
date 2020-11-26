#ifndef __LCD__H__
#define __LCD__H__

#include "pic18f4550_config.h"
#include "defines.h"
#include "xlcd.h"

#define DELAY_CLEAR 80
#define START_LCD   0x00
#define CMD_CLEAR   0x01
#define END_LCD     0x40
#define DOWN        'd'
#define UP          'u'

uint8_t sizeArray(const uint8_t array[]);
void writeArrayLCD(const int8_t string[], int8_t vertical_position);
void clearLCD();
void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);
void startLCD();

#endif

