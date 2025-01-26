#include "JogoDaVelhaAi.hpp"

std::vector<std::pair<int, int>> JogoDaVelhaAi::getMovimentosDisponiveis(
    const std::vector<std::vector<char>> &tabuleiro)
{
    std::vector<std::pair<int, int>> movimentosDisponiveis;

    for (int i = 0; i < TAB_ALTURA; i++)
    {
        for (int j = 0; j < TAB_LARGURA; j++)
        {
            if (tabuleiro[i][j] == ' ')
            {
                movimentosDisponiveis.push_back(std::make_pair(i, j));
            }
        }
    }

    return movimentosDisponiveis;
}

int JogoDaVelhaAi::ganhadorDiagonal(const std::vector<std::vector<char>> &tabuleiro)
{
    int contadorDiagonalPrincipal = 0;
    int contadorAntiDiagonal = 0;

    for (int i = 0; i < TAB_ALTURA; i++)
    {
        if (tabuleiro[i][i] == 1)
            contadorDiagonalPrincipal++;
        else if (tabuleiro[i][i] == -1)
            contadorDiagonalPrincipal--;
    }

    if (contadorDiagonalPrincipal == 3)
        return 1;
    else if (contadorDiagonalPrincipal == -3)
        return -1;

    for (int i = 0; i < TAB_ALTURA; i++)
    {
        if (tabuleiro[i][TAB_ALTURA - 1 - i] == 1)
            contadorAntiDiagonal++;
        else if (tabuleiro[i][TAB_ALTURA - 1 - i] == -1)
            contadorAntiDiagonal--;
    }

    if (contadorAntiDiagonal == 3)
        return 1;
    else if (contadorAntiDiagonal == -3)
        return -1;

    return 0;
}

int JogoDaVelhaAi::ganhadorLinha(const std::vector<std::vector<char>> &tabuleiro)
{
    for (int i = 0; i < TAB_ALTURA; i++)
    {
        int contador = 0;
        for (int j = 0; j < TAB_LARGURA; j++)
        {
            if (tabuleiro[i][j] == 1)
                contador++;
            else if (tabuleiro[i][j] == -1)
                contador--;
        }

        if (contador == 3)
            return 1;
        else if (contador == -3)
            return -1;
    }

    return 0;
}

int JogoDaVelhaAi::ganhadorColuna(const std::vector<std::vector<char>> &tabuleiro)
{
    for (int j = 0; j < TAB_LARGURA; j++)
    {
        int contador = 0;
        for (int i = 0; i < TAB_ALTURA; i++)
        {
            if (tabuleiro[i][j] == 1)
                contador++;
            else if (tabuleiro[i][j] == -1)
                contador--;
        }

        if (contador == 3)
            return 1;
        else if (contador == -3)
            return -1;
    }

    return 0;
}

int JogoDaVelhaAi::getStaticValue(const std::vector<std::vector<char>> &tabuleiro)
{

    int resultadoDiagonal = ganhadorDiagonal(tabuleiro);
    int resultadoLinha = ganhadorLinha(tabuleiro);
    int resultadoColuna = ganhadorColuna(tabuleiro);

    if (resultadoDiagonal == 1 || resultadoLinha == 1 || resultadoColuna == 1)
        return 1;
    else if (resultadoDiagonal == -1 || resultadoLinha == -1 || resultadoColuna == -1)
        return -1;

    return 0;
}

int JogoDaVelhaAi::minimax(std::vector<std::vector<char>> tabuleiro, int depth, int alpha, int beta,
                           bool isMaximizingPlayer)
{
    int resultado = getStaticValue(tabuleiro);

    if (depth == 0 or resultado)
        return resultado;

    std::vector<std::pair<int, int>> movimentos = getMovimentosDisponiveis(tabuleiro);

    if (isMaximizingPlayer)
    {
        int maxEval = -1;

        for (auto &movimento : movimentos)
        {
            tabuleiro[movimento.first][movimento.second] = 1;
            int eval = minimax(tabuleiro, depth - 1, alpha, beta, isAiMaximizingPlayer);
            tabuleiro[movimento.first][movimento.second] = 0;

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (maxEval == 1)
                return maxEval;

            if (beta <= alpha)
                break;
        }

        return maxEval;
    }
    else
    {
        int minEval = 1;

        for (auto &movimento : movimentos)
        {
            tabuleiro[movimento.first][movimento.second] = -1;
            int eval = minimax(tabuleiro, depth - 1, alpha, beta, isAiMaximizingPlayer);
            tabuleiro[movimento.first][movimento.second] = 0;

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);

            if (minEval == -1)
                return minEval;

            if (beta <= alpha)
                break;
        }

        return minEval;
    }
}

std::pair<int, int> JogoDaVelhaAi::getMelhorMovimento()
{
    int melhorValor = -1;
    std::pair<int, int> melhorMovimento = std::make_pair(-1, -1);

    std::vector<std::pair<int, int>> movimentos = getMovimentosDisponiveis(posicoesAtual);
    std ::cout << "Movimentos disponiveis: " << movimentos.size() << std::endl;

    for (auto &movimento : movimentos)
    {
        posicoesAtual[movimento.first][movimento.second] = 1;
        int valorMovimento = minimax(posicoesAtual, MAX_DEPTH, -1, 1, isAiMaximizingPlayer);
        std ::cout << "Valor do movimento: " << valorMovimento << std::endl;

        posicoesAtual[movimento.first][movimento.second] = 0;

        if (valorMovimento >= melhorValor)
        {
            melhorValor = valorMovimento;
            melhorMovimento = movimento;
        }
    }

    return melhorMovimento;
}

void JogoDaVelhaAi::marcarTab()
{
    std::pair<int, int> jogada;

    std::cin >> jogada.first >> jogada.second;

    posicoesAtual[jogada.first][jogada.second] = isAiMaximizingPlayer == 1 ? -1 : 1;

    for (int i = 0; i < TAB_ALTURA; i++)
    {
        for (int j = 0; j < TAB_LARGURA; j++)
        {
            if (posicoesAtual[i][j] == 1)
                std::cout << "X ";
            else if (posicoesAtual[i][j] == -1)
                std::cout << "O ";
            else
                std::cout << "- ";
        }
        std::cout << std::endl;
    }
}

void JogoDaVelhaAi::marcarTabAi()
{
    std::pair<int, int> melhorMovimento = getMelhorMovimento();
    posicoesAtual[melhorMovimento.first][melhorMovimento.second] = isAiMaximizingPlayer == 1 ? 1 : -1;

    for (int i = 0; i < TAB_ALTURA; i++)
    {
        for (int j = 0; j < TAB_LARGURA; j++)
        {
            if (posicoesAtual[i][j] == 1)
                std::cout << "X ";
            else if (posicoesAtual[i][j] == -1)
                std::cout << "O ";
            else
                std::cout << "- ";
        }
        std::cout << std::endl;
    }
}