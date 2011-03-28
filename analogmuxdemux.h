#ifndef AnalogMuxDeMux_h
#define AnalogMuxDeMux_h


#include "WProgram.h"

class AnalogMux
{
    public:
      AnalogMux(int S0, int S1, int S2, int readpin);
      int analogRead(int pin);
      int analogRead();
      void selectPin(int pin);
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
      void analogWrite(int value);
      void analogWrite(int pin, int value);
      void selectPin(int pin);
    
    private:
      int _writepin; // which input pin is being used by the arduino to write state
      int _S0; // MSB selector
      int _S1; // Centre bit selector
      int _S2; // LSB selector
      int _currentPin; // which pin on the multiplexer are we looking at.
};


#endif

