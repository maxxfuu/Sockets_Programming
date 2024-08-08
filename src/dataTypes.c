// Linked List Data Structure 

struct addrinfo {

    int ai_flags;
    int ai_family;                  
    int ai_socktype; 
    int ai_protocol; 
    size_t ai_addrlen; 

    struct sockaddr *ai_addr; // pointer to the struct sockaddr  
    char *ai_canonname;

    struct addrinfo *ai_next; 

};  

struct sockaddr { // holds socket address information for many types of sockets. 

    unsigned short  sa_family; // Store AF_INET(IPv4) or AF_INET6(IPv6) 
    char            sa_data[14]; // Holds contains a destination address and port number for the socket. 
}; 


struct sockaddr_in { // Parallel structure to be used with exclusively IPv4 (in - internet, s - socket) 

    short int           sin_family; 
    unsigned short int  sin_port; 
    struct in_addr      sin_addr; 
    unsigned char       sin_zero[8]; 

}; 

struct in_addr { 

    uint32_t s_addr; // Holds 32-bit ints
    
}; 

struct sockaddr_in6 {
    u_int16_t       sin6_family;   // address family, AF_INET6
    u_int16_t       sin6_port;     // port number, Network Byte Order
    u_int32_t       sin6_flowinfo; // IPv6 flow information
    struct in6_addr sin6_addr;     // IPv6 address
    u_int32_t       sin6_scope_id; // Scope ID
};

struct in6_addr {
    unsigned char   s6_addr[16];   // IPv6 address
}; 


struct sockaddr_storage {           // Stores both IPv4 and IPv6 ip addresses  
    sa_family_t ss_family; 

}; 

struct 
