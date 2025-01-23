#include "Reversi.hpp"

Reversi::Reversi(int tamanhoTabuleiro){
  tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro + 1, ' '));
}

void Reversi::Jogar(Jogador& Jogador1, Jogador& Jogador2) {
    // Implementar;
    return;
}

bool Reversi::checarVencedor(std::vector<std::pair<int, int>> &movimentos) {
    // Implementar;
    return true;
}

bool Reversi::checarJogada(int linha, int coluna) {
    // Implementar;
    return true;
}