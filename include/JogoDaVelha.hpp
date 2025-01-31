#ifndef JOGODAVELHA_HPP
#define JOGODAVELHA_HPP

#include "Jogos.hpp"
/**
 * @file JogoDaVelha.hpp
 * @brief Definição da classe JogoDaVelha.
 *
 * Esta classe representa o jogo da velha, um jogo de tabuleiro para dois jogadores. Ela herda da classe base `Jogos`
 * e implementa as funcionalidades específicas do jogo da velha, como leitura de jogadas, verificação de vitória
 * e empate, e anúncio do início da partida.
 *
 * ## Funcionalidades Principais:
 * - Gerenciamento de partidas de jogo da velha.
 * - Verificação de vitória (linhas, colunas ou diagonais completas).
 * - Verificação de empate (tabuleiro cheio sem vencedor).
 * - Anúncio do início da partida e alternância de turnos entre os jogadores.
 *
 * ## Integração com Outras Classes:
 * - Herda da classe `Jogos`, que define a interface comum para todos os jogos.
 * - Utiliza a classe `Jogador` para representar os jogadores participantes.
 * - É amiga da classe `JogoDaVelhaAi`, permitindo acesso a métodos protegidos para implementação de inteligência artificial.
 *
 * @see Jogos, Jogador, JogoDaVelhaAi
 */
class JogoDaVelha : public Jogos
{
  public:
    JogoDaVelha();
    JogoDaVelha(int tamanhoTabuleiro);

  protected:
    void anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    std::pair<int, int> lerJogada() override;

    bool checarDiagonal(std::vector<std::pair<int, int>> &jogadas);
    bool checarColunas(std::vector<std::pair<int, int>> &jogadas);
    bool checarLinhas(std::vector<std::pair<int, int>> &jogadas);
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) override;
    bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override;

    friend class JogoDaVelhaAi;
    friend class JogoDaVelhaTests;
};

#endif