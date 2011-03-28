#include "WProgram.h"
#include "analogmuxdemux.h"

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

void AnalogMux::selectPin(int pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break


}

int AnalogMux::analogRead() {
  // this method reads the currently selected pin and returns the value
  
  return 0;
  
}
int AnalogMux::analogRead(int pin) {
  // this method calculates which pin to read, switches to it and then returns
  // the currently value
  
  return 0;
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

void AnalogDeMux::selectPin(int pin) {
  // sets the required pin on using selection pins
  // there is no error checking if you go over 7 it will break
}

void AnalogDeMux::analogWrite(int value) {
  // writes the value to the pin currently used for output
  
}

void AnalogDeMux::analogWrite(int pin, int value) {
  // write the value to the specified pin
}
  
  
  
  
  
