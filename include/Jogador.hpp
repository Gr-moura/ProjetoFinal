#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Estatisticas.hpp"

/**
 * @file Jogador.hpp
 * @brief Definição da classe Jogador.
 *
 * Esta classe representa um jogador no sistema, armazenando informações como nome, apelido e estatísticas
 * em diferentes jogos. As estatísticas são gerenciadas por meio de um mapa que associa o nome do jogo a um
 * objeto da classe `Estatisticas`, permitindo o registro e consulta de vitórias, derrotas e empates para
 * cada jogo individualmente.
 *
 * ## Atributos:
 * - `apelido`: Apelido único do jogador, usado para identificação.
 * - `nome`: Nome completo do jogador.
 * - `estatisticasPorJogo`: Mapa que armazena as estatísticas do jogador para cada jogo. A chave é o nome do jogo
 *   (por exemplo, "VELHA", "LIG4", "REVERSI", "BATALHANAVAL"), e o valor é um objeto da classe `Estatisticas`.
 *
 * ## Funcionalidades Principais:
 * - Registro de vitórias, derrotas e empates para um jogo específico.
 * - Consulta das estatísticas (vitórias, derrotas e empates) para um jogo específico.
 * - Exibição das estatísticas de um jogo específico.
 *
 * ## Integração com Outras Classes:
 * - A classe `Jogador` utiliza a classe `Estatisticas` para armazenar e gerenciar as estatísticas de cada jogo.
 * - É usada pela classe `CentralDeJogos` para gerenciar os jogadores cadastrados no sistema.
 *
 * @see Estatisticas, CentralDeJogos
 */
class Jogador
{
  private:
    std::string apelido;
    std::string nome;
    std::unordered_map<std::string, Estatisticas> estatisticasPorJogo;

  public:
    Jogador(const std::string &apelido, const std::string &nome);
    Jogador(const std::string &apelido, const std::string &nome, int vitoriasJogoDaVelha, int derrotasJogoDaVelha,
            int empatesJogoDavelha, int vitoriasLig4, int derrotasLig4, int empatesLig4, int vitoriasReversi,
            int derrotasReversi, int empatesReversi, int vitoriasBatalhaNaval, int derrotasBatalhaNaval,
            int empatesBatalhaNaval);

    void registrarVitoria(const std::string &nomeJogo);
    void registrarDerrota(const std::string &nomeJogo);
    void registrarEmpate(const std::string &nomeJogo);

    std::string getApelido() const;
    std::string getNome() const;
    int getVitorias(std::string jogo);
    int getDerrotas(std::string jogo);
    int getEmpates(std::string jogo);

    void mostrarEstatisticas(const std::string &nomeJogo) const;
};

#endif