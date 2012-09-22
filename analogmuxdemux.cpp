#include "Arduino.h"
#include "analogmuxdemux.h"

// parts adapted from elements at: http://tomekness.files.wordpress.com/2007/02/analog_multiplexer_demultiplexer_4051.pdf

AnalogMux::AnalogMux(int MS0, int MS1, int MS2, int readpin){
  // Construct the AnalogMux object using the various digital pins
  // which are then set as part of this.

  pinMode(MS0, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  
  _MS0 = MS0;
  _MS1 = MS1;
  _MS2 = MS2;
  
  _readpin = readpin; // don't need to set this as it's an analog pin
  
  _currentPin = 0;
}

AnalogMux::AnalogMux(int readpin){
    // Alternative constructor which assumes the default digital pins
    // for set up and calls the main constructor with them.
    AnalogMux::AnalogMux(AMDM_MS0, AMDM_MS1, AMDM_MS2, readpin);
    
}

void AnalogMux::SelectPin(int pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break

  _currentPin = pin;
  WriteSelectionPins(_MS0, _MS1, _MS2, pin);

}

int AnalogMux::AnalogRead() {
  // this method reads the currently selected pin and returns the value
  return analogRead(_readpin);
  
}
int AnalogMux::AnalogRead(int pin) {
  // this method calculates which pin to read, switches to it and then returns
  // the currently value
  SelectPin(pin);
  return AnalogMux::AnalogRead();
}


AnalogDeMux::AnalogDeMux(int MS0, int MS1, int MS2, int writepin){

  pinMode(MS0, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  
  _MS0 = MS0;
  _MS1 = MS1;
  _MS2 = MS2;
  
  _writepin = writepin; // don't need to set this as it's an analog pin

}

AnalogDeMux::AnalogDeMux(int writepin){
    // Alternative constructor which assumes the default digital pins
    // for set up and calls the main constructor with them.
    AnalogDeMux::AnalogDeMux(AMDM_MS0, AMDM_MS1, AMDM_MS2, writepin);
    
}


void AnalogDeMux::SelectPin(int pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break

  _currentPin = pin;
  WriteSelectionPins(_MS0, _MS1, _MS2, pin);

}

void AnalogDeMux::AnalogWrite(int value) {
  // writes the value to the pin currently used for output - no checking
  // for correctness on this
  analogWrite(_writepin, value);
}

void AnalogDeMux::AnalogWrite(int wpin, int value) {
  // write the value to the specified pin - no checking for correctness of this
  SelectPin(wpin);
  AnalogDeMux::AnalogWrite(value);
}
  

// helper functions
void WriteSelectionPins(int MS0, int MS1, int MS2, int pin) {

  digitalWrite(MS0, (pin & 0x01)); // set the lowest bit
  digitalWrite(MS1, ((pin>>1) & 0x01)); // set the middle bit
  digitalWrite(MS2, ((pin>>2) & 0x01)); // set the highest bit.

}

