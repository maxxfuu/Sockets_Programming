An API (Application Programming Interface) in general can be through of as a set of rules, protocols, and tools taht allow different software application communicate with each other. In the specific case of Network Programming, the socket API in C is a specific interface that allows programs to create and manage network connection. 

To success in writing a TCP/IP Client-Server model, more than half of the battle is about understanding the socket api. Sockets API as mentioned previously can enable communication between process on different machines over a network. How the communication happens can be categorized by different Networking Protocols Such as TCP or UDP and many more. 

Header files:
```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
```
```c
Key functions in the socket API:
socket(): Creates a new socket
bind(): Associates a socket with a specific address and port
listen(): Marks a socket as passive, ready to accept incoming connections
accept(): Accepts an incoming connection attempt on a socket
connect(): Initiates a connection on a socket
send()/recv(): Send or receive data on a connected socket
close(): Closes a socket
```
```c
Socket types:
Stream sockets (SOCK_STREAM): For TCP connections
Datagram sockets (SOCK_DGRAM): For UDP connections
```

