#ifndef CENTRALDEJOGOS_HPP
#define CENTRALDEJOGOS_HPP

#include "Jogos.hpp"
#include "JogoDaVelha.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

class CentralDeJogos {
private:
    std::vector<Jogador> jogadoresCadastrados;
    JogoDaVelha JogoDaVelha;
    Lig4 ligue04;

    //Reversi reversi;
    //Jogo3 jogo3;

public:
    CentralDeJogos(); // Construtor deve puxar os dados do arquivo de Jogadores Cadastrados e adicionálos em "jogadoresCadastrados"
    ~CentralDeJogos(); // Destrutor deve atualizar o arquivo de Jogadores Cadastrados

    void cadastrarJogador(std::string &apelido, std::string &nome);
    void removerJogador(std::string &apelido, std::string &nome);
    void listarJogadores();

    void executarPartida();
};

#endif