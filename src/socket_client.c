#include "socket_client.h" 
#include <time.h>

#define MAX_MESSAGE_LENGTH 1024; 

void print_timestamp() { 
    time_t now = time(NULL); 
    struct tm *t = localtime(&now); 
    char time_str[9]; 
    strftime(time_str, sizeof(time_str),  "%H:%M:%S", t);
    printf("[%s] ", time_str); 
} 

void *receive_messages(void *socket_desc) {
    int sockfd = *(int *)socket_desc;
    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        
        // Clear the current line
        printf("\r");
        for (int i = 0; i < 100; i++) printf(" ");
        printf("\r");
        
        // Print the received message with timestamp
        print_timestamp();
        printf("STRANGER: %s\n", buffer);
        
        // Reprint the input prompt
        printf("Enter Message: ");
        fflush(stdout);
    }

    if (bytes_received == 0) {
        printf("Server closed the connection\n");
    } else {
        perror("recv failed");
    }

    return NULL;
}

