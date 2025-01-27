CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++11 -Wno-unused-parameter
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/ProjetoFinal

all: $(TARGET)

$(TARGET): $(OBJS)
	@if not exist "$(BIN_DIR)" mkdir $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Executable created at $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(OBJ_DIR)" mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist "$(OBJ_DIR)" rmdir /s /q $(OBJ_DIR)
	@if exist "$(BIN_DIR)" rmdir /s /q $(BIN_DIR)
	@echo "Cleaned up build files"

.PHONY: all clean
