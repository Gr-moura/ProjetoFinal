#include "JogoDaVelha.hpp"

JogoDaVelha::JogoDaVelha(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n, ' '));
}

bool JogoDaVelha::checarVencedor(std::vector<std::pair<int, int>>& movimentos,
                                 int tamanho) {
  if (!movimentos.empty()) {
    if (checarDiagonal(movimentos, tamanho) or
        checarColunas(movimentos, tamanho) or
        checarLinhas(movimentos, tamanho)) {
      return true;
    }
  }
  return false;
}

bool JogoDaVelha::checarDiagonal(std::vector<std::pair<int, int>>& movimentos,
                                 int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    auto it =
        std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, i));
    if (it == movimentos.end()) {
      return false;
    }
  }
  return true;
}

bool JogoDaVelha::checarColunas(std::vector<std::pair<int, int>>& movimentos,
                                int tamanho) {
  for (int j = 0; j < tamanho; j++) {
    bool colunaCompleta = true;
    for (int i = 0; i < tamanho; i++) {
      auto it =
          std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, j));
      if (it == movimentos.end()) {
        colunaCompleta = false;
        break;
      }
    }
    if (colunaCompleta) {
      return true;
    }
  }
  return false;
}

bool JogoDaVelha::checarLinhas(std::vector<std::pair<int, int>>& movimentos,
                               int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    bool linhaCompleta = true;
    for (int j = 0; j < tamanho; j++) {
      auto it =
          std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, j));
      if (it == movimentos.end()) {
        linhaCompleta = false;
        break;
      }
    }
    if (linhaCompleta) {
      return true;
    }
  }
  return false;
}