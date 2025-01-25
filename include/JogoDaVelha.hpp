#include "Jogos.hpp"

class JogoDaVelha : public Jogos
{
  public:
    JogoDaVelha();
    JogoDaVelha(int tamanhoTabuleiro);

  protected:
    void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) override;
    void iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    std::pair<int, int> lerJogada() override;

    bool checarDiagonal(std::vector<std::pair<int, int>> &movimentos);
    bool checarColunas(std::vector<std::pair<int, int>> &movimentos);
    bool checarLinhas(std::vector<std::pair<int, int>> &movimentos);
    bool checarVencedor(std::vector<std::pair<int, int>> &movimentos) override;

    friend class JogoDaVelhaAi; // Declara JogoDaVelhaAi como amiga
};