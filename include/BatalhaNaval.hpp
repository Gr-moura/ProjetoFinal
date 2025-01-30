#ifndef BATALHA_NAVAL
#define BATALHA_NAVAL

#include "Jogos.hpp"

/**
 * @class BatalhaNaval
 * @brief Classe que implementa o jogo de batalha naval.
 *
 * A classe `BatalhaNaval` herda da classe base `Jogos` e é responsável por gerenciar
 * toda a lógica do jogo de batalha naval. Isso inclui a inicialização do jogo,
 * o posicionamento dos barcos, a leitura das jogadas dos jogadores, a verificação
 * de vencedores e a exibição do tabuleiro.
 *
 * A classe também lida com exceções específicas do jogo, como tipos de barcos inválidos
 * e posicionamentos incorretos de barcos.
 *
 * @extends Jogos
 */
class BatalhaNaval : public Jogos
{
  public:
    BatalhaNaval();
    void Jogar(Jogador &Jogador1, Jogador &Jogador2) override;

  protected:
    void anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) override;

    bool checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) override { return false; };
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadasAtacante,
                        std::vector<std::pair<int, int>> &barcosOponente, Jogador &vencedor, Jogador &perdedor);
    bool checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor) override
    {
        return false;
    };
    
    std::pair<int, int> lerJogada(std::vector<std::vector<char>> &tabuleiroJogador);
    bool verificarEntrada(char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
    void checarPosicaoValida(std::vector<std::vector<char>> &tabuleiro);

    int getTamanhoBarco(char tipo);
    void lerBarcos(std::vector<std::pair<int, int>> &barcosJogador, Jogador &Jogador);
    bool quantidadeBarcosDisponiveis(std::map<char, int> &countBarcos, char tipo);
    bool verificarTamanhodoBarco(char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
    void inserirBarcos(std::vector<std::pair<int, int>> &barcosJogador, char tipo, int linhaInicial, int colunaInicial,
                       int linhaFinal, int colunaFinal);

    void mostrarTabuleiro(const std::vector<std::vector<char>> &tabuleiroJogador);
    void marcarTabuleiro(std::pair<int, int> &jogada, bool &turno, std::vector<std::vector<char>> &tabuleiroJogador,
                         std::vector<std::pair<int, int>> &barcosJogador);
};

/**
 * @class ExcecaoTipodeBarcoInvalido
 * @brief Exceção lançada quando um tipo de barco inválido é fornecido.
 *
 * Esta exceção é usada para indicar que o tipo de barco fornecido pelo jogador
 * não é válido no contexto do jogo.
 */
class ExcecaoTipodeBarcoInvalido : public std::exception
{
  public:
    const char *what() const throw() override { return "ERRO! Tipo de barco invalido."; }
};

/**
 * @class ExcecaoPosicionamentodeBarco
 * @brief Exceção lançada quando o posicionamento do barco é inválido.
 *
 * Esta exceção é usada para indicar que o posicionamento de um barco no tabuleiro
 * não segue as regras do jogo, como estar fora dos limites do tabuleiro ou não ser
 * alinhado horizontalmente ou verticalmente.
 */
class ExcecaoPosicionamentodeBarco : public std::exception
{
  public:
    const char *what() const throw() override
    {
        return "ERRO! Barcos devem ser colocados horizontalmente ou verticalmente.";
    }
};

#endif