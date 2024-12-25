#include "JogoDaVelha.hpp"

JogoDaVelha::JogoDaVelha(int tamanho) : n(tamanho) {
  tabuleiro.resize(n, std::vector<char>(n, ' '));
}

bool JogoDaVelha::checarVencedor() {}

bool JogoDaVelha::checarJogada() {}