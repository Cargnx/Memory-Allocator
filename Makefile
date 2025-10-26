# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -std=c11 -I$(INC_DIR)

# Sanitizer flags (compile vs link)
ASAN_CFLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
ASAN_LDFLAGS = -fsanitize=address -fsanitize=undefined

# Directories
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include

# Targets
TARGET = $(BUILD_DIR)/main
TARGET_ASAN = $(BUILD_DIR)/main_asan

# Sources / Objects
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJECTS_ASAN = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_asan.o)
DEPENDS = $(OBJECTS:.o=.d)
DEPENDS_ASAN = $(OBJECTS_ASAN:.o=.d)

# Default
all: $(TARGET)

# Ensure build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Normal build link
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# ASan build link
$(TARGET_ASAN): $(BUILD_DIR) $(OBJECTS_ASAN)
	$(CC) $(ASAN_LDFLAGS) $(OBJECTS_ASAN) -o $(TARGET_ASAN) $(LDFLAGS)

# Normal object build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ASan object build
$(BUILD_DIR)/%_asan.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(ASAN_CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPENDS)
-include $(DEPENDS_ASAN)

# Run normally
run: $(TARGET)
	./$(TARGET)

# Run with ASan & leak detection
test: $(TARGET_ASAN)
	ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 ./$(TARGET_ASAN)

# macOS-only leak inspection via `leaks` tool
test-leaks: $(TARGET_ASAN)
	MallocStackLogging=1 leaks --atExit -- ./$(TARGET_ASAN)

# Cleanup
clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all run test test-leaks clean rebuild
