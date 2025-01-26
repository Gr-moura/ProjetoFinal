#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "Jogos.hpp"

 public:class Reversi : public Jogos {

  Reversi();
  Reversi(int tamanhoTabuleiro);
  
 protected:
  void inciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override; 
  std::pair<int, int> lerJogada() override;
  void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) override;
  bool movimentoValido(std::pair<int, int> &jogada, char jogador, std::vector<std::pair<int, int>> &flips);

  bool checarVencedor(std::vector<std::pair<int, int>> &jogadas) override;
};

#endif