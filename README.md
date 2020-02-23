# Serial Communication

A simple C library to provide an API for serial communication.

## Usage

The library provides an abstraction layer between the serial device and the program. The connection is established over the path to the device (e.g. `/dev/ttyACM0`). Raw bytes can be read from and written to the serial port using the available functions. The serial connection baud rate can be defined by the user. When the connection is closed, the serial port is restored to its original state.

The library has been tested with Arduino microcontrollers.

See the header file for more details.

## Linking

The library can be linked with both C and C++ code.

## Licensing

Project available under GPLv3.
