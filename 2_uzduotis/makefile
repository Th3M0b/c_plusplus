# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Files
SRC = BST.cpp
MAIN = main.cpp
TEST = test.cpp
HEADER = BST.h
TARGET = bst_program
TEST_TARGET = bst_test
RESULTS = test_results.txt

# Targets
.PHONY: all build test clean demo

# Default target (builds everything)
all: build test

# Build main program (demo)
build: $(TARGET)

# Build test executable
test: $(TEST_TARGET)

# Run tests and save results
run_tests: $(TEST_TARGET)
	@echo "Running tests..."
	@./$(TEST_TARGET) | tee $(RESULTS)
	@echo "Test results saved to $(RESULTS)"

# Run demo program
demo: $(TARGET)
	@./$(TARGET)

# Clean everything
clean:
	@rm -f $(TARGET) $(TEST_TARGET) *.o $(RESULTS)
	@echo "Cleaned all build files"

# Compile main program
$(TARGET): $(MAIN) $(SRC) $(HEADER)
	@$(CXX) $(CXXFLAGS) $(MAIN) $(SRC) -o $(TARGET)
	@echo "Main program built successfully!"

# Compile tests
$(TEST_TARGET): $(TEST) $(SRC) $(HEADER)
	@$(CXX) $(CXXFLAGS) $(TEST) $(SRC) -o $(TEST_TARGET)
	@echo "Test program built successfully!"