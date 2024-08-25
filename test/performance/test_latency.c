#include "test_utils.h" 

double measure_latency(int sockfd, int iterations) {
    char ping[5] = "PING";
    char pong[5];
    struct timeval start, end;
    double total_time = 0;
    
    for (int i = 0; i < iterations; i++) {
        gettimeofday(&start, NULL);
        send(sockfd, ping, sizeof(ping), 0);
        recv(sockfd, pong, sizeof(pong), 0);
        gettimeofday(&end, NULL);
        
        total_time += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    }
    
    return (total_time / iterations) * 1000; // Average latency in ms
}
