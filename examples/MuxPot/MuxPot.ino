/**

Author: Andrew Fisher
Version: 0.1.1
Date: 1 April, 2013

History:
1 April 2013 - Small changes to bring into standard
22 September, 2012 - Andrew Fisher, First version

Uses the analog multiplexer library to read multiple potentiometers

This example uses 3 pots connected to 4051 inputs 0-2 which are then read
appropriately.
**/

#include "analogmuxdemux.h"

#define READPIN 0 // What analog input on the arduino do you want?

// how many input pins are you going to use on the Muxer, this example uses three
#define NO_PINS 3 

// set up the Muxer ready to be used. Watch the order of S0, S1 and S2. 
AnalogMux amux(4,3,2, READPIN);

void setup() {  
    Serial.begin(9600);
    Serial.println("Starting 4051 analog reader...");
    delay(1000);
}

void loop() {

    // go through each pin on the muxer in turn and just print out it's position
    // and it's reading then delay a bit and do the next one.
    for (int pinno=0; pinno < NO_PINS; pinno++){

        amux.SelectPin(pinno); // choose the pin you want to send signal to off the DeMux
        uint16_t reading = amux.AnalogRead();
        Serial.print("Pin: ");
        Serial.print(pinno);
        Serial.print(" Value: ");
        Serial.print(reading);
        Serial.print(" ");
    }

    Serial.println("-----");
    delay(5000);
}

