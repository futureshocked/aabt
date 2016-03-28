/*
  AnalogReadSerialPWM
  Reads an analog input on pin 0, prints the result to the serial monitor and map it to the 9 PWM pin.

 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  analogWrite(9, map(sensorValue, 0, 1023, 0, 255));
  delay(1);        // delay in between reads for stability
}
