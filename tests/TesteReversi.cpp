#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Reversi.hpp"
#include "Jogador.hpp"

// Classe de teste para acessar membros privados
class ReversiTestes {
public:
    static void testAnunciarInicioPartida(Reversi& reversi, Jogador& jogador1, Jogador& jogador2, bool& turno) {
        reversi.anunciarInicioPartida(jogador1, jogador2, turno);
    }

    static std::pair<int, int> testLerJogada(Reversi& reversi, bool turno) {
        return reversi.lerJogada(turno);
    }

    static void testMarcarTabuleiro(Reversi& reversi, std::pair<int, int>& jogada, bool& turno) {
        reversi.marcarTabuleiro(jogada, turno);
    }

    static bool testMovimentoValido(Reversi& reversi, std::pair<int, int>& jogada, char jogador, std::vector<std::pair<int, int>>& flips) {
        return reversi.movimentoValido(jogada, jogador, flips);
    }

    static bool testHaMovimentosDisponiveis(Reversi& reversi, char jogador) {
        return reversi.haMovimentosDisponiveis(jogador);
    }

    static void testLimparTabuleiro(Reversi& reversi) {
        reversi.limparTabuleiro();
    }

    static bool testChecarVencedor(Reversi& reversi) {
        return reversi.checarVencedor();
    }

    static std::vector<std::vector<char>> testGetTabuleiro(Reversi& reversi){
        return reversi.tabuleiro;
    }
};

// Testes
TEST_CASE("Testando o construtor padrão") {
    Reversi reversi;
    CHECK(ReversiTestes::testGetTabuleiro(reversi).size()==8);
}

TEST_CASE("Testando a função privada movimentoValido") {
    Reversi reversi;
    std::pair<int, int> jogada = {0, 0};
    char jogador = 'X';
    std::vector<std::pair<int, int>> flips;

    ReversiTestes::testLimparTabuleiro(reversi);

    CHECK(ReversiTestes::testMovimentoValido(reversi, jogada, jogador, flips) == false);
}

TEST_CASE("Testando a função privada haMovimentosDisponiveis") {
    Reversi reversi;
    char jogador = 'X';

    CHECK(ReversiTestes::testHaMovimentosDisponiveis(reversi, jogador) == true); 
}

TEST_CASE("Testando a função privada limparTabuleiro") {
    Reversi reversi;

    ReversiTestes::testLimparTabuleiro(reversi);
}

TEST_CASE("Testando a função privada checarVencedor") {
    Reversi reversi;

    CHECK(ReversiTestes::testChecarVencedor(reversi) == false); 
}