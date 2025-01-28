#ifndef JOGODAVELHAAI_HPP
#define JOGODAVELHAAI_HPP

#include "JogoDaVelha.hpp"
#include "Jogos.hpp"
#include <iostream>
#include <vector>

const int BOARD_SIZE = 9;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
class JogoDaVelhaAi
{
  public:
    JogoDaVelhaAi();
    void playGame();
    void Jogar(Jogador &Jogador1, Jogador &Jogador2);

  private:
    int MAX_DEPTH;

    JogoDaVelha jogo;
    std::vector<char> board;

    bool checkWin(char player) const;
    bool isBoardFull() const;
    int minimax(bool isMaximizing, int depth);
    int getBestMove();

    std::pair<int, int> humanMove(bool turno);
    std::pair<int, int> aiMove(bool turno);
};

#endif