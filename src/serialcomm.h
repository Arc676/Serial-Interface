// Copyright (C) 2020-1 Arc676/Alessandro Vinciguerra

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation (version 3)

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// See README and LICENSE for more details.

#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define _POSIX_SOURCE 1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encapsulates the properties of a serial connection
 * fd: File descriptor for the connection
 * freq: Serial connection baud rate
 * oldtio: Original port settings to restore when the connection is destroyed
 * newtio: New port settings to be used for serial communication
 */
typedef struct SerialConnection {
	int fd;
	int freq;
	struct termios oldtio, newtio;
} SerialConnection;

/**
 * Allocates memory for a new serial connection with baud rate 9600
 * @return A newly allocated, uninitialized serial connection
 */
SerialConnection* initSerialConnection();

/**
 * Disconnects a serial connection and restores original settings to its port
 * without destroying the connection object
 * @param sc Serial connection to disconnect
 */
void disconnectSerialConnection(SerialConnection* sc);

/**
 * Destroys a serial connection and restores original settings to its port
 * @param sc Serial connection to destroy
 */
void destroySerialConnection(SerialConnection* sc);

/**
 * Initializes a serial connection with the given parameters
 * @param sc Serial connection to initialize
 * @param device Device on which to establish the connection (e.g. "/dev/ttyACM0")
 * @return Whether the initialization succeeded
 */
int setupSerial(SerialConnection* sc, const char* device);

/**
 * Writes data through a serial connection
 * @param sc Serial connection to use
 * @param data Data to write
 * @param length Number of bytes to write
 * @return The number of bytes actually written
 */
size_t writeSerial(SerialConnection* sc, const unsigned char* data, const size_t length);

/**
 * Reads data from a serial connection
 * @param sc Serial connection to use
 * @param data Buffer into which to read the data
 * @param length Number of bytes to read
 * @return The number of bytes actually read
 */
size_t readSerial(SerialConnection* sc, unsigned char* data, const size_t length);

#ifdef __cplusplus
}
#endif

#endif
