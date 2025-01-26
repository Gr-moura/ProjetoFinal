#ifndef JOGODAVELHAAI_H
#define JOGODAVELHAAI_H

#include "Ai.hpp"
#include "JogoDaVelha.hpp"

#define TAB_LARGURA 3
#define TAB_ALTURA 3

class JogoDaVelhaAi : public Ai
{
  private:
    int MAX_DEPTH;
    std::vector<std::vector<char>> posicoesAtual;
    int isAiMaximizingPlayer = 1;

    int ganhadorDiagonal(const std::vector<std::vector<char>> &tabuleiro);
    int ganhadorLinha(const std::vector<std::vector<char>> &tabuleiro);
    int ganhadorColuna(const std::vector<std::vector<char>> &tabuleiro);

    int getStaticValue(const std::vector<std::vector<char>> &tabuleiro);

    std::vector<std::pair<int, int>> getMovimentosDisponiveis(const std::vector<std::vector<char>> &tabuleiro);

  public:
    JogoDaVelha jogo;
    JogoDaVelhaAi(int AiComeca) :
        MAX_DEPTH(9), posicoesAtual(TAB_ALTURA, std::vector<char>(TAB_LARGURA, ' ')), isAiMaximizingPlayer(AiComeca)
    {
    }

    int minimax(std::vector<std::vector<char>> tabuleiro, int depth, int alpha, int beta, bool isMaximizingPlayer);

    std::pair<int, int> getMelhorMovimento();

    void marcarTab();
    void marcarTabAi();
};

#endif // JOGODAVELHAAI_H