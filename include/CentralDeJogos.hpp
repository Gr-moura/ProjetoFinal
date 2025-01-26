#ifndef CENTRALDEJOGOS_HPP
#define CENTRALDEJOGOS_HPP

#include "Jogos.hpp"
#include "JogoDaVelha.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

class CentralDeJogos {
private:
    std::vector<Jogador> jogadoresCadastrados;
    JogoDaVelha velha;
    Lig4 lig4;

    //Reversi reversi;
    //Jogo3 jogo3;

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