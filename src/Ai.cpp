#include "Ai.hpp"
#include <iostream>

#define INFINITY 1000000
/*
std::pair<int, int> Ai::getBestMove(const board_t &board)
{
    std::pair<int, int> bestMove;
    int bestScore = -INFINITY;

    std::vector<std::pair<int, int>> availableMoves = getAvailableMoves(board);
    std::cout << "getBestMove" << std::endl;

    for (auto move : getAvailableMoves(board))
    {
        int alpha = -INFINITY;
        int beta = INFINITY;

        board_t newBoard = board;
        newBoard[move.first][move.second] = aiPlayer;

        int score = minimax(newBoard, depth, alpha, beta, !isAiMaximizingPlayer);
        std::cout << "Move: " << move.first << " " << move.second << std::endl;
        std::cout << "Score: " << score << std::endl;

        if (isAiMaximizingPlayer && score > bestScore)
        {
            bestScore = score;
            bestMove = std::make_pair(move.first, move.second);
        }

        else if (!isAiMaximizingPlayer && score < bestScore)
        {
            bestScore = score;
            bestMove = std::make_pair(move.first, move.second);
        }
    }

    return std::make_pair(bestMove.first, bestMove.second);
}

int Ai::minimax(const board_t &board, int depth, int alpha, int beta, bool isMaximizing) const
{
    if (depth == 0 or isTerminalState(board))
    {
        std::cout << "minimax" << evaluateBoard(board) << std::endl;
        return evaluateBoard(board);
    }

    if (isMaximizing)
    {
        int bestScore = -INFINITY;

        for (auto move : getAvailableMoves(board))
        {
            board_t newBoard = board;
            newBoard[move.first][move.second] = isAiMaximizingPlayer ? aiPlayer : humanPlayer;

            int score = minimax(newBoard, depth - 1, alpha, beta, false);

            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, score);

            if (beta <= alpha)
            {
                break;
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = INFINITY;

        for (auto move : getAvailableMoves(board))
        {
            board_t newBoard = board;
            newBoard[move.first][move.second] = isAiMaximizingPlayer ? humanPlayer : aiPlayer;

            int score = minimax(newBoard, depth - 1, alpha, beta, true);
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, score);

            if (beta <= alpha)
            {
                break;
            }
        }

        return bestScore;
    }

    return 0;
}
*/