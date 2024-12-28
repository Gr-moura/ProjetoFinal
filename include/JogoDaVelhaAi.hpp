#ifndef JOGODAVELHAAI_H
#define JOGODAVELHAAI_H

#include "Ai.hpp"

class JogoDaVelhaAi : public Ai
{
  public:
    JogoDaVelhaAi() : Ai() {}
    // Evaluate the current board state
    int evaluateBoard(const board_t &board) const override;
    std::vector<std::pair<int, int>> getAvailableMoves(const board_t &board) const override;
    bool isTerminalState(const board_t &board) const override;
};

#endif // JOGODAVELHAAI_H