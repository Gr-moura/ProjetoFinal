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
#include <iostream>
#include <fstream>

#include "Jogador.hpp"

class Jogos {
 protected:
  std::vector<std::vector<char>> tabuleiro;

  virtual void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno);
  virtual void limparTabuleiro();
  virtual void iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) = 0;
  void iniciarTurno(Jogador &Jogador);


  virtual bool sorteio(); 
  virtual bool checarJogadaExistente(std::vector<std::pair<int, int>> &jogadas, int linha, int coluna);
  virtual bool checarPosicaoValida(int linha, int coluna);
  virtual bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor, bool turno) = 0;
  virtual bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) = 0;
  std::string gerarDivisoriaTabuleiro();
  virtual std::pair<int, int> lerJogada() = 0;
  virtual std::pair<int, int> lerJogadaReversi(bool turno);

 public:
  virtual ~Jogos();
  virtual void mostrarTabuleiro();
  virtual void Jogar(Jogador &Jogador1, Jogador &Jogador2);
  virtual void JogarReversi(Jogador &Jogador1, Jogador &Jogador2);
};

#endif