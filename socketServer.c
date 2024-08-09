#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 


#define PORT 8080 
#define BACKLOG 5 

int main() { 

    int listenfd, connfd; // listening file descriptor, connection file descriptor 
    struct sockaddr_in serv_addr, client_addr; 

    socklen_t client_addr_len = sizeof(client_addr); 

    // (Step 1) Creating a listening socket for the server. 
    if (listenfd = socket(AF_INET, SOCK_STREAM, 0) < 0) { 
        perror("Socket creation failed"); 
        close(listenfd); 
        exit(EXIT_FAILURE);
    }

    // (Step 3) Prepare the sockaddr_in structure 
    memset(&serv_addr, 0, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(PORT); 

    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) { 
        perror("Bind failed"); 
        close(listenfd); 
        exit(EXIT_FAILURE); 
    }

    // Listen for incoming connections 
    if (listen(listenfd, BACKLOG) < 0) { 
        perror("Listen Failed"); 
        close(listenfd); 
        exit(EXIT_FAILURE); 
    } 

    printf("Server Listening on port %d\n", PORT); 

    // Accept incoming connection. 
    while((connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_len))) {
        printf("Connection Accepted!"); 
        close(connfd); 
    }

    if (connfd < 0) { 
        perror("Accept failed"); 
        close(listenfd); 
        exit(EXIT_FAILURE); 
    } 

    close(listenfd); 
    return 0; 

}