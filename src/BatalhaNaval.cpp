#include "BatalhaNaval.hpp"

/**
 * @brief Construtor da classe BatalhaNaval.
 *
 * Inicializa o tabuleiro do jogo com um tamanho de 10x10, preenchendo todas as posições com o caractere '~',
 * que representa água. Mesmo que o tabuleiro não seja usado durante o jogo, ele é importante para estabelecer
 * o tamanho de cada um dos 2 tabuleiros que serão usados.
 */
BatalhaNaval::BatalhaNaval()
{
    tabuleiro.resize(10, std::vector<char>(10, '~'));
}

/**
 * @brief Método principal que controla o fluxo do jogo de batalha naval.
 *
 * Este método é responsável por gerenciar todo o ciclo de vida do jogo, desde a inicialização
 * até a determinação do vencedor. Ele coordena as ações dos dois jogadores, alternando seus turnos
 * e verificando se algum deles atingiu a condição de vitória.
 *
 * O jogo começa com o sorteio de quem iniciará a partida. Em seguida, cada jogador posiciona seus
 * barcos no tabuleiro. Após o posicionamento, os jogadores alternam turnos para atacar as posições
 * do tabuleiro do oponente. O jogo continua até que todos os barcos de um jogador sejam afundados,
 * momento em que o oponente é declarado vencedor.
 *
 * Os tabuleiros mostrados durante a execução do código dizem respeito ao tabuleiro dos ataques, porque
 * caso o tabuleiro dos barcos de cada jogador aparecesse, a ideia de 2 jogadores no mesmo computador
 * seria impossível,
 *
 * Durante o jogo, o tabuleiro de cada jogador é exibido após cada jogada, mostrando os acertos ('X')
 * e os erros ('O'). O método também registra as vitórias e derrotas dos jogadores ao final da partida.
 *
 * @param Jogador1 Referência para o primeiro jogador.
 * @param Jogador2 Referência para o segundo jogador.
 *
 * @details O fluxo do jogo é o seguinte:
 * 1. Inicializa os tabuleiros de jogadas e os vetores de barcos para ambos os jogadores.
 * 2. Sorteia qual jogador começa a partida.
 * 3. Cada jogador posiciona seus barcos no tabuleiro, seguindo as regras do jogo.
 * 4. Alterna os turnos entre os jogadores, permitindo que cada um ataque o tabuleiro do oponente.
 * 5. Verifica, após cada jogada, se todos os barcos do oponente foram afundados.
 * 6. Declara o vencedor e registra o resultado no perfil dos jogadores.
 * 7. Encerra o jogo.
 */
void BatalhaNaval::Jogar(Jogador &Jogador1, Jogador &Jogador2)
{
    std::vector<std::vector<char>> tabuleiroJogadasJogador1 = tabuleiro;
    std::vector<std::vector<char>> tabuleiroJogadasJogador2 = tabuleiro;
    std::vector<std::pair<int, int>> movimentosJogador1;
    std::vector<std::pair<int, int>> movimentosJogador2;
    std::vector<std::pair<int, int>> barcosJogador1;
    std::vector<std::pair<int, int>> barcosJogador2;
    bool jogoEmAndamento = true;
    bool turno = sorteioTurno();
    int contadorTurnos = 0;

    std::pair<int, int> jogada;
    anunciarInicioPartida(Jogador1, Jogador2, turno);

    lerBarcos(barcosJogador1, Jogador1);
    std::cout << "\033[2J\033[1;1H"; // Limpador de linha
    lerBarcos(barcosJogador2, Jogador2);
    std::cout << "\033[2J\033[1;1H";

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        if (turno)
        {
            anunciarTurnoJogador(Jogador1);
            jogada = lerJogada(tabuleiroJogadasJogador1);

            marcarTabuleiro(jogada, turno, tabuleiroJogadasJogador1, barcosJogador2);
            mostrarTabuleiro(tabuleiroJogadasJogador1);

            movimentosJogador1.push_back(jogada);
            if (checarVencedor(movimentosJogador1, barcosJogador2, Jogador1, Jogador2))
            {
                std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!" << std::endl;
                jogoEmAndamento = false;
                Jogador1.registrarVitoria("BATALHANAVAL");
                Jogador2.registrarDerrota("BATALHANAVAL");
                return;
            }
            turno = not turno;
        }
        else
        {
            anunciarTurnoJogador(Jogador2);
            jogada = lerJogada(tabuleiroJogadasJogador2);

            marcarTabuleiro(jogada, turno, tabuleiroJogadasJogador2, barcosJogador1);
            mostrarTabuleiro(tabuleiroJogadasJogador2);

            movimentosJogador2.push_back(jogada);
            if (checarVencedor(movimentosJogador2, barcosJogador1, Jogador2, Jogador1))
            {
                std::cout << "O jogador " << Jogador2.getApelido() << " ganhou o jogo!" << std::endl;
                jogoEmAndamento = false;
                Jogador2.registrarVitoria("BATALHANAVAL");
                Jogador1.registrarDerrota("BATALHANAVAL");
                return;
            }
            turno = not turno;
        }
    }
}

