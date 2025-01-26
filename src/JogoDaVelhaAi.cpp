
#include "JogoDaVelhaAi.hpp"

TicTacToe::TicTacToe() : board(BOARD_SIZE, EMPTY), humanTurn(false) {}

void TicTacToe::printBoard() const
{
    std::cout << "\n";
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        std::cout << " " << board[i] << " ";
        if (i % 3 != 2)
            std::cout << "|";
        if (i % 3 == 2 && i != BOARD_SIZE - 1)
            std::cout << "\n-----------\n";
    }
    std::cout << "\n\n";
}

bool TicTacToe::checkWin(char player) const
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

bool TicTacToe::isBoardFull() const
{
    for (char c : board)
    {
        if (c == EMPTY)
            return false;
    }
    return true;
}

int TicTacToe::minimax(bool isMaximizing)
{
    if (checkWin(PLAYER_X))
        return 1;
    if (checkWin(PLAYER_O))
        return -1;
    if (isBoardFull())
        return 0;

    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i] == EMPTY)
            {
                board[i] = PLAYER_X;
                int score = minimax(false);
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
                int score = minimax(true);
                board[i] = EMPTY;
                bestScore = std::min(score, bestScore);
            }
        }
        return bestScore;
    }
}

int TicTacToe::getBestMove()
{
    int bestScore = INT_MIN;
    int bestMove = -1;
    const int moveOrder[9] = {0, 2, 6, 8, 4, 1, 3, 5, 7};

    for (int i : moveOrder)
    {
        if (board[i] == EMPTY)
        {
            board[i] = PLAYER_X;
            int score = minimax(false);
            board[i] = EMPTY;
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

void TicTacToe::humanMove()
{
    int move;
    while (true)
    {
        std::cout << "Sua vez (0-8): ";
        std::cin >> move;
        if (std::cin.fail() || move < 0 || move >= BOARD_SIZE || board[move] != EMPTY)
        {
            std::cout << "Movimento inválido! Tente novamente.\n";
            std::cin.clear();
        }
        else
        {
            board[move] = PLAYER_O;
            break;
        }
    }
}

void TicTacToe::aiMove()
{
    int aiMove = getBestMove();
    board[aiMove] = PLAYER_X;
    std::cout << "IA escolheu a posição " << aiMove << "\n";
}

void TicTacToe::playGame()
{
    std::cout << "Posições:\n";
    std::cout << " 0 | 1 | 2 \n";
    std::cout << "-----------\n";
    std::cout << " 3 | 4 | 5 \n";
    std::cout << "-----------\n";
    std::cout << " 6 | 7 | 8 \n\n";

    while (true)
    {
        printBoard();

        if (checkWin(PLAYER_X))
        {
            std::cout << "IA venceu!\n";
            break;
        }
        if (checkWin(PLAYER_O))
        {
            std::cout << "Você venceu! (Isso não deveria acontecer!)\n";
            break;
        }
        if (isBoardFull())
        {
            std::cout << "Empate!\n";
            break;
        }

        if (humanTurn)
        {
            humanMove();
        }
        else
        {
            aiMove();
        }

        humanTurn = !humanTurn;
    }
}