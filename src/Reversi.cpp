#include "Reversi.hpp"

Reversi::Reversi() {
    tabuleiro.resize(8, std::vector<char>(8, ' '));
    tabuleiro[3][3] = 'O';
    tabuleiro[3][4] = 'X';
    tabuleiro[4][3] = 'X';
    tabuleiro[4][4] = 'O';
}

Reversi::Reversi(int tamanhoTabuleiro) {
    tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro, ' '));
    int meio = tamanhoTabuleiro / 2;

    tabuleiro[meio - 1][meio - 1] = 'O';
    tabuleiro[meio - 1][meio] = 'X';
    tabuleiro[meio][meio - 1] = 'X';
    tabuleiro[meio][meio] = 'O';
}

void Reversi::iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno){
    if(turno) {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador1.getApelido() << " começará a partida!" << std::endl;
    }
    else {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador2.getApelido() << " começará a partida!" << std::endl;
    }
}

std::pair<int, int> Reversi::lerJogada(){
    int linha, coluna;
    bool entradaValida = false;

    while(!entradaValida) {
        std::cout << "Digite a linha e a coluna onde deseja jogar no tabuleiro, por favor." << std::endl;
        
        if(!(std::cin >> linha >> coluna)) {
            std::cout << "Entrada inválida! Digite dois números inteiros, por favor." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (checarPosicaoValida (linha - 1, coluna - 1) && tabuleiro[linha - 1][coluna - 1] == ' ') {
            entradaValida = true;
        }
        else {
            std::cout << "ERRO! A posição escolhida é inválida ou está ocupada. Tente novamente." << std::endl;
        }
    }

    return {linha - 1, coluna - 1}; //para o jogador a entrada que ele escolhe sempre será linha - 1 e coluna - 1 por usarmos vector. 
}

bool Reversi::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) {
    char jogador;
    if(turno) { 
        jogador = 'X';
    }
    else {
        jogador = 'O';
    }

    std:: vector<std::pair<int, int>> flips;

    if (movimentoValido(jogada, jogador, flips)) {
        tabuleiro[jogada.first][jogada.second] = jogador;
        for (const auto &[x, y] : flips) {
            tabuleiro[x][y] = jogador;
        }
        turno = !turno;
        return true;
    }
    else {
        std::cout << "Jogada inválida. Tente novamente." << std:: endl;
        return false;
    }
}

bool Reversi::movimentoValido(std::pair<int, int> &jogada, char jogador, std::vector<std::pair<int, int>> &flips) {
    flips.clear();
    char oponente = (jogador == 'X') ? 'O' : 'X';
    bool valido = false;

    const std::vector<std::pair<int, int>> direcoes = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &[dx, dy] : direcoes) {
        int x = jogada.first + dx;
        int y = jogada.second + dy;
        std::vector<std::pair<int, int>> capturas; //são as peças que seriam flipadas caso a respectiva jogada fosse escolhida.
        
        while(checarPosicaoValida(x, y) && tabuleiro[x][y] == oponente) {
            capturas.push_back({x, y});
            x += dx;
            y += dy;
        }

        if (!capturas.empty() && checarPosicaoValida(x, y) && tabuleiro[x][y] == jogador) {
            flips.insert(flips.end(), capturas.begin(), capturas.end()); //adiciona em flips as peças capturáveis.
            valido = true;
        }
    }

    return valido;
}

bool Reversi::checarVencedor(std::vector<std::pair<int, int>> &movimentos) {
    int contadorX = 0;
    int contadorO = 0;

    for(const auto &linha : tabuleiro) {
        for(char c : linha) {
            if(c == 'X'){
                contadorX++;
            }
            if(c == 'O'){
                contadorO++;
            }
        }
    }

    if(contadorX == 0 || contadorO == 0 || movimentos.size() == tabuleiro.size() * tabuleiro[0].size()){
        std::cout << "Fim de jogo! X: " << contadorX << " | O: " << contadorO << std::endl;
        if(contadorX > contadorO){
            std::cout << "O jogador X ganhou!" << std::endl;
        }
        else if(contadorX < contadorO){
            std::cout << "O jogador O ganhou!" << std::endl;
        }
        else {
            std::cout << "O jogo empatou!" << std::endl;
        }
    }
}