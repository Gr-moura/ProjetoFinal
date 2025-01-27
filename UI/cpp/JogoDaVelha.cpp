#include <emscripten.h>

const int linhas = 3;
const int colunas =3;
int tabuleiro[linhas][colunas];

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    bool checarDiagonal(int turno) {
        int contadorMainDiagonal = 0; 
        int contadorAntiDiagonal = 0;

        for (int i = 0; i < linhas; i++) {
            if(tabuleiro[i][i]==turno) contadorMainDiagonal++;
        }
        if (contadorMainDiagonal == linhas) 
            return true;

        for (int i = 0; i < linhas; i++) {
            if(tabuleiro[i][linhas-1-i]==turno) contadorAntiDiagonal++;
        }
        if (contadorAntiDiagonal == linhas)
            return true;

        return false;
    }

    bool checarColunas(int turno) {
        for(int i=0; i<colunas; i++){
            bool colunaCompleta = true;
            for (int j = 0; j < linhas; j++) {
                if(tabuleiro[j][i]!=turno) colunaCompleta = false;
            }
            if(colunaCompleta) return true;
        }
        return false;
    }

    bool checarLinhas(int turno) {
        for (int i=0; i<linhas; i++) {
            bool linhaCompleta = true;
            for (int j=0; j<colunas; j++) {
                if(tabuleiro[i][j]!=turno) linhaCompleta = false;
            }
            if (linhaCompleta) return true;
        }
        return false;
    }

    bool checarVencedor(int turno) {
        if (checarDiagonal(turno) || checarColunas(turno) || checarLinhas(turno)) {
            return true;
        }
        else{
            return false;
        }
    }
}

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    bool jogar(int linha, int coluna, int turno){
        tabuleiro[linha][coluna] = turno;
        return checarVencedor(turno);
    }

}