#include "types.h"
#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <crypt.h>

// Only first argument is usually given, everything else is legacy.
/*unsigned int default_reputation_for(struct member* name, unsigned int* a) {
    if (!a) {
        return (unsigned int)1.0f;
    }
    *a = -1;
}
*/

struct pass_member {
    char* pass;
    struct member member;
};

struct pass_member members[] = {
    {
        .pass = "$1$das find$pZdxvXfYwDMYYFf3e6gL31",
        .member = {
            .reputation = 4.0,
            .name = "jabuble",
            .debug = false
        }
    },
    {
        .pass = "$6$ehpyPndWqQ3Fk8gb$Y9oRFEXgNcE1MPjz4ImJSD9zqWB97UxqSOvbQVwMBnWwTa.PSAOm/u8o8wr5inLw3nRyEC4UrwqXNNVtcTnRt1",
        .member = {
            .reputation = 4.0,
            .name = "banane",
            .debug = false
        }
    },
    {
        .pass = "$6$auNL/0MgXQF/Ru7N$D3XuxTC4s3FJfDWQyw6aJNZIuS7kixgTX/nH6S5drnQY0QolV0YhfZWQpzG/rLIh/iUJkS4.0GCGP0j90DH9L1",
        .member = {
            .reputation = -1.0,
            .name = "bourne",
            .debug = false
        }
    }
};

const float guest_rep = 0.0;

unsigned int* valid_pw(const char* name, const char* pass) {
    struct member* mem = NULL;
    for (int i = 0; i < (sizeof(members)/sizeof(struct pass_member)); i++) {
        if (strcmp(name, members[i].member.name) == 0) {
            mem = &members[i].member;
        }
    }

    if (!mem) {
        return (unsigned int*) &guest_rep;
    }

    for (int i = 0; i < (sizeof(members)/sizeof(struct pass_member)); i++) {
        if (crypt(pass, members[i].pass) == members[i].pass) {
            return (unsigned int*)&members[i].member.reputation;
        }
    }

    return (unsigned int*) &guest_rep;
}

int login_user(char* name, char* pass, struct member* user) {

    printf("\"%s\" \"%s\"", name, pass);

    struct member* mem = NULL;
    for (int i = 0; i < (sizeof(members)/sizeof(struct pass_member)); i++) {
        if (strcmp(name, members[i].member.name) == 0) {
            mem = &members[i].member;
        }
    }

    if (!mem) {
        return 0;
    }

    printf("Found user: %s\n", mem->name);

    for (int i = 0; i < (sizeof(members)/sizeof(struct pass_member)); i++) {
        if (&members[i].member == mem) {
            printf("Found pass: %s \n", members[i].pass);
            char* res = crypt(pass, members[i].pass);
            if (strcmp(res, members[i].pass) == 0) {
                *user = *mem;
                return 1;
            }
        }
    }

    return 0;
}


int check_database_registration(char* buffer, char* name, int debug) {

	return 0;
}

//usergroup
int check_database_permissions(char* buffer, char* name, char* pw, unsigned int* reputation) {
	int return_value = 0;
	if(!pw || strlen(pw) == 0) {
		*reputation = 0;
		return GUEST_REPUTATION;
	}


	switch(*reputation) {
		case -1: return_value = admin;
			break;
		case 0: return_value = guest;
			break;
		default: return_value = user;
			break;
	}

	return return_value;
}


void listserver(char* buffer, struct member* mem) {
	if( mem->reputation == GUEST_REPUTATION ) {
		strcat(buffer, "Guests can't see serverstatus\n");
		return;
	}
	strcat(buffer, "Available Servers:\n");
	strcat(buffer, "-----------------:\n\n");
	strcat(buffer, "Server-ID:      [1234]\n");
	strcat(buffer, "Status:         [running]\n");
	strcat(buffer, "port:           [9000]\n");
	if( mem->reputation == ADMIN_REPUTATION ) {
		strcat(buffer, "connected user: [42]\n");
	}
	strcat(buffer, "\n\n");

	strcat(buffer, "Server-ID:    [1337]\n");
	strcat(buffer, "Status:       [running]\n");
	strcat(buffer, "port:         [1337]\n");
	if( mem->reputation == ADMIN_REPUTATION ) {
		strcat(buffer, "connected user: [142]\n");
	}
	strcat(buffer, "\n\n");


	strcat(buffer, "Server-ID:    [6666]\n");
	strcat(buffer, "Status:       [stopped]\n");
	strcat(buffer, "port:         [6666]\n");
	if( mem->reputation == ADMIN_REPUTATION ) {
		strcat(buffer, "connected user: [0]\n");
	}
	strcat(buffer, "\n\n");
}

