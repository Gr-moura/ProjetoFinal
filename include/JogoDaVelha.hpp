#include "Jogos.hpp"

class JogoDaVelha : public Jogos {
 public:
  JogoDaVelha();
  JogoDaVelha(int tamanhoTabuleiro);
protected:
  void inciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

  std::pair<int, int> lerJogada() override;

  bool checarDiagonal(std::vector<std::pair<int, int>> &jogadas);
  bool checarColunas(std::vector<std::pair<int, int>> &jogadas);
  bool checarLinhas(std::vector<std::pair<int, int>> &jogadas);
  bool checarVencedor(std::vector<std::pair<int, int>> &jogadas) override;
};