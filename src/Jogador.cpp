/**
 * @file Jogador.cpp
 * @brief Implementação dos métodos da classe Jogador.
 *
 * Este arquivo contém a implementação dos métodos da classe Jogador, que gerencia as informações e estatísticas
 * de um jogador nos diferentes jogos disponíveis.
 */
#include "Jogador.hpp"
#include <iostream>

/**
 * @brief Construtor padrão da classe Jogador.
 *
 * Inicializa o jogador com um apelido e nome, e cria estatísticas zeradas para todos os jogos disponíveis.
 *
 * @param apelido Apelido único do jogador
 * @param nome Nome completo do jogador
 */
Jogador::Jogador(const std::string &apelido, const std::string &nome) : apelido(apelido), nome(nome)
{
    estatisticasPorJogo["VELHA"] = Estatisticas();
    estatisticasPorJogo["LIG4"] = Estatisticas();
    estatisticasPorJogo["REVERSI"] = Estatisticas();
    estatisticasPorJogo["BATALHANAVAL"] = Estatisticas();
}

/**
 * @brief Construtor parametrizado da classe Jogador.
 *
 * Inicializa o jogador com um apelido, nome e estatísticas pré-definidas para todos os jogos disponíveis.
 *
 * @param apelido Apelido único do jogador
 * @param nome Nome completo do jogador
 * @param vitoriasJogoDaVelha Número de vitórias no Jogo da Velha
 * @param derrotasJogoDaVelha Número de derrotas no Jogo da Velha
 * @param empatesJogoDavelha Número de empates no Jogo da Velha
 * @param vitoriasLig4 Número de vitórias no Lig4
 * @param derrotasLig4 Número de derrotas no Lig4
 * @param empatesLig4 Número de empates no Lig4
 * @param vitoriasReversi Número de vitórias no Reversi
 * @param derrotasReversi Número de derrotas no Reversi
 * @param empatesReversi Número de empates no Reversi
 * @param vitoriasBatalhaNaval Número de vitórias no Batalha Naval
 * @param derrotasBatalhaNaval Número de derrotas no Batalha Naval
 * @param empatesBatalhaNaval Número de empates no Batalha Naval
 */
Jogador::Jogador(const std::string &apelido, const std::string &nome, const int vitoriasJogoDaVelha,
                 const int derrotasJogoDaVelha, const int empatesJogoDavelha, const int vitoriasLig4,
                 const int derrotasLig4, const int empatesLig4, const int vitoriasReversi, const int derrotasReversi,
                 const int empatesReversi, const int vitoriasBatalhaNaval, const int derrotasBatalhaNaval,
                 const int empatesBatalhaNaval) : apelido(apelido), nome(nome)
{
    estatisticasPorJogo["VELHA"] = Estatisticas(vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDavelha);
    estatisticasPorJogo["LIG4"] = Estatisticas(vitoriasLig4, derrotasLig4, empatesLig4);
    estatisticasPorJogo["REVERSI"] = Estatisticas(vitoriasReversi, derrotasReversi, empatesReversi);
    estatisticasPorJogo["BATALHANAVAL"] = Estatisticas(vitoriasBatalhaNaval, derrotasBatalhaNaval, empatesBatalhaNaval);
}

/**
 * @brief Registra uma vitória para o jogador em um jogo específico.
 *
 * @param nomeJogo Nome do jogo no qual a vitória será registrada (ex: "VELHA", "LIG4")
 */
void Jogador::registrarVitoria(const std::string &nomeJogo)
{
    estatisticasPorJogo.at(nomeJogo).registrarVitoria();
}

/**
 * @brief Registra um empate para o jogador em um jogo específico.
 *
 * @param nomeJogo Nome do jogo no qual o empate será registrado (ex: "VELHA", "LIG4")
 */
void Jogador::registrarEmpate(const std::string &nomeJogo)
{
    estatisticasPorJogo.at(nomeJogo).registrarEmpate();
}

/**
 * @brief Registra uma derrota para o jogador em um jogo específico.
 *
 * @param nomeJogo Nome do jogo no qual a derrota será registrada (ex: "VELHA", "LIG4")
 */
void Jogador::registrarDerrota(const std::string &nomeJogo)
{
    estatisticasPorJogo.at(nomeJogo).registrarDerrota();
}

/**
 * @brief Retorna o apelido do jogador.
 *
 * @return std::string Apelido do jogador
 */
std::string Jogador::getApelido() const
{
    return apelido;
}

/**
 * @brief Retorna o apelido do jogador.
 *
 * @return std::string Apelido do jogador
 */
std::string Jogador::getNome() const
{
    return nome;
}

/**
 * @brief Retorna o nome do jogador.
 *
 * @return std::string Nome do jogador
 */
int Jogador::getVitorias(std::string jogo)
{
    return estatisticasPorJogo[jogo].getVitorias();
}

/**
 * @brief Retorna o número de empates do jogador em um jogo específico.
 *
 * @param jogo Nome do jogo (ex: "VELHA", "LIG4")
 * @return int Número de empates no jogo especificado
 */
int Jogador::getDerrotas(std::string jogo)
{
    return estatisticasPorJogo[jogo].getDerrotas();
}

/**
 * @brief Retorna o número de empates do jogador em um jogo específico.
 *
 * @param jogo Nome do jogo (ex: "VELHA", "LIG4")
 * @return int Número de empates no jogo especificado
 */
int Jogador::getEmpates(std::string jogo)
{
    return estatisticasPorJogo[jogo].getEmpates();
}

/**
 * @brief Exibe as estatísticas do jogador em um jogo específico.
 *
 * @param nomeJogo Nome do jogo (ex: "VELHA", "LIG4")
 */
void Jogador::mostrarEstatisticas(const std::string &nomeJogo) const
{
    std::cout << nomeJogo << " ";
    estatisticasPorJogo.at(nomeJogo).mostrarEstatisticas();
}