#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

# define PORT 8080 // Up for definition 

int main() { 

    int sockfd; 
    struct sockaddr_in serv_addr; 

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

    // Conncet... 

    // Send to and recieve after connnecting.  

    closm(sockfd); 
    return 0; 

} 

// socket(Specifies IPv4 or IPv6, Specifies TCP or UDP and SOCK_STREAM is TCP, 0 lets the system choose the appropriate protocol
