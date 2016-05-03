/*
 * 
 * ZeroDebuggingExample.ino
 * 
 * This sketch is used to demonstrate some aspects of
 * debugging an Arduino sketch using the AtmelStudio package.
 * 
 * Connect one LED to pin 3 and one LED to pin 4.
 * The LEDs will start blinking.
 * When that happens, you can start the debugger.
 */


int led1            = 3;
int led2            = 4; 
int counter         = 0;
int delay_duration1  = 500;
int delay_duration2  = 100;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  counter += 1;
  Serial.println(counter%2);
  if (counter%2 == 0)
  {
    digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(delay_duration1);              // wait for a second
    digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
    delay(delay_duration1);              // wait for a second
  }

  if (counter%2 == 1)
  {
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(delay_duration1);              // wait for a second
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
    delay(delay_duration1);              // wait for a second
  }

  if (counter%5 == 0)
  {
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led1, HIGH);
    delay(delay_duration1);              // wait for a second
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(led1, LOW); 
    delay(delay_duration1);              // wait for a second
  }

  delay(delay_duration2);
}
