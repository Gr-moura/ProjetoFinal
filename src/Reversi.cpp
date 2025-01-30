#include "Reversi.hpp"

Reversi::Reversi()
{
    tabuleiro.resize(8, std::vector<char>(8, ' '));
    tabuleiro[3][3] = 'X';
    tabuleiro[3][4] = 'O';
    tabuleiro[4][3] = 'O';
    tabuleiro[4][4] = 'X';
}

Reversi::Reversi(int tamanhoTabuleiro)
{
    tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro, ' '));
    int meio = tamanhoTabuleiro / 2;

    tabuleiro[meio - 1][meio - 1] = 'X';
    tabuleiro[meio - 1][meio] = 'O';
    tabuleiro[meio][meio - 1] = 'O';
    tabuleiro[meio][meio] = 'X';
}

void Reversi::anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno)
{

    mostrarTabuleiro();

    if (turno)
    {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador1.getApelido()
                  << " comecara a partida com as pecas 'X'!" << std::endl;
    }
    else
    {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador2.getApelido()
                  << " comecara a partida com as pecas 'O'!" << std::endl;
    }
}

std::pair<int, int> Reversi::lerJogada(bool turno)
{
    int linha, coluna;
    bool entradaValida = false;

    while (not entradaValida)
    {
        std::cout << "Digite a linha e a coluna onde deseja jogar no tabuleiro, por favor. Sua jogada deve capturar ao "
                     "menos 1 peca adversaria!"
                  << std::endl;

        if (!(std::cin >> linha >> coluna))
        {
            std::cout << "ERRO: Entrada invalida! Digite dois numeros inteiros, por favor." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        char jogador = turno ? 'X' : 'O';
        std::vector<std::pair<int, int>> flips;
        std::pair<int, int> jogada = {linha - 1, coluna - 1};

        if (checarPosicaoValida(linha - 1, coluna - 1) and tabuleiro[linha - 1][coluna - 1] == ' ' and
            movimentoValido(jogada, jogador, flips))
        {
            entradaValida = true;
            return {linha - 1, coluna - 1};
        }
        else
        {
            std::cout << "ERRO: A posicao escolhida e invalida ou esta ocupada. Tente novamente." << std::endl;
        }
    }
    return {-1, -1};
}

bool Reversi::jogadorInicial(bool &turno)
{
    bool Primeirojogador = turno;
    std::cout << "!!!!!!! PrimeiroJogador é: " << Primeirojogador << std::endl;
    return Primeirojogador;
}

void Reversi::Jogar(Jogador &Jogador1, Jogador &Jogador2)
{
    bool jogoEmAndamento = true;
    bool turno = sorteioTurno();
    int contadorTurnos = 0;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;

    std::pair<int, int> jogada;
    anunciarInicioPartida(Jogador1, Jogador2, turno);
    bool PrimeiroJogador = jogadorInicial(turno);

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        bool movimentosJogadorAtual = turno ? haMovimentosDisponiveis('X') : haMovimentosDisponiveis('O');
        bool movimentosOutroJogador = !turno ? haMovimentosDisponiveis('X') : haMovimentosDisponiveis('O');

        if (!movimentosJogadorAtual && !movimentosOutroJogador)
        {
            std::cout << "Nao ha nenhum movimento possivel a ser realizado. Partida encerrada!" << std::endl;
            checarVencedor(movimentosJogador1, Jogador1, Jogador2, PrimeiroJogador);
            limparTabuleiro();
            return;
        }

        if (!movimentosJogadorAtual)
        {
            std::cout << "Jogador " << (turno ? Jogador1.getApelido() : Jogador2.getApelido())
                      << " nao tem movimentos validos. Turno passado para o proximo jogador." << std::endl;
            turno = !turno;
            continue;
        }

        if (turno)
        {
            anunciarTurnoJogador(Jogador1); // jogadorX no reversi
            jogada = lerJogada(turno);

            marcarTabuleiro(jogada, turno);
            mostrarTabuleiro();

            movimentosJogador1.push_back(jogada);
            if (checarVencedor(movimentosJogador1, Jogador1, Jogador2, PrimeiroJogador))
            {
                jogoEmAndamento = false;
                limparTabuleiro();
                return;
            }
            turno = not turno;
        }
        else
        {
            anunciarTurnoJogador(Jogador2); // jogadorO no reversi
            jogada = lerJogada(turno);

            marcarTabuleiro(jogada, turno);
            mostrarTabuleiro();

            movimentosJogador2.push_back(jogada);
            if (checarVencedor(movimentosJogador2, Jogador1, Jogador2, PrimeiroJogador))
            {
                jogoEmAndamento = false;
                limparTabuleiro();
                return;
            }
            turno = not turno;
        }

        if (checarEmpate(contadorTurnos, Jogador1, Jogador2))
        {
            jogoEmAndamento = false;
            limparTabuleiro();
            return;
        }
    }
}

