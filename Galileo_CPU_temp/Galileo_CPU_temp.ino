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
