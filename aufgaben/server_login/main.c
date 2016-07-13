#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> //don´t forget linking with lpthread
#include <unistd.h>
#include "main.h"
#include "server.h" //Includes the createServer-func, serverMutex, serverCondition

int main(int argc, char* argv[]) {
	pthread_mutex_init(&serverMutex, NULL);
	pthread_cond_init(&serverCondition, NULL);
	
	pthread_t serverThread;
	int port = DEFAULT_PORT;

	if(argc == 2) {
		if(argv[1] == "-h" || argv[1] == "--help") {
			fprintf(stdout, "[server] starts the server on Default-Port %d", port);
			fflush(stdout);
			fprintf(stdout, "[server] [port] starts the server on port [port]. Allowed port numbers are between 0 and 65535");
			fflush(stdout);
			fprintf(stdout, "[server] [-h|--help] show the help informations");
			fflush(stdout);
		} else {
			port = atoi(argv[1]);
			uid_t uid=getuid();
			uid_t euid=geteuid();

			if(port < 0 && port > 65535) {
				fprintf(stderr, "Illegal port number");
				fflush(stderr);
				return 1;
			}

			if((port < 1024 && uid!=0) || (port < 1024 && uid != euid)) {
				fprintf(stderr, "No root privilegs on reserved ports");
				fflush(stderr);
				return 1;
			}
		}
	}
	
	fprintf(stdout, "Starts the server at port %d\n", port);
	fflush(stdout);

	/* create the server thread for listening to connections */
	if(pthread_create(&serverThread, NULL, createServer, &port)) {
		fprintf(stderr, "Error creating thread\n");
		fflush(stderr);
		return 1;
	}

	/* wait for the server thread to finish */
	if(pthread_join(serverThread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		fflush(stderr);
		return 2;
	}

	return EXIT_SUCCESS;
}