/**
 * @brief Anuncia o início da partida de Batalha Naval entre dois jogadores e quem irá começar.
 * @param Jogador1 Referência para o primeiro jogador.
 * @param Jogador2 Referência para o segundo jogador.
 * @param turno Referência para a variável que controla o turno dos jogadores.
 */
void BatalhaNaval::anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno)
{
    if (turno)
    {
        std::cout << "Bem Vindo ao Batalha Naval! O jogador " << Jogador1.getApelido() << " comecara a partida!"
                  << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << "Bem Vindo ao Batalha Naval! O jogador " << Jogador2.getApelido() << " comecara a partida!"
                  << std::endl
                  << std::endl;
    }
}

/**
 * @brief Verifica se há um vencedor com base nas jogadas do atacante e nos barcos do oponente.
 * Há um iterador que passa por todos os barcos do jogador inimigo e os compara com as jogadas do atacante,
 * caso algum barco não seja encontrado, o retorno é falso e o jogo continua, caso contrário a vitória e a derrota são
 * contabilizadas nos respectivos jogadores e o jogo termina com o print do vencedor.
 *
 * @param jogadasAtacante Vetor de pares de inteiros representando as jogadas do atacante.
 * @param barcosOponente Vetor de pares de inteiros representando os barcos do oponente.
 * @param vencedor Referência para o jogador que venceu.
 * @param perdedor Referência para o jogador que perdeu.
 * @return Retorna `true` se houver um vencedor, `false` caso contrário.
 */
bool BatalhaNaval::checarVencedor(std::vector<std::pair<int, int>> &jogadasAtacante,
                                  std::vector<std::pair<int, int>> &barcosOponente, Jogador &vencedor,
                                  Jogador &perdedor)
{
    for (const auto &posicaoBarco : barcosOponente)
    {
        if (std::find(jogadasAtacante.begin(), jogadasAtacante.end(), posicaoBarco) == jogadasAtacante.end())
        {
            return false; // Ainda há barcos não atingidos
        }
    }
    return true; // Todos os barcos foram atingidos
}

/**
 * @brief Lê a jogada do jogador, verificando se a posição é válida e se o tipo de dado inserido é o desejado.
 * A inserção é feita usando (-1) nas posições para corrigir o erro entre a entrada real [1-10] e a divisão do tabuleiro
 * [0,9].abort
 *
 * @param tabuleiroJogador Matriz de caracteres representando o tabuleiro do jogador.
 * @return Par de inteiros representando a jogada (linha, coluna).
 */
