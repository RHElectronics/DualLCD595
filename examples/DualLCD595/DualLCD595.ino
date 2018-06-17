//Dual LCD using one 595
//Data lines are parallel on both displays
//Q7=D4, Q6=D5, Q5=D6, Q4=D7

//Control lines use the remaining 4 bits

//Q3=E      Display 0
//Q2=RS

//Q1=E      Display 1
//Q0=RS

#include <DualLCD595.h>
DualLCD595 LCD(5,6,7); //Data Pin, Clock Pin, Latch Pin

void setup() {

  LCD.begin();    //Always start with the begin() command

  //All further commands have the display as the LAST command
  //0 for the first display, 1 for the second display

  //Display 0
  LCD.Clear(0);
  LCD.SetCursor(0,0,0);
  LCD.Str("595 LCD 0",0);

  //Display 1
  LCD.Clear(1);
  LCD.SetCursor(0,0,1);
  LCD.Str("595 LCD 1",1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
