#include "Lig4.hpp"

Lig4::Lig4(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n + 1, ' '));
}

Lig4::Lig4(){
  tabuleiro.resize(7, std::vector<char>(6, ' '));
}
