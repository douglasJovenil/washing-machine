#include "main.h"

void main(){
  uint8_t old_mode = -1;
  definitions();
  
  while(TRUE){
    old_mode = PORTD;
    if (MODE_BUTTON1 && MODE_BUTTON2) f_mode11();
    else if (MODE_BUTTON1 && !MODE_BUTTON2) f_mode10();
    else if (!MODE_BUTTON1 && MODE_BUTTON2) f_mode01();
    else if (!MODE_BUTTON1 && !MODE_BUTTON2) f_mode00();
    if (old_mode != PORTD) clearLCD();
  }
}

void f_mode11(){
  writeArrayLCD("Ciclo normal\0", UP);
  if (START_BUTTON){
    f_filling();
    f_shaking();
    f_emptying_out();
    f_spinning();
  }
}

void f_mode10(){
  writeArrayLCD("2x Enxague\0", UP);
  writeArrayLCD("2x Agitamento\0", DOWN);
  if (START_BUTTON){
    for (uint8_t i = 0; i < 2; i++){
      f_filling();
      f_emptying_out();
      f_spinning();
    }
    for (uint8_t i = 0; i < 2; i++) f_shaking();
  }
}

void f_mode01(){
  writeArrayLCD("3x Enxague\0", UP);
  writeArrayLCD("Sem agitamento\0", DOWN);
  if (START_BUTTON){
    for (uint8_t i = 0; i < 3; i++){
      f_filling();
      f_emptying_out();
      f_spinning();
    }
  }
}

void f_mode00(){
  writeArrayLCD("2x Enxague\0", UP);
  writeArrayLCD("+ Secagem\0", DOWN);
  if (START_BUTTON){
    for (uint8_t i = 0; i < 2; i++){
      f_filling();
      f_emptying_out();
      f_spinning();
    }
    f_drying();
  }
}

void f_filling(){
  clearLCD();
  writeArrayLCD("Enchendo\0", UP);
  shiftRightON(&LATD, CLK1, FILLING_TIME);
  clearLCD();
}

void f_shaking(){
  writeArrayLCD("Agitando\0", UP);
  for (uint8_t i = 0; i < SHAKING_QNT; i++){
    shiftLeftON(&LATD, CLK2, SHAKING_TIME);
    shiftRightON(&LATD, CLK2, SHAKING_TIME);
  }
  turnOFF(&LATD, CLK2);
  clearLCD();
}

void f_emptying_out(){
  writeArrayLCD("Esvaziando\0", UP);
  turnOFF(&LATD, CLK2);
  shiftLeftOFF(&LATD, CLK1, FILLING_TIME);
  clearLCD();
}

void f_spinning(){
  writeArrayLCD("Centrifugando\0", UP);
  for (uint8_t i = 0; i < SPINNING_QNT; i++) toggleFourBits(&LATD, CLK2, SPINNING_TIME);
  turnOFF(&LATD, CLK2);
  clearLCD();
}

void f_drying(){
  writeArrayLCD("Secando\0", UP);
  for (uint8_t i = 0; i < DRYING_QNT; i++) toggleAllBits(&LATD, CLK2, DRYING_TIME);
  turnOFF(&LATD, CLK2);
  clearLCD();
}

void definitions(){
  startLCD();
  TRISB = OUT;
  TRISD = 0b00111000;
}