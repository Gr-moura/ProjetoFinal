#ifndef JOGODAVELHAAI_HPP
#define JOGODAVELHAAI_HPP

#include "JogoDaVelha.hpp"
#include "Jogos.hpp"
#include <iostream>
#include <vector>

const int TABULEIRO_SIZE = 9;
const char VAZIO = ' ';
const char JOGADOR_X = 'X';
const char JOGADOR_O = 'O';
class JogoDaVelhaAi
{
  public:
    JogoDaVelhaAi();
    void Jogar(Jogador &Jogador1, Jogador &Jogador2);

  private:
    int MAX_PROFUNDIDADE;

    JogoDaVelha jogo;
    std::vector<char> tabuleiro;

    bool checarVitoria(char player) const;
    bool isTabuleiroCheio() const;
    int minimax(bool isMaximizing, int depth);
    int getMelhorMovimento();

    std::pair<int, int> jogadaHumano(bool turno);
    std::pair<int, int> jogadaAI(bool turno);
};

#endif