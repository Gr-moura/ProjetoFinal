#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./includes/doctest.h"
#include "JogoDaVelha.hpp"
#include "Jogador.hpp"

// Classe de teste para acessar membros privados
class JogoDaVelhaTests {
public:
    std::pair<int, int> testLerJogada(JogoDaVelha& jogo){
        return jogo.lerJogada();
    }

    static bool testChecarPosicaoValida(JogoDaVelha& jogo, int linha, int coluna) {
        return jogo.checarPosicaoValida(linha, coluna);
    }
    static bool testChecarDiagonal(JogoDaVelha& jogo, std::vector<std::pair<int, int>>& jogadas) {
        return jogo.checarDiagonal(jogadas);
    }
    static bool testChecarColunas(JogoDaVelha& jogo, std::vector<std::pair<int, int>>& jogadas) {
        return jogo.checarColunas(jogadas);
    }
    static bool testChecarLinhas(JogoDaVelha& jogo, std::vector<std::pair<int, int>>& jogadas) {
        return jogo.checarLinhas(jogadas);
    }
    static bool testChecarVencedor(JogoDaVelha& jogo, std::vector<std::pair<int, int>>& jogadas, Jogador& vencedor, Jogador& perdedor){
        return jogo.checarVencedor(jogadas, vencedor, perdedor);
    }
    static bool testRetornarEmpate(JogoDaVelha& jogo, int numeroJogadas, Jogador& j1, Jogador& j2){
        return jogo.checarEmpate(numeroJogadas, j1, j2);
    }

    std::vector<std::vector<char>> testRetornarTabuleiro(JogoDaVelha& jogo){
        return jogo.tabuleiro;
    }
    
};


JogoDaVelhaTests testes = JogoDaVelhaTests();

// Testes
TEST_CASE("Testando o construtor padrão") {
    JogoDaVelha jogo;
    CHECK(testes.testRetornarTabuleiro(jogo).size() == 3);
    for (const auto& linha : testes.testRetornarTabuleiro(jogo)) {
        for (char celula : linha) {
            CHECK(celula == ' ');
        }
    }
}

TEST_CASE("Testando o construtor parametrizado") {
    JogoDaVelha jogo(4);
    CHECK(testes.testRetornarTabuleiro(jogo).size() == 4);
    for (const auto& linha : testes.testRetornarTabuleiro(jogo)) {
        for (char celula : linha) {
            CHECK(celula == ' '); // Verifica se todas as células estão vazias
        }
    }
}

TEST_CASE("Testando a função privada checarPosicaoValida") {
    JogoDaVelha jogo;

    // Testes para a função privada checarPosicaoValida
    CHECK(JogoDaVelhaTests::testChecarPosicaoValida(jogo, 0, 0) == true);  // Posição válida
    CHECK(JogoDaVelhaTests::testChecarPosicaoValida(jogo, 2, 2) == true);  // Posição válida
    CHECK(JogoDaVelhaTests::testChecarPosicaoValida(jogo, 3, 3) == false); // Posição inválida
    CHECK(JogoDaVelhaTests::testChecarPosicaoValida(jogo, -1, 0) == false); // Posição inválida
}

TEST_CASE("Testando a função privada checarDiagonal") {
    JogoDaVelha jogo;
    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {1, 1}, {2, 2}};
    CHECK(JogoDaVelhaTests::testChecarDiagonal(jogo, jogadas) == true); // Diagonal principal completa

    jogadas = {{0, 2}, {1, 1}, {2, 0}};
    CHECK(JogoDaVelhaTests::testChecarDiagonal(jogo, jogadas) == true); // Diagonal secundária completa

    jogadas = {{0, 0}, {1, 1}, {2, 1}};
    CHECK(JogoDaVelhaTests::testChecarDiagonal(jogo, jogadas) == false); // Diagonal não completa
}

TEST_CASE("Testando a função privada checarColunas") {
    JogoDaVelha jogo;
    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {1, 0}, {2, 0}};
    CHECK(JogoDaVelhaTests::testChecarColunas(jogo, jogadas) == true); // Coluna completa

    jogadas = {{0, 1}, {1, 1}, {2, 1}};
    CHECK(JogoDaVelhaTests::testChecarColunas(jogo, jogadas) == true); // Coluna completa

    jogadas = {{0, 0}, {1, 1}, {2, 2}};
    CHECK(JogoDaVelhaTests::testChecarColunas(jogo, jogadas) == false); // Coluna não completa
}

TEST_CASE("Testando a função privada checarLinhas") {
    JogoDaVelha jogo;
    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {0, 1}, {0, 2}};
    CHECK(JogoDaVelhaTests::testChecarLinhas(jogo, jogadas) == true); // Linha completa

    jogadas = {{1, 0}, {1, 1}, {1, 2}};
    CHECK(JogoDaVelhaTests::testChecarLinhas(jogo, jogadas) == true); // Linha completa

    jogadas = {{0, 0}, {1, 1}, {2, 2}};
    CHECK(JogoDaVelhaTests::testChecarLinhas(jogo, jogadas) == false); // Linha não completa
}

TEST_CASE("Testando a função lerJogada") {
    JogoDaVelha jogo;
    // Simula uma entrada válida
    std::istringstream inputValido("1 1\n");
    std::cin.rdbuf(inputValido.rdbuf());
    auto jogada = testes.testLerJogada(jogo);
    CHECK(jogada == std::make_pair(0, 0)); // Verifica se a jogada foi registrada corretamente
    // Simula uma entrada inválida
    std::istringstream inputInvalido("4 4\n");
    std::cin.rdbuf(inputInvalido.rdbuf());
    // Verifique se a função lida corretamente com a entrada inválida
}

TEST_CASE("Testando a função checarVencedor") {
    JogoDaVelha jogo;
    Jogador jogador1("Jogador1", "jogador1");
    Jogador jogador2("Jogador2", "jogador2");

    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {1, 1}, {2, 2}};
    CHECK(JogoDaVelhaTests::testChecarVencedor(jogo, jogadas, jogador1, jogador2) == true);

    jogadas = {{0, 0}, {0, 1}, {0, 2}};
    CHECK(JogoDaVelhaTests::testChecarVencedor(jogo, jogadas, jogador1, jogador2) == true);

    jogadas = {{0, 0}, {1, 0}, {2, 0}};
    CHECK(JogoDaVelhaTests::testChecarVencedor(jogo, jogadas, jogador1, jogador2) == true);

    jogadas = {{0, 0}, {1, 1}, {2, 1}};
    CHECK(JogoDaVelhaTests::testChecarVencedor(jogo, jogadas, jogador1, jogador2) == false);
}

TEST_CASE("Testando a função checarEmpate") {
    JogoDaVelha jogo;
    Jogador jogador1("Jogador1", "jogador1");
    Jogador jogador2("Jogador2", "jogador2");

    CHECK(JogoDaVelhaTests::testRetornarEmpate(jogo, 9, jogador1, jogador2) == true);
    CHECK(JogoDaVelhaTests::testRetornarEmpate(jogo, 8, jogador1, jogador2) == false);
}