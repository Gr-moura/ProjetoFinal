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
    std::vector<std::vector<int>> posicoesAtual;
    int isAiMaximizingPlayer = 1;

    int ganhadorDiagonal(const std::vector<std::vector<int>> &tabuleiro);
    int ganhadorLinha(const std::vector<std::vector<int>> &tabuleiro);
    int ganhadorColuna(const std::vector<std::vector<int>> &tabuleiro);

    int getStaticValue(const std::vector<std::vector<int>> &tabuleiro);

    std::vector<std::pair<int, int>> getMovimentosDisponiveis(const std::vector<std::vector<int>> &tabuleiro);

  public:
    JogoDaVelhaAi(int AiComeca) :
        MAX_DEPTH(9), posicoesAtual(TAB_ALTURA, std::vector<int>(TAB_LARGURA, 0)), isAiMaximizingPlayer(AiComeca)
    {
    }

    int minimax(std::vector<std::vector<int>> tabuleiro, int depth, int alpha, int beta, bool isMaximizingPlayer);

    std::pair<int, int> getMelhorMovimento();

    void marcarTab();
    void marcarTabAi();
};

#endif // JOGODAVELHAAI_H