# Compiler and flags
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

# Source files
SRCS = assembler.c first_pass.c second_pass.c first_pass_utils.c second_pass_utils.c \
	   first_pass_table_utils.c second_pass_table_utils.c data_utils.c \
	   instruction_utils.c parser_utils.c defs.c

# Header files
HDRS = $(SRCS:.c=.h) defs.h

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = assembler

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable file
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET) *.ent *.ob *.ext
