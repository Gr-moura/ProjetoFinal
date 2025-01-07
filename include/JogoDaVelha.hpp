#include "Jogos.hpp"

class JogoDaVelha : public Jogos {
 private:
  int n;

 public:
  JogoDaVelha(int tamanho);

  bool checarVencedor(std::vector<std::pair<int, int>>&, int) override;
  bool checarDiagonal(std::vector<std::pair<int, int>>&, int);
  bool checarColunas(std::vector<std::pair<int, int>>&, int);
  bool checarLinhas(std::vector<std::pair<int, int>>&, int);
};