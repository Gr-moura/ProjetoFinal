CC = g++
CFLAGS = -std=c++11 -Wall -Iinclude
INCLUDE_DIR = include
OBJ_DIR = build
BIN = main

all: $(BIN)

$(BIN): $(OBJ_DIR)/main.o $(OBJ_DIR)/Ai.o $(OBJ_DIR)/JogoDaVelhaAi.o $(OBJ_DIR)/Lig4Ai.o $(OBJ_DIR)/Tabuleiro.o
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Ai.hpp $(INCLUDE_DIR)/JogoDaVelhaAi.hpp $(INCLUDE_DIR)/Lig4Ai.hpp $(INCLUDE_DIR)/Tabuleiro.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/Ai.o: $(SRC_DIR)/Ai.cpp $(INCLUDE_DIR)/Ai.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/JogoDaVelhaAi.o: $(SRC_DIR)/JogoDaVelhaAi.cpp $(INCLUDE_DIR)/JogoDaVelhaAi.hpp $(INCLUDE_DIR)/Ai.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/Lig4Ai.o: $(SRC_DIR)/Lig4Ai.cpp $(INCLUDE_DIR)/Lig4Ai.hpp $(INCLUDE_DIR)/Ai.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/Tabuleiro.o: $(SRC_DIR)/Tabuleiro.cpp $(INCLUDE_DIR)/Tabuleiro.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean