#ifndef JOGOS_HPP
#define JOGOS_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

class Jogador;

class Jogos {
 protected:
  std::vector<std::vector<char>> tabuleiro;

 public:
  virtual ~Jogos();

  std::string gerarDivisoriaTabuleiro(std::vector<std::vector<char>>&);
  virtual void mostrarTabuleiro();
  virtual bool checarVencedor(std::vector<std::pair<int, int>>&, int) = 0;
  virtual bool checarJogada(int, int, std::vector<std::vector<char>>&);
  bool sorteio();
  virtual void Jogar(Jogador&, Jogador&);
};

#endif