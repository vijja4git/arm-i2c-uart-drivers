# ---------------------------------------------------------------------------
# Makefile for ARM I2C + UART Driver Simulation Project
# Builds:
#   - main application  -> build/main
#   - unit tests        -> build/tests
#
# This Makefile is designed to compile on macOS/Linux using GCC.
# No ARM hardware required — HAL is fully simulated.
# ---------------------------------------------------------------------------

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude -Idrivers -Isrc -Itests

# Output folders
BUILD_DIR = build
APP_OUT = $(BUILD_DIR)/main
TEST_OUT = $(BUILD_DIR)/tests

# Source files
APP_SRC = \
    src/main.c \
    drivers/uart.c \
    drivers/i2c.c \
    hal/hal_uart.c \
    hal/hal_i2c.c

TEST_SRC = \
    tests/test_i2c_uart.c \
    drivers/uart.c \
    drivers/i2c.c \
    hal/hal_uart.c \
    hal/hal_i2c.c

# Create build directory
$(shell mkdir -p $(BUILD_DIR))

# ---------------------------------------------------------------------------
# Build main application
# ---------------------------------------------------------------------------
app: $(APP_SRC)
	$(CC) $(CFLAGS) $^ -o $(APP_OUT)
	@echo ""
	@echo "Build complete -> $(APP_OUT)"

# ---------------------------------------------------------------------------
# Build unit tests
# ---------------------------------------------------------------------------
test: $(TEST_SRC)
	$(CC) $(CFLAGS) $^ -o $(TEST_OUT)
	@echo ""
	@echo "Running tests..."
	./$(TEST_OUT)

# ---------------------------------------------------------------------------
# Clean generated files
# ---------------------------------------------------------------------------
clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build outputs."

# Default target
all: app test
