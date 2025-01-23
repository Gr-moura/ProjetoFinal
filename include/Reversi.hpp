#include "Jogos.hpp"

class Reversi : public Jogos {
 private:
  int n;

 public:
  Reversi(int tamanho) {}
  
  void Jogar(Jogador& Jogador1, Jogador& Jogador2) override;
  bool checarVencedor(std::vector<std::pair<int, int>> &movimentos) override;
  bool checarJogada(int linha, int coluna) override {}

};