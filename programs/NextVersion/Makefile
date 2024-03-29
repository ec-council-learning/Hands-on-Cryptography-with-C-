# This file is part of the programs built in the online
# course: Hands-On Cryptography with C++ for ECCouncil.
#
# Following commands are available:
#
# - make start
# - make install
# - make clean
#
EXECUTABLE_FILE = NextVersion
TARGET_DIR = .
BUILD_DIR = ./build
SOURCES_DIR = ./src

TARGET = $(TARGET_DIR)/$(EXECUTABLE_FILE)

CC = clang++ -arch x86_64
XX_FLAGS = -std=c++2b
CXX = $(CC) $(XX_FLAGS)

SOURCES = $(shell find $(SOURCES_DIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

start:
	@$(TARGET)

install: clean $(OBJECTS)
	@echo "Linking..."
	@echo "Linking $(TARGET)"; $(CC) $(OBJECTS) -o $(TARGET)
	@chmod a+x $(TARGET)
	@echo ""
	@echo "NextVersion built successfully with $(XX_FLAGS)"
	@echo "Compiled assets can be found in $(OUTDIR)"
	@echo "To run NextVersion, use: $(TARGET)"

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@echo "Compiling $<..."; $(CXX) -c -o $@ $< -I.

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)