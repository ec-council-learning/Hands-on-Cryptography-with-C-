# Makefile
EXECUTABLE_FILE = ztx
TARGET_DIR = .
BUILD_DIR = ./build
SOURCES_DIR = ./src

TARGET = $(TARGET_DIR)/$(EXECUTABLE_FILE)

BOTAN_CC = `botan config cflags`
BOTAN_LIBS = `botan config libs`
CRYPTOPP_LIB = "-lcryptopp"

CC = clang++ -arch x86_64
XX_FLAGS = -std=c++20
CXX = $(CC) $(XX_FLAGS) $(BOTAN_CC)

SOURCES = $(shell find $(SOURCES_DIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

${TARGET}: clean $(OBJECTS)
	@echo "Linking $(TARGET)"; $(CC) $(OBJECTS) -o $(TARGET) $(BOTAN_LIBS) $(CRYPTOPP_LIB)
	@chmod a+x $(TARGET)
	@echo ""
	@echo "ZThanks built successfully"
	@echo "To run ZThanks, use: $(TARGET)"

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@echo "Compiling $<..."; $(CXX) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)
