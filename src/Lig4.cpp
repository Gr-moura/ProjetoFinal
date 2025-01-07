#include "Lig4.hpp"

// linhas- -2 pra ganhar, tamanho -2
Lig4::Lig4(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n + 1, ' '));
}

bool Lig4::checarVencedor(std::vector<std::pair<int, int>>& movimentos,
                          int tamanho) {
  if (!movimentos.empty()) {
    while (1) {
      if (checarDiagonais(movimentos, tamanho) or
          checarColunas(movimentos, tamanho) or
          checarLinhas(movimentos, tamanho)) {
      }
    }
  }
}

bool Lig4::checarDiagonais(std::vector<std::pair<int, int>>& movimentos,
                           int tamanho) {
  int count = 0;
  for (int i = 0, j = 0; i < tamanho or j < tamanho + 1; i++, j++) {
    auto it =
        std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, j)) {}
    if (it != movimentos.end()) {
      count++;
    } else {
      count = 0;
    }
    if (count == tamanho - 2) {
      return true;
    }
    count = 0;
    for (int k = 1; k < tamanho; ++k) {
      auto it = std::find(movimentos.begin(), movimentos.end(),
                          std::make_pair(i - k, j - k));
      if (it != movimentos.end()) {
        count++;
      } else {
        count = 0;
      }
      if (count == tamanho - 2) {
        return true;
      }
    }
  }
  return false;
}