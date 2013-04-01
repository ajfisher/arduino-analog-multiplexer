/**

Author: Andrew Fisher
Version: 0.1.1
Date: 1 April, 2013

History:
1 April 2013 - Minor changes to bring into standard form.
23 September, 2012 - Andrew Fisher, First version

Uses the analog multiplexer library to read multiple potentiometers off multiple
4051 chips that are daisy chained together

To use this code wire up a minimum of 3x4051 in a master slave arrangement. IE:

Master 4051 is connected to the arduino with output pin to Arduino Analog 0

Slave 4051s then have each of their output pins connected to the master's analog pins

for a maximum of 64 input channels.

**/

#include "analogmuxdemux.h"


#define READPIN 0 // What analog input on the arduino do you want?

// how many input pins are you going to use on the Muxer, this example uses
// three
#define NO_PINS 16


// set up the DeMux ready to be used. Watch the order of S0, S1 and S2. 

// master selects
#define M_S0 4
#define M_S1 3
#define M_S2 2
// slave selects
#define S_S0 7
#define S_S1 6
#define S_S2 5
AnalogMux amx(M_S0,M_S1,M_S2, S_S0,S_S1,S_S2, READPIN);

void setup() {  
    Serial.begin(9600);
    Serial.println("Starting 4051 analog reader...");
    delay(1000);
}

void loop() {

  // go through each pin on the muxer in turn and just print out it's pin number
  // and it's reading then wait a bit and do it again
    
    for (int pinno=0; pinno< NO_PINS; pinno++) {
        amx.SelectPin(pinno);
        uint16_t reading = amx.AnalogRead();
        Serial.print("Pin: ");
        Serial.print(pinno);
        Serial.print(" Value: ");
        Serial.print(reading);
        Serial.println();             
    }

    Serial.println("---");
    delay(5000);
}

