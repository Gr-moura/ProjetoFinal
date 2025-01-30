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
  public:
    virtual void mostrarTabuleiro();
    virtual void mostrarTabuleiro(const std::vector<std::vector<char>> &tabuleiro);
    virtual void Jogar(Jogador &Jogador1, Jogador &Jogador2);

  protected:
    std::vector<std::vector<char>> tabuleiro;

    virtual void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno);
    virtual void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno,
                                 std::vector<std::vector<char>> &tabuleiroJogador,
                                 std::vector<std::pair<int, int>> &barcosJogador);
    virtual void limparTabuleiro();
    virtual void iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) = 0;
    void iniciarTurno(Jogador &Jogador);

    virtual bool sorteio();
    virtual bool checarJogadaExistente(std::vector<std::pair<int, int>> &jogadas, int linha, int coluna);
    virtual bool checarPosicaoValida(int linha, int coluna);
    virtual bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) = 0;
    virtual bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) = 0;

    std::string gerarDivisoriaTabuleiro();

    virtual std::pair<int, int> lerJogada() = 0;
};

#endif