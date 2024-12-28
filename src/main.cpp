#include "Ai.hpp"
#include "JogoDaVelhaAi.hpp"
#include "Jogos.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{
    Jogos tab;
    JogoDaVelhaAi ai;
    int x, y;
    char c = 'X';

    while (true)
    {
        tab.imprime();
        std::cout << "Digite a posição (linha coluna): ";
        std::cin >> x >> y;
        tab.insere(x, y, c);

        c = c == 'X' ? 'O' : 'X';

        auto move = ai.getBestMove(tab.getTabuleiro());
        std::cout << "AI move: " << move.first << " " << move.second << std::endl;

        tab.insere(move.first, move.second, c);

        c = c == 'X' ? 'O' : 'X';
    }

    tab.imprime();
    return 0;
}