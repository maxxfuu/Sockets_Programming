#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>

double measure_throughput(int sockfd, int data_size, int iterations) {
    char *data = malloc(data_size);
    if (!data) {
        perror("Failed to allocate memory");
        return -1;
    }
    memset(data, 'A', data_size);
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < iterations; i++) {
        int bytes_sent = 0;
        while (bytes_sent < data_size) {
            int ret = send(sockfd, data + bytes_sent, data_size - bytes_sent, 0);
            if (ret == -1) {
                if (errno == EINTR) continue;
                perror("send failed");
                free(data);
                return -1;
            }
            bytes_sent += ret;
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    free(data);
    
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    double throughput = (data_size * iterations * 8.0) / (time_taken * 1e6); // Mbps
    
    return throughput;
}