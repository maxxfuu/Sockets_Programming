#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <pthread.h> 

# define PORT 8080 // Up for definition 

void *receive_messages(void *socket_desc) {
    int sockfd = *(int *)socket_desc;
    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("Server: %s\n", buffer);
    }

    if (bytes_received == 0) {
        printf("Server closed the connection\n");
    } else {
        perror("recv failed");
    }

    return NULL;
}

