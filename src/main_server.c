#include "socket_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

int main(void) { 
    struct sockaddr_storage client_addr;
    struct sockaddr_in serv_addr; 
    socklen_t client_addr_len = sizeof(client_addr);
    struct addrinfo hints, *res;
    int sockfd; // listening file descriptor, connection file descriptor 
    int status; 
    pthread_t tid; 


    // (Step 3) Prepare the sockaddr_in structure 
    memset(&hints, 0, sizeof(serv_addr));  
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags= AI_PASSIVE; 

    status = getaddrinfo(NULL, MYPORT, &hints, &res); 
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // (Step 1) Creating a listening socket for the server. 

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 
    if (sockfd < 0)  {
        perror("Socket Creation Failed"); 
        freeaddrinfo(res); 
        return 1; 
    }

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0 ) { 
        perror("Bind failed"); 
        freeaddrinfo(res); 
        return 1; 
    }

    freeaddrinfo(res); 
    
    if (listen(sockfd, BACKLOG) == -1) { 
        perror("Listen Failed"); 
        close(sockfd); 
        exit(EXIT_FAILURE); 
    } 

    printf("Server Listening on port %s\n", MYPORT); 

    // Accept for incoming connections 
    while(1) {
        client_addr_len = sizeof(client_addr); 
        int *new_fd = malloc(sizeof(int)); // To allocate memory for the new socket descriptor 
        *new_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len); 
        if (*new_fd == -1) { 
            perror("Accept Failed"); 
            free(new_fd); 
            return 1; 
        } 

    // Adding clients to the list 
    pthread_mutex_lock(&clients_mutex); 
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client_sockets[i] == 0) {
            client_sockets[i] = *new_fd; 
            break; 
        }
    } 
    pthread_mutex_unlock(&clients_mutex); 

    // Create a thread for each client 
    if (pthread_create(&tid, NULL, handle_client, new_fd) != 0) { 
        perror("Error to create another thread for client"); 
        free(new_fd); 
    } 

    printf("Connection accepted\n");

    }

    close(sockfd); 
    return 0; 

}


