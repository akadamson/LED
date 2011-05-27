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

#ifndef LED_H
#define LED_H

#include "WProgram.h" 

     enum RunState {
      REPEAT = 2,
      PAUSE = 3,
      COUNTDN = 4,
      REPEATCTDN = 5
    };

class LED {
  public:
     enum LedStates {
      OFF = 0,
      ON = 1
    };

    LED(uint8_t ledPin, LedStates _state = OFF);
  	inline bool getState(void) { return state; };
    void on(void);
  	void off(void);
  	inline void toggle(void) { (state == ON) ? off() : on(); };

  private:
  	LedStates state;
  	uint8_t pin;
};

class BlinkLED : public LED {
  public:

    BlinkLED(uint8_t _ledpin, unsigned long _interval = 1000000, byte _times = 99);
    inline unsigned long getInterval(void) { return this->interval; };
    inline void setInterval(unsigned long _interval) { this->interval = _interval; };
    inline RunState getRunState(void) { return this->runState; };
    inline void setRunState(RunState _state) { this->runState = _state;} ;
    void setCountDown(byte _times, RunState _state = COUNTDN);
//    inline void setCountDown(byte _times) { this->blinkCount = _times; this->state = COUNTDN; };
    void setPattern(unsigned int _pattern, byte _numBits = 16);
    void pause(void);
    void resume(void);
    virtual void run(unsigned long _currentTime);
    void setOn(void);
    void setOff(void);

  private:
    unsigned long lastTime;
    unsigned long interval;
    byte blinkCount;
    byte blinkNum;
    byte pauseCount;
    byte pauseNum;
    RunState runState; 
    RunState saveState; 
    byte pattern;
    byte numBits;
    byte bitPosition; 
  
};

//class SequencedLED : public BlinkLED {
//};

#endif

/*
|| @changelog
|| | 2011-04-11 - Alan Adamson : Initial Release
|| #
*/