void print_help_guest(char* buffer) {
	strcat(buffer, "Following commands are available:\n");
	strcat(buffer, "---------------------------------\n\n");
	strcat(buffer, "help\n");
	strcat(buffer, "showuser\n");
	strcat(buffer, "logout\n");
	strcat(buffer, "showlisence\n");
}

void print_help_user(char* buffer) {
	print_help_guest(buffer);
	strcat(buffer, "listserver\n");
	strcat(buffer, "serverstatus SERVERID\n");

}

void print_help_admin(char* buffer) {
	print_help_guest(buffer);
	print_help_user(buffer);
	strcat(buffer, "enableDebug\n");
}

void print_login(char* buffer, int reputation) {
	strcat(buffer, "UserInfo:\n");
	strcat(buffer, "---------\n\n");

	strcat(buffer, "reputation:   [");
	sprintf(&buffer[strlen(buffer)], "%i", reputation);
	strcat(buffer, "]\n");

	strcat(buffer, "name:         ");
}

void print_guest(char* buffer) {
	strcat(buffer, "[guest]\n");
}

void print_user(char* buffer, char* name) {
	strcat(buffer, "[");
	strcat(buffer, name);
	strcat(buffer, "]\n");
}

void print_admin(char* buffer, bool debug) {
	strcat(buffer, "[admin]\n");

	strcat(buffer, "debug:        [");
	if(debug) {
		strcat(buffer, "True");
	} else {
		strcat(buffer, "False");
	}
	strcat(buffer, "]\n");
}

void print_lisence(char* buffer) {
	strcat(buffer, "The Do What The Fuck You Want To Public License (WTFPL) is a free software license.\n\nThere is a long ongoing battle between GPL zealots and BSD fanatics, about which license type is the most free of the two. In fact, both license types have unacceptable obnoxious clauses (such as reproducing a huge disclaimer that is written in all caps) that severely restrain our freedoms. The WTFPL can solve this problem.\n\nWhen analysing whether a license is free or not, you usually check that it allows free usage, modification and redistribution. Then you check that the additional restrictions do not impair fundamental freedoms. The WTFPL renders this task trivial: it allows everything and has no additional restrictions. How could life be easier? You just DO WHAT THE FUCK YOU WANT TO.\n");
}

bool is_server_online(unsigned int id) {
	bool return_value = false;

	switch(id) {
		case 1234: return_value = true;
			break;
		case 1337: return_value = true;
			break;
		case 6666: return_value = false;
			break;
		default:
			break;
	}

	return return_value;
}

unsigned int get_server_port(unsigned int id) {
	int return_value = 0;
	switch(id) {
		case 1234: return_value = 9000;
			break;
		case 1337: return_value = 1337;
			break;
		case 6666: return_value = 6666;
			break;
		default:
			break;
	}
	return return_value;
}

void show_server_info(char buffer[], int server_id, user_group rights, unsigned int* status) {
	int state = is_server_online(server_id);

	if(status && (state == false)){
		*status = -1;
	}

	int port = get_server_port(server_id);
	if(status && (port == 0)) {
		*status = -1;
	}

	strcat(buffer, "Serverstatus: ");
	strcat(buffer, "-----------------:\n\n");
	strcat(buffer, "ID:        [");
	sprintf(&buffer[strlen(buffer)], "%d", server_id);
	strcat(buffer, "]\n");

	strcat(buffer, "Status:    [");
	if(state){
		strcat(buffer, "running]\n");
	} else {
		strcat(buffer, "stopped]\n");
	}

	strcat(buffer, "Port:      [");
	//strcat(buffer, port);
	sprintf(&buffer[strlen(buffer)], "%d", port);
	strcat(buffer, "]\n");
}
