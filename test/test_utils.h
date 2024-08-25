#ifndef TEST_UTILS_H
#define TEST_UTILS_H 
#include <sys/time.h>

double measure_throughput(int sockfd, int data_size, int iterations); 
double measure_latency(int sockfd, int iterations); 
double measure_error_rate(int sockfd, int data_size, int interations); 

#endif 