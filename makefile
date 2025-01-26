# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Ilookup -Isession -I.

# Find all C source files recursively
SRC = $(wildcard examples/console_playground/*.c protocol/*.c session_server/*.c session_client/*.c services/iso14229-3/*.c services/iso14229-1/*.c lookup/*.c)

# Output binary
TARGET = examples/console_playground/console_playground

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up generated files
clean:
	rm -f $(TARGET)
