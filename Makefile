EXEC = vpl_execution

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

CXX = g++
CXXFLAGS = -Wall -I$(INCLUDE_DIR)

SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/list.cpp
OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/list.o

$(EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)