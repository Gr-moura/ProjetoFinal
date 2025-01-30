/**
 * @file JogoDaVelhaAi.cpp
 * @brief Implementação da lógica do jogo da velha com IA usando o algoritmo Minimax.
 *
 * Este arquivo contém a implementação das funções da classe JogoDaVelhaAi, incluindo
 * a lógica de verificação da vitória, do empate, e do algoritmo Minimax para a IA.
 */

#include "JogoDaVelhaAi.hpp"

/**
 * @brief Construtor que inicializa o tabuleiro com células vazias
 */
JogoDaVelhaAi::JogoDaVelhaAi() : tabuleiro(TABULEIRO_SIZE, VAZIO) {}

/**
 * @brief Verifica se o jogador especificado alcançou uma condição de vitória
 *
 * Checa todas as combinações possíveis de vitória (linhas, colunas e diagonais)
 *
 * @param player Jogador a ser verificado (JOGADOR_X ou JOGADOR_O)
 * @return true Se o jogador tem três símbolos consecutivos em alguma linha/coluna/diagonal
 * @return false Caso não haja vitória
 */
bool JogoDaVelhaAi::checarVitoria(char jogador) const
{
    const int combinacoesVitoria[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
        {0, 4, 8}, {2, 4, 6}             // Diagonais
    };

    for (auto &combo : combinacoesVitoria)
    {
        if (tabuleiro[combo[0]] == jogador && tabuleiro[combo[1]] == jogador && tabuleiro[combo[2]] == jogador)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica se todas as posições do tabuleiro estão ocupadas
 *
 * @return true Se não há mais espaços vazios no tabuleiro
 * @return false Se há pelo menos um espaço vazio restante
 */
bool JogoDaVelhaAi::isTabuleiroCheio() const
{
    for (char c : tabuleiro)
    {
        if (c == VAZIO)
            return false;
    }
    return true;
}

/**
 * @brief Implementa o algoritmo Minimax para avaliação de jogadas
 *
 * Avalia recursivamente todas as jogadas possíveis até a profundidade máxima configurada,
 * alternando entre jogadores de maximização (IA) e minimização (jogador humano)
 *
 * @param isMaximizador Indica se é o turno do jogador maximizador (IA)
 * @param profundidade Profundidade atual da recursão
 * @return int Valor heurístico da posição (1 para vitória IA, -1 para derrota, 0 para neutro)
 */
int JogoDaVelhaAi::minimax(bool isMaximizador, int profundidade)
{
    if (checarVitoria(JOGADOR_X))
        return 1;
    if (checarVitoria(JOGADOR_O))
        return -1;
    if (isTabuleiroCheio() or profundidade == 0)
        return 0;

    if (isMaximizador)
    {
        int melhorScore = -2;
        for (int i = 0; i < TABULEIRO_SIZE; i++)
        {
            if (tabuleiro[i] == VAZIO)
            {
                tabuleiro[i] = JOGADOR_X;
                int score = minimax(false, profundidade - 1);
                tabuleiro[i] = VAZIO;

                melhorScore = std::max(score, melhorScore);
            }
        }
        return melhorScore;
    }
    else
    {
        int melhorScore = 2;
        for (int i = 0; i < TABULEIRO_SIZE; i++)
        {
            if (tabuleiro[i] == VAZIO)
            {
                tabuleiro[i] = JOGADOR_O;
                int score = minimax(true, profundidade - 1);
                tabuleiro[i] = VAZIO;
                melhorScore = std::min(score, melhorScore);
            }
        }
        return melhorScore;
    }
}

/**
 * @brief Calcula a melhor jogada para a IA usando Minimax
 *
 * Utiliza uma ordem otimizada de verificação de movimentos (cantos primeiro, centro depois, bordas por último)
 * para acelerar a busca pela jogada ideal e para evitar jogadas subótimas, uma vez que, como jogadores perfeitos
 * sempre empatam, uma má ordenação dos movimentos pode dificultar a IA na escolha da melhor jogada.
 *
 * @return int Índice da melhor jogada no tabuleiro (0-8)
 */
int JogoDaVelhaAi::getMelhorMovimento()
{
    int melhorScore = -2;
    int melhorMovimento = -1;
    const std::vector<int> ordemMovimentos = {0, 2, 6, 8, 4, 1, 3, 5, 7};

    for (int i : ordemMovimentos)
    {
        if (tabuleiro[i] == VAZIO)
        {
            tabuleiro[i] = JOGADOR_X;
            int score = minimax(false, MAX_PROFUNDIDADE);
            tabuleiro[i] = VAZIO;

            if (melhorScore < score)
            {
                melhorScore = score;
                melhorMovimento = i;

                if (melhorScore == 1)
                    break;
            }
        }
    }
    return melhorMovimento;
}

/**
 * @brief Processa e registra uma jogada do jogador humano
 *
 * A jogada é marcada no tabuleiro da AI e no objeto JogoDaVelha, uma vez que
 * a exibição do jogo depende do estado do tabuleiro do objeto JogoDaVelha.
 *
 * @param turno Indica de qual jogador é o turno (não utilizado na implementação atual)
 * @return std::pair<int, int> Coordenadas (linha, coluna) da jogada
 */
std::pair<int, int> JogoDaVelhaAi::jogarHumano(bool turno)
{
    std::pair<int, int> jogada = jogo.lerJogada();
    int move = jogada.first * 3 + jogada.second;

    tabuleiro[move] = JOGADOR_O;

    jogo.marcarTabuleiro(jogada, turno);
    return jogada;
}

/**
 * @brief Calcula e executa a jogada da IA
 *
 * A jogada é marcada no tabuleiro da AI e no objeto JogoDaVelha, uma vez que
 * a exibição do jogo depende do estado do tabuleiro do objeto JogoDaVelha.
 *
 * @param turno Indica de qual jogador é o turno (não utilizado na implementação atual)
 * @return std::pair<int, int> Coordenadas (linha, coluna) da jogada
 */
std::pair<int, int> JogoDaVelhaAi::jogarAI(bool turno)
{
    int jogadaAI = getMelhorMovimento();
    tabuleiro[jogadaAI] = JOGADOR_X;

    std::pair<int, int> jogada = {jogadaAI / 3, jogadaAI % 3};

    jogo.marcarTabuleiro(jogada, turno);
    return jogada;
}

/**
 * @brief Controla o fluxo principal do jogo
 *
 * Gerencia todo o ciclo de vida do jogo, incluindo:
 * - Configuração inicial de jogadores e dificuldade
 * - Alternância de turnos entre jogadores
 * - Verificação de condições de término (vitória/empate)
 * - Reinicialização do jogo ao final
 *
 * @param Jogador1 Primeiro jogador (normalmente humano)
 * @param Jogador2 Segundo jogador (normalmente IA)
 */
void JogoDaVelhaAi::Jogar(Jogador &Jogador1, Jogador &Jogador2)
{
    bool jogoEmAndamento = true;

    std::cout << "Bem vindo ao Jogo da velha! Qual jogador deverá começar a partida?\n"
              << Jogador1.getApelido() << " (0)\nAI (1)" << std::endl;

    bool turno;
    while (true)
    {
        while (not(std::cin >> turno))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira somente um inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (turno == 0 or turno == 1)
            break;
    }

    int dificuldade = 0;
    std::cout << "Qual será a dificuldade da AI?\n"
              << "Fácil (0)\nMédio (1)\nDifícil (2)" << std::endl;

    while (true)
    {
        while (not(std::cin >> dificuldade))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira somente um inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (dificuldade == 0 or dificuldade == 1 or dificuldade == 2)
            break;
    }

    if (dificuldade == 0)
        MAX_PROFUNDIDADE = 0;
    else if (dificuldade == 1)
        MAX_PROFUNDIDADE = 3;
    else
        MAX_PROFUNDIDADE = 9;

    turno = !turno;

    int contadorTurnos = 0;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;

    jogo.anunciarInicioPartida(Jogador1, Jogador2, turno);

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        if (turno)
        {
            jogo.anunciarTurnoJogador(Jogador1);

            movimentosJogador1.push_back(jogarHumano(turno));
            jogo.mostrarTabuleiro();

            if (jogo.checarVencedor(movimentosJogador1, Jogador1, Jogador2))
            {
                std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!" << std::endl;
                jogoEmAndamento = false;
            }
            turno = not turno;
        }
        else
        {
            jogo.anunciarTurnoJogador(Jogador2);

            movimentosJogador2.push_back(jogarAI(turno));
            jogo.mostrarTabuleiro();

            if (jogo.checarVencedor(movimentosJogador2, Jogador2, Jogador1))
            {
                jogoEmAndamento = false;
                std::cout << "O jogador " << Jogador2.getApelido() << " ganhou o jogo!" << std::endl;
            }
            turno = not turno;
        }

        if (jogo.checarEmpate(contadorTurnos, Jogador1, Jogador2))
            jogoEmAndamento = false;
    }

    if (!jogoEmAndamento)
    {
        jogo = JogoDaVelha();
        tabuleiro = std::vector<char>(TABULEIRO_SIZE, VAZIO);
    }
}