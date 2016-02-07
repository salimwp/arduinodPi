/*
 * arduino.h - contains the function definitions needed to communicate with
 * the arduino. 
 * 
 * Copyright (C) 2015  Salim Haniff <blog@salimhaniff.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should review the GNU General Public License to accept the agreements to
 * use this program. Available at http://www.gnu.org/licenses/gpl-3.0.html .
 */


#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#define ARDUINO_PORT "/dev/ttyACM0"

int initializeArduino();
int closeArduinoPort(int fd);
int writeToArduino(int fd, char *data);
void readFromArduino(int fd, char *data);
