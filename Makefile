# Compilador a ser utilizado
CXX = g++

# Flags do compilador:
# -Iinclude: adiciona o diretório 'include' ao caminho de busca de cabeçalhos.
# -Wall -Wextra: ativa avisos adicionais para evitar erros comuns.
# -std=c++11: especifica a versão do padrão C++ a ser usada (C++11).
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++11

# Flags do linker (pode ser deixado vazio se não houver opções específicas).
LDFLAGS =

# Diretórios do projeto
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Arquivos-fonte: obtém todos os arquivos .cpp do diretório src.
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos-objeto: converte cada arquivo .cpp em .o dentro de obj/.
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Nome do executável final
TARGET = $(BIN_DIR)/ProjetoFinal

# Detecta o sistema operacional
# Se for Windows, usa comandos do Windows (if not exist e rmdir).
# Caso contrário, usa comandos UNIX (mkdir -p e rm -rf).
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    RMDIR = if exist "$(1)" rmdir /s /q "$(1)"
else
    MKDIR = mkdir -p $(1)
    RMDIR = rm -rf $(1)
endif

# Regra principal: compila todo o projeto e gera o executável final
all: $(TARGET)

# Regras para gerar o executável
# 1. Garante que o diretório bin/ exista (usa $(call MKDIR)).
# 2. Compila todos os arquivos objeto e cria o executável final.
# 3. Exibe uma mensagem de sucesso.
$(TARGET): $(OBJS)
	$(call MKDIR,$(BIN_DIR))
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Executable created at $(TARGET)"

# Regra para compilar arquivos-fonte (.cpp) em arquivos-objeto (.o)
# 1. Garante que o diretório obj/ exista (usa $(call MKDIR)).
# 2. Compila cada arquivo .cpp em um arquivo .o correspondente.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(call MKDIR,$(OBJ_DIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados pela compilação
# Remove os diretórios obj/ e bin/ e exibe uma mensagem.
clean:
	$(call RMDIR,$(OBJ_DIR))
	$(call RMDIR,$(BIN_DIR))
	@echo "Cleaned up build files"

# Declara as regras que não são arquivos reais
.PHONY: all clean
