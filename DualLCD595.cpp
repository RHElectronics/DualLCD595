/*
  RH Electronics Dual 595 LCD Library
  2 LCDs with parallel data lines and individual RS and E
  June 2018
*/

#include "Arduino.h"
#include "DualLCD595.h"

//Declare
DualLCD595::DualLCD595(byte dataPin, byte clockPin, byte latchPin){
  _dataPin = dataPin;
  _clockPin = clockPin;
  _latchPin = latchPin;
}

//Begin
DualLCD595::begin(){
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  
  delay(50);
  LCD_Init(0);	//Init Display 0
  LCD_Init(1);	//Init Display 1
}

//Write to LCD via shift regsiter
void DualLCD595::LCD_Write(byte cmd,byte cmddta, byte display){
//Value of RS

  byte bit;		//For the RS line of the display
  if(display == 0){ bit = 32;}
  if(display == 1){ bit = 128;}
  
  if(cmddta == 1){_lcdval = (_lcdval & ~B10100000) | bit; }
  else {_lcdval = (_lcdval & ~B10100000);}

  LCDShift(_lcdval);
  
  //Write MSB
  _cmdval = (cmd & 240) >>4;
  _lcdval = (_lcdval & ~B00001111) | _cmdval;

  LCDShift(_lcdval);
  SetE(display);

  //Write LSB
  _cmdval = cmd & 15;
  _lcdval = (_lcdval & ~B00001111) | _cmdval;
  
  LCDShift(_lcdval);
  SetE(display);
}

//Pulse the E line
void DualLCD595::SetE(byte display){

  byte bit;
  if(display == 0){ bit = 16;}
  if(display == 1){ bit = 64;}

  delay(0.5);
  _lcdval = (_lcdval & ~B01010000) | bit;    //Add bit
  LCDShift(_lcdval);
  delay(0.5);
  _lcdval = (_lcdval & ~B01010000);         //Remove bit
  LCDShift(_lcdval);
  delay(1);
}

//LCD Shift Out
void DualLCD595::LCDShift(byte _lcdval){
  digitalWrite(_latchPin,LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, _lcdval);
  digitalWrite(_latchPin,HIGH);
}

//Write Character
void DualLCD595::LCD_Char(char character, byte display){
  LCD_Write(character,1,display);
}

//Write String
void DualLCD595::Str(String text, byte display){
 char *chrarray = new char[text.length()];
 strcpy(chrarray, text.c_str());
 while(*chrarray) LCD_Char (*chrarray++,display);
}

//Write Integer
void DualLCD595::Int(int n, byte display){
  char c[10];
  sprintf(c, "%d", n);
  for (int i=0;c[i] > 0 ;i++) LCD_Char(c[i],display); 
 }

//Clear LCD
void DualLCD595::Clear(byte display){
  LCD_Write(0x01,0,display);
}

//Set Cursor
void DualLCD595::SetCursor(byte row, byte col, byte display){
   if (col == 0)LCD_Write((row | 0x80),0,display);
   if (col == 1)LCD_Write((row | 0x80)+ 0x40,0,display);
   if (col == 2)LCD_Write((row | 0x80)+ 0x10,0,display);
   if (col == 3)LCD_Write((row | 0x80)+ 0x50,0,display);
   delay(0.5);
}

//Initialize
void DualLCD595::LCD_Init(byte display){
  LCD_Write(0x33,0,display);
  delay(0.5);
  LCD_Write(0x32,0,display);
  delay(0.5);
  LCD_Write(0x28,0,display);
  delay(0.5);
  LCD_Write(0x0C,0,display);
  delay(0.5);
  LCD_Write(0x06,0,display);
  delay(0.5);
  LCD_Write(0x01,0,display);
  delay(0.5);
}