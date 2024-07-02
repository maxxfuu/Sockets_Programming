#include <sys/socket.h> 

#include <sys/types.h> 
#include <netdb.h>


//socket descriptors is a type int. 

struct sockaddr {
    // struct sockaddr holds socket address information for many types of sockets.
    unsigned short  sa_family;          // address family, AF_xxx (AF_INET (IPv4) or AF_INET6 (IPv6))
    char            sa_data[14];        // 14 bytes of destination address. 
}; 


// parallel structure, very similar to struct sockaddr except larger, and then cast it to the type you need:
// designed to hold IPv4 and IPv6 addresses 
struct sockaddr_storage {
    sa_family_t  ss_family;     // address family

    // all this is padding, implementation specific, ignore it:
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
};

struct addrinfo {
    struct addrinfo *ai_next;           // linked list to the next node

    int             ai_flags;           // AI_PASSIVE, AI_CANONNAME, etc.
    int             ai_family;          // AF_INET, AF_INET6, AF_UNSPEC
    int             ai_sockettype;      // SOCK_STREAM, SOCK_DGRAM
    int             ai_protocol;        // use 0 for "any"
    size_t          ai_addrlen;         // size of ai_addr in bytes
    struct sockaddr *ai_addr;           // struct sockaddr_in or _in6
    char            *ai_canonname;      // full canonical hostname
    
}; 

struct in_addr {
    uint32_t s_addr; // 32-bit int (4 bytes)
};

struct sockaddr_in {
    short int                   sin_family;     // Notice sin_family corresponds to sa_family in a struct sockaddr 
    unsigned short int          sin_port;       // Holds Port Number 
    struct in_addr              sin_addr;       // IPv4 address/ 
    unsigned char               sin_zero[8];    // Padding to ensure struct size matches. 
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


// Client Side: Client initates a TCP connection, it binds to a local port number. 
//              specifying the IP  destination IP address  and  port number. 


int getaddrinfo(const char *node, 
                const char *service, 
                const struct addrinfo *hints, 
                struct addrinfo **res);