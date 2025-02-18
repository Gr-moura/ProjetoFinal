#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "Jogos.hpp"
class Reversi : public Jogos
{
  public:
    Reversi();
    Reversi(int tamanhoTabuleiro);
    void Jogar(Jogador &Jogador1, Jogador &Jogador2) override;

  protected:
    void anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    std::pair<int, int> lerJogada(bool turno);

    void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) override;
    bool movimentoValido(std::pair<int, int> &jogada, char jogador, std::vector<std::pair<int, int>> &flips);
    bool haMovimentosDisponiveis(char Jogador);

    void limparTabuleiro() override;
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor)
    {
        return false;
    };
    bool checarVencedor();
    bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override { return false; };

    Jogador *JogadorX = nullptr;
    Jogador *JogadorO = nullptr;
    int ContadorTurnos = 0;

    friend class ReversiTestes;
};

#endif