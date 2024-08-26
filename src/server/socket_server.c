#include "../include/server/socket_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <stdbool.h> 
#include "../test/test_utils.h"

//Initialize clients_mutex 
int client_sockets[MAX_CLIENT];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int client_socket = *(int *)arg; // type casting and dereferencing operation 
    free(arg); // free the allocated memory for the socket descriptor 
    char buffer[1024]; 
    int bytes_received;
    char message[1064]; // buffer to hold the message with the id. 
    int client_id = client_socket; //assign a unique id to the client, using socket descriptor as an id. 
    bool is_test_mode = false; 

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) { // Writing tests outputs for latency, throughput and error rate
        buffer[bytes_received] = '\0';

        if (strncmp(buffer, "TEST_MODE", 9) == 0) {
            is_test_mode = true;
            send(client_socket, "TEST_MODE_ACK", 13, 0);
            continue;
        }

        if (is_test_mode) {
            if (strncmp(buffer, "TEST_THROUGHPUT", 15) == 0) {
                // Handle throughput test
                char *data = malloc(1024 * 1024);  // 1MB of data
                memset(data, 'A', 1024 * 1024);
                send(client_socket, data, 1024 * 1024, 0);
                free(data);
            } else if (strncmp(buffer, "TEST_LATENCY", 12) == 0) {
                // Handle latency test
                send(client_socket, "PONG", 4, 0);
            } else if (strncmp(buffer, "TEST_ERROR_RATE", 15) == 0) {
                // Handle error rate test
                send(client_socket, buffer, bytes_received, 0);
            }
        } else {
            printf("Client %d: %s\n", client_id, buffer);
            snprintf(message, sizeof(message), "Client %d: %s", client_id, buffer);
            pthread_mutex_lock(&clients_mutex);
            for(int i = 0; i < MAX_CLIENT; i++) {
                if(client_sockets[i] != 0 && client_sockets[i] != client_socket) {
                    send(client_sockets[i], buffer, bytes_received, 0);
                }
            }
            pthread_mutex_unlock(&clients_mutex);
        }
    }    

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

