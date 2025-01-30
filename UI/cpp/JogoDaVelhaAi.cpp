#include <emscripten.h>

const int lines = 3;
const int columns = 3;
int board[lines*columns]={0};

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    void colocarPeca(int position, int turno){
        board[position] = turno;
    }

    bool checkWin(int player)
    {
        const int winCombos[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
            {0, 4, 8}, {2, 4, 6}             // Diagonais
        };
        for (int i=0; i<8; i++)
        {
            if (board[winCombos[i][0]] == player && board[winCombos[i][1]] == player && board[winCombos[i][2]] == player)
            {
                return true;
            }
        }
        return false;
    }

    bool isBoardFull()
    {
        for (int c : board)
        {
            if (c == 0)
                return false;
        }
        return true;
    }

    int minimax(bool isMaximizing, int depth)
    {
        if (checkWin(1)) return 1;
        if (checkWin(2)) return -1;
        if (isBoardFull() or depth == 0) return 0;

        if (isMaximizing)
        {
            int bestScore = -2;
            for (int i = 0; i < lines*columns; i++)
            {
                if (board[i] != 1 && board[i]!=2)
                {
                    board[i] = 1;
                    int score = minimax(false, depth - 1);
                    board[i] = 0;
                    if(score>bestScore) bestScore = score;
                }
            }
            return bestScore;
        }
        else
        {
            int bestScore = 2;
            for (int i = 0; i < lines*columns; i++)
            {
                if (board[i] != 1 && board[i]!=2)
                {
                    board[i] = 2;
                    int score = minimax(true, depth - 1);
                    board[i] = 0;
                    if(bestScore>score) bestScore = score;
                }
            }
            return bestScore;
        }
    }
}

extern "C"{
    EMSCRIPTEN_KEEPALIVE
    
    int getBestMove(int difficulty)
    {
        int bestScore = -2;
        int bestMove = -1;
        const int moveOrder[] = {0, 2, 6, 8, 4, 1, 3, 5, 7};

        for (int i=0; i<lines*columns; i++)
        {
            if (board[moveOrder[i]] != 1 && board[moveOrder[i]]!=2)
            {
                board[moveOrder[i]] = 1;
                int score = minimax(false, difficulty);
                board[moveOrder[i]] = 0;

                if (bestScore < score)
                {
                    bestScore = score;
                    bestMove = moveOrder[i];

                    if (bestScore == 1)
                        break;
                }
            }
        }
        return bestMove;
    }
}