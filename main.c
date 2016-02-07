/*
 * main.c - contains the main function used for arduinod
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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "network.h"
#include "arduino.h"

void usage(int exit_code){
	printf("Usage: arduinod [-h host_ip] [-p port_number]\n");
	exit(exit_code);
}

int main(int argc, char *argv[]){

	int flags, opt;
	int nsecs, tfnd;

	int port_num;
	int port_num_defined = 0;
	int ip_defined = 0;
	int serverfd = -1;

	int arduinofd;

	int result;

	char ip_addr[32];
	
	while ((opt = getopt(argc, argv, "h:p:")) != -1){
		switch(opt){
			case 'p':
				port_num = atoi(optarg);
				port_num_defined = 1;
				break;
			case 'h':
				strncpy(ip_addr, optarg, sizeof(ip_addr));
				/*inet_aton(optarg, &serveraddr.sin_addr);*/
				ip_defined = 1;
				break;
			default:
				usage(-1);	
				break;
		}
	}

	arduinofd = initializeArduino();
	sleep(5);

	if(arduinofd < 0){
                printf("Error: failed to open arduino\n");
                exit(-1);
        }

	if(ip_defined && port_num_defined){
		printf("Binding to %s on port %d\n", ip_addr, port_num);
		result = makeSocket(ip_addr, port_num, arduinofd);
		if(result < 0){
			printf("Error: Could not create server. Terminating application.\n");
			exit(-1);
		}
	}

	if(!ip_defined && port_num_defined){
		strcpy(ip_addr,"0.0.0.0");
		printf("Starting TCP Server on port %d, binded to %s\n", port_num, ip_addr);
		result = makeSocket(ip_addr, port_num, arduinofd);
		if(result < 0){
			printf("Error: Could not create server. Terminating application.\n");
                        exit(-1);

		}
	}

	return 0;
}
