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

  virtual void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) = 0;
  virtual void inciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) = 0;
  void iniciarTurno(Jogador &Jogador);

  virtual bool sorteio(); 
  virtual bool checarVencedor(std::vector<std::pair<int, int>> &movimentos) = 0;
  virtual bool checarEmpate(int numeroJogadas);
  std::string gerarDivisoriaTabuleiro();
  virtual std::pair<int, int> lerJogada() = 0;

 public:
  virtual ~Jogos();
  virtual void mostrarTabuleiro();
  virtual void Jogar(Jogador &Jogador1, Jogador &Jogador2);
};

#endif