#include "Lig4.hpp"
#include "JogoDaVelha.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

int main(){
    Jogador jogador1("Super", "Gabriel"), jogador2("Pokow19", "Pedro");
    Lig4 c4(5);

    c4.Jogar(jogador1, jogador2);
    return 0;
}