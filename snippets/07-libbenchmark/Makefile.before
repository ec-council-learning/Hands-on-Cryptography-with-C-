EXECUTABLE_FILE = FiboBenchmark
TARGET_DIR = .
BUILD_DIR = ./build
SOURCES_DIR = ./src

TARGET = $(TARGET_DIR)/$(EXECUTABLE_FILE)

CC = clang++ -arch x86_64
XX_FLAGS = -std=c++11
CXX = $(CC) $(XX_FLAGS)

SOURCES = $(shell find $(SOURCES_DIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@echo "Compiling $<..."; $(CXX) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)

install: clean $(OBJECTS)
	@echo "Linking $(TARGET)"; $(CC) $(OBJECTS) -o $(TARGET)
	@chmod a+x $(TARGET)
	@echo ""
	@echo "FiboBenchmark built successfully"
	@echo "Compiled assets can be found in $(OUTDIR)"
	@echo "To run FiboBenchmark, use: $(TARGET)"