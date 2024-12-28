#ifndef LIG4AI_H
#define LIG4AI_H

#include "Ai.hpp"

class Lig4Ai : public Ai
{
  public:
    // Evaluate the current board state
    int evaluateBoard(const board_t &board) const override;
    std::vector<std::pair<int, int>> getAvailableMoves(const board_t &board) const override;
    bool isTerminalState(const board_t &board) const override;
};

#endif // LIG4AI_H