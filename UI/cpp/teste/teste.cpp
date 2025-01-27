
#include <emscripten.h>


int board[3][3];

extern "C"{
    EMSCRIPTEN_KEEPALIVE
    bool play(int x, int y){
        board[x-1][y-1] = 1;
        if(board[0][0]==1 && board[0][1]==1 && board[0][2]==1) return true;
        else return false;
    }
}