/*
 * Advanced Arduino Boards, a course by Peter Dalmaris.
 * 
 * zero_usb_host_keyboard.ino
 * 
  This sketch demonstrates the USB host port on the Arduino Zero.
  Connect a wire to pin 7, and leave it unconnected. Then, connect 
  one USB cable to the programming port, and one to the native port.

  Upload the sketch to the Arduino Zero.

  When the upload finishes, open a text editor and click in the 
  text editor window to ensure that it can receive text from the 
  keyboard.

  Then, connect the wire from pin 7 to GND. The Zero will now start
  writting text to your text editor!

  Beware: if you click anywhere else, the text from the Arduino will
  start filling whatever window you clicked on, and the results
  could be dramatic!
 */

#include "Keyboard.h"

int button = 7;  // Use a button connected to this pin
                // to stop and start typing.

int counter = 0; // Use this counter to have something new 
                // to type

void setup() {
  
  pinMode(button , INPUT_PULLUP);   // set pin to input and
                                    //enable the pull up resistor

  // initialize control over the keyboard:
  Keyboard.begin();
  Keyboard.println("Hi, this is the Arduino typing!");
}

void loop() {
  if (digitalRead(button)==LOW){
    Keyboard.print("Line ");
    Keyboard.println(counter++);
    Keyboard.println(" ");
    delay(200);
  }
}

