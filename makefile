# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -g -O0

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/a.out

# Source and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.S)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter %.c,$(SOURCES))) \
           $(patsubst $(SRC_DIR)/%.S, $(OBJ_DIR)/%.o, $(filter %.S,$(SOURCES)))

# Default rule: always rebuild
all:
	$(MAKE) clean
	$(MAKE) build

# Build target: compile and link
build: $(TARGET)

# Linking step
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(OBJECTS) -o $@

# Compilation step for C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation step for assembly files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean: remove build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Mark targets as phony
.PHONY: all clean build
