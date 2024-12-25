#include "Jogos.hpp"

class JogoDaVelha : public Jogos {
 private:
  int n;

 public:
  JogoDaVelha(int tamanho);

  bool checarVencedor() override;
  bool checarJogada() override;
};