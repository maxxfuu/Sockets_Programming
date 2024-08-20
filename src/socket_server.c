#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <pthread/pthread.h> 

#include "socket_server.h"

#define MYPORT "8080" 
#define BACKLOG 5 
#define MAX_CLIENT 100 

int client_sockets[MAX_CLIENT]; 
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER; 

void *handle_client(void *arg) {
    int client_socket = *(int *)arg; // type casting and dereferencing operation 
    free(arg); // free the allocated memory for the socket descriptor 
    char buffer[1024]; 
    int bytes_received;
    char message[1064]; // buffer to hold the message with the id. 

    // assign a unique id to the client
    int client_id = client_socket; // using socket descriptor as an id. 


    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer) , 0)) > 0 ) {

        buffer[bytes_received] = '\0'; 
        printf("Client %d: %s\n", client_id, buffer); 

        //Prepend the client id to the message
        snprintf(message, sizeof(message), "Client %d: %s", client_id, buffer); 
        // Broadcast mesage to all other clients
        pthread_mutex_lock(&clients_mutex); 
        for(int i = 0; i < MAX_CLIENT; i++) { 
            if(client_sockets[i] != 0 && client_sockets[i] != client_socket) {
                send(client_sockets[i], buffer, bytes_received, 0); 
            }
        }
        pthread_mutex_unlock(&clients_mutex); 
    }


    // Remove client from list and close socket 
    pthread_mutex_lock(&clients_mutex); 
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client_sockets[i] == client_socket) {
            client_sockets[i] = 0; 
            break; 
        } 
    }

    pthread_mutex_unlock(&clients_mutex); 

    close(client_socket); 
    return NULL; 
} 

