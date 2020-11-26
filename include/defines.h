#ifndef __DEFINES__H__
#define __DEFINES__H__

#define HIGH    1
#define LOW     0
#define FALSE   0
#define TRUE    1
#define OFF     0
#define ON      1
#define OUT     0
#define IN      1
  
#define START_BUTTON RD3
#define MODE_BUTTON1 RD4
#define MODE_BUTTON2 RD5

#define MSB_BIT_LAT 0b10000000
#define SIZE_LAT    0xFF
#define CLK1        0b00000010
#define CLK2        0b00000100

#define SPINNING_TIME   150
#define FILLING_TIME    200
#define SHAKING_TIME    100
#define DRYING_TIME     100

#define SPINNING_QNT    4
#define SHAKING_QNT     3
#define DRYING_QNT      10

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef char int8_t;

#endif