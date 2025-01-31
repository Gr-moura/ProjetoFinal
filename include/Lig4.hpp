#ifndef LIG4_HPP
#define LIG4_HPP

#include "Jogos.hpp"

/**
 * @file Lig4.hpp
 * @brief Definição da classe Lig4.
 *
 * Esta classe representa o jogo Lig4 (Connect Four), um jogo de tabuleiro para dois jogadores.
 * Ela herda da classe base `Jogos` e implementa as funcionalidades específicas do Lig4, como
 * leitura de jogadas, verificação de vitória e empate, e anúncio do início da partida.
 *
 * ## Funcionalidades Principais:
 * - Gerenciamento de partidas de Lig4.
 * - Verificação de vitória (linhas, colunas ou diagonais completas).
 * - Verificação de empate (tabuleiro cheio sem vencedor).
 * - Anúncio do início da partida e alternância de turnos entre os jogadores.
 *
 * ## Métodos Sobrescritos:
 * - `anunciarInicioPartida`: Anuncia o início da partida e define o jogador que começa.
 * - `checarVencedor`: Verifica se há um vencedor no jogo.
 * - `checarEmpate`: Verifica se o jogo terminou em empate.
 * - `lerJogada`: Lê a jogada do jogador atual.
 *
 * ## Métodos Adicionais:
 * - `checarDiagonal`: Verifica se há um vencedor nas diagonais do tabuleiro.
 * - `checarColunas`: Verifica se há um vencedor nas colunas do tabuleiro.
 * - `checarLinhas`: Verifica se há um vencedor nas linhas do tabuleiro.
 *
 * ## Integração com Outras Classes:
 * - Herda da classe `Jogos`, que define a interface comum para todos os jogos.
 * - Utiliza a classe `Jogador` para representar os jogadores participantes.
 *
 * @see Jogos, Jogador
 */
class Lig4 : public Jogos
{
  public:
    Lig4(int tamanhoTabuleiro);
    Lig4();

  protected:
    void anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    bool checarDiagonal(std::vector<std::pair<int, int>> &jogadas);
    bool checarColunas(std::vector<std::pair<int, int>> &jogadas);
    bool checarLinhas(std::vector<std::pair<int, int>> &jogadas);
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) override;
    bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override;

    std::pair<int, int> lerJogada() override;

    friend class Lig4Testes;
};

#endif