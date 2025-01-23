#include "Jogos.hpp"

class Reversi : public Jogos {
 public:
  Reversi(int tamanhoTabuleiro);
  
  void Jogar(Jogador& Jogador1, Jogador& Jogador2) override;
  bool checarVencedor(std::vector<std::pair<int, int>> &movimentos) override;
  bool checarJogada(int linha, int coluna) override;
};