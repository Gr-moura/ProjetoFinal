/**
 * @file Reversi.hpp
 * @brief Definição da classe Reversi e seus métodos para o jogo Reversi.
 */
#include "Reversi.hpp"

/**
 * @brief Construtor padrão da classe Reversi.
 * Inicializa o tabuleiro com o tamanho padrão 8x8 e configura as peças iniciais.
 */
Reversi::Reversi()
{
    tabuleiro.resize(8, std::vector<char>(8, ' '));
    tabuleiro[3][3] = 'X';
    tabuleiro[3][4] = 'O';
    tabuleiro[4][3] = 'O';
    tabuleiro[4][4] = 'X';
}

/**
 * @brief Construtor da classe Reversi com tamanho personalizado do tabuleiro.
 * @param tamanhoTabuleiro Tamanho do tabuleiro (deve ser par)
 */
Reversi::Reversi(int tamanhoTabuleiro)
{
    tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro, ' '));
    int meio = tamanhoTabuleiro / 2;

    tabuleiro[meio - 1][meio - 1] = 'X';
    tabuleiro[meio - 1][meio] = 'O';
    tabuleiro[meio][meio - 1] = 'O';
    tabuleiro[meio][meio] = 'X';
}

/**
 * @brief Anuncia o início da partida e mostra o tabuleiro inicial.
 * @param Jogador1 Referência para o primeiro jogador declarado.
 * @param Jogador2 Referência para o segundo jogador declarado.
 * @param turno Indica qual jogador começará a partida e irá ser o 'X'. Caso turno seja "true",
 * será o Jogador1, caso contrário, será o Jogador2.
 */
void Reversi::anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno)
{

    mostrarTabuleiro();

    if (turno)
    {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador1.getApelido()
                  << " comecara a partida com as pecas 'X'!" << std::endl;
        JogadorX = &Jogador1;
        JogadorO = &Jogador2;
    }
    else
    {
        std::cout << "Bem-vindo ao Reversi! O jogador " << Jogador2.getApelido()
                  << " comecara a partida com as pecas 'X'!" << std::endl;
        JogadorX = &Jogador2;
        JogadorO = &Jogador1;
    }
}

/**
 * @brief Lê a jogada do jogador atual.
 * @param turno Herança da classe Jogos, não é utilizado no Reversi.
 * @return Um par de inteiros representando a posição da jogada, a qual será
 * avaliado pelos métodos: "checarPosicaoValida" e "movimentoValido"
 */
