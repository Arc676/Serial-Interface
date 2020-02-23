// Copyright (C) 2020 Arc676/Alessandro Vinciguerra

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

#include "serialcomm.h"

SerialConnection* initSerialConnection() {
	SerialConnection* sc = malloc(sizeof(SerialConnection));
	memset(sc, 0, sizeof(SerialConnection));
	sc->fd = -1;
	sc->freq = 9600;
	return sc;
}

void disconnectSerialConnection(SerialConnection* sc) {
	tcsetattr(sc->fd, TCSANOW, &(sc->oldtio));
	sc->fd = -1;
}

void destroySerialConnection(SerialConnection* sc) {
	tcsetattr(sc->fd, TCSANOW, &(sc->oldtio));
	free(sc);
}

int setupSerial(SerialConnection* sc, char* device) {
	if (strlen(device) == 0) {
		return 0;
	}
	int fd = open(device, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		return 0;
	}
	struct termios oldtio, newtio;
	tcgetattr(fd, &oldtio);

	memset(&newtio, 0, sizeof(newtio));
	newtio.c_cflag = sc->freq | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	// initialize all control characters 
	newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	sc->fd = fd;
	sc->oldtio = oldtio;
	sc->newtio = newtio;
	return 1;
}

size_t writeSerial(SerialConnection* sc, unsigned char* data, size_t length) {
	if (sc->fd < 0) return 0;
	return write(sc->fd, data, length);
}

size_t readSerial(SerialConnection* sc, unsigned char* data, size_t length) {
	if (sc->fd < 0) return 0;
	return read(sc->fd, data, length);
}
