CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++11
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/ProjetoFinal

# Detect OS
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    RMDIR = if exist "$(1)" rmdir /s /q "$(1)"
else
    MKDIR = mkdir -p $(1)
    RMDIR = rm -rf $(1)
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(call MKDIR,$(BIN_DIR))
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Executable created at $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(call MKDIR,$(OBJ_DIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(call RMDIR,$(OBJ_DIR))
	$(call RMDIR,$(BIN_DIR))
	@echo "Cleaned up build files"

.PHONY: all clean
