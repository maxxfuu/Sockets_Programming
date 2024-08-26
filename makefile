# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -pthread -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
BIN_DIR = bin

# Source files
SERVER_SRC = $(wildcard $(SRC_DIR)/server/*.c)
CLIENT_SRC = $(wildcard $(SRC_DIR)/client/*.c)
TEST_SRC = $(wildcard $(TEST_DIR)/performance/*.c) $(TEST_DIR)/test_main.c

# Object files
SERVER_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CLIENT_SRC))
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/test/%.o,$(TEST_SRC))

# Executables
SERVER = $(BIN_DIR)/server
CLIENT = $(BIN_DIR)/client
TEST_RUNNER = $(BIN_DIR)/test_runner

# Targets
.PHONY: all clean test

all: $(SERVER) $(CLIENT) $(TEST_RUNNER)

$(SERVER): $(SERVER_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_RUNNER): $(TEST_OBJ) $(filter-out $(OBJ_DIR)/server/main_server.o $(OBJ_DIR)/client/main_client.o, $(SERVER_OBJ) $(CLIENT_OBJ)) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

test: $(TEST_RUNNER)
	./$(TEST_RUNNER)