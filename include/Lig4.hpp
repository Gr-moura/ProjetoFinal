#include "Jogos.hpp"

class Lig4 : public Jogos {
 public:
  Lig4(int tamanhoTabuleiro);
  Lig4();
  
 protected:
  void iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;
  

  bool checarDiagonal(std::vector<std::pair<int, int>> &jogadas);
  bool checarColunas(std::vector<std::pair<int, int>> &jogadas);
  bool checarLinhas(std::vector<std::pair<int, int>> &jogadas);
  bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) override;
  bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override;
  std::pair<int, int> lerJogada() override;
};
