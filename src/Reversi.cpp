#include "Reversi.hpp"

Reversi::Reversi(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n + 1, ' '));
}

void Reversi::Jogar() {}

bool Reversi::checarVencedor() {}

bool Reversi::checarJogada() {}