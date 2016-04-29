/*
 * 
 * Galileo_LCD_I2C_Hello.ino
 * 
 * This sketch is used to demonstrate some how data can be
 * exchanged between the Linux side and the Arduino side
 * of the Arduino Galileo Gen 2.
 * 
 * Boot the Galileo using the full Yocto OS from the uSD card.
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello from Tech");
  lcd.setCursor(0,1);
  lcd.print("Explorations!");
}


void loop()
{
}
