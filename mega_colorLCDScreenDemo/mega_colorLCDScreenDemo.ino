/*
  TestPattern - An example sketch for the Color LCD Shield Library
  by: Jim Lindblom
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute. Let me know if you make hugely, awesome, great changes.

  This sketch has example usage of the Color LCD Shield's three
  buttons. It also shows how to use the setRect and contrast
  functions.
  
  Hit S1 to increase the contrast, S2 decreases the contrast, and
  S3 sets the contrast back to the middle.
*/
#include <ColorLCDShield.h>

LCDShield lcd;

byte cont = 40;  // Good center value for contrast
int counter = 0;

void setup()
{
  Serial.begin(9600);
  analogWrite(10, 1023); //PWM control blacklight
  lcd.init(PHILLIPS);  // Initialize the LCD, try using PHILLIPS if it's not working
  lcd.contrast(cont);  // Initialize contrast
  lcd.clear(WHITE);  // Set background to white
  tech_explorations();  // Print the Tech Explorations name and lines
}

void loop()
{
  char buf [5];
  sprintf (buf, "%04i", counter);

  lcd.setStr( buf, 70,50, RED, YELLOW); 
  Serial.print(counter);
  Serial.print(" - ");
  Serial.println(buf);
  counter++;
  delay(1000);  // Delay to give each button press a little more meaning
}

void tech_explorations()
{
  lcd.setStr("Tech", 10, 10, RED, WHITE);
  lcd.setStr("Explorations", 30, 10, BLUE, WHITE);
  lcd.setLine(9, 9, 9, 115, MAGENTA);
  lcd.setLine(9, 9, 50, 9, MAGENTA);
  lcd.setLine(50, 9, 50, 115, MAGENTA);
  lcd.setLine(9, 115, 50, 115, MAGENTA);
}

