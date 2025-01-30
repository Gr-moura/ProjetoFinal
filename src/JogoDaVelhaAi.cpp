/**
 * @file JogoDaVelhaAi.cpp
 * @brief
 *
 *
 *
 */

#include "JogoDaVelhaAi.hpp"

JogoDaVelhaAi::JogoDaVelhaAi() : tabuleiro(TABULEIRO_SIZE, VAZIO) {}

bool JogoDaVelhaAi::checarVitoria(char player) const
{
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
        {0, 4, 8}, {2, 4, 6}             // Diagonais
    };

    for (auto &combo : winCombos)
    {
        if (tabuleiro[combo[0]] == player && tabuleiro[combo[1]] == player && tabuleiro[combo[2]] == player)
        {
            return true;
        }
    }
    return false;
}

bool JogoDaVelhaAi::isTabuleiroCheio() const
{
    for (char c : tabuleiro)
    {
        if (c == VAZIO)
            return false;
    }
    return true;
}

int JogoDaVelhaAi::minimax(bool isMaximizing, int depth)
{
    if (checarVitoria(JOGADOR_X))
        return 1;
    if (checarVitoria(JOGADOR_O))
        return -1;
    if (isTabuleiroCheio() or depth == 0)
        return 0;

    if (isMaximizing)
    {
        int bestScore = -2;
        for (int i = 0; i < TABULEIRO_SIZE; i++)
        {
            if (tabuleiro[i] == VAZIO)
            {
                tabuleiro[i] = JOGADOR_X;
                int score = minimax(false, depth - 1);
                tabuleiro[i] = VAZIO;

                bestScore = std::max(score, bestScore);
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 2;
        for (int i = 0; i < TABULEIRO_SIZE; i++)
        {
            if (tabuleiro[i] == VAZIO)
            {
                tabuleiro[i] = JOGADOR_O;
                int score = minimax(true, depth - 1);
                tabuleiro[i] = VAZIO;
                bestScore = std::min(score, bestScore);
            }
        }
        return bestScore;
    }
}

int JogoDaVelhaAi::getMelhorMovimento()
{
    int bestScore = -2;
    int bestMove = -1;
    const std::vector<int> moveOrder = {0, 2, 6, 8, 4, 1, 3, 5, 7};

    for (int i : moveOrder)
    {
        if (tabuleiro[i] == VAZIO)
        {
            tabuleiro[i] = JOGADOR_X;
            int score = minimax(false, MAX_PROFUNDIDADE);
            tabuleiro[i] = VAZIO;

            if (bestScore < score)
            {
                bestScore = score;
                bestMove = i;

                if (bestScore == 1)
                    break;
            }
        }
    }
    return bestMove;
}

std::pair<int, int> JogoDaVelhaAi::jogadaHumano(bool turno)
{
    std::pair<int, int> jogada = jogo.lerJogada();
    int move = jogada.first * 3 + jogada.second;

    tabuleiro[move] = JOGADOR_O;

    jogo.marcarTabuleiro(jogada, turno);
    return jogada;
}

std::pair<int, int> JogoDaVelhaAi::jogadaAI(bool turno)
{
    int aiMove = getMelhorMovimento();
    tabuleiro[aiMove] = JOGADOR_X;

    std::pair<int, int> jogada = {aiMove / 3, aiMove % 3};

    jogo.marcarTabuleiro(jogada, turno);
    return jogada;
}

void JogoDaVelhaAi::Jogar(Jogador &Jogador1, Jogador &Jogador2)
{
    bool jogoEmAndamento = true;

    std::cout << "Bem vindo ao Jogo da velha! Qual jogador deverá começar a partida?\n"
              << Jogador1.getApelido() << " (0)\nAI (1)" << std::endl;

    bool turno;
    while (true)
    {
        while (not(std::cin >> turno))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira somente um inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (turno == 0 or turno == 1)
            break;
    }

    int dificuldade = 0;
    std::cout << "Qual será a dificuldade da AI?\n"
              << "Fácil (0)\nMédio (1)\nDifícil (2)" << std::endl;

    while (true)
    {
        while (not(std::cin >> dificuldade))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira somente um inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (dificuldade == 0 or dificuldade == 1 or dificuldade == 2)
            break;
    }

    if (dificuldade == 0)
        MAX_PROFUNDIDADE = 0;
    else if (dificuldade == 1)
        MAX_PROFUNDIDADE = 3;
    else
        MAX_PROFUNDIDADE = 9;

    turno = !turno;

    int contadorTurnos = 0;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;

    jogo.anunciarInicioPartida(Jogador1, Jogador2, turno);

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        if (turno)
        {
            jogo.anunciarTurnoJogador(Jogador1);

            movimentosJogador1.push_back(jogadaHumano(turno));
            jogo.mostrarTabuleiro();

            if (jogo.checarVencedor(movimentosJogador1, Jogador1, Jogador2))
            {
                std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!" << std::endl;
                jogoEmAndamento = false;
            }
            turno = not turno;
        }
        else
        {
            jogo.anunciarTurnoJogador(Jogador2);

            movimentosJogador2.push_back(jogadaAI(turno));
            jogo.mostrarTabuleiro();

            if (jogo.checarVencedor(movimentosJogador2, Jogador2, Jogador1))
            {
                jogoEmAndamento = false;
                std::cout << "O jogador " << Jogador2.getApelido() << " ganhou o jogo!" << std::endl;
            }
            turno = not turno;
        }

        if (jogo.checarEmpate(contadorTurnos, Jogador1, Jogador2))
            jogoEmAndamento = false;
    }

    if (!jogoEmAndamento)
    {
        jogo = JogoDaVelha();
        tabuleiro = std::vector<char>(TABULEIRO_SIZE, VAZIO);
    }
}