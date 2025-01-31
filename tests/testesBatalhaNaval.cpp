#include "../include/Jogos.hpp"
#include "../include/BatalhaNaval.hpp"
#include "doctest.h"
#include <bits/stdc++.h>

#include "Jogos.hpp"
#include "BatalhaNaval.hpp"
#include "doctest.h"
#include <bits/stdc++.h>

#include "Jogos.hpp"
#include "BatalhaNaval.hpp"
#include "doctest.h"
#include <bits/stdc++.h>

class Teste : public Jogos, public BatalhaNaval {
public:
    TEST_SUITE("BatalhaNaval") {
        TEST_CASE("Construtor inicializa tabuleiro corretamente") {
            BatalhaNaval jogo;
            auto tabuleiro = jogo.getTabuleiro(); // Adicione um método getTabuleiro() na classe BatalhaNaval

            CHECK(tabuleiro.size() == 10);
            for (const auto& linha : tabuleiro) {
                CHECK(linha.size() == 10);
                for (const auto& celula : linha) {
                    CHECK(celula == '~');
                }
            }
        }

        TEST_CASE("Checar vencedor") {
            BatalhaNaval jogo;
            Jogador jogador1("Jogador1");
            Jogador jogador2("Jogador2");

            std::vector<std::pair<int, int>> jogadasAtacante = {{0, 0}, {1, 1}, {2, 2}};
            std::vector<std::pair<int, int>> barcosOponente = {{0, 0}, {1, 1}, {2, 2}};

            CHECK(jogo.checarVencedor(jogadasAtacante, barcosOponente, jogador1, jogador2) == true);

            std::vector<std::pair<int, int>> barcosOponente2 = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
            CHECK(jogo.checarVencedor(jogadasAtacante, barcosOponente2, jogador1, jogador2) == false);
        }

        TEST_CASE("Ler jogada válida") {
            BatalhaNaval jogo;
            std::vector<std::vector<char>> tabuleiroJogador(10, std::vector<char>(10, '~'));

            // Simular entrada do usuário
            std::istringstream input("5 5\n");
            std::cin.rdbuf(input.rdbuf());

            auto jogada = jogo.lerJogada(tabuleiroJogador);
            CHECK(jogada == std::make_pair(4, 4)); // Lembrando que a entrada é ajustada com (-1)
        }

        TEST_CASE("Ler jogada inválida") {
            BatalhaNaval jogo;
            std::vector<std::vector<char>> tabuleiroJogador(10, std::vector<char>(10, '~'));

            // Simular entrada do usuário inválida
            std::istringstream input("15 15\n5 5\n");
            std::cin.rdbuf(input.rdbuf());

            auto jogada = jogo.lerJogada(tabuleiroJogador);
            CHECK(jogada == std::make_pair(4, 4)); // A segunda entrada deve ser válida
        }

        TEST_CASE("Inserir barcos corretamente") {
            BatalhaNaval jogo;
            Jogador jogador("Jogador");
            std::vector<std::pair<int, int>> barcosJogador;

            // Simular entrada do usuário para um barco válido
            std::istringstream input("P 1 1 1 5\n");
            std::cin.rdbuf(input.rdbuf());

            jogo.lerBarcos(barcosJogador, jogador);
            CHECK(barcosJogador.size() == 5); // Porta-aviões tem tamanho 5
        }

        TEST_CASE("Verificar tamanho do barco") {
            BatalhaNaval jogo;

            CHECK(jogo.verificarTamanhodoBarco('P', 1, 1, 1, 5) == true); // Porta-aviões válido
            CHECK(jogo.verificarTamanhodoBarco('P', 1, 1, 1, 6) == false); // Tamanho inválido
            CHECK(jogo.verificarTamanhodoBarco('E', 1, 1, 1, 4) == true); // Encouraçado válido
            CHECK(jogo.verificarTamanhodoBarco('C', 1, 1, 1, 3) == true); // Contratorpedeiro válido
            CHECK(jogo.verificarTamanhodoBarco('S', 1, 1, 1, 2) == true); // Submarino válido
        }

        TEST_CASE("Quantidade de barcos disponíveis") {
            BatalhaNaval jogo;
            std::map<char, int> countBarcos = {{'P', 0}, {'E', 0}, {'C', 0}, {'S', 0}};

            CHECK(jogo.quantidadeBarcosDisponiveis(countBarcos, 'P') == true); // Pode adicionar mais um Porta-aviões
            countBarcos['P'] = 1;
            CHECK(jogo.quantidadeBarcosDisponiveis(countBarcos, 'P') == false); // Não pode adicionar mais Porta-aviões

            CHECK(jogo.quantidadeBarcosDisponiveis(countBarcos, 'E') == true); // Pode adicionar Encouraçados
            countBarcos['E'] = 2;
            CHECK(jogo.quantidadeBarcosDisponiveis(countBarcos, 'E') == false); // Não pode adicionar mais Encouraçados
        }
    };
};

int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run();
}