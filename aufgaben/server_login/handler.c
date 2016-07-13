#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h> //don´t forget linking with lpthread
#include "handler.h"
#include "types.h"

#define COMMAND(x, y, z) if (strncmp(x, y, z) == 0)

extern int check_database_registration(char*, char*, int);
extern int check_database_permissions(char*, char*, char*, float*);
extern void listserver(char*, struct member*);
extern void print_help_guest(char*);
extern void print_help_user(char*);
extern void print_help_admin(char*);

extern void print_login(char*, bool);
extern void print_user(char*, char*);
extern void print_admin(char*);
extern void print_guest(char*);

extern void print_lisence(char*);
extern void show_server_info(char*, int, user_group);

extern int login_user(char*, char*, struct member*);

//size of recv-buffer
#define IN_SIZE 2000

/*
 * Read line from socket
 */
int read_line(int* sock, char* line_buffer, bool* should_die) {
	//char buff[IN_SIZE];
	char c = 0;
	int received = 0;
	int status;

	while( (status = recv(*sock, &c, 1, 0)) != 0) {
		if(received >= IN_SIZE)
			return -1;

		if(status == -1){
			*should_die = true;
			return -1;
		}

		if( c == 0x0D )
			break;

		if( 	(c >= 'A' && c <= 'Z') ||
				(c >= 'a' && c <= 'z') ||
				(c >= '0' && c <= '9') || c == ' ')
			line_buffer[received++] = c;
	}

	if(status == 0)
		*should_die = true;

	return received;
}

struct member* login(int* sock, bool* should_die) {
    struct member* mem = malloc(sizeof(struct member));
	char client_message[IN_SIZE];
	char buf[20];
	char pw[50];
	char name[50];

	strcpy(buf, "User: ");
	write(*sock, buf, strlen(buf));
	read_line(sock, client_message, should_die);
	memcpy(name, client_message, strlen(client_message));

	strcpy(buf, "Pass: ");
	write(*sock, buf, strlen(buf));
	read_line(sock, client_message, should_die);
	memcpy(pw, client_message, strlen(client_message));

    if (strcmp(name, "guest") != 0) {
        if (!login_user(name, pw, mem)) {
            memset(buf, 0, 20);
            strcat(buf, "Wrong Password.\n");
            write(*sock, buf, strlen(buf));
            *should_die = true;
            return NULL;
        }
    } else {
        mem->name = "guest";
        mem->reputation = 0.0;
        mem->debug = false;
    }

	memset(buf, 0, 20);
	strcat(buf, "\n> ");
	write(*sock, buf, strlen(buf));
    return mem;
}

void parse_command(char* data, char* answer, struct member* mem, bool* should_die) {
	bool is_parsed = false;

	COMMAND("help", data, 4) {
		if(mem->reputation == GUEST_REPUTATION)
			print_help_guest(answer);
		else if(mem->reputation >= GUEST_REPUTATION)
			print_help_user(answer);
		else
			print_help_admin(answer);
		is_parsed = true;
	}

	COMMAND("showuser", data, 8) {
		print_login(answer, (int) mem->reputation);

		if(mem->reputation == GUEST_REPUTATION)
			print_guest(answer);
		else if(mem->reputation >= GUEST_REPUTATION)
			print_user(answer, mem->name);
		else
			print_admin(answer);
		is_parsed = true;
	}

	COMMAND("listserver", data, 10) {
		listserver(answer, mem);
		is_parsed = true;
	}

	COMMAND("serverstatus", data, 12) {
		char token[] = " ";
		char* split;
		split = strtok(data, token);
		split = strtok(NULL, token);

		if(split == NULL) {
			strcat(answer, "Missing serverID argument\n");
		} else {
			int id = atoi(split);
			check_database_permissions(answer, mem->name, "passwort", &mem->reputation);
			if(id == 6666)
				show_server_info(answer, 6666, ADMIN_REPUTATION);
			else if(id == 1234 || id == 1337)
				show_server_info(answer, id, ADMIN_REPUTATION);
			else
				strcat(answer, "unknown ID\n");

		}

		is_parsed = true;
	}

	COMMAND("showlisence", data, 7) {
		print_lisence(answer);
		is_parsed = true;
	}

	COMMAND("logout", data, 6) {
		strcat(answer, "logged out");
		*should_die = true;
		is_parsed = true;
	}


	if(!is_parsed)
		strcat(answer, "Command not found. Enter help for an overview of existing commands\n");

	if(*should_die == false)
		strcat(answer, "\n> ");
}

/*
 * This will handle connection for each client (in a new thread)
 * */
void *connection_handler(void* sock_void_ptr) {
	int *sock = (int *)sock_void_ptr; //Get the socket descriptor
	char client_message[IN_SIZE];
	char buf[20000];
	int read_size;
	bool should_die = false;
	char user_name[50];

	struct member* mem = login(sock, &should_die);

	//Receive a message from client
	while(!should_die) {

		read_size = read_line(sock, client_message, &should_die);
		parse_command(client_message, buf, mem, &should_die);
		write(*sock, buf, strlen(buf));

		memset(client_message, 0, IN_SIZE);
		memset(buf, 0, 20000);
	}

	fprintf(stdout,"Client disconnected\n");
	fflush(stdout);

	/* do not edit */
    free(mem);
	close(*sock);
	return NULL;
}
