// // Building the TCP/IP Stack, 1: ethernet & ARP

// #include <net/if.h>
// #include <fcntl.h> 
// // #include <errno.h> 

// #define IFF_TAP    0x0002  /* TAP device (Ethernet layer 2) */
// #define IFF_NO_PI  0x1000  /* Do not provide packet information */


// // Instantiate a Tap Device to represent L2 and above. 

// int tun_alloc(char *dev) { 

//     struct ifreq interface_request;       // struct ifreq of variable ifr, interface request.  
//     int file_descriptor, error_codes; 

//     if( (file_descriptor = open("/dev/net/tap", O_RDWR)) < 0 ) { //O_RDWR, arguement flags for reading and writing.  
//         print_error("Cannot open TUN/TAP dev"); 
//         exit(1); 
//     } 
    
//     CLEAR(interface_request); 

//     /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
//      *        IFF_TAP   - TAP device
//      *
//      *        IFF_NO_PI - Do not provide packet information
//      */

//     interface_request.ifr_flags = IFF_TAP | IFF_NO_PI; 
//     if (*dev) { 
//         strncpy(interface_request.ifr_name, dev, IFNAMSIZ); 
//     }

//     if( (error_codes = ioctl(file_descriptor, TUNSETIFF, (void * ) &interface_request)) < 0) { 
//         print_error("ERR: COULD NOT IOCTL TUNL: %s\n", strerror(errno)); 
//         close(file_descriptor); 
//         return error_codes; 
//     }

// }