std::pair<int, int> Reversi::lerJogada(bool turno)
{
    int linha, coluna;
    bool entradaValida = false;

    while (not entradaValida)
    {
        std::cout << "Digite a linha e a coluna onde deseja jogar no tabuleiro, por favor. Sua jogada deve capturar ao "
                     "menos 1 peca adversaria!"
                  << std::endl;

        if (!(std::cin >> linha >> coluna))
        {
            std::cout << "ERRO: Entrada invalida! Digite dois numeros inteiros, por favor." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        char jogador = (ContadorTurnos % 2 == 1) ? 'X' : 'O';
        std::vector<std::pair<int, int>> flips;
        std::pair<int, int> jogada = {linha - 1, coluna - 1};

        if (checarPosicaoValida(linha - 1, coluna - 1) and tabuleiro[linha - 1][coluna - 1] == ' ' and
            movimentoValido(jogada, jogador, flips))
        {
            entradaValida = true;
            return {linha - 1, coluna - 1};
        }
        else
        {
            std::cout << "ERRO: A posicao escolhida e invalida ou esta ocupada. Tente novamente." << std::endl;
        }
    }
    return {-1, -1};
}

/**
 * @brief Método principal para executar o jogo.
 * @param Jogador1 Referência para o Jogador1 (primeiro a ser declarado para jogar).
 * @param Jogador2 Referência para o Jogador2 (segundo a ser declarado para jogar).
 */
void Reversi::Jogar(Jogador &Jogador1, Jogador &Jogador2)
{
    bool jogoEmAndamento = true;
    bool turno = sorteioTurno();
    ContadorTurnos = 0;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;

    std::pair<int, int> jogada;
    anunciarInicioPartida(Jogador1, Jogador2, turno);

    while (jogoEmAndamento)
    {
        ContadorTurnos++;
        bool movimentosJogadorAtual =
            (ContadorTurnos % 2 == 1) ? haMovimentosDisponiveis('X') : haMovimentosDisponiveis('O');
        bool movimentosOutroJogador =
            !(ContadorTurnos % 2 == 1) ? haMovimentosDisponiveis('X') : haMovimentosDisponiveis('O');

        if (!movimentosJogadorAtual && !movimentosOutroJogador)
        {
            std::cout << "Nao ha nenhum movimento possivel a ser realizado. Partida encerrada!" << std::endl;
            checarVencedor();
            limparTabuleiro();
            return;
        }

        if (!movimentosJogadorAtual)
        {
            std::cout << "Jogador " << ((ContadorTurnos % 2 == 1) ? Jogador1.getApelido() : Jogador2.getApelido())
                      << " nao tem movimentos validos. Turno passado para o proximo jogador." << std::endl;
            turno = !turno;
            continue;
        }

        if ((ContadorTurnos % 2 == 1))
        {
            anunciarTurnoJogador(Jogador1); // jogadorX no reversi
            bool aux = (ContadorTurnos % 2 == 1);
            jogada = lerJogada((ContadorTurnos % 2 == 1));

            marcarTabuleiro(jogada, aux);
            mostrarTabuleiro();

            movimentosJogador1.push_back(jogada);
            turno = not turno;
        }
        else
        {
            anunciarTurnoJogador(Jogador2); // jogadorO no reversi
            jogada = lerJogada((ContadorTurnos % 2 == 1));
            bool aux = (ContadorTurnos % 2 == 1);

            marcarTabuleiro(jogada, aux);
            mostrarTabuleiro();

            movimentosJogador2.push_back(jogada);
            turno = not turno;
        }

        if (checarEmpate(ContadorTurnos, Jogador1, Jogador2))
        {
            jogoEmAndamento = false;
            limparTabuleiro();
            return;
        }
    }
}

/**
 * @brief Marca a jogada no tabuleiro e atualiza as peças, flipando as peças capturadas, caso o movimento seja válido.
 * @param jogada Par de inteiros representando a posição da jogada
 * @param turno Herança da classe Jogos, não é utilizado no Reversi.
 */
void Reversi::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno)
{
    char jogador;
    if (ContadorTurnos % 2 == 1)
    {
        jogador = 'X';
    }
    else
    {
        jogador = 'O';
    }

    std::vector<std::pair<int, int>> flips;

    if (movimentoValido(jogada, jogador, flips))
    {
        tabuleiro[jogada.first][jogada.second] = jogador;
        for (const auto &par : flips)
        {
            tabuleiro[par.first][par.second] = jogador;
        }
    }
    else
    {
        std::cout << "ERRO: Jogada invalida. Tente novamente." << std::endl;
    }
}

/**
 * @brief Verifica se uma jogada é válida. É um método extremamente importante, determinando a boa execução da partida.
 *
 * @param jogada Par de inteiros representando a posição da jogada
 * @param jogador Caractere representando o jogador ('X' ou 'O')
 * @param flips Vetor de pares de inteiros para armazenar as peças a serem viradas, ou seja, é o vetor que contém as
 * peças capturadas
 *
 * @return true Se a jogada for válida
 * @return false Se a jogada for inválida
 */
