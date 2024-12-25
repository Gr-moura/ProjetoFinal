#ifndef JOGOS_HPP
#define JOGOS_HPP

#include <iostream>
#include <string>
#include <vector>

class Jogador;

class Jogos {
 protected:
  std::vector<std::vector<char>> tabuleiro;

 public:
  virtual ~Jogos();

  virtual void mostrarTabuleiro();
  std::string gerarDivisoriaTabuleiro();
  virtual bool checarJogada() = 0;
  virtual bool checarVencedor() = 0;
  virtual void Jogar(Jogador& Jogador1, Jogador& Jogador2);
};

#endif