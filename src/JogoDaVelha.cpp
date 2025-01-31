/**
 * @file JogoDaVelha.cpp
 * @brief Implementação dos métodos da classe JogoDaVelha.
 *
 * Este arquivo contém a implementação dos métodos da classe JogoDaVelha, que gerencia o jogo da velha,
 * incluindo a inicialização do tabuleiro, leitura de jogadas, verificação de vitória e empate, e anúncio
 * do início da partida.
 */

#include "JogoDaVelha.hpp"

/**
 * @brief Construtor padrão da classe JogoDaVelha.
 *
 * Inicializa o tabuleiro com tamanho 3x3 e todas as posições vazias.
 */
JogoDaVelha::JogoDaVelha()
{
    tabuleiro.resize(3, std::vector<char>(3, ' '));
}

/**
 * @brief Construtor parametrizado da classe JogoDaVelha.
 *
 * Inicializa o tabuleiro com um tamanho personalizado e todas as posições vazias.
 *
 * @param tamanhoTabuleiro Tamanho do tabuleiro (ex: 3 para um tabuleiro 3x3).
 */
JogoDaVelha::JogoDaVelha(int tamanhoTabuleiro)
{
    tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro, ' '));
}

/**
 * @brief Anuncia o início da partida e define o jogador que começa.
 *
 * Exibe uma mensagem de boas-vindas e informa qual jogador começa a partida.
 *
 * @param Jogador1 Referência para o primeiro jogador
 * @param Jogador2 Referência para o segundo jogador
 * @param turno Referência para a variável que controla o turno dos jogadores
 */
void JogoDaVelha::anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno)
{
    if (turno)
    {
        std::cout << "Bem Vindo ao Jogo da velha! O jogador " << Jogador1.getApelido() << " comecara a partida!"
                  << std::endl;
    }
    else
    {
        std::cout << "Bem Vindo ao Jogo da velha! O jogador " << Jogador2.getApelido() << " comecara a partida!"
                  << std::endl;
    }
    mostrarTabuleiro();
}

/**
 * @brief Lê a jogada do jogador atual.
 *
 * Solicita ao jogador que insira as coordenadas da jogada (linha e coluna) e valida a entrada.
 *
 * @return std::pair<int, int> Coordenadas (linha, coluna) da jogada válida.
 */
std::pair<int, int> JogoDaVelha::lerJogada()
{
    std::cout << "Insira a posicao que deseja marcar no tabuleiro, linha e coluna respectivamente." << std::endl;
    int linha, coluna;
    bool entradaValida = false;
    while (not(entradaValida))
    {
        while (not(std::cin >> linha >> coluna))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira dois inteiros." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (checarPosicaoValida(linha - 1, coluna - 1))
        {
            if (tabuleiro[linha - 1][coluna - 1] == ' ')
            {
                std::pair<int, int> jogada = {linha - 1, coluna - 1};
                entradaValida = true;
                return jogada;
            }
            else
            {
                std::cout << "ERRO!  A posicao escolhida ja esta ocupada. Insira uma posicao valida!" << std::endl;
            }
        }
        else
        {
            std::cout << "ERRO! A posicao escolhida nao esta dentro dos limites do tabuleiro. Escolha uma opcao valida!"
                      << std::endl;
        }
    }
    return {0, 0};
}

/**
 * @brief Verifica se há um vencedor nas diagonais do tabuleiro.
 *
 * @param jogadas Vetor de jogadas realizadas.
 * @return bool True se houver um vencedor, False caso contrário.
 */
bool JogoDaVelha::checarDiagonal(std::vector<std::pair<int, int>> &jogadas)
{
    int numeroLinhasTabuleiro = static_cast<int>(tabuleiro.size());
    int contadorMainDiagonal = 0;
    int contadorAntiDiagonal = 0;

    for (int i = 0; i < numeroLinhasTabuleiro; i++)
    {
        if (std::find(jogadas.begin(), jogadas.end(), std::make_pair(i, i)) != jogadas.end())
            contadorMainDiagonal++;
    }

    if (contadorMainDiagonal == numeroLinhasTabuleiro)
        return true;

    for (int i = 0; i < numeroLinhasTabuleiro; i++)
    {
        if (std::find(jogadas.begin(), jogadas.end(), std::make_pair(i, numeroLinhasTabuleiro - 1 - i)) !=
            jogadas.end())
            contadorAntiDiagonal++;
    }

    if (contadorAntiDiagonal == numeroLinhasTabuleiro)
        return true;

    return false;
}

/**
 * @brief Verifica se há um vencedor nas colunas do tabuleiro.
 *
 * @param jogadas Vetor de jogadas realizadas.
 * @return bool True se houver um vencedor, False caso contrário.
 */
bool JogoDaVelha::checarColunas(std::vector<std::pair<int, int>> &jogadas)
{
    for (int j = 0; j < static_cast<int>(tabuleiro.size()); j++)
    {
        bool colunaCompleta = true;
        for (int i = 0; i < static_cast<int>(tabuleiro[0].size()); i++)
        {
            auto it = std::find(jogadas.begin(), jogadas.end(), std::make_pair(i, j));
            if (it == jogadas.end())
            {
                colunaCompleta = false;
                break;
            }
        }
        if (colunaCompleta)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica se há um vencedor nas linhas do tabuleiro.
 *
 * @param jogadas Vetor de jogadas realizadas.
 * @return bool True se houver um vencedor, False caso contrário.
 */
bool JogoDaVelha::checarLinhas(std::vector<std::pair<int, int>> &jogadas)
{
    for (int i = 0; i < static_cast<int>(tabuleiro.size()); i++)
    {
        bool linhaCompleta = true;
        for (int j = 0; j < static_cast<int>(tabuleiro.size()); j++)
        {
            auto it = std::find(jogadas.begin(), jogadas.end(), std::make_pair(i, j));
            if (it == jogadas.end())
            {
                linhaCompleta = false;
                break;
            }
        }
        if (linhaCompleta)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica se há um vencedor no jogo.
 *
 * @param jogadas Vetor de jogadas realizadas.
 * @param vencedor Referência para o jogador vencedor.
 * @param perdedor Referência para o jogador perdedor.
 * @return bool True se houver um vencedor, False caso contrário.
 */
bool JogoDaVelha::checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor)
{
    if (!jogadas.empty())
    {
        if (checarDiagonal(jogadas) or checarColunas(jogadas) or checarLinhas(jogadas))
        {
            vencedor.registrarVitoria("VELHA");
            perdedor.registrarDerrota("VELHA");
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica se o jogo terminou em empate.
 *
 * @param numeroJogadas Número total de jogadas realizadas.
 * @param jogador_01 Referência para o primeiro jogador.
 * @param jogador_02 Referência para o segundo jogador.
 * @return bool True se o jogo terminou em empate, False caso contrário.
 */
bool JogoDaVelha::checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02)
{
    if (numeroJogadas >= (static_cast<int>(tabuleiro.size() * tabuleiro[0].size())))
    {
        std::cout << "O jogo finalizou com um EMPATE. Ninguem ganhou!" << std::endl;
        jogador_01.registrarEmpate("VELHA");
        jogador_02.registrarEmpate("VELHA");
        return true;
    }
    else
        return false;
}