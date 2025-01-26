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
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador1.getApelido() << " começara a partida!" << std::endl;
    }
    else {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador2.getApelido() << " começara a partida!" << std::endl;
    }
}

std::pair<int, int> Reversi::lerJogada(){
    int linha, coluna;
    bool entradaValida = false;

    while(!entradaValida) {
        std::cout << "Digite a linha e a coluna onde deseja jogar no tabuleiro, por favor." << std::endl;
        
        if(!(std::cin >> linha >> coluna)) {
            std::cout << "ERRO: Entrada invalida! Digite dois numeros inteiros, por favor." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (checarPosicaoValida (linha - 1, coluna - 1) && tabuleiro[linha - 1][coluna - 1] == ' ') {
            entradaValida = true;
        }
        else {
            std::cout << "ERRO: A posição escolhida e invalida ou esta ocupada. Tente novamente." << std::endl;
        }
    }

    return {linha - 1, coluna - 1}; //para o jogador a entrada que ele escolhe sempre será linha - 1 e coluna - 1 por usarmos vector. 
}

void Reversi::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) {
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
        for (const auto &par : flips) {
            tabuleiro[par.first][par.second] = jogador;
        }
        turno = !turno;
    }
    else {
        std::cout << "ERRO: Jogada invalida. Tente novamente." << std:: endl;
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

    for (const auto &par : direcoes) {
        int dx = par.first;
        int dy = par.second;

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

bool Reversi::checarVencedor(std::vector<std::pair<int, int>> &movimentos, Jogador &jogador_1, Jogador &jogador_2, bool turno) {
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
            
            if (turno) {
                std::cout << "O jogador "  << jogador_1.getApelido() <<" ganhou!" << std::endl;
                jogador_1.registrarVitoria("REVERSI");
                jogador_2.registrarDerrota("REVERSI");
            }
            else {
                std::cout << "O jogador "  << jogador_2.getApelido() <<" ganhou!" << std::endl;
                jogador_2.registrarVitoria("REVERSI");
                jogador_1.registrarDerrota("REVERSI");
            }
        }
        else if(contadorO > contadorX){
            std::cout << "O jogador O ganhou!" << std::endl;
            if (turno) {
                std::cout << "O jogador "  << jogador_2.getApelido() <<" ganhou!" << std::endl;
                jogador_2.registrarVitoria("REVERSI");
                jogador_1.registrarDerrota("REVERSI");
            }
            else {
                std::cout << "O jogador "  << jogador_1.getApelido() <<" ganhou!" << std::endl;
                jogador_1.registrarVitoria("REVERSI");
                jogador_2.registrarDerrota("REVERSI");
            }
        }
        else {
            std::cout << "O jogo empatou!" << std::endl;
            jogador_1.registrarEmpate("REVERSI");
            jogador_2.registrarEmpate("REVERSI");
        }
        return true;
    }
    return false;
}

bool Reversi::checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) {
    return false;
}