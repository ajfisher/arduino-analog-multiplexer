#include "Arduino.h"
#include "analogmuxdemux.h"

// parts adapted from elements at: http://tomekness.files.wordpress.com/2007/02/analog_multiplexer_demultiplexer_4051.pdf

AnalogMux::AnalogMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t readpin){
  // Construct the AnalogMux object using the various digital pins
  // which are then set as part of this.

    SetupMaster(MS0, MS1, MS2, readpin);
}

AnalogMux::AnalogMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t SS0, uint8_t SS1, uint8_t SS2, uint8_t readpin){
    // constructor that sets up a master slave arrangement on the 4051s
    
    SetupMaster(MS0, MS1, MS2, readpin);
    
    // now set the additional pins and vars for the slave chips
    pinMode(SS0, OUTPUT);
    pinMode(SS1, OUTPUT);
    pinMode(SS2, OUTPUT);
    
    _SS0 = SS0;
    _SS1 = SS1;
    _SS2 = SS2;

    // now do the remainder
    /**_readpin = readpin; // don't need to set this as it's an analog pin
    _currentPin = 0;    **/
    _ms = true;
}

AnalogMux::AnalogMux(uint8_t readpin){
    // Alternative constructor which assumes the default digital pins
    // for set up and calls the main constructor with them.
    SetupMaster(AMDM_MS0, AMDM_MS1, AMDM_MS2, readpin);  
}

void AnalogMux::SetupMaster(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t readpin) {
    // reusable set up method for the master chip.
    
    pinMode(MS0, OUTPUT);
    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);

    _MS0 = MS0;
    _MS1 = MS1;
    _MS2 = MS2;

    _readpin = readpin; // don't need to set this as it's an analog pin

    _currentPin = 0;
    _ms = false;

}

void AnalogMux::SelectPin(uint8_t pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break

  _currentPin = pin;
  
    if (_ms) {
        // we need to consider multi mux arrangement

        // the master is the significant bit so it determines which
        // of the slave 4051s to route to, after that it's simply determining
        // which pin on the slave IC needs to be switched to and then do with
        // it what you will.        
        WriteSelectionPins(_MS0, _MS1, _MS2, (pin / 8));
        WriteSelectionPins(_SS0, _SS1, _SS2, (pin % 8));
    } else {
        WriteSelectionPins(_MS0, _MS1, _MS2, pin);
    }
}

uint16_t AnalogMux::AnalogRead() {
  // this method reads the currently selected pin and returns the value
  return analogRead(_readpin);
  
}
uint16_t AnalogMux::AnalogRead(uint8_t pin) {
  // this method calculates which pin to read, switches to it and then returns
  // the currently value
  SelectPin(pin);
  return AnalogMux::AnalogRead();
}


AnalogDeMux::AnalogDeMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t writepin){

  pinMode(MS0, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  
  _MS0 = MS0;
  _MS1 = MS1;
  _MS2 = MS2;
  
  _writepin = writepin; // don't need to set this as it's an analog pin

}

AnalogDeMux::AnalogDeMux(uint8_t writepin){
    // Alternative constructor which assumes the default digital pins
    // for set up and calls the main constructor with them.
    AnalogDeMux(AMDM_MS0, AMDM_MS1, AMDM_MS2, writepin);
    
}


void AnalogDeMux::SelectPin(uint8_t pin) {
  // sets the required pin on using selection pins
  // there is no error checking on this so if you go over 7 it will break

  _currentPin = pin;
  WriteSelectionPins(_MS0, _MS1, _MS2, pin);

}

void AnalogDeMux::AnalogWrite(uint8_t value) {
  // writes the value to the pin currently used for output - no checking
  // for correctness on this
  analogWrite(_writepin, value);
}

void AnalogDeMux::AnalogWrite(uint8_t wpin, uint8_t value) {
  // write the value to the specified pin - no checking for correctness of this
  SelectPin(wpin);
  AnalogDeMux::AnalogWrite(value);
}
  

// helper functions
void WriteSelectionPins(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t pin) {

  digitalWrite(S0, (pin & 0x01)); // set the lowest bit
  digitalWrite(S1, ((pin>>1) & 0x01)); // set the middle bit
  digitalWrite(S2, ((pin>>2) & 0x01)); // set the highest bit.

}

