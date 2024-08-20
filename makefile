# Define the compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -pthread

# Define targets
SERVER = server
CLIENT = client

# Define source files
SERVER_SRC = src/socket_server.c src/server_main.c
CLIENT_SRC = src/socket_client.c src/client_main.c

# Define object files
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Default target
all: $(SERVER) $(CLIENT)

# Compile server
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile client
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(SERVER) $(CLIENT) $(SERVER_OBJ) $(CLIENT_OBJ)

.PHONY: all clean