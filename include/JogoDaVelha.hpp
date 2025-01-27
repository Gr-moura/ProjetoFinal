#ifndef JOGODAVELHA_HPP
#define JOGODAVELHA_HPP

#include "Jogos.hpp"

class JogoDaVelha : public Jogos
{
  public:
    JogoDaVelha();
    JogoDaVelha(int tamanhoTabuleiro);

  protected:
    void iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    std::pair<int, int> lerJogada() override;

    bool checarDiagonal(std::vector<std::pair<int, int>> &jogadas);
    bool checarColunas(std::vector<std::pair<int, int>> &jogadas);
    bool checarLinhas(std::vector<std::pair<int, int>> &jogadas);
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor,
                        bool turno) override;
    bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override;

    friend class JogoDaVelhaAi;
};

#endif