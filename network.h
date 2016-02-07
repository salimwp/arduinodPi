/*
 * network.h - contains the function prototypes needed to create the TCP 
 * connections
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
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct TCPHelper{
	int clientfd;
	int arduinofd;
};

int makeSocket(char *ip_address, int portnum, int arduinofd);
void *clientHandler(void *client);
void nonThreadedClient(int arduinofd, int clientfd);
