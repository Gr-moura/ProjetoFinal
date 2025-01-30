#include "BatalhaNaval.hpp"

BatalhaNaval::BatalhaNaval()
{
    tabuleiro.resize(10, std::vector<char>(10, '~'));
}

void BatalhaNaval::anunciarInicioPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno)
{
    if (turno)
    {
        std::cout << "Bem Vindo ao Batalha Naval! O jogador " << Jogador1.getApelido() << " comecara a partida!"
                  << std::endl;
    }
    else
    {
        std::cout << "Bem Vindo ao Batalha Naval! O jogador " << Jogador2.getApelido() << " comecara a partida!"
                  << std::endl;
    }
}

void BatalhaNaval::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno,
                                   std::vector<std::vector<char>> &tabuleiroJogador,
                                   std::vector<std::pair<int, int>> &barcosJogador)
{
    for (const auto &barcos : barcosJogador)
    {
        if (barcos == jogada)
        {
            tabuleiroJogador[jogada.first][jogada.second] = 'X'; // X indica acerto
        }
        else
        {
            tabuleiroJogador[jogada.first][jogada.second] = 'O';
        }
    }
}

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

bool BatalhaNaval::quantidadeBarcosDisponiveis(std::map<char, int> &countBarcos, char tipo)
{
    switch (tipo)
    {
    case 'P':
        if (!countBarcos['P'])
        {
            return true;
        }
    case 'E':
        if (countBarcos['E'] < 2)
        {
            return true;
        }
    case 'C':
        if (countBarcos['C'] < 3)
        {
            return true;
        }
    case 'S':
        if (countBarcos['S'] < 4)
        {
            return true;
        }
    }

    return false;
}

void BatalhaNaval::inserirBarcos(std::vector<std::pair<int, int>> &barcosJogador, char tipo, int linhaInicial, int colunaInicial,
                   int linhaFinal, int colunaFinal)
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

    int tamanhoBarco;
    switch (tipo)
    {
    case 'P':
        tamanhoBarco = 5;
        break;
    case 'E':
        tamanhoBarco = 4;
        break;
    case 'C':
        tamanhoBarco = 3;
        break;
    case 'S':
        tamanhoBarco = 2;
        break;
    }

    if (barcoHorizontal)
    {
        for (int colunas = colunaInicial; colunas < colunaInicial + tamanhoBarco; ++colunas)
        {
            barcosJogador.push_back({linhaInicial, colunas});
        }
    }
    else
    {
        for (int linhas = linhaInicial; linhas < linhaInicial + tamanhoBarco; ++linhas)
        {
            barcosJogador.push_back({linhas, colunaInicial});
        }
    }
}

bool BatalhaNaval::checarVencedor(std::vector<std::pair<int, int>> &jogadasAtacante,
                                  std::vector<std::pair<int, int>> &barcosOponente, Jogador &vencedor,
                                  Jogador &perdedor)
{
    for (const auto &posicaoBarco : barcosOponente)
    {
        if (std::find(jogadasAtacante.begin(), jogadasAtacante.end(), posicaoBarco) == jogadasAtacante.end())
        {
            return false;
        }
    }
    return true;
}

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
                 "tamanhos 5, 4, 3 ,2 e quantidades 1, 2, 3, 4, respectivamente."
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

bool BatalhaNaval::verificarTamanhodoBarco(char tipo, int linhaInicial, int colunaInicial, int linhaFinal,
                                           int colunaFinal)
{
    switch (tipo)
    {
    case 'P':
        if (fabs(linhaInicial - linhaFinal + colunaInicial - colunaFinal) != 4)
        {
            return false;
        }
    case 'E':
        if (fabs(linhaInicial - linhaFinal + colunaInicial - colunaFinal) != 3)
        {
            return false;
        }
    case 'C':
        if (fabs(linhaInicial - linhaFinal + colunaInicial - colunaFinal) != 2)
        {
            return false;
        }
    case 'S':
        if (fabs(linhaInicial - linhaFinal + colunaInicial - colunaFinal) != 1)
        {
            return false;
        }
    }
    return true;
}

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
            throw std::out_of_range("Erro: Fora dos limites do tabuleiro");
        }

        if (linhaInicial != linhaFinal or colunaInicial != colunaFinal)
        {
            throw ExcecaoPosicionamentodeBarco();
        }

        if (!verificarTamanhodoBarco(tipo, linhaInicial, colunaInicial, linhaFinal, colunaFinal))
        {
            throw std::length_error("O barco esta com tamanho incorreto");
        }
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

    return true;
}

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
    std::cout << "\033[2J\033[1;1H";
    lerBarcos(barcosJogador2, Jogador2);
    std::cout << "\033[2J\033[1;1H";

    while (jogoEmAndamento)
    {
        contadorTurnos++;
        if (turno)
        {
            anunciarTurnoJogador(Jogador1); // jogadorX no reversi
            jogada = lerJogada(tabuleiroJogadasJogador1);

            marcarTabuleiro(jogada, turno, tabuleiroJogadasJogador1, movimentosJogador1);
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
            anunciarTurnoJogador(Jogador2); // jogadorO no reversi
            jogada = lerJogada(tabuleiroJogadasJogador2);

            marcarTabuleiro(jogada, turno, tabuleiroJogadasJogador2, movimentosJogador2);
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

std::pair<int, int> BatalhaNaval::lerJogada(std::vector<std::vector<char>> &tabuleiroJogador)
{
    std::cout << "Insira a posicao que atacar seu adversario, linha e coluna respectivamente." << std::endl;
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

        if (Jogos::checarPosicaoValida(linha - 1, coluna - 1))
        {
            if (tabuleiro[linha - 1][coluna - 1] == '~')
            {
                std::pair<int, int> jogada = {linha - 1, coluna - 1};
                entradaValida = true;
                return jogada;
            }
            else
            {
                std::cout << "ERRO!  A posicao escolhida ja foi atacada!. Insira uma posicao valida!" << std::endl;
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