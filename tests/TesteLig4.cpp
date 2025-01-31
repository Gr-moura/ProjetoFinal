#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Lig4.hpp"
#include "Jogador.hpp"

// Classe de teste para acessar membros privados
class Lig4Testes {
public:
    static bool testChecarDiagonal(Lig4& lig4, std::vector<std::pair<int, int>>& jogadas) {
        return lig4.checarDiagonal(jogadas);
    }

    static bool testChecarColunas(Lig4& lig4, std::vector<std::pair<int, int>>& jogadas) {
        return lig4.checarColunas(jogadas);
    }

    static bool testChecarLinhas(Lig4& lig4, std::vector<std::pair<int, int>>& jogadas) {
        return lig4.checarLinhas(jogadas);
    }

    static bool testChecarVencedor(Lig4& lig4, std::vector<std::pair<int, int>>& jogadas, Jogador& vencedor, Jogador& perdedor) {
        return lig4.checarVencedor(jogadas, vencedor, perdedor);
    }

    static bool testChecarEmpate(Lig4& lig4, int numeroJogadas, Jogador& jogador1, Jogador& jogador2) {
        return lig4.checarEmpate(numeroJogadas, jogador1, jogador2);
    }

    static std::pair<int, int> testLerJogada(Lig4& lig4) {
        return lig4.lerJogada();
    }
};

// Testes
TEST_CASE("Testando o construtor padrão") {
    Lig4 lig4;
    // Verifique se o tabuleiro foi inicializado corretamente
}

TEST_CASE("Testando o construtor parametrizado") {
    Lig4 lig4(4); // Tabuleiro 4x4
    // Verifique se o tabuleiro foi inicializado corretamente
}

TEST_CASE("Testando a função privada checarDiagonal") {
    Lig4 lig4;
    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    CHECK(Lig4Testes::testChecarDiagonal(lig4, jogadas) == true);

    jogadas = {{0, 3}, {1, 2}, {2, 1}, {3, 0}};
    CHECK(Lig4Testes::testChecarDiagonal(lig4, jogadas) == true); 

    jogadas = {{0, 0}, {1, 1}, {2, 2}, {3, 1}};
    CHECK(Lig4Testes::testChecarDiagonal(lig4, jogadas) == false); 
}

TEST_CASE("Testando a função privada checarColunas") {
    Lig4 lig4;
    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    CHECK(Lig4Testes::testChecarColunas(lig4, jogadas) == true); 

    jogadas = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
    CHECK(Lig4Testes::testChecarColunas(lig4, jogadas) == true); 

    jogadas = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    CHECK(Lig4Testes::testChecarColunas(lig4, jogadas) == false); 
}

TEST_CASE("Testando a função privada checarLinhas") {
    Lig4 lig4;
    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    CHECK(Lig4Testes::testChecarLinhas(lig4, jogadas) == true); 

    jogadas = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
    CHECK(Lig4Testes::testChecarLinhas(lig4, jogadas) == true); 

    jogadas = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    CHECK(Lig4Testes::testChecarLinhas(lig4, jogadas) == false); 
}

TEST_CASE("Testando a função privada checarVencedor") {
    Lig4 lig4;
    Jogador jogador1("Jogador1", "j1");
    Jogador jogador2("Jogador2", "j2");

    std::vector<std::pair<int, int>> jogadas = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    CHECK(Lig4Testes::testChecarVencedor(lig4, jogadas, jogador1, jogador2) == true); 

    jogadas = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    CHECK(Lig4Testes::testChecarVencedor(lig4, jogadas, jogador1, jogador2) == true); 

    jogadas = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    CHECK(Lig4Testes::testChecarVencedor(lig4, jogadas, jogador1, jogador2) == true); 

    jogadas = {{0, 0}, {1, 1}, {2, 2}, {3, 1}};
    CHECK(Lig4Testes::testChecarVencedor(lig4, jogadas, jogador1, jogador2) == false);
}

TEST_CASE("Testando a função privada checarEmpate") {
    Lig4 lig4;
    Jogador jogador1("Jogador1", "j1");
    Jogador jogador2("Jogador2", "j2");

    CHECK(Lig4Testes::testChecarEmpate(lig4, 16, jogador1, jogador2) == true); 
    CHECK(Lig4Testes::testChecarEmpate(lig4, 15, jogador1, jogador2) == false);
}

TEST_CASE("Testando a função privada lerJogada") {
    Lig4 lig4;

    // Simula uma entrada válida
    std::istringstream inputValido("1 1\n");
    std::cin.rdbuf(inputValido.rdbuf());
    auto jogada = Lig4Testes::testLerJogada(lig4);
    CHECK(jogada == std::make_pair(0, 0));

    // Simula uma entrada inválida
    std::istringstream inputInvalido("5 5\n");
    std::cin.rdbuf(inputInvalido.rdbuf());
    // Verifique se a função lida corretamente com a entrada inválida
}