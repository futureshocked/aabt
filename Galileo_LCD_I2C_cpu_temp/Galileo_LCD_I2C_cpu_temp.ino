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
