#include "../test/test_utils.h"
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define TIMEOUT_SECONDS 5

double measure_latency(int sockfd, int iterations) {
    char ping[5] = "PING";
    char pong[5];
    struct timeval start, end, timeout;
    double total_time = 0;
    
    // Set receive timeout
    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof timeout) < 0) {
        perror("setsockopt failed");
        return -1;
    }

    for (int i = 0; i < iterations; i++) {
        printf("Iteration %d: Sending PING...\n", i+1);
        gettimeofday(&start, NULL);
        
        if (send(sockfd, ping, sizeof(ping), 0) < 0) {
            perror("send failed");
            return -1;
        }

        printf("Waiting for PONG...\n");
        int recv_bytes = recv(sockfd, pong, sizeof(pong), 0);
        if (recv_bytes < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                printf("recv timed out\n");
            } else {
                perror("recv failed");
            }
            return -1;
        } else if (recv_bytes == 0) {
            printf("Server closed the connection\n");
            return -1;
        }

        gettimeofday(&end, NULL);
        
        if (strncmp(pong, "PONG", 4) != 0) {
            printf("Received unexpected response: %.*s\n", recv_bytes, pong);
            return -1;
        }

        printf("PONG received\n");
        
        total_time += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    }
    
    return (total_time / iterations) * 1000; // Average latency in ms
}