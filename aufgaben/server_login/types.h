#ifndef __LIB_H
#define __LIB_H

#define ADMIN_REPUTATION -1
#define GUEST_REPUTATION 0

typedef enum {admin, user, guest} user_group;
typedef enum {false, true} bool;


struct member {
    float reputation;
    char* name;
	bool debug;
};



#endif /* end of include guard: __LIB_H */
