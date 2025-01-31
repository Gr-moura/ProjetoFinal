#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "BatalhaNaval.hpp"
#include "Jogador.hpp"

// Classe de teste para acessar membros privados
class BatalhaNavalTests {
public:
    static bool testChecarPosicaoValida(BatalhaNaval& jogo, int linha, int coluna) {
        return jogo.checarPosicaoValida(linha, coluna);
    }

    static bool testChecarVencedor(BatalhaNaval& jogo, std::vector<std::pair<int, int>>& jogadasAtacante,
                                   std::vector<std::pair<int, int>>& barcosOponente, Jogador& vencedor, Jogador& perdedor) {
        return jogo.checarVencedor(jogadasAtacante, barcosOponente, vencedor, perdedor);
    }

    static bool testVerificarEntrada(BatalhaNaval& jogo, char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
        return jogo.verificarEntrada(tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    }

    static bool testVerificarSobreposicao(BatalhaNaval& jogo, const std::vector<std::pair<int, int>>& barcosJogador, char tipo,
                                          int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
        return jogo.verificarSobreposicao(barcosJogador, tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    }

    static int testGetTamanhoBarco(BatalhaNaval& jogo, char tipo) {
        return jogo.getTamanhoBarco(tipo);
    }

    static bool testQuantidadeBarcosDisponiveis(BatalhaNaval& jogo, std::map<char, int>& countBarcos, char tipo) {
        return jogo.quantidadeBarcosDisponiveis(countBarcos, tipo);
    }

    static bool testVerificarTamanhodoBarco(BatalhaNaval& jogo, char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
        return jogo.verificarTamanhodoBarco(tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    }

    static void testInserirBarcos(BatalhaNaval& jogo, std::vector<std::pair<int, int>>& barcosJogador, char tipo,
                                  int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
        jogo.inserirBarcos(barcosJogador, tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    }

    static void testMarcarTabuleiro(BatalhaNaval& jogo, std::pair<int, int>& jogada, bool& turno,
                                    std::vector<std::vector<char>>& tabuleiroJogador, std::vector<std::pair<int, int>>& barcosJogador) {
        jogo.marcarTabuleiro(jogada, turno, tabuleiroJogador, barcosJogador);
    }

    static std::vector<std::vector<char>> testGetTabuleiro(BatalhaNaval& jogo){
        return jogo.tabuleiro;
    }
};

BatalhaNavalTests testes;

TEST_CASE("Testando o construtor padrão") {
    BatalhaNaval jogo;
    CHECK(BatalhaNavalTests::testGetTabuleiro(jogo).size() == 10);
    for (const auto& linha : BatalhaNavalTests::testGetTabuleiro(jogo)) {
        for (char celula : linha) {
            CHECK(celula == '~');
        }
    }
}

TEST_CASE("Testando a função checarPosicaoValida") {
    BatalhaNaval jogo;
    CHECK(testes.testChecarPosicaoValida(jogo, 0, 0) == true);  
    CHECK(testes.testChecarPosicaoValida(jogo, 9, 9) == true);
    CHECK(testes.testChecarPosicaoValida(jogo, 10, 10) == false);
    CHECK(testes.testChecarPosicaoValida(jogo, -1, 0) == false); 
}

TEST_CASE("Testando a função checarVencedor") {
    BatalhaNaval jogo;
    Jogador jogador1("Jogador1", "jogador1");
    Jogador jogador2("Jogador2", "jogador2");

    std::vector<std::pair<int, int>> jogadasAtacante = {{0, 0}, {1, 1}, {2, 2}};
    std::vector<std::pair<int, int>> barcosOponente = {{0, 0}, {1, 1}, {2, 2}};
    CHECK(testes.testChecarVencedor(jogo, jogadasAtacante, barcosOponente, jogador1, jogador2) == true);

    barcosOponente = {{0, 0}, {1, 1}, {2, 1}};
    CHECK(testes.testChecarVencedor(jogo, jogadasAtacante, barcosOponente, jogador1, jogador2) == false);
}

TEST_CASE("Testando a função verificarEntrada") {
    BatalhaNaval jogo;
    CHECK(testes.testVerificarEntrada(jogo, 'P', 1, 1, 1, 5) == true); 
    CHECK(testes.testVerificarEntrada(jogo, 'E', 1, 1, 4, 1) == true); 
    CHECK(testes.testVerificarEntrada(jogo, 'C', 1, 1, 1, 3) == true); 
    CHECK(testes.testVerificarEntrada(jogo, 'S', 1, 1, 2, 1) == true); 
    CHECK(testes.testVerificarEntrada(jogo, 'X', 1, 1, 1, 5) == false);
    CHECK(testes.testVerificarEntrada(jogo, 'P', 0, 1, 1, 5) == false); 
}

TEST_CASE("Testando a função verificarSobreposicao") {
    BatalhaNaval jogo;
    std::vector<std::pair<int, int>> barcosJogador = {{0, 0}, {1, 1}, {2, 2}};
    CHECK(testes.testVerificarSobreposicao(jogo, barcosJogador, 'P', 1, 1, 1, 5) == true);  
    CHECK(testes.testVerificarSobreposicao(jogo, barcosJogador, 'E', 3, 1, 6, 1) == false); 
}

TEST_CASE("Testando a função getTamanhoBarco") {
    BatalhaNaval jogo;
    CHECK(testes.testGetTamanhoBarco(jogo, 'P') == 5);  
    CHECK(testes.testGetTamanhoBarco(jogo, 'E') == 4);  
    CHECK(testes.testGetTamanhoBarco(jogo, 'C') == 3);  
    CHECK(testes.testGetTamanhoBarco(jogo, 'S') == 2);  
    CHECK(testes.testGetTamanhoBarco(jogo, 'X') == -1); 
}

TEST_CASE("Testando a função quantidadeBarcosDisponiveis") {
    BatalhaNaval jogo;
    std::map<char, int> countBarcos = {{'P', 0}, {'E', 0}, {'C', 0}, {'S', 0}};
    CHECK(testes.testQuantidadeBarcosDisponiveis(jogo, countBarcos, 'P') == true);  
    CHECK(testes.testQuantidadeBarcosDisponiveis(jogo, countBarcos, 'E') == true);  
    CHECK(testes.testQuantidadeBarcosDisponiveis(jogo, countBarcos, 'C') == true);  
    CHECK(testes.testQuantidadeBarcosDisponiveis(jogo, countBarcos, 'S') == true);  
    countBarcos['P'] = 1;
    CHECK(testes.testQuantidadeBarcosDisponiveis(jogo, countBarcos, 'P') == false); 
}

TEST_CASE("Testando a função verificarTamanhodoBarco") {
    BatalhaNaval jogo;
    CHECK(testes.testVerificarTamanhodoBarco(jogo, 'P', 1, 1, 1, 5) == true);  
    CHECK(testes.testVerificarTamanhodoBarco(jogo, 'E', 1, 1, 4, 1) == true);  
    CHECK(testes.testVerificarTamanhodoBarco(jogo, 'C', 1, 1, 1, 3) == true);  
    CHECK(testes.testVerificarTamanhodoBarco(jogo, 'S', 1, 1, 2, 1) == true);  
    CHECK(testes.testVerificarTamanhodoBarco(jogo, 'P', 1, 1, 1, 4) == false); 
}

TEST_CASE("Testando a função inserirBarcos") {
    BatalhaNaval jogo;
    std::vector<std::pair<int, int>> barcosJogador;
    testes.testInserirBarcos(jogo, barcosJogador, 'P', 1, 1, 1, 5);
    CHECK(barcosJogador.size() == 5); 
}

TEST_CASE("Testando a função marcarTabuleiro") {
    BatalhaNaval jogo;
    std::vector<std::vector<char>> tabuleiroJogador(10, std::vector<char>(10, '~'));
    std::vector<std::pair<int, int>> barcosJogador = {{0, 0}, {1, 1}, {2, 2}};
    std::pair<int, int> jogada = {0, 0};
    bool turno = true;
    testes.testMarcarTabuleiro(jogo, jogada, turno, tabuleiroJogador, barcosJogador);
    CHECK(tabuleiroJogador[0][0] == 'X'); 
}