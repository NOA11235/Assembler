# Compiler and flags
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

# Source files
SRCS = src/assembler.c src/first_pass.c src/second_pass.c src/first_pass_utils.c \
	   src/second_pass_utils.c src/first_pass_table_utils.c src/second_pass_table_utils.c \
	   src/data_utils.c src/instruction_utils.c src/parser_utils.c src/defs.c

# Header files
HDRS = $(wildcard include/*.h)

# Object files
OBJS = $(SRCS:src/%.c=build/%.o)

# Executable name
TARGET = assembler

# Default target
all: $(TARGET)

# Compile source files into object files
build/%.o: src/%.c $(HDRS)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# Rule to build the executable file
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET) *.ent *.ob *.ext
