#include <emscripten.h>

const int linhas = 6;
const int colunas = 7;
int tabuleiro[linhas][colunas];

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    bool checarDiagonal(int turno){
        int contadorDiagonal = 0; 
        //checando para diagonais principais
        for(int linha=0; linha<=linhas-4; linha++){
            for(int coluna=0; coluna<=colunas-4; coluna++){
                contadorDiagonal = 0;
                if(tabuleiro[linha][coluna]==turno) contadorDiagonal++;
                if(tabuleiro[linha+1][coluna+1]==turno) contadorDiagonal++;
                if(tabuleiro[linha+2][coluna+2]==turno) contadorDiagonal++;
                if(tabuleiro[linha+3][coluna+3]==turno) contadorDiagonal++;
            }
            if(contadorDiagonal==4) return true;
        }
        for(int linha=linhas-1; linha>=3; linha--){
            for(int coluna=colunas-1; coluna>=3; coluna--){
                contadorDiagonal = 0;
                if(tabuleiro[linha][coluna]==turno) contadorDiagonal++;
                if(tabuleiro[linha-1][coluna-1]==turno) contadorDiagonal++;
                if(tabuleiro[linha-2][coluna-2]==turno) contadorDiagonal++;
                if(tabuleiro[linha-3][coluna-3]==turno) contadorDiagonal++;
            }
            if(contadorDiagonal==4) return true;
        }

        //checando para diagonais secundárias
        for(int linha=0; linha<=linhas-4; linha++){
            for(int coluna=colunas-1; coluna>=3; coluna--){
                contadorDiagonal = 0;
                if(tabuleiro[linha][coluna]==turno) contadorDiagonal++;
                if(tabuleiro[linha+1][coluna-1]==turno) contadorDiagonal++;
                if(tabuleiro[linha+2][coluna-2]==turno) contadorDiagonal++;
                if(tabuleiro[linha+3][coluna-3]==turno) contadorDiagonal++;
            }
            if(contadorDiagonal==4) return true;
        }
        for(int linha=linhas-1; linha>=3; linha--){
            for(int coluna=0; coluna<=colunas-4; coluna++){
                contadorDiagonal = 0;
                if(tabuleiro[linha][coluna]==turno) contadorDiagonal++;
                if(tabuleiro[linha-1][coluna+1]==turno) contadorDiagonal++;
                if(tabuleiro[linha-2][coluna+2]==turno) contadorDiagonal++;
                if(tabuleiro[linha-3][coluna+3]==turno) contadorDiagonal++;
            }
            if(contadorDiagonal==4) return true;
        }
        return false;
    }

    bool checarLinhas(int turno){
        int contadorLinhas = 0;
        for(int coluna=0; coluna<colunas; coluna++){
            contadorLinhas = 0;
            for(int linha=0; linha<linhas; linha++){
                if(tabuleiro[linha][coluna]==turno) contadorLinhas++;
                else contadorLinhas = 0;
                if(contadorLinhas==4) return true;
            }
        }
        return false;
    }

    bool checarColunas(int turno){
        int contadorColunas = 0;
        for(int linha=0; linha<linhas; linha++){
            contadorColunas = 0;
            for(int coluna=0; coluna<colunas; coluna++){
                if(tabuleiro[linha][coluna]==turno) contadorColunas++;
                else contadorColunas = 0;
                if(contadorColunas==4) return true;
            }
        }
        return false;
    }

    bool checarVencedor(int turno) {
        if (checarDiagonal(turno) || checarLinhas(turno) || checarColunas(turno)) {
            return true;
        }
        return false;
    }
}


extern "C"{
    EMSCRIPTEN_KEEPALIVE

    bool jogar(int linha, int coluna, int turno){
        tabuleiro[linha][coluna] = turno;
        return checarVencedor(turno);
    }
}