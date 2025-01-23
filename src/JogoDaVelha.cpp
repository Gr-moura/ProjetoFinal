#include "JogoDaVelha.hpp"

JogoDaVelha::JogoDaVelha(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n, ' '));
}

bool JogoDaVelha::checarVencedor(std::vector<std::pair<int, int>>& movimentos) {
  if (!movimentos.empty()) {
    if (checarDiagonal(movimentos) or
        checarColunas(movimentos) or
        checarLinhas(movimentos)) {
      return true;
    }
  }
  return false;
}

bool JogoDaVelha::checarDiagonal(std::vector<std::pair<int, int>>& movimentos) {
  for (int i = 0; i < tabuleiro.size(); i++) {
    auto it =
        std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, i));
    if (it == movimentos.end()) {
      return false;
    }
  }
  return true;
}

bool JogoDaVelha::checarColunas(std::vector<std::pair<int, int>>& movimentos) {
  for (int j = 0; j < tabuleiro.size(); j++) {
    bool colunaCompleta = true;
    for (int i = 0; i < tabuleiro[0].size(); i++) {
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

bool JogoDaVelha::checarLinhas(std::vector<std::pair<int, int>>& movimentos) {
  for (int i = 0; i < tabuleiro.size(); i++) {
    bool linhaCompleta = true;
    for (int j = 0; j < tabuleiro[0].size(); j++) {
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