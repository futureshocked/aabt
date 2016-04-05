import processing.serial.*;

import cc.arduino.*;

int end = 10;    // the number 10 is ASCII for linefeed (end of serial.println), later we will look for this to break up individual messages
String serial;   // declare a new string called 'serial' . A string is a sequence of characters (data type know as "char")
Serial port;  // The serial port, this is a new instance of the Serial class (an Object)


void setup() {

  size(200,200);
  port = new Serial(this, Serial.list()[5], 9600); // initializing the object by assigning a port and baud rate (must match that of Arduino)
  port.clear();  // function from serial library that throws out the first reading, in case we started reading in the middle of a string from Arduino
  serial = port.readStringUntil(end); // function that reads the string from serial port until a println and then assigns string to our string variable (called 'serial')
  serial = null; // initially, the string will be null (empty)
  
  rectMode(CENTER);
}


  
  void draw() {
  while (port.available() > 0) { //as long as there is data coming from serial port, read it and store it 
    serial = port.readStringUntil(end);
  }
    if (serial != null) {  //if the string is not empty, print the following
    
    /*  Note: the split function used below is not necessary if sending only a single variable. However, it is useful for parsing (separating) messages when
        reading from multiple inputs in Arduino. Below is example code for an Arduino sketch
    */
      background(#EBF2BF);
      String[] a = split(serial, ',');  //a new array (called 'a') that stores values into separate cells (separated by commas specified in your Arduino program)
      print(a[0]); //print Value1 (in cell 1 of Array - remember that arrays are zero-indexed)
      print(",");
      print(a[1]); //print Value2 value
      print(",");
      println(a[2]); //print Value2 value
      
      fill(#FF003C);
      rect(width*0.2,width*0.5,width*0.25,(Float.parseFloat(a[0]))*0.5*height);
      fill(#BCFF00);
      rect(width*0.5,width*0.5,width*0.25,(Float.parseFloat(a[1]))*0.5*height);
      fill(#00EEFF);
      rect(width*0.8,width*0.5,width*0.25,(Float.parseFloat(a[2]))*0.5*height);
      
      fill(0);
      textSize(20);
      text("X", width*0.1, width*0.5);
      text("Y", width*0.45, width*0.5);
      text("Z", width*0.75, width*0.5);
      
      if (Float.parseFloat(a[0]) > 0.5)  //If X-axis exeeds 0.5, light up the LED
        port.write('1');
      
    }
}