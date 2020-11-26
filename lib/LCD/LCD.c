#include "LCD.h"

uint8_t sizeArray(const uint8_t array[]){
    uint8_t i = 0;
    while (array[i] != '\0') i++;
    return i;
}

void writeArrayLCD(const int8_t string[], int8_t vertical_position){
    uint8_t ram_position = (vertical_position == UP) ? START_LCD : END_LCD;
    
    for (uint8_t i = 0; i <= sizeArray(string); i++){
        while(BusyXLCD());
        SetDDRamAddr(ram_position);
        while(BusyXLCD());
        putcXLCD(string[i]);
        while(BusyXLCD());
        ram_position++;
    }
}

void clearLCD(){	
   while(BusyXLCD());  
   WriteCmdXLCD(CMD_CLEAR);
   while(BusyXLCD());
   for (uint32_t i=0; i<DELAY_CLEAR; i++) __delay_ms(1);
}

void DelayFor18TCY(void){
    __delay_us((8*18.0*4000000.0)/_XTAL_FREQ); 
}

void DelayPORXLCD(void){
    __delay_ms(60);
}

void DelayXLCD(void){
    __delay_ms(20);
}

void startLCD(){
    OpenXLCD(FOUR_BIT&LINES_5X7);
    while(BusyXLCD());            
    WriteCmdXLCD(0x06);
    while(BusyXLCD()); 
    WriteCmdXLCD(0x0C);
    while(BusyXLCD()); 
}