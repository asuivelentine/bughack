/*
 * server.h
 */

#ifndef SERVER_H_
#define SERVER_H_

pthread_mutex_t serverMutex;
pthread_cond_t serverCondition;
void *createServer(void *port_void_ptr);

#endif /* SERVER_H_ */

