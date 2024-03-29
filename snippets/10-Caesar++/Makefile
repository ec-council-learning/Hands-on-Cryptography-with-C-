# Makefile
EXECUTABLE_FILE = Caesar++
TARGET_DIR = .
BUILD_DIR = ./build
SOURCES_DIR = ./src

TARGET = $(TARGET_DIR)/$(EXECUTABLE_FILE)

CC = clang++ -arch x86_64
XX_FLAGS = -std=c++11
CXX = $(CC) $(XX_FLAGS)

SOURCES = $(shell find $(SOURCES_DIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

${TARGET}: clean $(OBJECTS)
	@echo "Linking $(TARGET)"; $(CC) $(OBJECTS) -o $(TARGET) -lcryptopp
	@chmod a+x $(TARGET)
	@echo ""
	@echo "Caesar++ built successfully"
	@echo "To run Caesar++, use: $(TARGET)"

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@echo "Compiling $<..."; $(CXX) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)
