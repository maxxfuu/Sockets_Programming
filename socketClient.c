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


int main() { 

    int sockfd; 
    struct sockaddr_in serv_addr; 
    char buffer[1024]; 
    int bytes_received; 

    // (Step 1:) Create a socket. 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Failed: "); 
        exit(EXIT_FAILURE); 
    }
    
    // (Step 2) Prepare sockaddr_in structure to hold address and port number for the socket server to bind to. 
    memset(&serv_addr, 0, sizeof(serv_addr)); // set a memory block to some value. 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); // htons()	host to network, short data type 

    // (Step 3) Convert IPv4 address from text to binary form.  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { 
        perror("Invalid address or address not supported!"); 
        close(sockfd); 
        exit(EXIT_FAILURE); 
    }

    // (Step 4) Connect to the server 
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        perror("Connection failed"); 
        close(sockfd); 
        exit(EXIT_FAILURE); 
    }

    // Hooray... Maybe ??? 
    printf("Connected to server on 127.0.0.1\n"); 

    // Communication Loop: Send and receive messages
    while(1) {
        // Send a message to the server
        printf("Enter Message: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character from the input
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == 'n')
        {
            buffer[len - 1] = '\0';
        } 

        send(sockfd, buffer, strlen(buffer), 0); 

        //Check for exit condition 
        if (strcmp(buffer, "exit") == 0) { 
            printf("Exiting...\n"); 
            break; 
        } 

        //Recieve a message from the server 
        bytes_received = recv(sockfd, buffer, sizeof(buffer) -1, 0); 
        if (bytes_received <= 0) { 
            printf("Server close the connection. \n"); 
            break; 
        } 
        buffer[bytes_received] = '\0';
        printf("Server: %s\n", buffer);
    } 

    // Close the socket 
    close(sockfd); 
    return 0; 

} 

// socket(Specifies IPv4 or IPv6, Specifies TCP or UDP and SOCK_STREAM is TCP, 0 lets the system choose the appropriate protocol
