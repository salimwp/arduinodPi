/*
 * arduino.c - contains the implementation of the functions to communicate with 
 * tthe arduino
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


#include "arduino.h"

int closeArduinoPort(int fd){
        if(close(fd) == -1) {
                perror("closeArduinoPort: Unable to close port to Arduino");
                return -1;
        } else {
                return 0;
        }
}

int writeArduinoPort(int fd, char *data){
        int numWrite;

        numWrite = write(fd, data, sizeof(char));
        if (numWrite < 0){
                perror("writeArduinoPort: Error writing data to Arduino");
                return -1;
        } else {
                return 0;
        }
}

void readArduinoPort(int fd, char *byte){
        int numRead;

        numRead = read(fd, byte, sizeof(byte));


        printf("Read %d number of bytes: %s\n",numRead,byte);


        if ( numRead == -1 || numRead == 0 ){
                byte = '\0';
        } else {
                printf("readArduinoPort: %s\n",byte);
        }

}

int initializeArduino(){
        int arduinofd;
        struct termios options;

        arduinofd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY );

        if(arduinofd == -1){
                perror("openArduinoPort: Unable to open port to Arduino");
                return -1;
        } else {
                fcntl(arduinofd, F_SETFL, 0);
        }

        tcgetattr(arduinofd, &options);
        cfmakeraw(&options);
        cfsetispeed(&options, B9600);
        cfsetospeed(&options, B9600);

        if( tcsetattr(arduinofd, TCSANOW, &options) == -1 ){
                perror("configArduinoPort: Fail to set port configurations");
                return -1;
        }

        return arduinofd;
}
