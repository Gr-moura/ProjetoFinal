#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <Jogos.hpp>
#include <vector> // For managing board states and moves

class Ai
{
  public:
    /*
      // Constructor
      Ai() : aiPlayer('O'), humanPlayer('X'), depth(9), isAiMaximizingPlayer(false) {}
      // Function to get the best move for the AI
      virtual std::pair<int, int> getBestMove() = 0;

      // Setters for AI and Human player symbols ( "X" or "O" )
      void setAiPlayer(char aiPlayer) { this->aiPlayer = aiPlayer; }
      void setHumanPlayer(char humanPlayer) { this->humanPlayer = humanPlayer; }

      // Setters for AI depth and starting player (AI or Human)
      void setDifficulty(int depth) { this->depth = depth; }
      void setStartingPlayer(bool isAiStartingPlayer) { this->isAiMaximizingPlayer = isAiStartingPlayer; }
  */
  protected:
    /*
    // Character symbols for AI and Human players
      char aiPlayer;
      char humanPlayer;
      int depth;
      bool isAiMaximizingPlayer;

      // Minimax algorithm with alpha-beta pruning
      int minimax() const = 0;

      // Evaluate the current board state
      virtual int evaluateBoard() const = 0;

      // Get all available moves on the board
      virtual std::vector<std::pair<int, int>> getAvailableMo) const = 0;

      // Utility to check if the board state is terminal
      virtual bool isTerminalState() const = 0;
      */
};

#endif // MINIMAX_HPP
