
# This file is part of the programs
# built in the online course: Hands-On Cryptography with C++.
#
# Following commands are available:
#
# - make all
# - make clean
#
EXECUTABLE_FILE = FiboWithLib
TARGET_DIR = .
BUILD_DIR = ./build
SOURCES_DIR = ./src
LIB_PATH = /tmp/lib

TARGET = $(TARGET_DIR)/$(EXECUTABLE_FILE)

CC = clang++ -arch x86_64
XX_FLAGS = -std=c++11
CXX = $(CC) $(XX_FLAGS)

SOURCES = $(shell find $(SOURCES_DIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

start:
	@$(TARGET)

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@echo "Compiling $<..."; $(CXX) -c -o $@ $< -I../libbenchmark/src

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)

install: clean $(OBJECTS)
	@echo "Linking..."
	@echo "Linking $(TARGET)"; $(CC) -L$(LIB_PATH) $(OBJECTS) -o $(TARGET) -lbenchmark
	@chmod a+x $(TARGET)
	@echo ""
	@echo "FiboWithLib built successfully"
	@echo "Compiled assets can be found in $(OUTDIR)"
	@echo "To run FiboWithLib, use: $(TARGET)"
