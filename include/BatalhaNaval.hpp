#ifndef BATALHA_NAVAL
#define BATALHA_NAVAL

#include "Jogos.hpp"

class BatalhaNaval : public Jogos
{
  public:
    BatalhaNaval();
    void Jogar(Jogador &Jogador1, Jogador &Jogador2) override;

  protected:
    void anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) override {return false;};
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadasAtacante, std::vector<std::pair<int, int>> &barcosOponente,Jogador &vencedor, Jogador &perdedor);
    std::pair<int, int> lerJogada(std::vector<std::vector<char>> &tabuleiroJogador);

    void lerBarcos(std::vector<std::pair<int, int>> &barcosJogador, Jogador &Jogador);
    void inserirBarcos(std::vector<std::pair<int, int>> &barcosJogador, char tipo, int linhaInicial, int colunaInicial,
                       int linhaFinal, int colunaFinal);
    bool quantidadeBarcosDisponiveis(std::map<char,int> &countBarcos, char tipo);
    bool verificarEntrada(char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
    bool verificarTamanhodoBarco(char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

    void checarPosicaoValida(std::vector<std::vector<char>> &tabuleiro);
    void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno,
                         std::vector<std::vector<char>> &tabuleiroJogador,
                         std::vector<std::pair<int, int>> &barcosJogador);
    void mostrarTabuleiro(const std::vector<std::vector<char>> &tabuleiroJogador);
    bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override {return false;};
};

class ExcecaoTipodeBarcoInvalido : public std::exception {
public:
    const char* what() const throw() override {
        return "ERRO! Tipo de barco invalido.";
    }
};

class ExcecaoPosicionamentodeBarco : public std::exception {
public:
    const char* what() const throw() override {
        return "ERRO! Barcos devem ser colocados horizontalmente ou verticalmente.";
    }
};

#endif