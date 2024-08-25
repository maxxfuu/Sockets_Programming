#include "test_utils.h"

double measure_throughput(int sockfd, int data_size, int iterations) {
    char *data = malloc(data_size);
    memset(data, 'A', data_size);
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < iterations; i++) {
        send(sockfd, data, data_size, 0);
    }
    
    gettimeofday(&end, NULL);
    free(data);
    
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    double throughput = (data_size * iterations * 8) / (time_taken * 1e6); // Mbps
    
    return throughput;
}