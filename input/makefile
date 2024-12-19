# Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

# Source files
SRCS = mainc.c noeud.c data.c 
OBJS = $(SRCS:.c=.o)
TARGET = C-wire

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)