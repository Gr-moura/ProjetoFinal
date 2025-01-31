/**
 * @file Jogos.cpp
 * @brief Implementação dos métodos da classe Jogos.
 *
 * Este arquivo contém a implementação dos métodos da classe Jogos, que fornece funcionalidades básicas
 * para gerenciar partidas de jogos de tabuleiro, como exibição do tabuleiro, controle de turnos,
 * validação de jogadas e execução de partidas.
 */

#include "Jogos.hpp"
#include "Jogador.hpp"

/**
 * @brief Gera uma divisória para separar as linhas do tabuleiro.
 *
 * @return std::string Uma string contendo a divisória do tabuleiro.
 */
std::string Jogos::gerarDivisoriaTabuleiro()
{
    std::string divisor;
    divisor.push_back('\n');

    if (!tabuleiro.empty())
    {
        int numCols = static_cast<int>((tabuleiro.size()));
        for (int i = 0; i < numCols * 4 - 1; i++)
        {
            divisor.push_back('-');
        }
    }

    divisor.push_back('\n');
    return divisor;
}

/**
 * @brief Exibe o tabuleiro atual.
 *
 * Mostra o estado atual do tabuleiro, incluindo as marcações dos jogadores.
 */
void Jogos::mostrarTabuleiro()
{
    for (int i = 0; i < static_cast<int>(tabuleiro.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(tabuleiro[i].size()); j++)
        {
            if (j > 0)
            {
                std::cout << "| " << tabuleiro[i][j] << " ";
            }
            else
            {
                std::cout << " " << tabuleiro[i][j] << " ";
            }
        }
        if (i < static_cast<int>(tabuleiro.size()) - 1)
        {
            std::cout << gerarDivisoriaTabuleiro();
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Limpa o tabuleiro, preparando-o para uma nova partida.
 *
 * Todas as posições do tabuleiro são redefinidas como vazias (' ').
 */
void Jogos::limparTabuleiro()
{
    for (auto &linha : tabuleiro)
    {
        for (auto &coluna : linha)
        {
            coluna = ' ';
        }
    }
    return;
}

/**
 * @brief Marca uma jogada no tabuleiro.
 *
 * @param jogada Coordenadas (linha, coluna) da jogada
 * @param turno Indica o turno do jogador (true para jogador 1, false para jogador 2)
 */
void Jogos::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno)
{
    if (turno)
        tabuleiro[jogada.first][jogada.second] = 'X';
    else
        tabuleiro[jogada.first][jogada.second] = 'O';
}

/**
 * @brief Anuncia o turno do jogador atual.
 *
 * @param Jogador Referência para o jogador cujo turno será anunciado
 */
void Jogos::anunciarTurnoJogador(Jogador &Jogador)
{
    std::cout << "Turno de " << Jogador.getApelido() << "!" << std::endl;
}

/**
 * @brief Sorteia qual jogador começa a partida.
 *
 * @return true Se o jogador 1 começar
 * @return false Se o jogador 2 começar
 */
bool Jogos::sorteioTurno()
{
    srand(std::time(0));
    bool sorteioTurno = std::rand() % 2;
    return sorteioTurno;
}

/**
 * @brief Verifica se uma jogada já foi realizada.
 *
 * @param jogadas Vetor de jogadas realizadas
 * @param linha Linha da jogada a ser verificada
 * @param coluna Coluna da jogada a ser verificada
 *
 * @return true Se a jogada já foi realizada
 * @return false Se a jogada não foi realizada
 */
bool Jogos::checarJogadaExistente(std::vector<std::pair<int, int>> &jogadas, int linha, int coluna)
{
    std::pair<int, int> jogada = {linha, coluna};
    if (std::find(jogadas.begin(), jogadas.end(), jogada) != jogadas.end())
        return true;
    else
        return false;
}

/**
 * @brief Verifica se uma posição no tabuleiro é válida.
 *
 * @param linha Linha da posição a ser verificada
 * @param coluna Coluna da posição a ser verificada
 *
 * @return true Se a posição for válida
 * @return false Se a posição for inválida
 */
bool Jogos::checarPosicaoValida(int linha, int coluna)
{
    try
    {
        if (linha < static_cast<int>(tabuleiro.size()) and linha >= 0 and
            coluna < static_cast<int>(tabuleiro[0].size()) and coluna >= 0)
        {
            return true;
        }
        else
        {
            throw std::out_of_range("");
        }
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }
    catch (...)
    {
        std::cerr << "ERRO: um erro inesperado aconteceu, contate o desenvolvedor para a resolucao do problema."
                  << std::endl;
        return false;
    }
    return false;
}

/**
 * @brief Executa uma partida entre dois jogadores.
 *
 * Gerencia o fluxo da partida, alternando turnos entre os jogadores, validando jogadas,
 * verificando vitórias e empates, e exibindo o tabuleiro.
 *
 * @param Jogador1 Referência para o primeiro jogador
 * @param Jogador2 Referência para o segundo jogador
 */
void Jogos::Jogar(Jogador &Jogador1, Jogador &Jogador2)
{
    bool jogoEmAndamento = true;
    bool turno = sorteioTurno();
    int contadorTurnos = 0;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;

    std::pair<int, int> jogada;
    anunciarInicioPartida(Jogador1, Jogador2, turno);

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        if (turno)
        {
            anunciarTurnoJogador(Jogador1);
            jogada = lerJogada();

            marcarTabuleiro(jogada, turno);
            mostrarTabuleiro();

            movimentosJogador1.push_back(jogada);
            if (checarVencedor(movimentosJogador1, Jogador1, Jogador2))
            {
                std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!" << std::endl;
                jogoEmAndamento = false;
                limparTabuleiro();
                return;
            }
            turno = not turno;
        }
        else
        {
            anunciarTurnoJogador(Jogador2);
            jogada = lerJogada();

            marcarTabuleiro(jogada, turno);
            mostrarTabuleiro();

            movimentosJogador2.push_back(jogada);
            if (checarVencedor(movimentosJogador2, Jogador2, Jogador1))
            {
                jogoEmAndamento = false;
                std::cout << "O jogador " << Jogador2.getApelido() << " ganhou o jogo!" << std::endl;
                limparTabuleiro();
                return;
            }
            turno = not turno;
        }
        if (checarEmpate(contadorTurnos, Jogador1, Jogador2))
        {
            jogoEmAndamento = false;
            limparTabuleiro();
            return;
        }
    }
}