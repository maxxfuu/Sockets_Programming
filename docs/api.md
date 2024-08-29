# 🔌 Sockets API in C 

## Brief Introduction to Sockets API 
To start, lets define some terminologies to better understand what the Socket API is. 

Firstly, an API (Application Programming Interface) in general can be thought of as a set of rules, protocols, and tools that allow different software application to communicate with each other. In the specific case of this project we implemented an API that is written in C allowing programs to create and manage network connection. 

Secondly, in the broad topic of network programming, it deals with writing programs or process to communicate with other programs or processes across networks. Sockets in the context of network programming and sockets API can be thought of as an endpoint for communication between two nodes on a network. The componenets of a socket consists of an IP address, a port number, and a transport protocol (usually TCP or UDP). 

In this project we created a TCP/IP Client Server Model that uses the C Sockets API. Below are some of the essential functions that are relevant in making this project. 

Header files:
```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
```
Key functions in the socket API:
```c
socket(); // Creates a new socket
bind(); // Associates a socket with a specific address and port
listen(); // Marks a socket as passive, ready to accept incoming connections
accept(); // Accepts an incoming connection attempt on a socket
connect(); // Initiates a connection on a socket
send()/recv(); // Send or receive data on a connected socket
close(); // Closes a socket
```
Socket types:
```c
Stream sockets (SOCK_STREAM); // For TCP connections
Datagram sockets (SOCK_DGRAM); // For UDP connections
```


