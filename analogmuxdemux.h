#ifndef AnalogMuxDeMux_h
#define AnalogMuxDeMux_h


#include "Arduino.h"

#define AMDM_MS0 4
#define AMDM_MS1 3
#define AMDM_MS2 2

class AnalogMux
{
    public:
      AnalogMux(int MS0, int MS1, int MS2, int readpin);
      AnalogMux(int MS0, int MS1, int MS2, int SS0, int SS1, int SS2, int readpin);
      AnalogMux(int readpin);
      int AnalogRead(int pin);
      int AnalogRead();
      void SelectPin(int pin);
    private:
      int _readpin; // which input pin is being used by the arduino to read state
      int _MS0; // MSB selector
      int _MS1; // Centre bit selector
      int _MS2; // LSB selector
      int _currentPin; // which pin on the multiplexer are we looking at.
};


class AnalogDeMux
{
    public:
      AnalogDeMux(int MS0, int MS1, int MS2, int writepin);
      AnalogDeMux(int writepin);
      void AnalogWrite(int value);
      void AnalogWrite(int wpin, int value);
      void SelectPin(int pin);
    
    private:
      int _writepin; // which input pin is being used by the arduino to write state
      int _MS0; // MSB selector
      int _MS1; // Centre bit selector
      int _MS2; // LSB selector
      int _currentPin; // which pin on the multiplexer are we looking at.
};

void WriteSelectionPins(int MS0, int MS1, int MS2, int pin);

#endif

