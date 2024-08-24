# Define the compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -pthread -Iinclude -Itests

# Define directories
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

# Define targets
SERVER = server
CLIENT = client

# Define source files
SERVER_SRC = $(SRC_DIR)/socket_server.c $(SRC_DIR)/main_server.c
CLIENT_SRC = $(SRC_DIR)/socket_client.c $(SRC_DIR)/main_client.c
TEST_SRC = $(TEST_DIR)/test_throughput.c $(TEST_DIR)/test_latency.c $(TEST_DIR)/test_error_rate.c

# Define object files
SERVER_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CLIENT_SRC))
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Default target
all: $(SERVER) $(CLIENT)

# Compile server
$(SERVER): $(SERVER_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile client
$(CLIENT): $(CLIENT_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files for src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile object files for tests
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -f $(SERVER) $(CLIENT) $(OBJ_DIR)/*.o

.PHONY: all clean