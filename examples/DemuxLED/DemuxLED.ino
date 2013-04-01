/**

Author: Andrew Fisher
Version: 0.1.3
Date: 1 April, 2013

History:
1 April, 2013 - Minor updates to standardise the code.
23 September, 2012 - Updates for the change to Demuxer arrangement
22 September, 2012 - Andrew Fisher, Updates to Arduino 1.0
May 1, 2011 - Andrew Fisher, Original

Uses the analog multiplexer library to control some LEDs

See the fritzing circuit in the code library for set up.
**/

#include "analogmuxdemux.h"

#define WRITEPIN 6 // connect to a PWM pin in order to be able to output an analog signal
#define NO_PINS 3 // how many output pins are you going to use on the DeMux? This exmample uses 3.

// set up the DeMux ready to be used. Watch the order of S0, S1 and S2. 
AnalogDeMux admux(4,3,2, WRITEPIN);

void setup() {  
  pinMode(WRITEPIN, OUTPUT);
  delay(1000);
}

void loop() {
  
  // go through each pin in turn and then just light it up like a dimmer
  for (int pinno=0; pinno < NO_PINS; pinno++){
    
    admux.SelectPin(pinno); // choose the pin you want to send signal to off the DeMux
    for (int i=0; i<255; i++){
      admux.AnalogWrite(i); // simply pass an analog value as per normal.
      delay(10);
    }
    for (int i=255; i>=0; i--) {
      admux.AnalogWrite(pinno, i); // different way of using analogWrite specifying pin
      delay(10);
    }
  }
}

