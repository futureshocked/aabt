//This sketch provides an example on using the DAC on the Arduino Zero.
//It was used in a video tutorial on the ForceTronics YouTube Channel.
//This code is free and open for anybody to use and modify at their own risk

void setup()
{
  Serial.begin(57600); //start serial communication
  analogWriteResolution(10); //set the Arduino DAC for 10 bits of resolution (max)
  analogReadResolution(12); //set the ADC resolution to 12 bits, default is 10
  
  //Get user entered voltage, convert to DAC value, output DAC value
//  analogWrite(A0,setDAC(getVoltValue()));
analogWrite(A0,1023);
}

void loop()
{
  delay(2000);
  Serial.println();
  Serial.print("Measured voltage value is ");
  Serial.println(convertToVolt(analogRead(A1))); //Read value at ADC pin A1 and print it

}

//this function converts a user entered voltage value into a 10 bit DAC value 
int setDAC(float volt) {
 //formula for calculating DAC output voltage Vdac = (dVal / 1023)*3.3V
 return (int)((volt*1023)/3.3);
}

//this function gets the user entered DAC voltage value from serial monitor
float getVoltValue() {
 float v = 0; //variable to store voltage 
 Serial.println("Enter the voltage you want the DAC to output (range 0V to 3.3V)");
 v = readParameter();
 if (v < 0 || v > 3.3) v = 0; //check to make sure it is between 0 and 3.3V
 Serial.print("DAC voltage set to ");
 Serial.println(v);
 Serial.println("Outputting DAC value........");
 return v;
}

//waits for serial data and reads it in. This function reads in the parameters
// that are entered into the serial terminal
float readParameter() {
 while(!Serial.available()); //Wait for user to enter setting
 return Serial.parseFloat(); //get int that was entered on Serial monitor
}

//This function takes and ADC integer value (0 to 4095) and turns it into a voltage level. The input is the measured 12 bit ADC value.
float convertToVolt(int aVAL) {
 return (((float)aVAL/4095)*3.3); //formula to convert ADC value to voltage reading
}
