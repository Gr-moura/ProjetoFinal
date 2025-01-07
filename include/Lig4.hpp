#include "Jogos.hpp"

class Lig4 : public Jogos {
 private:
  int n;

 public:
  Lig4(int tamanho);

  bool checarVencedor(std::vector<std::pair<int, int>>&, int) override;
  bool checarDiagonais(std::vector<std::pair<int, int>>&, int);
  bool checarColunas(std::vector<std::pair<int, int>>&, int);
  bool checarLinhas(std::vector<std::pair<int, int>>&, int);
};