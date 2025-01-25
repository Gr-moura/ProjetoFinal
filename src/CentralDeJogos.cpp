#include <CentralDeJogos.hpp>

CentralDeJogos::CentralDeJogos() {
    std::ifstream DadosJogadoresCadastrados("../data/DadosJogadoresCadastrados.txt");
    if (!DadosJogadoresCadastrados.is_open()) {
        std::cerr << "ERRO! Nao foi possivel abrir o arquivo de dados. Os dados não foram carregados." << std::endl;
        return;
    }

    std::string nome, apelido;
    int vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDaVelha;
    int vitoriasLig4, derrotasLig4, empatesLig4;
    int vitoriasReversi, derrotasReversi, empatesReversi;
    // int vitoriasJogo3, derrotasJogo3, empatesJogo3;

    while (DadosJogadoresCadastrados >> nome >> apelido 
           >> vitoriasJogoDaVelha >> derrotasJogoDaVelha >> empatesJogoDaVelha 
           >> vitoriasLig4 >> derrotasLig4 >> empatesLig4
           >> vitoriasReversi >> derrotasReversi >> empatesReversi) {

        Jogador jogador(apelido, nome,
        vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDaVelha,
        vitoriasLig4, derrotasLig4, empatesLig4,
        vitoriasReversi, derrotasReversi, empatesReversi);
        jogadoresCadastrados.push_back(jogador);
    }

    DadosJogadoresCadastrados.close();
}

void CentralDeJogos::listarJogadores() {
    for (Jogador &jogador : jogadoresCadastrados) {
        std::cout << jogador.getApelido() << " " << jogador.getNome() << std::endl;
        jogador.mostrarEstatisticas("Reversi");
        jogador.mostrarEstatisticas("Lig4");
        jogador.mostrarEstatisticas("Velha");
    }
}