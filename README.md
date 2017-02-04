# Analog MuxDemux library

This library is used in order to abstract away a few of the details to do with analog multiplexing and demultiplexing. It assumes the following:

- The multiplexer is analog and is compatible with the 4051 type (ie: 8 analog inputs or outputs, selected by setting HIGH/LOW on 3 digital input pins for 3 bit resolution and an input selection pin active LOW)

- At this point the library assumes that the IO selector is set high or low by an external method not related to this library. In most instances it's typical to set the component for either input or output not flipping back and forth. This will be resolved in a later version.

See: http://www.arduino.cc/playground/Learning/4051 for more details about the component itself and basic usage. (http://en.wikipedia.org/wiki/Multiplexer for general mux info)

## Installation

Download the latest library from it's github repository:

http://github.com/ajfisher/arduino-analog-multiplexer

Next, install the libary in your sketchbook libraries directory:

IE: wherever your sketchbook is (mine's in my home directory in Linux) then in your libraries folder (create it if you don't have it) drop in the analogmuxdemux folder with all files in it.

# Using the libary

In a sketch, you can now import the libary using the standard method:

    #include <analogmuxdemux.h>

Whether you multiplex or demultiplex the format for instantiating an object is the same. You create a new object of the relevant type and then you pass in the digital output pins that will be used to control which pin is selected on the IC. Alongside this is the pin you would like to use for reading or writing

## Multiplexer (for reading):

### Create a new instance

    AnalogMux amux(int S0, int S1, int S2, int arduino_analog_input);

eg: 

    AnalogMux amux(4, 3, 2, 0);

or 

    AnalogMux amux(int arduino_analog_input);

eg: 

    AnalogMux amux(0);

The first constructor type specifies the values for S0, S1, S2 on the 4051 however the second version assumes S0=4, S1=3, S2=2 for digital outs.

### Reading a specific pin from the IC

    int val = amux.AnalogRead(int pin_no);

analogRead() takes the number of the pin to read on the IC (between 0 and 7) and returns a value between 0 and 1023 based on the 8-bit resolution of the Arduino analog input pin. 

## Demultiplexer (for writing):

### Create a new instance

    AnalogDeMux demux(int S0, int S1, int S2, int arduino_analog_output);

eg: 

    AnalogDeMux demux(4, 3, 2, 11);

or

    AnalogDeMux demux(int arduino_analog_output);

eg: 

    AnalogDeMux demux(11);

The first constructor type specifies the values for S0, S1, S2 on the 4051 however the second version assumes S0=4, S1=3, S2=2 for digital outs.

Note that given you are using an ANALOG demux, you'd probably want to make sure you're using a PWM pin so you can use it.

### Writing a specific pin to the IC

    demux.AnalogWrite(int pin_no, int value);

analogWrite writes a value to the specified pin and can set a value beween 0 and 255 as per normal analog output.

## Setting the selection pin for read or write:

Sometimes you might want to set a particular pin on the multiplexer and leave it there for a while for some reason. In this instance you use the selectPin() function.

    amux.SelectPin(int pin);

You can then read or write from the multiplexer using simply:

    amux.AnalogRead(); 
    // or 
    demux.AnalogWrite(value);

With no pin specified. 

# Multiple multiplexers

At this stage this only works with Mux not DeMux. Honestly if you want to do this with DeMux you're probably better with a shift register.

Using daisy chained 4051s you can actually get a large number of analog inputs (up to 64) by setting the output of a "slave" 4051 to be the input of the "master" 4051 which in turn outputs the value to the arduino analog input.

To do this you need to sacrifice another 3 IO pins however from 2 to 8 slaves can all be run off the same 3 additional pins.

To make this work, plug your master into 2,3,4 per normal, connect all of the slaves' select lines to 5,6,7 and then using the consutructor that requires passing across the slave select lines as well.

    AnalogMux amx(4,3,2, 7,6,5, READPIN);

At this point it pretty much works as normal. Note that your master can't be addressed directly now, however you get to have up to 64 analog inputs.

# Examples
## Simple Demultiplexer (writing)

- example-write-schematic.fz (fritzing example)
- Demux LED (Arduino code example)

## Simple Multiplexer (reading)

- Mux Pot (Arduino code example)

## Multi Multiplexer (reading)

- Multi Muxer (Arduino Code example)

#TODO:

- Make MuxDemux class which each of the others inherits from to reduce code
- Write a Multi Demuxer example
- Make the code deal with switching between MUX and DEMUX on the fly
