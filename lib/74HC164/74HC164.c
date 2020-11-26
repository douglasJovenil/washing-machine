#include "74HC164.h"

void numToArray(uint8_t num, uint8_t array[]){
  for (int i = SIZE_BIN_ARRAY - 1; i >= 0; i--){
    array[i] = (num > 0) ? (num % 2) : 0;
    num /= 2;
  }
}

void setLed(volatile uint8_t *LAT, uint8_t pin_clk, uint8_t value, uint8_t const OPTION){
  uint8_t bin_value[SIZE_BIN_ARRAY];
  numToArray(value, bin_value);

  for (uint8_t i = 0; i < SIZE_BIN_ARRAY; i++){
    *LAT = (OPTION) ? (PIN_MUX & bin_value[i]) : (PIN_MUX & (~bin_value[i]));
    *LAT |= pin_clk;
    *LAT = (OPTION) ? (PIN_MUX & bin_value[i]) : (PIN_MUX & (~bin_value[i]));
  }
}

void shiftRightON(volatile uint8_t *LAT, uint8_t pin_clk, uint8_t time){
  uint8_t aux_value = MSB_BIT_LAT;
  for (uint8_t i = 0; i < SIZE_BIN_ARRAY; i++){
    setLed(LAT, pin_clk, aux_value, TRUE);
    aux_value |= aux_value >> 1;
    for (uint32_t i=0; i<time; i++) __delay_ms(1);
  }
}

void shiftLeftON(volatile uint8_t *LAT, uint8_t pin_clk, uint8_t time){
  uint8_t aux_value = 1;
  for (uint8_t i = 0; i < SIZE_BIN_ARRAY; i++){
    setLed(LAT, pin_clk, aux_value, TRUE);
     aux_value |= aux_value << 1;
    for (uint32_t i=0; i<time; i++) __delay_ms(1);
  }
}

void shiftLeftOFF(volatile uint8_t *LAT, uint8_t pin_clk, uint8_t time){
  uint8_t aux_value = 1;
  for (uint8_t i = 0; i < SIZE_BIN_ARRAY; i++){
    setLed(LAT, pin_clk, aux_value, FALSE);
     aux_value |= aux_value << 1;
    for (uint32_t i=0; i<time; i++) __delay_ms(1);
  }
}

void turnOFF(volatile uint8_t *LAT, uint8_t pin_clk){
  for (uint8_t i = 0; i < SIZE_BIN_ARRAY; i++) setLed(LAT, pin_clk, 0, TRUE);
}

void toggleFourBits(volatile uint8_t *LAT, uint8_t pin_clk, uint8_t time){
  uint8_t aux_value = 0xF0;
  for (uint8_t i = 0; i < 2; i++){
    setLed(LAT, pin_clk, aux_value, TRUE);
    aux_value = ~aux_value;
    for (uint32_t i=0; i<time; i++) __delay_ms(1);
  }
}

void toggleAllBits(volatile uint8_t *LAT, uint8_t pin_clk, uint8_t time){
  uint8_t aux_value = 0b10101010;
  for (uint8_t i = 0; i < 2; i++){
    setLed(LAT, pin_clk, aux_value, TRUE);
    aux_value = ~aux_value;
    for (uint32_t i=0; i<time; i++) __delay_ms(1);
  }
}