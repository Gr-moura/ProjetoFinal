#include "Lig4.hpp"
#include "JogoDaVelha.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

int main(){
    Jogador jogador1("Super", "Gabriel"), jogador2("Pokow19", "Pedro");
    JogoDaVelha veia(5);

    veia.mostrarTabuleiro();
    veia.Jogar(jogador1, jogador2);
    return 0;
}