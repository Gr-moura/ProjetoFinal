#ifndef JOGODAVELHAAI_HPP
#define JOGODAVELHAAI_HPP

#include "JogoDaVelha.hpp"
#include <iostream>
#include <vector>

const int BOARD_SIZE = 9;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
class TicTacToe
{
  public:
    TicTacToe();
    void playGame();
    JogoDaVelha jogo;

  private:
    std::vector<char> board;
    bool humanTurn;

    void printBoard() const;
    bool checkWin(char player) const;
    bool isBoardFull() const;
    int minimax(bool isMaximizing);
    int getBestMove();
    void humanMove();
    void aiMove();
};

#endif