#ifndef ESTATISTICAS_HPP
#define ESTATISTICAS_HPP

#include <vector>

/**
 * @file Estatisticas.hpp
 * @brief Definição da classe Estatisticas.
 *
 * Esta classe é responsável por armazenar e gerenciar as estatísticas de um jogador em um jogo específico.
 * Ela registra o número de vitórias, derrotas e empates, além de fornecer métodos para acessar e exibir
 * essas informações.
 *
 * A classe é utilizada em conjunto com a classe `Jogador` para armazenar as estatísticas de cada jogo
 * (Jogo da Velha, Lig4, Reversi, Batalha Naval) individualmente.
 *
 * ## Atributos:
 * - `vitorias`: Número de vitórias do jogador no jogo.
 * - `derrotas`: Número de derrotas do jogador no jogo.
 * - `empates`: Número de empates do jogador no jogo.
 *
 * ## Funcionalidades Principais:
 * - Registrar vitórias, derrotas e empates.
 * - Acessar o número de vitórias, derrotas e empates.
 * - Exibir as estatísticas de forma organizada.
 *
 * @see Jogador
 */
class Estatisticas
{
  private:
    int vitorias;
    int derrotas;
    int empates;

  public:
    Estatisticas();
    Estatisticas(int vitorias, int derrotas, int empates);

    void registrarVitoria();
    void registrarDerrota();
    void registrarEmpate();

    int getVitorias() const;
    int getDerrotas() const;
    int getEmpates() const;
    std::vector<char> getHistorico() const;
    void mostrarEstatisticas() const;
};

#endif