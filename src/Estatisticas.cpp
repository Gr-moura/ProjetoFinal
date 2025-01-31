/**
 * @file Estatisticas.cpp
 * @brief Implementação dos métodos da classe Estatisticas.
 *
 * Este arquivo contém a implementação dos métodos da classe Estatisticas, que gerencia as estatísticas
 * de um jogador em um jogo específico, incluindo vitórias, derrotas e empates.
 */

#include "Estatisticas.hpp"
#include <iostream>

/**
 * @brief Construtor padrão da classe Estatisticas.
 *
 * Inicializa as estatísticas com zero vitórias, zero derrotas e zero empates.
 */
Estatisticas::Estatisticas() : vitorias(0), derrotas(0), empates(0) {}

/**
 * @brief Construtor parametrizado da classe Estatisticas.
 *
 * Inicializa as estatísticas com os valores fornecidos para vitórias, derrotas e empates.
 *
 * @param vitorias Número inicial de vitórias
 * @param derrotas Número inicial de derrotas
 * @param empates Número inicial de empates.
 *
 */
Estatisticas::Estatisticas(int vitorias, int derrotas, int empates) :
    vitorias(vitorias), derrotas(derrotas), empates(empates)
{
}

/**
 * @brief Registra uma vitória.
 *
 * Incrementa o contador de vitórias.
 */
void Estatisticas::registrarVitoria()
{
    vitorias++;
}

/**
 * @brief Registra uma derrota.
 *
 * Incrementa o contador de derrotas.
 */
void Estatisticas::registrarDerrota()
{
    derrotas++;
}

/**
 * @brief Registra um empate.
 *
 * Incrementa o contador de empates.
 */
void Estatisticas::registrarEmpate()
{
    empates++;
}

/**
 * @brief Retorna o número de vitórias.
 *
 * @return int Número de vitórias
 */
int Estatisticas::getVitorias() const
{
    return vitorias;
}

/**
 * @brief Retorna o número de derrotas.
 *
 * @return int Número de derrotas.
 */
int Estatisticas::getDerrotas() const
{
    return derrotas;
}

/**
 * @brief Retorna o número de empates.
 *
 * @return int Número de empates
 */
int Estatisticas::getEmpates() const
{
    return empates;
}

/**
 * @brief Exibe as estatísticas formatadas.
 *
 * Mostra o número de vitórias, derrotas e empates no formato:
 * - V: <vitórias> D: <derrotas> E: <empates>
 */
void Estatisticas::mostrarEstatisticas() const
{
    std::cout << "- V: <" << getVitorias() << "> D: <" << getDerrotas() << ">" << " E: <" << getEmpates() << "> "
              << std::endl;
}