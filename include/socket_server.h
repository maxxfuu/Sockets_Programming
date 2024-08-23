#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H 

#include <pthread.h> 

#define MYPORT "8080" 
#define BACKLOG 5 
#define MAX_CLIENT 100 

// Declare the mutex as extern, 
extern pthread_mutex_t clients_mutex;

// function declaration 
void *handle_client(void *socket_desc); 

// Declare varibles for amount of clients and thread concurrency 
extern int client_sockets[MAX_CLIENT]; 
extern pthread_mutex_t clients_mutex;  



#endif 
