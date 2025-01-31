#ifndef CENTRALDEJOGOS_HPP
#define CENTRALDEJOGOS_HPP

#include "BatalhaNaval.hpp"
#include "JogoDaVelha.hpp"
#include "JogoDaVelhaAi.hpp"
#include "Jogos.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

/**
 * @file CentralDeJogos.hpp
 * @brief Definição da classe CentralDeJogos.
 *
 * A classe CentralDeJogos é o núcleo do sistema de gerenciamento de jogos e jogadores, atuando como uma centralizadora
 *  de operações, conectando os jogadores aos jogos e garantindo que as estatísticas sejam atualizadas corretamente.
 *
 * - Gerenciar uma lista de jogadores cadastrados, incluindo suas estatísticas em diferentes jogos.
 * - Controlar as instâncias dos jogos disponíveis: Jogo da Velha, Lig4, Reversi e Batalha Naval.
 * - Facilitar a execução de partidas, permitindo que os jogadores escolham um jogo e compitam entre si ou contra uma
 * inteligência artificial (no caso do Jogo da Velha).
 * - Fornecer funcionalidades para cadastrar, remover, ordenar e listar jogadores.
 *
 *
 * ## Exemplo de Uso:
 * 1. Inicialize uma instância de `CentralDeJogos`.
 * 2. Cadastre jogadores usando o método `cadastrarJogador`.
 * 3. Execute partidas usando o método `executarPartida`, escolhendo o jogo e os jogadores participantes.
 * 4. Liste os jogadores e suas estatísticas usando o método `listarJogadores`.
 * 5. Ao finalizar, os dados dos jogadores são automaticamente salvos no arquivo de texto.
 *
 * @note A classe depende de um arquivo de texto (`data/DadosJogadoresCadastrados.txt`) para carregar e
 * salvar os dados dos jogadores. Certifique-se de que o arquivo esteja no formato correto.
 *
 * @see Jogador, JogoDaVelha, Lig4, Reversi, BatalhaNaval, JogoDaVelhaAi
 */

class CentralDeJogos
{
  private:
    std::vector<Jogador> jogadoresCadastrados;

    JogoDaVelhaAi Ai;
    JogoDaVelha velha;
    Lig4 lig4;
    Reversi reversi;
    BatalhaNaval batalha;

  public:
    CentralDeJogos();
    ~CentralDeJogos();

    std::string validarEntrada();

    bool buscarJogador(std::string &apelido);

    void cadastrarJogador(std::string &apelido, std::string &nome);
    void removerJogador(std::string &apelido);
    void ordenarJogadores();
    void listarJogadores();

    void executarPartida();
};

#endif