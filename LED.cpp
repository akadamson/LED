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

#include "LED.h"

LED::LED(uint8_t ledPin, LedStates _state) :
  pin(ledPin),
  state(_state) {
	pinMode(this->pin, OUTPUT);
}

void LED::on(void) {
  if (this->state == OFF) {
	  digitalWrite(pin, HIGH);
	  this->state = ON;
	}
}

void LED::off(void) {
  if (this->state == ON) {
	  digitalWrite(pin, LOW);
	  this->state = OFF;
	}
}
	
BlinkLED::BlinkLED(uint8_t _ledpin, unsigned long _interval, byte _times) :
  LED(_ledpin),
  interval(_interval),
  blinkCount(_times),
  blinkNum(0),
  pauseCount(10),
  pauseNum(0),
  pattern(0),
  numBits(0),
  bitPosition(8),
  runState(_times == 99 ? PAUSE : COUNTDN),
  lastTime(0) {
}

void BlinkLED::run(unsigned long _currentTime) {
  if (_currentTime > this->lastTime + interval) {                     // do not block, if not time
    switch (this->runState) {                                         // switch on getRunState
      case ON:
        this->on();
        break;
      case OFF:
        this->off();
        break;
      case REPEAT:
        this->pauseCount = 0;
      case REPEATCTDN:
        if (this->blinkNum == 0) {                                    // if blinkCount has gone to zero
          this->off();                                                // make sure were are off
          if (++this->pauseNum < this->pauseCount)                    // do a pause in the repeat
            break;                                                    // skip a cycle
          else {                                                      // pause over
            this->pauseNum = 0;                                       // clear the pause
            this->blinkNum = this->blinkCount;                        // reload the blinkCount
          }
        }
      case COUNTDN:
        if (this->blinkNum > 0) {
          if (this->pattern) {                                        // is there a blink pattern set
            if (this->pattern & (1 << --this->bitPosition))           // shift left and &
              this->on();                                             // if bit was set turn on
            else 
              this->off();                                            // if bit was not set turn off
            if (this->bitPosition == 0) {                             // check to see if we are at the end
              this->bitPosition = this->numBits;                      // reload if we are
              if(this->runState == COUNTDN || this->runState == REPEATCTDN)                      // check for COUNTDN
                this->blinkNum--;                                     // if so decrement blinkCount
            }
          } else {                                                    // not a custom pattern
            toggle();                                                 // so toggle
            if ((this->runState == COUNTDN || this->runState == REPEATCTDN) && this->getState() == ON) // check for COUNTDN AND LED On
              this->blinkNum--;                                       // if so decrement blinkCount
          } 
        } else                                                        // blinkCount is equal zero
          this->off();                                                // when done make sure to turn it off
        break;
      case PAUSE:
        break;
      default:
        break;
    }
    this->lastTime = _currentTime;                                    // set time to currentTime
  }
}
/*
void BlinkLED::setRunState(RunState _state) {
   this->runState = _state;
} ;
*/

void BlinkLED::pause(void) { 
  if(this->runState != PAUSE) {
    this->saveState = this->runState;
    this->runState = PAUSE;
  }
}


void BlinkLED::setOn(void) {
  if (this->runState != PAUSE && this->runState != ON) {
    if (this->runState != OFF)
      this->saveState = this->runState;
    this->runState = (RunState)ON;
  }
}

void BlinkLED::setOff(void) {
  if (this->runState != PAUSE && this->runState != OFF)  {
    if (this->runState != ON)
      this->saveState = this->runState;
    this->runState = (RunState)OFF;
  }
}

void BlinkLED::setCountDown(byte _times, RunState _state) {
  this->blinkCount = _times; 
  if(_state != REPEATCTDN)
    this->blinkNum = _times;
  this->runState = _state;
}

void BlinkLED::resume(void) {
  if (this->runState != this->saveState) {
    this->runState = saveState;
    switch(this->runState) {
      case REPEATCTDN:
        this->pauseNum = 0;
        this->blinkNum = 0;
        break;
      case COUNTDN:
        this->blinkNum = this->blinkCount;
        break;
      default:
        break;
    }
  }
};

void BlinkLED::setPattern(unsigned int _pattern, byte _numBits) {
  pattern = _pattern;
  numBits = _numBits;
}

/*
|| @changelog
|| | 2011-04-11 - Alan Adamson : Initial Release
|| #
*/