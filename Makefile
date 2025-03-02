# Define the C++ compiler to use
CXX = g++

# Set compiler flags:
# -g: include debugging information
# -Wall: enable all compiler warnings
# Add -I include helps to find headers
CXXFLAGS = -g -Wall -I include 

# In order to use multi threads
LDFLAGS = -pthread
# Name of the final executable
TARGET = make_gen/main

# Build directory
BUILD_DIR = make_gen

# Source file(s) (you can add more .cpp files here if needed)
SRCS = main.cpp $(wildcard src/*.cpp)

# Object files will be placed in the BUILD_DIR directory
# Automatically generate object file names by replacing .cpp with .o
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Get unique directories of object files
#$(dir $(OBJS)) → make_gen/ make_gen/src/ and sort removes duplicated directory

OBJ_DIRS = $(sort $(dir $(OBJS)))

# Default target that builds the executable
# The all target ensures that the required directories exist before building the final executable
all: $(OBJ_DIRS) $(TARGET)

# Ensure all build directories exist
$(OBJ_DIRS):
	mkdir -p $@

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS)

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp | $(OBJ_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR)
