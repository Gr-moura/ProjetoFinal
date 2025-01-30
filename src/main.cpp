#include <CentralDeJogos.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

std::string validarEntrada()
{
    std::string entrada;
    while (not(std::cin >> entrada))
    {
        std::cout << "ERRO, tipo de dado invalido. Por favor insira uma string." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return entrada;
}

void exibirMenu()
{
    std::cout << "===== MENU =====" << std::endl;
    std::cout << "CJ - Cadastrar Jogador" << std::endl;
    std::cout << "RJ - Remover Jogador" << std::endl;
    std::cout << "LJ - Listar Jogadores" << std::endl;
    std::cout << "EP - Executar Partida" << std::endl;
    std::cout << "FS - Finalizar Sistema" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "Digite sua opcao: ";
    return;
}


/**
 * @file main.cpp
 * @brief Função principal do sistema de gerenciamento de jogos.
 *
 * Este arquivo contém a função `main`, que é o ponto de entrada do programa. A função gerencia
 * a interação com o usuário, exibindo um menu de opções e executando as funcionalidades
 * correspondentes, como cadastrar jogadores, remover jogadores, listar jogadores e executar partidas.
 *
 * ## Fluxo do Programa:
 * 1. Exibe um menu de opções para o usuário.
 * 2. Lê a entrada do usuário e valida o comando.
 * 3. Executa a funcionalidade correspondente ao comando:
 *    - **CJ**: Cadastra um novo jogador.
 *    - **RJ**: Remove um jogador existente.
 *    - **LJ**: Lista todos os jogadores cadastrados.
 *    - **EP**: Executa uma partida em um dos jogos disponíveis.
 *    - **FS**: Finaliza o sistema.
 * 4. Repete o processo até que o usuário escolha a opção de finalizar o sistema.
 *
 * ## Dependências:
 * - Utiliza a classe `CentralDeJogos` para gerenciar jogadores e partidas.
 * - Utiliza funções auxiliares como `validarEntrada` e `exibirMenu` para interação com o usuário.
 *
 * @see CentralDeJogos
 */
int main()
{
    CentralDeJogos central;
    std::string comando;

    do
    {
        exibirMenu();
        comando = validarEntrada();

        if (comando == "CJ")
        {
            std::string apelido, nome;
            std::cout << "Digite o apelido do jogador: ";
            std::cin >> apelido;
            std::cout << "Digite o nome do jogador: ";
            std::getchar();
            std::getline(std::cin, nome);
            central.cadastrarJogador(apelido, nome);
        }
        else if (comando == "RJ")
        {
            std::string apelido;
            std::cout << "Digite o apelido do jogador a ser removido: ";
            std::cin >> apelido;
            central.removerJogador(apelido);
        }
        else if (comando == "LJ")
        {
            std::cout << "Jogadores cadastrados:" << std::endl;
            central.listarJogadores();
        }
        else if (comando == "EP")
        {
            std::cout << "Digite o nome do jogo que deseja jogar." << std::endl;
            std::cout << "Jogo Da Velha:           (V)" << std::endl;
            std::cout << "Jogo Da Velha contra IA: (A)" << std::endl;
            std::cout << "Ligue 4:                 (L)" << std::endl;
            std::cout << "Reversi:                 (R)" << std::endl;
            std::cout << "Batalha Naval:           (B)" << std::endl;
            central.executarPartida();
        }
        else if (comando == "FS")
        {
            std::cout << "Finalizando o sistema..." << std::endl;
            break;
        }
        else
        {
            std::cout << "Comando inválido! Tente novamente." << std::endl;
        }
    } while (comando != "FS");

    return 0;
}