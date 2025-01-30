#ifndef JOGOS_HPP
#define JOGOS_HPP

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "Jogador.hpp"

class Jogos
{
  protected:
    std::vector<std::vector<char>> tabuleiro;

    virtual bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) = 0;
    virtual bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) = 0;
    virtual void anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) = 0;

    virtual void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno);

    virtual void limparTabuleiro();

    void anunciarTurnoJogador(Jogador &Jogador);

    virtual bool sorteioTurno();
    virtual bool checarJogadaExistente(std::vector<std::pair<int, int>> &jogadas, int linha, int coluna);
    virtual bool checarPosicaoValida(int linha, int coluna);

    std::string gerarDivisoriaTabuleiro();

    virtual std::pair<int, int> lerJogada() { return {0, 0};};

  public:
    virtual void mostrarTabuleiro();
    virtual void Jogar(Jogador &Jogador1, Jogador &Jogador2);
};

#endif