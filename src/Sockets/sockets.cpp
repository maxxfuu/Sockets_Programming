#include <sys/socket.h> 

//socket descriptors is a type int. 

struct addrinfo {
    int             ai_flags; 
    int             ai_family; 
    int             ai_sockettype; 
    int             ai_protocol; 
    size_t          ai_addrlen; 
    struct sockaddr *ai_addr; 
    char            *ai_canonname; 
    
    struct addrinfo *ai_next; 
}; 
