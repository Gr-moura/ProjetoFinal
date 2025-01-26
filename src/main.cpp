#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// Check if player has won
bool checkWin(const vector<char> &board, char player)
{
    // All possible winning combinations
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
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

// Check if board is full
bool isBoardFull(const vector<char> &board)
{
    for (char c : board)
    {
        if (c == ' ')
            return false;
    }
    return true;
}

// Minimax implementation
int minimax(vector<char> &board, bool isMaximizing)
{
    // Terminal states
    if (checkWin(board, 'X'))
        return 1;
    if (checkWin(board, 'O'))
        return -1;
    if (isBoardFull(board))
        return 0;

    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == ' ')
            {
                board[i] = 'X';
                int score = minimax(board, false);
                board[i] = ' ';
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == ' ')
            {
                board[i] = 'O';
                int score = minimax(board, true);
                board[i] = ' ';
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

// Get AI's best move
int getBestMove(vector<char> &board)
{
    int bestScore = INT_MIN;
    int bestMove = -1;

    // Move priorities (center first, then corners, then edges)
    const int moveOrder[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

    for (int i : moveOrder)
    {
        if (board[i] == ' ')
        {
            board[i] = 'X';
            int score = minimax(board, false);
            board[i] = ' ';

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

// Print board
void printBoard(const vector<char> &board)
{
    for (int i = 0; i < 9; i++)
    {
        cout << board[i];
        if (i % 3 != 2)
            cout << "|";
        if (i % 3 == 2 && i != 8)
            cout << "\n-+-+-\n";
    }
    cout << "\n\n";
}

int main()
{
    vector<char> board(9, ' ');
    bool humanTurn = true; // AI plays first

    while (true)
    {
        printBoard(board);

        if (checkWin(board, 'X'))
        {
            cout << "AI wins!\n";
            break;
        }
        if (checkWin(board, 'O'))
        {
            cout << "Human wins! (This should never happen!)\n";
            break;
        }
        if (isBoardFull(board))
        {
            cout << "It's a tie!\n";
            break;
        }

        if (humanTurn)
        {
            int move;
            cout << "Enter your move (0-8): ";
            cin >> move;

            if (move < 0 || move >= 9 || board[move] != ' ')
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            board[move] = 'O';
        }
        else
        {
            int aiMove = getBestMove(board);
            board[aiMove] = 'X';
            cout << "AI chooses position " << aiMove << "\n";
        }

        humanTurn = !humanTurn;
    }

    return 0;
}