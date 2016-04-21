/*  due_mouse_demo
 * 
 *  Advanced Arduino Boards, course by Peter Dalmaris
 * 
 * This sketch demonstrates the operation of the Mouse class
 * with the Arduino Due
 * 
 * Upload to the Arduino Due, and connect a micro-USB cable to
 * the native USB port on the Due, and to the computer
 * Place your mouse pointer in the middle of the screen.
 * When the sketch starts, the cursor will move in a box
 * pattern on its own (controlled by the Arduino Due).
 * 
 */

#include "Mouse.h"

int responseDelay = 50;        // response delay of the mouse, in ms

int x_amount=0;
int y_amount=0;
int step = 0;

void setup() {
  Mouse.begin();
  Serial.begin(9600);
}

void loop() {

  

  if (step == 0)
    {x_amount = 0;
    y_amount = 5;
    }
  if (step == 100)
    {x_amount = 5;
    y_amount = 0;
    }  

    if (step == 200)
    {x_amount = 0;
    y_amount = -5;
    }

    if (step == 300)
    {x_amount = -5;
    y_amount = 0;
    }

    step++;
    
    if (step == 400)
    {step =0;
    x_amount = 0;
    y_amount = 0;
    }
  
      Mouse.move(x_amount, y_amount, 0);
      Serial.print(x_amount);
      Serial.print(",");
      Serial.println(y_amount);




  delay(responseDelay);
}





