#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "Jogos.hpp"
class Reversi : public Jogos {
  public:
   Reversi();
   Reversi(int tamanhoTabuleiro);
  
 protected:
  void iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override; 
  std::pair<int, int> lerJogada() override;
  void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) override;
  bool movimentoValido(std::pair<int, int> &jogada, char jogador, std::vector<std::pair<int, int>> &flips);

  bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor, bool turno) override;
  bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override;
};

#endif