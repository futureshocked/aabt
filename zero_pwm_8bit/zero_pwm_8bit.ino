/*  zero_pwm_pin_8bits
 * 
 *  Advanced Arduino Boards, course by Peter Dalmaris
 * 
 * This sketch demonstrates the ability of the Arduino Zero to
 * create a PWM signal set to 8-bit resolution.
 * 
 * Connect an osciloscope to pin 11 and set it to 100mV horizontal and
 * 2us vertical divisions.
 * 
 */

int pwm_value = 0; 

void setup(){
  pinMode(11, OUTPUT);
  analogWriteResolution(8);
}

void loop(){

  for (pwm_value=0;pwm_value<255;pwm_value++)
  { 
    //The map function is used to convert the 
    analogWrite(11, pwm_value); 
    delay(5);
  }

  for (pwm_value=254;pwm_value>=0;pwm_value--)
  { 
    analogWrite(11, pwm_value); 
    delay(5);
  }

}
