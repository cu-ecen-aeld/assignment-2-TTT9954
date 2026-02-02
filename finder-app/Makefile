# Compiler: use CROSS_COMPILE if provided, otherwise default gcc
CC := $(CROSS_COMPILE)gcc

# Flags
CFLAGS := -Wall -Werror -g
LDFLAGS :=

# Target executable
TARGET := writer

# Source and object files
SRCS := writer.c
OBJS := $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile step
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

