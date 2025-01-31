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

/**
 * @file Jogos.hpp
 * @brief Definição da classe Jogos.
 *
 * Esta classe é uma classe base abstrata que define a interface comum para todos os jogos do sistema.
 * Ela fornece métodos e atributos básicos para gerenciar partidas, como manipulação do tabuleiro,
 * verificação de vitória e empate, e controle de turnos. Classes derivadas, como `JogoDaVelha`,
 * `Lig4`, `Reversi` e `BatalhaNaval`, implementam as funcionalidades específicas de cada jogo.
 *
 * ## Funcionalidades Principais:
 * - Gerenciamento de tabuleiros genéricos.
 * - Controle de turnos entre jogadores.
 * - Verificação de vitória e empate (a serem implementados pelas classes derivadas).
 * - Exibição do tabuleiro e anúncio de turnos.
 * - Sorteio de quem começa a partida.
 *
 * ## Métodos Virtuais Puros:
 * - `checarVencedor`: Verifica se há um vencedor no jogo (deve ser implementado pelas classes derivadas).
 * - `checarEmpate`: Verifica se o jogo terminou em empate (deve ser implementado pelas classes derivadas).
 * - `anunciarInicioPartida`: Anuncia o início da partida e define o jogador que começa (deve ser implementado pelas
 * classes derivadas).
 *
 * ## Métodos Virtuais:
 * - `marcarTabuleiro`: Marca uma jogada no tabuleiro.
 * - `limparTabuleiro`: Limpa o tabuleiro para uma nova partida.
 * - `lerJogada`: Lê a jogada do jogador (pode ser sobrescrito pelas classes derivadas).
 *
 * ## Métodos Públicos:
 * - `mostrarTabuleiro`: Exibe o tabuleiro atual.
 * - `Jogar`: Inicia e gerencia uma partida entre dois jogadores.
 *
 * ## Integração com Outras Classes:
 * - Utiliza a classe `Jogador` para representar os participantes do jogo.
 * - Serve como base para classes de jogos específicos, como `JogoDaVelha`, `Lig4`, `Reversi` e `BatalhaNaval`.
 *
 * @see Jogador, JogoDaVelha, Lig4, Reversi, BatalhaNaval
 */
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

    virtual std::pair<int, int> lerJogada() { return {0, 0}; };

  public:
    virtual void mostrarTabuleiro();
    virtual void Jogar(Jogador &Jogador1, Jogador &Jogador2);
};

#endif