bool Reversi::movimentoValido(std::pair<int, int> &jogada, char jogador, std::vector<std::pair<int, int>> &flips)
{
    flips.clear();
    char oponente = (jogador == 'X') ? 'O' : 'X';
    bool valido = false;

    const std::vector<std::pair<int, int>> direcoes = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};

    for (const auto &par : direcoes)
    {
        int dx = par.first;
        int dy = par.second;

        int x = jogada.first + dx;
        int y = jogada.second + dy;
        std::vector<std::pair<int, int>>
            capturas; // são as peças que seriam flipadas caso a respectiva jogada fosse escolhida.

        while (checarPosicaoValida(x, y) && tabuleiro[x][y] == oponente)
        {
            capturas.push_back({x, y});
            x += dx;
            y += dy;
        }

        if (!capturas.empty() && checarPosicaoValida(x, y) && tabuleiro[x][y] == jogador)
        {
            flips.insert(flips.end(), capturas.begin(), capturas.end()); // adiciona em flips as peças capturáveis.
            valido = true;
        }
    }

    return valido;
}

/**
 * @brief Verifica se há movimentos disponíveis para um jogador, ou seja, se há movimentos que capturam ao menos uma
 * peça do adversário.
 *
 * @param jogador Caractere representando o jogador ('X' ou 'O')
 *
 * @return true Se houver movimentos disponíveis
 * @return false Se não houver movimentos disponíveis
 */
bool Reversi::haMovimentosDisponiveis(char jogador)
{
    std::vector<std::pair<int, int>> flips;

    for (int i = 0; i < static_cast<int>(tabuleiro.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(tabuleiro[i].size()); j++)
        {
            std::pair<int, int> jogada = {i, j};
            if (tabuleiro[i][j] == ' ' && movimentoValido(jogada, jogador, flips))
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Limpa o tabuleiro e recoloca as peças iniciais.
 */
void Reversi::limparTabuleiro()
{
    for (auto &linha : tabuleiro)
    {
        for (auto &posicao : linha)
        {
            posicao = ' ';
        }
    }

    tabuleiro.resize(8, std::vector<char>(8, ' '));
    tabuleiro[3][3] = 'X';
    tabuleiro[3][4] = 'O';
    tabuleiro[4][3] = 'O';
    tabuleiro[4][4] = 'X';

    ContadorTurnos = 0;
}

/**
 * @brief Verifica o vencedor da partida e atualiza os registros dos jogadores envolvidos na partida.
 *
 * @param movimentos Vetor de pares de inteiros representando as jogadas do jogador
 * @param jogador_1 Referência para o Jogador1
 * @param jogador_2 Referência para o Jogador2
 * @param PrimeiroJogador Indica qual jogador começou a partida
 *
 * @return true se houver um vencedor ou caso ocorra empat
 * @return false Se a partida ainda não acabou
 */
bool Reversi::checarVencedor()
{
    int contadorX = 0;
    int contadorO = 0;

    for (const auto &linha : tabuleiro)
    {
        for (char c : linha)
        {
            if (c == 'X')
            {
                contadorX++;
            }
            if (c == 'O')
            {
                contadorO++;
            }
        }
    }

    bool semMovimentos = !haMovimentosDisponiveis('X') && !haMovimentosDisponiveis('O');

    if (contadorX == 0 || contadorO == 0 || semMovimentos)
    {
        std::cout << "Fim de jogo! X: " << contadorX << " | O: " << contadorO << std::endl;

        if (contadorX > contadorO)
        {
            std::cout << "O jogador dos X ganhou!" << std::endl;
            std::cout << "O jogador " << JogadorX->getApelido() << " ganhou o jogo!" << std::endl;
            JogadorX->registrarVitoria("REVERSI");
            JogadorO->registrarDerrota("REVERSI");
        }
        else if (contadorO > contadorX)
        {
            std::cout << "O jogador dos O ganhou!" << std::endl;
            std::cout << "O jogador " << JogadorO->getApelido() << " ganhou o jogo!" << std::endl;
            JogadorO->registrarVitoria("REVERSI");
            JogadorX->registrarDerrota("REVERSI");
        }
        else
        {
            std::cout << "O jogo empatou!" << std::endl;
            JogadorO->registrarEmpate("REVERSI");
            JogadorX->registrarEmpate("REVERSI");
        }

        return true;
    }
    return false;
}