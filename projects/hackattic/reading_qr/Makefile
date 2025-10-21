# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra
CURL_DIR := C:/lib/curl
INCLUDES := -Iinclude -I$(CURL_DIR)/include
LIBS := -L$(CURL_DIR)/lib -lcurl -lws2_32

# Directories
BUILD_DIR := build
TARGET := $(BUILD_DIR)/main.exe

# Source files
SOURCES := src/main.cpp src/api.cpp

# Build target
all: $(TARGET)

$(TARGET): $(SOURCES)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET) $(LIBS)
	@echo Build complete!

run: $(TARGET)
	./$(TARGET)

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

rebuild: clean all

.PHONY: all run clean rebuild
