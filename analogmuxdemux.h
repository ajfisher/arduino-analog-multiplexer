#ifndef AnalogMuxDeMux_h
#define AnalogMuxDeMux_h


#include "Arduino.h"

#define AMDM_MS0 4
#define AMDM_MS1 3
#define AMDM_MS2 2

#define AMDM_SS0 7
#define AMDM_SS1 6
#define AMDM_SS2 5

class AnalogMux
{
    public:
        AnalogMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t readpin);
        AnalogMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t SS0, uint8_t SS1, uint8_t SS2, uint8_t readpin);
        AnalogMux(uint8_t readpin);
        uint16_t AnalogRead(uint8_t pin);
        uint16_t AnalogRead();
        void SelectPin(uint8_t pin);
    private:
        void SetupMaster(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t readpin);

        uint8_t   _readpin; // which input pin is being used by the arduino to read state
        uint8_t   _MS0;   // MSB selector for the master controller
        uint8_t   _MS1;   // Centre bit selector for the master controller
        uint8_t   _MS2;   // LSB selector for the master controller
        uint8_t   _SS0;   // MSB selector for the slave controller
        uint8_t   _SS1;   // Centre bit selector for the slave controller
        uint8_t   _SS2;   // LSB selector for the slave controller
        uint8_t   _currentPin; // which pin on the multiplexer are we looking at.
        bool  _ms;    // are we a master slave arrangement
};


class AnalogDeMux
{
    public:
      AnalogDeMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t writepin);
      AnalogDeMux(uint8_t MS0, uint8_t MS1, uint8_t MS2, uint8_t SS0, uint8_t SS1, uint8_t SS2, uint8_t writepin);
      AnalogDeMux(uint8_t writepin);
      void AnalogWrite(uint8_t value);
      void AnalogWrite(uint8_t wpin, uint8_t value);
      void SelectPin(uint8_t pin);
    
    private:
      uint8_t _writepin; // which input pin is being used by the arduino to write state
      uint8_t _MS0; // MSB selector for the master controller
      uint8_t _MS1; // Centre bit selector for the master controller
      uint8_t _MS2; // LSB selector for the master controller
      uint8_t _SS0; // MSB selector for the slave controller
      uint8_t _SS1; // Centre bit selector for the slave controller
      uint8_t _SS2; // LSB selector for the slave controller
      uint8_t _currentPin; // which pin on the multiplexer are we looking at.
};

void WriteSelectionPins(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t pin);

#endif

