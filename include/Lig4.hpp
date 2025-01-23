#include "Jogos.hpp"

class Lig4 : public Jogos {
 private:
  int n;

 public:
  Lig4(int tamanho);
  Lig4();
  bool checarVencedor(std::vector<std::pair<int, int>> &movimentos) override;
  
};