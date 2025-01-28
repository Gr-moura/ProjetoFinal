#include <emscripten.h>

const int linhas = 8;
const int colunas = 8;
int tabuleiro[linhas][colunas];

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    void colocarNoTabuleiro(int linha, int coluna, int turno){
        tabuleiro[linha][coluna] = turno;
    }

    //checa se uma posição é válida no tabuleiro
    bool checarPosicaoValida(int linha, int coluna){
        //chcando se a linha é válida
        bool linhavalida = true;
        if(linha<0 || linha>=linhas) linhavalida=false;
        //checando se a coluna é válida
        bool colunavalida = true;
        if(coluna<0 || coluna>=colunas) colunavalida=false;

        return (colunavalida&&linhavalida);
    }
}

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    int movimentoValidoY(int turno, int linha, int coluna){
        const int direcoes[][2] = {{-1, -1}, {-1, 0}, {-1, 1},{0, -1}, {0, 1},{1, -1}, {1, 0}, {1, 1}};

        for (const auto par : direcoes) {
            int dlinha = par[0];
            int dcoluna = par[1];
            int xcoluna = coluna + dcoluna;
            int ylinha = linha + dlinha;

            int oponente;
            if(turno == 1) oponente = 2;
            if(turno == 2) oponente = 1;

            while(checarPosicaoValida(ylinha, xcoluna) && tabuleiro[ylinha][xcoluna] == oponente){
                xcoluna += dcoluna;
                ylinha += dlinha;
            }
            if ((ylinha!=linha+dlinha || xcoluna!=coluna+dcoluna) && checarPosicaoValida(ylinha, xcoluna) && tabuleiro[ylinha][xcoluna] == turno) {
                return ylinha;
            }
        }
        return -1;
    }
}

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    int movimentoValidoX(int turno, int linha, int coluna){
        const int direcoes[][2] = {{-1, -1}, {-1, 0}, {-1, 1},{0, -1}, {0, 1},{1, -1}, {1, 0}, {1, 1}};

        for (const auto par : direcoes) {
            int dlinha = par[0];
            int dcoluna = par[1];
            int xcoluna = coluna + dcoluna;
            int ylinha = linha + dlinha;

            int oponente;
            if(turno == 1) oponente = 2;
            if(turno == 2) oponente = 1;

            while(checarPosicaoValida(ylinha, xcoluna) && tabuleiro[ylinha][xcoluna] == oponente){
                xcoluna += dcoluna;
                ylinha += dlinha;
            }
            if ((ylinha!=linha+dlinha || xcoluna!=coluna+dcoluna) && checarPosicaoValida(ylinha, xcoluna) && tabuleiro[ylinha][xcoluna] == turno) {
                return xcoluna;
            }
        }
        return -1;
    }
}

extern "C"{
    EMSCRIPTEN_KEEPALIVE

    int checarVencedor(int turno){
        bool semMaisMovimentosValidos = true;
        //checando se ainda há movimentos válidos
        for(int linha=0; linha<linhas; linha++){
            for(int coluna=0; coluna<colunas; coluna++){
                if((tabuleiro[linha][coluna]!=1 && tabuleiro[linha][coluna]!=2) && 
                (movimentoValidoX(turno, linha, coluna)!=-1 && movimentoValidoY(turno, linha, coluna)!=-1)){
                    semMaisMovimentosValidos = false;
                }
            }
        }
        //se não, calculando vencedor
        int pontosP1 = 0;
        int pontosp2 = 0;
        if(semMaisMovimentosValidos){
            for(int linha=0; linha<linhas; linha++){
                for(int coluna=0; coluna<colunas; coluna++){
                    if(tabuleiro[linha][coluna]==1) pontosP1++;
                    if(tabuleiro[linha][coluna]==2) pontosp2++;
                }
            }
            if(pontosP1>pontosp2) return 1;
            if(pontosP1==pontosp2) return 0;
            if(pontosP1<pontosp2) return 2;;
        }
        //se ainda houverem movimentos válidos, o jogo ainda pode ser jogado
        return -1;
    }
}