std::pair<int, int> BatalhaNaval::lerJogada(std::vector<std::vector<char>> &tabuleiroJogador)
{
    std::cout << "Insira a posicao que atacar seu adversario, linha e coluna respectivamente." << std::endl;
    int linha, coluna;
    bool entradaValida = false;
    while (!entradaValida)
    {
        while (!(std::cin >> linha >> coluna))
        {
            std::cout << "ERRO, tipo de dado invalido. Por favor insira dois inteiros." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (Jogos::checarPosicaoValida(linha - 1, coluna - 1))
        {
            if (tabuleiroJogador[linha - 1][coluna - 1] == '~')
            {
                std::pair<int, int> jogada = {linha - 1, coluna - 1};
                entradaValida = true;
                return jogada;
            }
            else
            {
                std::cout << "ERRO! A posicao escolhida ja foi atacada!. Insira uma posicao valida!" << std::endl;
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
 * @brief Verifica se a entrada para posicionar o barco é válida e serve como uma função auxiliar para
 * lerBarcos e funciona com um sistema de try-catch-throw, usando também de exceptions personalizadas para
 * deixar os erros mais evidentes no caso de que algum deles aconteça.
 *
 * @param tipo Caractere representando o tipo de barco.
 * @param linhaInicial Inteiro representando a linha inicial do barco.
 * @param colunaInicial Inteiro representando a coluna inicial do barco.
 * @param linhaFinal Inteiro representando a linha final do barco.
 * @param colunaFinal Inteiro representando a coluna final do barco.
 * @return Retorna `true` se a entrada for válida, `false` caso contrário.
 */
bool BatalhaNaval::verificarEntrada(char tipo, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal)
{
    try
    {
        std::vector<char> tiposValidos = {'P', 'E', 'C', 'S'};
        if (std::find(tiposValidos.begin(), tiposValidos.end(), tipo) == tiposValidos.end())
        {
            throw ExcecaoTipodeBarcoInvalido();
        }

        if (linhaInicial < 1 or linhaInicial > 10 or colunaInicial < 1 or colunaInicial > 10 or linhaFinal < 1 or
            linhaFinal > 10 or colunaFinal < 1 or colunaFinal > 10)
        {
            throw std::out_of_range("Erro: Coordenadas fora dos limites do tabuleiro (1 a 10).");
        }

        if (linhaInicial != linhaFinal and colunaInicial != colunaFinal)
        {
            throw ExcecaoPosicionamentodeBarco();
        }

        if (!verificarTamanhodoBarco(tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal))
        {
            throw std::length_error("Erro: O tamanho do barco nao corresponde ao tipo informado.");
        }

        return true;
    }
    catch (ExcecaoTipodeBarcoInvalido &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    catch (ExcecaoPosicionamentodeBarco &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    catch (std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    catch (std::length_error &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Retorna o tamanho de um barco com base no tipo usando um switch-case básico.
 *
 * @param tipo Caractere representando o tipo de barco ('P', 'E', 'C', 'S').
 * @return Tamanho do barco. Retorna -1 se o tipo for inválido.
 */
int BatalhaNaval::getTamanhoBarco(char tipo)
{
    switch (tipo)
    {
    case 'P':
        return 5;
    case 'E':
        return 4;
    case 'C':
        return 3;
    case 'S':
        return 2;
    default:
        return -1; // Tipo inválido
    }
}

/**
 * @brief Lê e posiciona os barcos no tabuleiro do jogador, mantendo o controle sobre a quantidade de barcos específicos
 * já inseridos, evitando que este limite estoure. Além disso, as mensagens deixam claro como a inserção deve ser feita
 * e o sistema loop for itera até que os 10 barcos necessários tenham sido inseridos.
 *
 * A cada iteração, os dados inseridos passam por 2 sistemas de
 * controle de qualidade, analisando se eles podem ser introduzidos no vetor de barcos do respectivo jogador e caso não
 * possam, uma mensagem de erro aparece, o número de iterações é mantido e o loop continua.
 *
 * @param barcosJogador Vetor de pares de inteiros representando as posições dos barcos do jogador.
 * @param Jogador Referência para o jogador.
 */
void BatalhaNaval::lerBarcos(std::vector<std::pair<int, int>> &barcosJogador, Jogador &Jogador)
{
    std::map<char, int> countBarcos = {{'P', 0}, {'E', 0}, {'C', 0}, {'S', 0}};
    char tipo;
    int linhaInicial = 0, colunaInicial = 0, linhaFinal = 0, colunaFinal = 0;
    std::cout << Jogador.getApelido()
              << ", insira o tipo (apenas a letra inicial), as coordenadas iniciais e as coordenadas finais de seus "
                 "barcos, respectivamente."
              << std::endl;
    std::cout << "Os tipos de barco sao Porta-Avioes(P), Encouracados(E), Contratorpedeiros(C) e Submarinos(S), de "
                 "tamanhos 5, 4, 3, 2 e quantidades 1, 2, 3, 4, respectivamente."
              << std::endl;
    for (int barcosLidos = 0; barcosLidos < 10; barcosLidos++)
    {
        std::cin >> tipo >> linhaInicial >> colunaInicial >> linhaFinal >> colunaFinal;
        if (verificarEntrada(tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal) and
            quantidadeBarcosDisponiveis(countBarcos, tipo))
        {
            inserirBarcos(barcosJogador, tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            countBarcos[tipo]++;
        }
        else
        {
            std::cout << "Insira novamente com parametros validos, atente-se tambem a quantidade especifica de cada "
                         "tipo de barco."
                      << std::endl;
            barcosLidos--;
        }
    }
}

/**
 * @brief Verifica se a quantidade de barcos disponíveis para um tipo específico é suficiente e serve como auxiliar para
 * a função de lerBarcos, impedindo que o número de barcos supere o permitido.
 *
 * @param countBarcos Mapa que conta a quantidade de barcos disponíveis por tipo.
 * @param tipo Caractere representando o tipo de barco ('P', 'E', 'C', 'S').
 * @return `true` se houver barcos disponíveis, `false` caso contrário.
 */
bool BatalhaNaval::quantidadeBarcosDisponiveis(std::map<char, int> &countBarcos, char tipo)
{
    switch (tipo)
    {
    case 'P': // Porta-Aviões (1 permitido)
        return countBarcos['P'] < 1;
    case 'E': // Encouraçados (2 permitidos)
        return countBarcos['E'] < 2;
    case 'C': // Contratorpedeiros (3 permitidos)
        return countBarcos['C'] < 3;
    case 'S': // Submarinos (4 permitidos)
        return countBarcos['S'] < 4;
    default:
        return false; // Tipo inválido
    }
}

/**
 * @brief Verifica se o tamanho do barco corresponde ao tipo informado, e é uma fução auxiliar para
 * verificarEntrada() para garantir que o usuário não insira barcos com tamanhos além dos permitidos. O swap existe para
 * garantir que a Final seja sempre maior que a Incial, para garantir que não hajam números negativos.
 *
 * @param tipo Caractere representando o tipo de barco ('P', 'E', 'C', 'S').
 * @param linhaInicial Linha inicial do barco.
 * @param colunaInicial Coluna inicial do barco.
 * @param linhaFinal Linha final do barco.
 * @param colunaFinal Coluna final do barco.
 * @return `true` se o tamanho do barco for válido, `false` caso contrário.
 */
bool BatalhaNaval::verificarTamanhodoBarco(char tipo, int linhaInicial, int colunaInicial, int linhaFinal,
                                           int colunaFinal)
{
    int tamanhoBarco = getTamanhoBarco(tipo);
    if (tamanhoBarco == -1)
    {
        return false;
    }

    if (linhaInicial > linhaFinal)
    {
        std::swap(linhaInicial, linhaFinal);
    }
    if (colunaInicial > colunaFinal)
    {
        std::swap(colunaInicial, colunaFinal);
    }

    if (linhaInicial == linhaFinal)
    {
        return (colunaFinal - colunaInicial + 1) == tamanhoBarco;
    }
    else if (colunaInicial == colunaFinal)
    {
        return (linhaFinal - linhaInicial + 1) == tamanhoBarco;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Insere os barcos no vetor de barcos do jogador. Ele implementa o mesmo sistema de swap de Inicial e Final,
 * a inserção é feita percorrendo os limites superiores e inferiores obtidos na entrada do jogador, e introduz todas as
 * posições ocupadas por barcos no vector com o (-1), para garantir a correspondência entre o sistema do vector e a entrada.abort
 *
 * @param barcosJogador Vetor de pares de inteiros representando as posições dos barcos do jogador.
 * @param tipo Caractere representando o tipo de barco ('P', 'E', 'C', 'S').
 * @param linhaInicial Linha inicial do barco.
 * @param colunaInicial Coluna inicial do barco.
 * @param linhaFinal Linha final do barco.
 * @param colunaFinal Coluna final do barco.
 */
void BatalhaNaval::inserirBarcos(std::vector<std::pair<int, int>> &barcosJogador, char tipo, int linhaInicial,
                                 int colunaInicial, int linhaFinal, int colunaFinal)
{
    if (colunaInicial > colunaFinal)
    {
        std::swap(colunaInicial, colunaFinal);
    }
    if (linhaInicial > linhaFinal)
    {
        std::swap(linhaInicial, linhaFinal);
    }

    bool barcoHorizontal = (linhaInicial == linhaFinal);
    int tamanhoBarco = getTamanhoBarco(tipo);

    if (tamanhoBarco == -1)
    {
        return; // Tipo de barco inválido
    }

    if (barcoHorizontal)
    {
        for (int colunas = colunaInicial; colunas < colunaInicial + tamanhoBarco; ++colunas)
        {
            barcosJogador.push_back({linhaInicial - 1, colunas - 1});
        }
    }
    else
    {
        for (int linhas = linhaInicial; linhas < linhaInicial + tamanhoBarco; ++linhas)
        {
            barcosJogador.push_back({linhas - 1, colunaInicial - 1});
        }
    }
}

/**
 * @brief Exibe o tabuleiro do jogador no console, e recebe um parâmetro tabuleiro, diferentemente da classe Pai Jogos, porque
 * há 2 tabuleiros durante a execução do jogo, e precisamos printar ambos a cada rodada, por isso, foi necessário sobrecarregar o
 * método para usar o parâmetro em questão.
 *
 * @param tabuleiroJogador Matriz de caracteres representando o tabuleiro do jogador.
 */
void BatalhaNaval::mostrarTabuleiro(const std::vector<std::vector<char>> &tabuleiroJogador)
{
    for (int i = 0; i < static_cast<int>(tabuleiroJogador.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(tabuleiroJogador[i].size()); j++)
        {
            if (j > 0)
            {
                std::cout << "| " << tabuleiroJogador[i][j] << " ";
            }
            else
            {
                std::cout << " " << tabuleiroJogador[i][j] << " ";
            }
        }
        if (i < static_cast<int>(tabuleiroJogador.size()) - 1)
        {
            std::cout << gerarDivisoriaTabuleiro();
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Marca o tabuleiro com a jogada realizada, indicando acerto ('X') ou erro ('O'). A função 
 * usa da iteração no vetor de posições barcos do inimigo e a comparação com a jogada da respectiva rodada. Caso a jogada
 * seja igual a alguma das posições, é sinalizado o acerto.
 *
 * @param jogada Par de inteiros representando a jogada (linha, coluna).
 * @param turno Referência para a variável que controla o turno dos jogadores.
 * @param tabuleiroJogador Matriz de caracteres representando o tabuleiro do jogador.
 * @param barcosJogador Vetor de pares de inteiros representando as posições dos barcos do jogador.
 */
void BatalhaNaval::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno,
                                   std::vector<std::vector<char>> &tabuleiroJogador,
                                   std::vector<std::pair<int, int>> &barcosJogador)
{
    bool acerto = false;
    for (const auto &barcos : barcosJogador)
    {
        if (barcos == jogada)
        {
            tabuleiroJogador[jogada.first][jogada.second] = 'X'; // X indica acerto
            acerto = true;
            break;
        }
    }
    if (!acerto)
    {
        tabuleiroJogador[jogada.first][jogada.second] = 'O'; // O indica erro
    }
}