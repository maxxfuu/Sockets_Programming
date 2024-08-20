#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// function declaration 
void *handle_client(void *socket_desc); 

#endif 
