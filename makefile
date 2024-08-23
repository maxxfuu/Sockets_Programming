# Define the com# Define the compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -pthread -Iinclude

# Define directories
SRC_DIR = src
OBJ_DIR = obj

# Define targets
SERVER = server
CLIENT = client

# Define source files
SERVER_SRC = $(SRC_DIR)/socket_server.c $(SRC_DIR)/main_server.c
CLIENT_SRC = $(SRC_DIR)/socket_client.c $(SRC_DIR)/main_client.c

# Define object files
SERVER_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CLIENT_SRC))

# Default target
all: $(SERVER) $(CLIENT)

# Compile server
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile client
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -f $(SERVER) $(CLIENT) $(OBJ_DIR)/*.o

.PHONY: all clean