void Reversi::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno)
{
    char jogador;
    if (turno)
    {
        jogador = 'X';
    }
    else
    {
        jogador = 'O';
    }

    std::vector<std::pair<int, int>> flips;

    if (movimentoValido(jogada, jogador, flips))
    {
        tabuleiro[jogada.first][jogada.second] = jogador;
        for (const auto &par : flips)
        {
            tabuleiro[par.first][par.second] = jogador;
        }
    }
    else
    {
        std::cout << "ERRO: Jogada invalida. Tente novamente." << std::endl;
    }
}

bool Reversi::movimentoValido(std::pair<int, int> &jogada, char jogador, std::vector<std::pair<int, int>> &flips)
{
    flips.clear();
    char oponente = (jogador == 'X') ? 'O' : 'X';
    bool valido = false;

    const std::vector<std::pair<int, int>> direcoes = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};

    for (const auto &par : direcoes)
    {
        int dx = par.first;
        int dy = par.second;

        int x = jogada.first + dx;
        int y = jogada.second + dy;
        std::vector<std::pair<int, int>>
            capturas; // são as peças que seriam flipadas caso a respectiva jogada fosse escolhida.

        while (checarPosicaoValida(x, y) && tabuleiro[x][y] == oponente)
        {
            capturas.push_back({x, y});
            x += dx;
            y += dy;
        }

        if (!capturas.empty() && checarPosicaoValida(x, y) && tabuleiro[x][y] == jogador)
        {
            flips.insert(flips.end(), capturas.begin(), capturas.end()); // adiciona em flips as peças capturáveis.
            valido = true;
        }
    }

    return valido;
}

bool Reversi::haMovimentosDisponiveis(char jogador)
{
    std::vector<std::pair<int, int>> flips;

    for (int i = 0; i < static_cast<int>(tabuleiro.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(tabuleiro[i].size()); j++)
        {
            std::pair<int, int> jogada = {i, j};
            if (tabuleiro[i][j] == ' ' && movimentoValido(jogada, jogador, flips))
            {
                return true;
            }
        }
    }
    return false;
}

void Reversi::limparTabuleiro()
{
    for (auto &linha : tabuleiro)
    {
        for (auto &posicao : linha)
        {
            posicao = ' ';
        }
    }

    tabuleiro.resize(8, std::vector<char>(8, ' '));
    tabuleiro[3][3] = 'X';
    tabuleiro[3][4] = 'O';
    tabuleiro[4][3] = 'O';
    tabuleiro[4][4] = 'X';
}

bool Reversi::checarVencedor(std::vector<std::pair<int, int>> &movimentos, Jogador &jogador_1, Jogador &jogador_2,
                             bool &PrimeiroJogador)
{
    int contadorX = 0;
    int contadorO = 0;

    for (const auto &linha : tabuleiro)
    {
        for (char c : linha)
        {
            if (c == 'X')
            {
                contadorX++;
            }
            if (c == 'O')
            {
                contadorO++;
            }
        }
    }

    bool semMovimentos = !haMovimentosDisponiveis('X') && !haMovimentosDisponiveis('O');

    if (contadorX == 0 || contadorO == 0 || semMovimentos)
    {
        std::cout << "Fim de jogo! X: " << contadorX << " | O: " << contadorO << std::endl;
        if (contadorX > contadorO)
        {
            std::cout << "O jogador dos X ganhou!" << std::endl;
            if (PrimeiroJogador)
            {
                std::cout << "O jogador " << jogador_1.getApelido() << " ganhou o jogo!" << std::endl;
                jogador_1.registrarVitoria("REVERSI");
                jogador_2.registrarDerrota("REVERSI");
            }
            else
            {
                std::cout << "O jogador " << jogador_2.getApelido() << " ganhou o jogo!" << std::endl;
                jogador_2.registrarVitoria("REVERSI");
                jogador_1.registrarDerrota("REVERSI");
            }
        }
        else if (contadorO > contadorX)
        {
            std::cout << "O jogador dos O ganhou!" << std::endl;
            if (PrimeiroJogador)
            {
                std::cout << "O jogador " << jogador_2.getApelido() << " ganhou o jogo!" << std::endl;
                jogador_2.registrarVitoria("REVERSI");
                jogador_1.registrarDerrota("REVERSI");
            }
            else
            {
                std::cout << "O jogador " << jogador_1.getApelido() << " ganhou o jogo!" << std::endl;
                jogador_1.registrarVitoria("REVERSI");
                jogador_2.registrarDerrota("REVERSI");
            }
        }
        else
        {
            std::cout << "O jogo empatou!" << std::endl;
            jogador_1.registrarEmpate("REVERSI");
            jogador_2.registrarEmpate("REVERSI");
        }
        return true;
    }
    return false;
}