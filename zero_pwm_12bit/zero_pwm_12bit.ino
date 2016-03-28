/*  zero_pwm_pin_12bits
 * 
 *  Advanced Arduino Boards, course by Peter Dalmaris
 * 
 * This sketch demonstrates the ability of the Arduino Zero to
 * create a PWM signal set to 12-bit resolution.
 * 
 * Connect an osciloscope to pin 11 and set it to 100mV horizontal and
 * 2us vertical divisions.
 * 
 */

int pwm_value = 0; 

void setup(){
  pinMode(11, OUTPUT);
  analogWriteResolution(12);  //Set the pwm resolution to 10 bits
                              //This is the maximum supported by the Zero
}

void loop(){
 
  for (pwm_value=0;pwm_value<4096;pwm_value++)
  { 
    analogWrite(11, pwm_value);  
    delay(5);
  }

  for (pwm_value=4095;pwm_value>=0;pwm_value--)
  { 
    analogWrite(11, pwm_value);  
    delay(5);
  }
}
