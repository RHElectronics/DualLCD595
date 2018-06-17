/*
  RH Electronics 595 LCD
  June 2018
*/
#ifndef DualLCD595_h
#define DualLCD595_h

#include "Arduino.h"

class DualLCD595{

  public:
    DualLCD595(byte dataPin, byte clockPin, byte latchPin);
	begin();
	void LCD_Char(char character, byte display);
	void Str(String text, byte display);
	void Int(int n, byte display);
	void Clear(byte display);
	void SetCursor(byte row, byte col, byte display);
	
  private:
	byte _dataPin;
	byte _clockPin;
	byte _latchPin;
	byte _cmdval;
    byte _lcdval;
	void SetE(byte display);
	void LCD_Init(byte display);
	void LCD_Write(byte cmd, byte cmddta, byte display);
	void LCDShift(byte lcdval);
};

#endif