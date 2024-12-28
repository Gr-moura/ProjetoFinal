#include "JogoDaVelhaAi.hpp"
#include <iostream>

#define INFINITY 1000000

// Implementation of the evaluateBoard function for JogoDaVelhaAi
int JogoDaVelhaAi::evaluateBoard(const board_t &board) const
{
    // Return a positive score if the AI is winning, negative if losing, and 0 for a draw or ongoing game
    int score = 0;

    // Check rows
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == aiPlayer && isAiMaximizingPlayer)
            {
                return +INFINITY;
            }

            return -INFINITY;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == aiPlayer && isAiMaximizingPlayer)
            {
                return +INFINITY;
            }

            return -INFINITY;
        }
    }

    // Check diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == aiPlayer && isAiMaximizingPlayer)
        {
            return +INFINITY;
        }

        return -INFINITY;
    }

    // Check anti-diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == aiPlayer && isAiMaximizingPlayer)
        {
            return +INFINITY;
        }

        return -INFINITY;
    }

    return score;
}

// Implementation of the getAvailableMoves function for JogoDaVelhaAi
std::vector<std::pair<int, int>> JogoDaVelhaAi::getAvailableMoves(const board_t &board) const
{
    std::vector<std::pair<int, int>> availableMoves;

    // Iterate over the board to find empty cells
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (board[i][j] == '-')
            {
                availableMoves.push_back(std::make_pair(i, j));
            }
        }
    }

    return availableMoves;
}

bool JogoDaVelhaAi::isTerminalState(const board_t &board) const
{
    // Check if the board is full or if a player has won
    return getAvailableMoves(board).empty() || evaluateBoard(board) != 0;
}