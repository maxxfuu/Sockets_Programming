#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdlib.h>


# define PORT 8000 // Up for definition 
# define BACKLOG 5

struct in_addr {
    in_addr_t s_addr;  // base type for internet address - in_addr & s_ddr holds 32-bit in binary representing IPv4 address
};


struct sockaddr_in { // Parallel structure to be used with exclusively IPv4 (in - internet, s - socket) 
    short int           sin_family; 
    unsigned short int  sin_port; 
    unsigned char       sin_zero[8]; 
    struct in_addr      sin_addr; 
}; 


int main() {
    int listenfd = 0, connfd = 0; // listen_file_descriptor     connection_file_descriptor 
    
    if (listenfd = socket(AF_INET, SOCK_STREAM, 0) == 0) {
        perror("Socke Failed: "); 
        exit(EXIT_FAILURE); 
    }

    struct sockaddr_in serv_addr; // Initalizng a struct object representing server address. ( 4 fields )
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    serv_addr.sin_addr.s_addr = INADDR_ANY;  
    
    




} 

// socket(Specifies IPv4 or IPv6, Specifies TCP or UDP and SOCK_STREAM is TCP, 0 lets the system choose the appropriate protocol