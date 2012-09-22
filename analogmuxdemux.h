#ifndef AnalogMuxDeMux_h
#define AnalogMuxDeMux_h


#include "Arduino.h"

#define AMDM_S0 2
#define AMDM_S1 3
#define AMDM_S2 4

class AnalogMux
{
    public:
      AnalogMux(int S0, int S1, int S2, int readpin);
      AnalogMux(int readpin);
      int AnalogRead(int pin);
      int AnalogRead();
      void SelectPin(int pin);
    private:
      int _readpin; // which input pin is being used by the arduino to read state
      int _S0; // MSB selector
      int _S1; // Centre bit selector
      int _S2; // LSB selector
      int _currentPin; // which pin on the multiplexer are we looking at.
};


class AnalogDeMux
{
    public:
      AnalogDeMux(int S0, int S1, int S2, int writepin);
      AnalogDeMux(int writepin);
      void AnalogWrite(int value);
      void AnalogWrite(int wpin, int value);
      void SelectPin(int pin);
    
    private:
      int _writepin; // which input pin is being used by the arduino to write state
      int _S0; // MSB selector
      int _S1; // Centre bit selector
      int _S2; // LSB selector
      int _currentPin; // which pin on the multiplexer are we looking at.
};

void WriteSelectionPins(int S0, int S1, int S2, int pin);

#endif

