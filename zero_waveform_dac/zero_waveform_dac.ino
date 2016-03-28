/*
 * Advanced Arduino Boards, a course by Peter Dalmaris.
 * 
  Simple Waveform generator with Arduino Zero

  Modified by Peter Dalmaris, from the original at arduino.cc.

  Set the osciloscope to 50mV vertical divisions and 20us horizontal divisions.

  You can create your own waveform tables using the sine wave form table generator at 
  http://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml,

  ...or Decaying Wave Look Up Table Generator at
  http://www.daycounter.com/Calculators/Decaying-Wave-Generator-Calculator.phtml

  ...or Triangle Wave Look Up Table Generator at
  http://www.daycounter.com/Calculators/Triangle-Wave-Generator-Calculator.phtml

 */

#include "Waveforms.h"

int i = 0;


void setup() {
  analogWriteResolution(10);  // set the analog output resolution to 10 bit (4096 levels)

}

void loop() {
  

  analogWrite(A0, waveformsTable[3][i]);  // write the selected waveform on A0

  i++;
  if(i == maxSamplesNum)  // Reset the counter to repeat the wave
    i = 0;

  delayMicroseconds(2);  // Hold the sample value for the sample time
}

