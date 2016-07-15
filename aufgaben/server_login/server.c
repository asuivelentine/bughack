#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> //don´t forget linking with lpthread
#include "server.h"
#include "handler.h" //Includes the Handler

void *createServer(void *port_void_ptr) {
	pthread_mutex_lock(&serverMutex);
	int *port_ptr = (int *)port_void_ptr;

	int socketDesc, tmpClientSock, tmp, *newClientSock;
	struct sockaddr_in server, client;
     
	//Create socket
	socketDesc = socket(AF_INET, SOCK_STREAM, 0);
	if (socketDesc == -1) {
		fprintf(stderr, "Could not create socket\n");
		fflush(stderr);
		exit(1);
	}
	fprintf(stdout, "Socket successfully created\n");
	fflush(stdout);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(*port_ptr);
     
	//Bind Server Socket
	if(bind(socketDesc,(struct sockaddr *)&server , sizeof(server)) < 0) {
		fprintf(stderr, "Bind failed, port already in use or reserved?!?\n");
		fflush(stderr);
		exit(1);
	}
	fprintf(stdout, "Server successfully started at port %d\n", *port_ptr);
	fflush(stdout);
     
	//Listen
	listen(socketDesc , 3);
	fprintf(stdout, "Waiting/listening for new connections\n");
	fflush(stdout);

	tmp = sizeof(struct sockaddr_in);
	while((tmpClientSock = accept(socketDesc, (struct sockaddr *)&client, (socklen_t*)&tmp))) {
		fprintf(stdout, "Client connection accepted\n");
		fflush(stdout);
        
		pthread_t handler_thread;
		newClientSock = malloc(1);
		*newClientSock = tmpClientSock;

		if(pthread_create(&handler_thread, NULL, connection_handler, (void*) newClientSock)) {
			fprintf(stderr, "Could not create thread for client\n");
			fflush(stderr);
			exit(1);
		}

		fprintf(stdout, "Client assigned to handler\n");
		fflush(stdout);
	}
     
	if (tmpClientSock < 0) { //Happens, if program don´t get in while loop
		fprintf(stderr, "Could´t accept client connection\n");
		fflush(stderr);
		exit(1);
	}

	pthread_cond_broadcast(&serverCondition);
	pthread_mutex_unlock(&serverMutex);

	return NULL;
}
