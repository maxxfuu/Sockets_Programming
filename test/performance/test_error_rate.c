double measure_error_rate(int sockfd, int data_size, int iterations) {
    char *send_data = malloc(data_size);
    char *recv_data = malloc(data_size);
    memset(send_data, 'A', data_size);
    
    int errors = 0;
    
    for (int i = 0; i < iterations; i++) {
        send(sockfd, send_data, data_size, 0);
        recv(sockfd, recv_data, data_size, 0);
        
        if (memcmp(send_data, recv_data, data_size) != 0) {
            errors++;
        }
    }
    
    free(send_data);
    free(recv_data);
    
    return (double)errors / iterations;
}