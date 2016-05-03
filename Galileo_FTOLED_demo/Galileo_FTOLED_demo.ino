
/*
 * 
 * Galileo_FTOLED_demo.ino
 * 
 * This sketch is used to demonstrate the use of the FTOLED
 * display with the Galileo Gen 2
 * 
 * Boot the Galileo using the full Yocto OS from the uSD card.
 * Connect the screen to the Galileo as per the setup instructions
 * at txplo.re/1TzBDnV
 */

#include <SPI.h>
#include <SD.h>
#include <FTOLED.h>
#include <fonts/SystemFont5x7.h>

const byte pin_cs = 7;
const byte pin_dc = 2;
const byte pin_reset = 3;

OLED oled(pin_cs, pin_dc, pin_reset);
OLED_TextBox box(oled);

void setup()
{
  oled.begin();

  // Fill the background with dark red (the values in the curly braces are {RED,GREEN,BLUE} )
  OLED_Colour background = {10,0,0};
  oled.fillScreen(background);

  // Horizontal blue line from (30,30) to (90,30)
  oled.drawLine(30,30,90,30,ROYALBLUE);

  // Diagonal black line across the screen
  oled.drawLine(0,127,127,0,BLACK);

  // Draw a filled circle and then an outline of a circle around it
  oled.drawFilledCircle(64,64,12,CYAN);
  oled.drawCircle(64,64,18,WHITE);

  // Draw a yellow box in the top-right
  oled.drawFilledBox(90,90,120,120,YELLOW);

  // With an outline of a violet box underneath it
  oled.drawBox(90,50,120,80,5,VIOLET);

    oled.selectFont(SystemFont5x7);
    box.print("Hello from Tech Explorations!");
}

void loop()
{
}
