#include "WProgram.h"
#include "analogmuxdemux.h"

// parts adapted from elements at: http://tomekness.files.wordpress.com/2007/02/analog_multiplexer_demultiplexer_4051.pdf

AnalogMux::AnalogMux(int S0, int S1, int S2, int readpin){
  // constructor

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  
  _S0 = S0;
  _S1 = S1;
  _S2 = S2;
  
  _readpin = readpin; // don't need to set this as it's an analog pin
  
  _currentPin = 0;
}

void AnalogMux::SelectPin(int pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break

  _currentPin = pin;
  WriteSelectionPins(_S0, _S1, _S2, pin);

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


AnalogDeMux::AnalogDeMux(int S0, int S1, int S2, int writepin){

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  
  _S0 = S0;
  _S1 = S1;
  _S2 = S2;
  
  _writepin = writepin; // don't need to set this as it's an analog pin

}

void AnalogDeMux::SelectPin(int pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break

  _currentPin = pin;
  WriteSelectionPins(_S0, _S1, _S2, pin);

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
void WriteSelectionPins(int S0, int S1, int S2, int pin) {

  digitalWrite(S0, (pin & 0x01)); // set the lowest bit
  digitalWrite(S1, ((pin>>1) & 0x01)); // set the middle bit
  digitalWrite(S2, ((pin>>2) & 0x01)); // set the highest bit.

}
  

  
