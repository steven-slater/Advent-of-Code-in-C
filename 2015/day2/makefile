# Compiler and Linker configuration
CC       := gcc
CFLAGS   := -Wall -Wextra -Wpedantic -std=c11 -O2 -g
LDFLAGS  := 

# Target library (GLib 2.0)
LIB_NAME := glib-2.0

# Dynamic flag gathering via pkg-config
CFLAGS   += $(shell pkg-config --cflags $(LIB_NAME))
LDLIBS   += $(shell pkg-config --libs $(LIB_NAME))

# Build targets and directories
TARGET   := main
SRCS     := $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)
DEPS     := $(SRCS:.c=.d)

# Default rule (runs when you type 'make')
.PHONY: all
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile source files to object files
# -MMD -MP automatically tracks header file dependency changes
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include generated dependency fragments safely
-include $(DEPS)

# Clean up build artifacts
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)
