# Nome do arquivo de entrada e saída
TARGET = JogoDaVelha 
OUTPUT = $(TARGET).js

# Exported functions
FUNCTIONS = ['_checarVencedor']

# Regra principal
all: $(OUTPUT)

# Regra para compilar o código C++ para WebAssembly
$(OUTPUT): $(TARGET).cpp
	em++ $(TARGET).cpp -o $(OUTPUT) -s EXPORTED_FUNCTIONS=$(FUNCTIONS)  -s EXPORTED_RUNTIME_METHODS=['ccall'] -s MODULARIZE