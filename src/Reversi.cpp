#include "Reversi.hpp"

Reversi::Reversi(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n + 1, ' '));
}

void Reversi::Jogar(Jogador& Jogador1, Jogador& Jogador2) {}

bool Reversi::checarVencedor() {}

bool Reversi::checarJogada() {}