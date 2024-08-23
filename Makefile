# Makefile to compile all C files in the "src" directory and its subdirectories into an executable

CC = clang
CFLAGS = -Wall -O3
CFLAGS += -D_CRT_SECURE_NO_WARNINGS
DEBUG_FLAGS = -g -O0  # Debug flags: -g for debug info, -O0 to disable optimization
INCLUDES = -Iinclude
SRCDIR = src
BUILD_DIR = build
TARGET = mp3_rng_util.exe
SOURCES = $(shell find $(SRCDIR) -name '*.c')

# Object files (generated in the "build" directory)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target (build the executable)
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	@echo "Compiled successfully: $(TARGET)"

# Rule to build the debug version of the executable
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Rule to compile C source files into object files
$(BUILD_DIR)/%.o: $(SRCDIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D) # Ensure the build directory exists
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create the "build/" directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean up the generated files
clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)

.PHONY: all clean debug
