/*
 * 
 * Galileo_LCD_I2C_cpu_temp.ino
 * 
 * This sketch is used to demonstrate some how data can be
 * exchanged between the Linux side and the Arduino side
 * of the Arduino Galileo Gen 2.
 * 
 * The sketch also shows how a common 16x2 LCD screen can 
 * be used with the Galileo.
 * 
 * Boot the Galileo using the full Yocto OS from the uSD card.
 * Connect and LCD screen via the I2C backpack. The wirings are:
 *
 * Backpack  |  Arduino
 * --------------------
 *     GND   |   GND
 *     Vcc   |   5V
 *     SDA   |   A4
 *     SCL   |   A5
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

}


void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CPU Temp:");
  lcd.setCursor(0,1);
  system("echo $((`cat /sys/class/thermal/thermal_zone0/temp` / 1000)) > /dev/ttyGS0"); //This will print the CPU temperature to the serial port (open the serial monitor!)
  system("echo $((`cat /sys/class/thermal/thermal_zone0/temp` / 1000)) > /home/root/temp.txt");
  FILE *temp;
  temp = fopen("/home/root/temp.txt","r");
  char temperature[3];
  fgets(temperature,3,temp);
  fclose(temp);
  lcd.print(temperature[0]);
  lcd.print(temperature[1]);
  
  delay(1000);
}
