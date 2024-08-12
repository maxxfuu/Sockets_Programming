#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>

#define MYPORT "8080" 
#define BACKLOG 5 
#define MAX_CLIENT 100 


int client_sockets[MAX_CLIENT] 
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITALIZER; 

void *handle_clint(void *arg) {

    int client_socket = *(int *)arg; // type casting and dereferencing operation 
    char buffer[1024]; 
    int bytes_received; 

    while ((bytes_received = recv(clinet_socket, buffer, sizeof(buffer) , 0)) > 0 ) {

        buffer[bytes_received] = '\0'; 
        printf("Received: %s\n", buffer); 

        // Broadcast mesage to all other clients
        pthread_mutex_lock(&clients_mutex); 
        for(int i = 0; i < MAX_CLIENT; i++) { 
            if(clinet_sockets[i] != 0 && client_sockets[i] != clinet_socket) {
                send(client_sockets[i], buffer, bytes_received, 0); 
            }
        }
        pthread_mutex_unlock(&clinets_mutex); 
    }


    // Remove client from list and close socket 
    pthread_mutex_lock(&client_mutex); 
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client_sockets[i] == client socket) {
            client_socket[i] = 0; 
            break; 
        } 
    }

    pthread_mutex_unlock(&client_mutex); 

    close(client_socket); 
    return NULL; 
}

int main(void) { 
    struct sockaddr_storage client_addr;
    struct sockaddr_in serv_addr; 
    socklen_t client_addr_len = sizeof(client_addr);
    struct addrinfo hints, *res;
    int sockfd, new_fd; // listening file descriptor, connection file descriptor 
    int status; 


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
    client_addr_len = sizeof(client_addr); 
    new_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len); 
    if (new_fd == -1) { 
        perror("Accept Failed"); 
        close(sockfd); 
        return 1; 
    } 
    
    printf("Connection accepted\n");


    close(new_fd); 
   

    close(sockfd); 
    return 0; 

}
