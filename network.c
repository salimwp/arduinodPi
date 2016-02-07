/*
 * network.c - contains the implementation needed to create the TCP 
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

#include "network.h"
#include "arduino.h"

int makeSocket(char *ip_address, int portnum, int arduinofd){
	int result;
	int clientfd;
	int clientlen;
	struct sockaddr_in client, server;

	pthread_t thread;

	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverfd < 0){
		printf("Error: Failed to create socket\n");
		return -1;
	}

	memset(&server, '\0', sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip_address);
	server.sin_port = htons(portnum);

	result = bind(serverfd, (struct sockaddr *)&server, sizeof(server));
	if (result < 0){
		perror("bind");
		printf("Error: Failed to bind socket\n");
		return -1;
	}

	result = listen(serverfd,1);
	if (result < 0){
		printf("Error: Failed to listen on socket\n");
		return -1;
	} else {
		printf("Server is now listening for connections\n");
	}


	clientlen = sizeof(client);
	while(1){
		clientfd = accept(serverfd, (struct sockaddr*) &client, (socklen_t*) &clientlen);
		/*result = pthread_create(&thread, NULL, clientHandler, (void *) &clientfd);*/
		nonThreadedClient(arduinofd, clientfd);
		if(result < 0){
			printf("Error: Couldn't create thread. Aborting.\n");
			return -1;
		}
		printf("client disconnected\n");
	}	
}

void nonThreadedClient(int arduinofd, int clientfd){
	char *message;
	char buffer;
	char value[5];
	int n;
	int pos = 0;

	printf("Client connected\n");
	memset(value, '\0', sizeof(value));
	while(1){
		buffer = '\0';
		/*memset(buffer, '\0', sizeof(char));*/
		n = read(arduinofd, &buffer, sizeof(buffer));
		if( n == -1 || n == 0){
			printf("No data\n");
		} else {
			if(buffer == '\n' || pos == 4){
				printf("Sending: %s\n",value);
				n = write(clientfd, value, strlen(value));
				if (n == -1){
					perror("Client disconnect\n");
					break;
				}
				memset(value, '\0', sizeof(value));
				pos = 0;
			} else {
				value[pos] = buffer;
				pos++;
			}
		}
	}
}

void *clientHandler(void *client){
	int clientSocket = *(int *)client;
	char *message;
	int arduinofd;
	char buffer[4];
	char value[4];
	int n;

	arduinofd = initializeArduino();


	if(arduinofd < 0){
		printf("Error: failed to open arduino\n");
		exit(-1);
	}

	printf("Client connected\n");
	
	message = "Connected to server\n";
	write(clientSocket, message, strlen(message));

	while(1){
		printf("Getting data\n");
		memset(buffer, '\0', sizeof(buffer));
		n = read(arduinofd, &buffer, sizeof(buffer));
		if( n == -1 || n == 0){
			printf("No data\n");
		} else {
			if(buffer[0] == '\n'){
				write(clientSocket, value, strlen(value));
				memset(value, '\0', sizeof(value));
			} else {
				strcat(value, buffer);
				printf("Value: %s\n",value);
			}
		}
		sleep(1);
	}


	
}
