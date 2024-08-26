#include "../include/server/socket_server.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(MYPORT));
       
    if(inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Enter test mode
    send(sock, "TEST_MODE", 9, 0);
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);
    if (strcmp(buffer, "TEST_MODE_ACK") != 0) {
        printf("Failed to enter test mode\n");
        return -1;
    }
    
    printf("Running throughput test...\n");
    double throughput = measure_throughput(sock, 1024 * 1024, 100);
    printf("Throughput: %.2f Mbps\n", throughput);

    printf("Running latency test...\n");
    double latency = measure_latency(sock, 1000);
    printf("Average Latency: %.2f ms\n", latency);

    printf("Running error rate test...\n");
    double error_rate = measure_error_rate(sock, 1024, 1000);
    printf("Error Rate: %.2f%%\n", error_rate * 100);

    close(sock);
    return 0;
}