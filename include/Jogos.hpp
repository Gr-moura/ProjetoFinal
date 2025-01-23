#ifndef JOGOS_HPP
#define JOGOS_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits>

#include "Jogador.hpp"

class Jogos {
 protected:
  std::vector<std::vector<char>> tabuleiro;

 public:
  virtual ~Jogos();

  std::string gerarDivisoriaTabuleiro();
  virtual void mostrarTabuleiro();
  bool sorteio(); 
  virtual void Jogar(Jogador &Jogador1, Jogador &Jogador2);
  virtual bool checarVencedor(std::vector<std::pair<int, int>> &movimentos) = 0;
  virtual bool checarJogada(int linha, int coluna);
};

#endif