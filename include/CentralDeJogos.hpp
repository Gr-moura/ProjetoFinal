#ifndef CENTRALDEJOGOS_HPP
#define CENTRALDEJOGOS_HPP

#include "JogoDaVelha.hpp"
#include "JogoDaVelhaAi.hpp"
#include "Jogos.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

class CentralDeJogos
{
  private:
    std::vector<Jogador> jogadoresCadastrados;
    JogoDaVelhaAi Ai;
    JogoDaVelha velha;
    Lig4 lig4;
    Reversi reversi;

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