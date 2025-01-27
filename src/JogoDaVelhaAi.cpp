#include "JogoDaVelhaAi.hpp"

JogoDaVelhaAi::JogoDaVelhaAi() : board(BOARD_SIZE, EMPTY) {}

bool JogoDaVelhaAi::checkWin(char player) const
{
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
        {0, 4, 8}, {2, 4, 6}             // Diagonais
    };

    for (auto &combo : winCombos)
    {
        if (board[combo[0]] == player && board[combo[1]] == player && board[combo[2]] == player)
        {
            return true;
        }
    }
    return false;
}

bool JogoDaVelhaAi::isBoardFull() const
{
    for (char c : board)
    {
        if (c == EMPTY)
            return false;
    }
    return true;
}

int JogoDaVelhaAi::minimax(bool isMaximizing, int depth)
{
    if (checkWin(PLAYER_X))
        return 1;
    if (checkWin(PLAYER_O))
        return -1;
    if (isBoardFull() or depth == 0)
        return 0;

    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i] == EMPTY)
            {
                board[i] = PLAYER_X;
                int score = minimax(false, depth - 1);
                board[i] = EMPTY;

                bestScore = std::max(score, bestScore);
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i] == EMPTY)
            {
                board[i] = PLAYER_O;
                int score = minimax(true, depth - 1);
                board[i] = EMPTY;
                bestScore = std::min(score, bestScore);
            }
        }
        return bestScore;
    }
}

int JogoDaVelhaAi::getBestMove()
{
    int bestScore = INT_MIN;
    int bestMove = -1;
    const int moveOrder[9] = {0, 2, 6, 8, 4, 1, 3, 5, 7};

    for (int i : moveOrder)
    {
        if (board[i] == EMPTY)
        {
            board[i] = PLAYER_X;
            int score = minimax(false, MAX_DEPTH);
            board[i] = EMPTY;

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

std::pair<int, int> JogoDaVelhaAi::humanMove(bool turno)
{
    std::pair<int, int> jogada = jogo.lerJogada();
    int move = jogada.first * 3 + jogada.second;

    board[move] = PLAYER_O;

    jogo.marcarTabuleiro(jogada, turno);
    return jogada;
}

std::pair<int, int> JogoDaVelhaAi::aiMove(bool turno)
{
    int aiMove = getBestMove();
    board[aiMove] = PLAYER_X;

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

    int dificuldade = 2;
    std::cout << "Qual será a dificuldade da AI?\n"
              << "Fácil (0)\nMédio (1)\nDifícil (2)" << std::endl;

    while (true)
    {
        while (not(std::cin >> turno))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira somente um inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (dificuldade == 0 or dificuldade == 1 or dificuldade == 2)
            break;
    }

    MAX_DEPTH = (dificuldade + 1) * 3;
    turno = !turno;

    int contadorTurnos = 0;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;

    jogo.iniciarPartida(Jogador1, Jogador2, turno);

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        if (turno)
        {
            jogo.iniciarTurno(Jogador1);

            movimentosJogador1.push_back(humanMove(turno));
            jogo.mostrarTabuleiro();

            if (jogo.checarVencedor(movimentosJogador1, Jogador1, Jogador2, turno))
            {
                std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!" << std::endl;
                jogoEmAndamento = false;
            }
            turno = not turno;
        }
        else
        {
            jogo.iniciarTurno(Jogador2);

            movimentosJogador2.push_back(aiMove(turno));
            jogo.mostrarTabuleiro();

            if (jogo.checarVencedor(movimentosJogador2, Jogador2, Jogador1, turno))
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
        board = std::vector<char>(BOARD_SIZE, EMPTY);
    }
}