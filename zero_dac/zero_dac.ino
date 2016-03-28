/*
 * Advanced Arduino Boards, a course by Peter Dalmaris.
 * 
 * Demo sketch, play with the Arduino Zero DAC.

  Written by Peter Dalmaris
  
This sketch is used to play with the Arduino Zero DAC capabilities.
Connect an osciloscope to A0 and run the sketch.
Set the osciloscope to 100mV vertical divisions and 1s horizontal divisions,
and see how the DAC produces a nice triagonal waveform.

You can also use A1 as analog input at 12-bit resolution. Connect a potentiometer
and uncomment the first two code lines in the loop function to make this work.
You should also comment out the rest of the content in the loop function.
*/

int pwm_value = 0; 

void setup(){
  // make our digital pin an output
  pinMode(A1, INPUT);  
  analogWriteResolution(10);
  analogReadResolution(12);    //This is useful if you want to test the digital to 
                               //analog conversion
}

void loop(){
    //Connect a potentiometer to A1 and uncomment the next line to play around with
    //Analog to Digital conversion.
  analogWrite(A0, map(analogRead(A1), 0, 4096, 0 ,1023));
  delay(5);

// To view this waveform on the osciloscope, set it to 100mV vertical divisions
// and 500ms or 1s horizontal.
  
//  analogWrite(A0, 0);  //start with a low
//  delay(20);
//  //Write true analog values to Zero's A0 pin
//  for (pwm_value=0;pwm_value<1023;pwm_value++)  //This will create the upslope of the waveform
//  {
//    analogWrite(A0, pwm_value);
//    delay(2);
//  }
//  
//  for (pwm_value=1023;pwm_value>0;pwm_value--)  //This will create the downslope of the waveform
//  {
//    analogWrite(A0, pwm_value);
//    delay(2);
//  }
//
//
//  analogWrite(A0, 0); //finish with a low
//  delay(20);

}
