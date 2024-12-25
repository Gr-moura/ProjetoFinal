#include "Jogos.hpp"

class Lig4 : public Jogos {
 private:
  int n;

 public:
  Lig4(int tamanho);

  bool checarVencedor() override;
  bool checarJogada() override;
};