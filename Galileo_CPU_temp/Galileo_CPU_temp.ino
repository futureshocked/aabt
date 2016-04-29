/*
 * 
 * Galileo_CPU_temp.ino
 * 
 * This sketch is used to demonstrate some how data can be
 * exchanged between the Linux side and the Arduino side
 * of the Arduino Galileo Gen 2.
 * 
 * Boot the Galileo using the full Yocto OS from the uSD card.
 */
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  system("echo $((`cat /sys/class/thermal/thermal_zone0/temp` / 1000)) > /home/root/temp.txt");
   FILE *temp;
  temp = fopen("/home/root/temp.txt","r");
  char temperature[3];
  fgets(temperature,3,temp);
  fclose(temp);

  Serial.println(temperature);
  delay(1000);
  
}
