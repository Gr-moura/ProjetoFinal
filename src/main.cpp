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