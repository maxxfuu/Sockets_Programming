#include "socket_client.h" 

int main() { 

    int sockfd; 
    struct sockaddr_in serv_addr; 
    char buffer[1024]; 
    pthread_t recv_thread; 

    // (Step 1:) Create a socket. TCP meaning we are using TCP  
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

    // Create a thread to reieve message from server 
    if(pthread_create(&recv_thread, NULL, receive_messages, &sockfd) != 0) { 
        perror("Could not create recieve thread"); 
        close(sockfd); 
        exit(EXIT_FAILURE); 
    }

    // Communication Loop: Send and receive messages
    while(1) {
        // Send a message to the server
        printf("Enter Message: ");
        fflush(stdout); 
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break; 
        }

        // Remove newline character from the input
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == 'n')
        {
            buffer[len - 1] = '\0';
        } 
        
        if(strlen(buffer) > 0) { 
            send(sockfd, buffer, strlen(buffer), 0); 
            print_timestamp(); 
            printf("YOU: %s\n", buffer); 
        }

        //Check for exit condition 
        if (strcmp(buffer, "exit") == 0) { 
            printf("Exiting...\n"); 
            break; 
        } 
    } 

    pthread_join(recv_thread, NULL);  

    // Close the socket 
    close(sockfd); 
    return 0; 
} 

// socket(Specifies IPv4 or IPv6, Specifies TCP or UDP and SOCK_STREAM is TCP, 0 lets the system choose the appropriate protocol
