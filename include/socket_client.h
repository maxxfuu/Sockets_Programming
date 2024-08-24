#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <time.h> 

#define PORT 8080 
// function declaration 
void *receive_messages(void *arg);  

// Time stamp function 
void print_timestamp();

#endif 
