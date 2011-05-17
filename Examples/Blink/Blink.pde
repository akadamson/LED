/*
||
|| @file LED.cpp
|| @version 1.0
|| @author Alan Adamson
|| @contact adamson_alan@hotmail.com
||
|| @description
|| | Provide an easy way of making LEDs
|| #
||
|| @license
|| | Copyright (c) 2011 Alan Adamson. All rights reserved.
|| | This code is subject to GNU General Public License, version 3 (GPLv3)
|| | http://www.opensource.org/licenses/gpl-3.0
|| #
||
*/

#include <LED.h>

// create your standard LED
// give it the pin number attached to the LED in question
// see blocking blink in loop below
// LED methods on, off, toggle, getState
// LED led(13);

// create your standard blinking LED
// git it a pin number or alternately, you can give it a pin and blink rate
// BlinkLED led(13,500); // with blink rate
// BlinkLED can have run states of
//   REPEAT - continually do some blink pattern
//   PAUSED - pause what it's doing, note it doesn not save the state or restore it
//   RUNNING - blink is running
//   STOPPED - similar to pause, but for future enhancement
//   COUNTDN - do the blink n number of times and then stop
// BlinkLED methods all above, get,set interval, get,set RunState
// BlinkLED methods setCountDown, setPattern, pause, resume, 
// BlinkLED processLED
BlinkLED led(13); // default blink rate of 1second
// BlinkLED led(13, 500); // change the default blink rate
// BlinkLED led(13, 500, 5); // create a 500ms blinker that runs 5 time.

void setup() {
  Serial.begin(115200);
  led.setInterval(150000); // change to 300ms blink rate
//  led.setPattern(0b10101100, 8); 
//  led.setCountDown(8);
//  led.setCountDown(4, REPEATCTDN);
  //
//  led.setRunState(REPEAT);

}

unsigned long currentTime, deltaTime;
unsigned long previousTime = 0;
int frameCounter = 0;
int i = 0;
int j = 0;
int k = 0;

void loop() {
  currentTime = micros();
  deltaTime = currentTime - previousTime;
  
  // Main scheduler loop set for 200hz
  if (deltaTime >= 5000) {    

    frameCounter++;
    
    // 1Hz loop timer for debugging info
    if(frameCounter % 200 == 0) {
      Serial.println(i, DEC);
      if(i++ == 10)
        led.setOn();
      if(i == 20)
        led.resume();
      if(i == 30)
        led.setOn();
      if(i == 40)
        led.setOff();
    }
   
    led.run(currentTime);
    previousTime = currentTime;
  }
  if (frameCounter >= 200) 
      frameCounter = 0;
 
}
