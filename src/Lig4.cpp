#include "Lig4.hpp"

Lig4::Lig4(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n + 1, ' '));
}

bool Lig4::checarVencedor() {}

bool Lig4::checarJogada() {}