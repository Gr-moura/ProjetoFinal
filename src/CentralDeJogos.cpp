#include "CentralDeJogos.hpp"

/**
 * @brief Construtor da classe CentralDeJogos.
 *
 * Este construtor é responsável por inicializar a classe CentralDeJogos, carregando os dados dos jogadores
 * cadastrados a partir de um arquivo de texto. O arquivo deve estar localizado no caminho especificado
 * (`data/DadosJogadoresCadastrados.txt`) e deve seguir um formato específico para que os dados sejam lidos
 * corretamente.
 *
 * O arquivo de dados deve conter, para cada jogador, as seguintes informações em ordem:
 * 1. Nome do jogador (uma linha completa).
 * 2. Apelido do jogador.
 * 3. Número de vitórias no Jogo da Velha.
 * 4. Número de derrotas no Jogo da Velha.
 * 5. Número de empates no Jogo da Velha.
 * 6. Número de vitórias no Lig4.
 * 7. Número de derrotas no Lig4.
 * 8. Número de empates no Lig4.
 * 9. Número de vitórias no Reversi.
 * 10. Número de derrotas no Reversi.
 * 11. Número de empates no Reversi.
 * 12. Número de vitórias no Batalha Naval.
 * 13. Número de derrotas no Batalha Naval.
 * 14. Número de empates no Batalha Naval.
 *
 * Caso o arquivo não exista ou esteja corrompido, o construtor exibirá uma mensagem de erro e prosseguirá
 * sem carregar os dados, iniciando o sistema com uma lista vazia de jogadores.
 *
 * @note O arquivo de dados deve estar no formato correto. Caso contrário, o sistema pode falhar ao ler os dados
 *       e exibir uma mensagem de erro indicando que o arquivo está corrompido.
 *
 * @warning Se o arquivo não puder ser aberto, o sistema exibirá uma mensagem de erro e não carregará os dados.
 *          Isso pode ocorrer se o arquivo não existir ou se houver problemas de permissão.
 */
CentralDeJogos::CentralDeJogos()
{
    std::ifstream DadosJogadoresCadastrados("data/DadosJogadoresCadastrados.txt");
    if (!DadosJogadoresCadastrados.is_open())
    {
        std::cerr << "ERRO! Nao foi possivel abrir o arquivo de dados. Os dados nao foram carregados." << std::endl;
        // É obrigatório que o sistema tenha um jogador do tipo AI;
        Jogador AI("AI", "AI");
        jogadoresCadastrados.push_back(AI);
        return;
    }

    std::string nome, apelido;
    int vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDaVelha;
    int vitoriasLig4, derrotasLig4, empatesLig4;
    int vitoriasReversi, derrotasReversi, empatesReversi;
    int vitoriasBatalhaNaval, derrotasBatalhaNaval, empatesBatalhaNaval;

    while (std::getline(DadosJogadoresCadastrados, nome))
    {
        if (!(DadosJogadoresCadastrados >> apelido >> vitoriasJogoDaVelha >> derrotasJogoDaVelha >>
              empatesJogoDaVelha >> vitoriasLig4 >> derrotasLig4 >> empatesLig4 >> vitoriasReversi >> derrotasReversi >>
              empatesReversi >> vitoriasBatalhaNaval >> derrotasBatalhaNaval >> empatesBatalhaNaval))
        {
            std::cerr << "ERRO: arquivo de save corrompido, iniciando com o save zerado. " << nome << std::endl;
            break;
        }

        DadosJogadoresCadastrados.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Jogador jogador(apelido, nome, vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDaVelha, vitoriasLig4,
                        derrotasLig4, empatesLig4, vitoriasReversi, derrotasReversi, empatesReversi,
                        vitoriasBatalhaNaval, derrotasBatalhaNaval, empatesBatalhaNaval);

        jogadoresCadastrados.push_back(jogador);
    }
    auto posicaoAI = std::find_if(jogadoresCadastrados.begin(), jogadoresCadastrados.end(),
                                            [&](const Jogador &jogador) { return jogador.getApelido() == "AI"; });
    if (posicaoAI == jogadoresCadastrados.end())
    {
        Jogador AI("AI", "AI");
        jogadoresCadastrados.push_back(AI);
    }

    DadosJogadoresCadastrados.close();
}

/**
 * @brief Destrutor da classe CentralDeJogos.
 *
 * Este destrutor é responsável por salvar os dados dos jogadores cadastrados em um arquivo de texto
 * (`data/DadosJogadoresCadastrados.txt`) antes de liberar a memória alocada para a classe. O arquivo é
 * sobrescrito com as informações atualizadas dos jogadores, incluindo nome, apelido e estatísticas de
 * cada jogo (vitórias, derrotas e empates).
 *
 * O formato do arquivo é o seguinte para cada jogador:
 * 1. Nome do jogador (uma linha completa).
 * 2. Apelido do jogador, seguido pelas estatísticas de cada jogo na ordem:
 *    - Vitórias no Jogo da Velha.
 *    - Derrotas no Jogo da Velha.
 *    - Empates no Jogo da Velha.
 *    - Vitórias no Lig4.
 *    - Derrotas no Lig4.
 *    - Empates no Lig4.
 *    - Vitórias no Reversi.
 *    - Derrotas no Reversi.
 *    - Empates no Reversi.
 *    - Vitórias no Batalha Naval.
 *    - Derrotas no Batalha Naval.
 *    - Empates no Batalha Naval.
 *
 * Caso o arquivo não possa ser aberto para escrita, o destrutor exibirá uma mensagem de erro e não
 * salvará os dados. Isso pode ocorrer se o diretório `data` não existir ou se houver problemas de
 * permissão.
 *
 * @note O arquivo é sobrescrito a cada execução do programa, garantindo que os dados estejam sempre
 *       atualizados.
 *
 * @warning Se o arquivo não puder ser aberto, os dados não serão salvos, e uma mensagem de erro será
 *          exibida. Isso pode resultar na perda de informações se o problema não for corrigido.
 */
CentralDeJogos::~CentralDeJogos()
{
    std::ofstream DadosJogadoresCadastrados("data/DadosJogadoresCadastrados.txt");
    if (!DadosJogadoresCadastrados.is_open())
    {
        std::cerr << "ERRO! Nao foi possivel abrir o arquivo de dados. Os dados nao foram salvos." << std::endl;
        return;
    }

    for (Jogador &jogador : jogadoresCadastrados)
    {
        DadosJogadoresCadastrados << jogador.getNome() << std::endl
                                  << jogador.getApelido() << " " << jogador.getVitorias("VELHA") << " "
                                  << jogador.getDerrotas("VELHA") << " " << jogador.getEmpates("VELHA") << " "
                                  << jogador.getVitorias("LIG4") << " " << jogador.getDerrotas("LIG4") << " "
                                  << jogador.getEmpates("LIG4") << " " << jogador.getVitorias("REVERSI") << " "
                                  << jogador.getDerrotas("REVERSI") << " " << jogador.getEmpates("REVERSI") << " "
                                  << jogador.getVitorias("BATALHANAVAL") << " " << jogador.getDerrotas("BATALHANAVAL")
                                  << " " << jogador.getEmpates("BATALHANAVAL") << std::endl;
        ;
    }

    DadosJogadoresCadastrados.close();
}

/**
 * @brief Valida a entrada do usuário, garantindo que seja uma string.
 *
 * Este método solicita uma entrada do usuário e verifica se o tipo de dado fornecido é uma string.
 * Caso a entrada seja inválida, uma mensagem de erro é exibida, e o usuário é solicitado a tentar novamente.
 *
 * @return std::string A entrada válida fornecida pelo usuário.
 */
std::string CentralDeJogos::validarEntrada()
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

/**
 * @brief Busca um jogador pelo apelido na lista de jogadores cadastrados.
 *
 * Este método percorre a lista de jogadores cadastrados e verifica se o apelido fornecido corresponde
 * ao apelido de algum jogador na lista.
 *
 * @param apelido O apelido do jogador a ser buscado.
 * @return bool True se o jogador for encontrado, False caso contrário.
 */
bool CentralDeJogos::buscarJogador(std::string &apelido)
{
    for (Jogador &jogador : jogadoresCadastrados)
    {
        if (jogador.getApelido() == apelido)
            return true;
    }
    return false;
}

/**
 * @brief Cadastra um novo jogador no sistema.
 *
 * Este método verifica se o jogador já está cadastrado (pelo apelido) e, caso não esteja,
 * cria um novo jogador e o adiciona à lista de jogadores cadastrados.
 *
 * @param apelido O apelido do jogador a ser cadastrado.
 * @param nome O nome do jogador a ser cadastrado.
 */
void CentralDeJogos::cadastrarJogador(std::string &apelido, std::string &nome)
{
    if (buscarJogador(apelido))
        std::cout << "ERRO: o jogador ja existe no sistema!" << std::endl;
    else
    {
        Jogador novoJogador(apelido, nome);
        jogadoresCadastrados.push_back(novoJogador);
        std::cout << "Jogador " << apelido << " cadastrado com sucesso!" << std::endl;
    }
}

/**
 * @brief Remove um jogador da lista de jogadores cadastrados.
 *
 * Este método busca um jogador pelo apelido e, caso encontrado, o remove da lista de jogadores cadastrados.
 * Se o jogador não for encontrado, exibe uma mensagem de erro.
 *
 * @param apelido O apelido do jogador a ser removido.
 */
void CentralDeJogos::removerJogador(std::string &apelido)
{
    auto posicaoNoVetor = std::find_if(jogadoresCadastrados.begin(), jogadoresCadastrados.end(),
                                       [&apelido](const Jogador &jogador) { return jogador.getApelido() == apelido; });

    if (posicaoNoVetor != jogadoresCadastrados.end())
    {
        jogadoresCadastrados.erase(posicaoNoVetor);
        std::cout << "Jogador  " << apelido << " removido com sucesso!" << std::endl;
    }
    else
    {
        std::cout << "ERRO: Jogador inexistente" << std::endl;
    }
}

/**
 * @brief Ordena a lista de jogadores cadastrados pelo apelido.
 *
 * Este método utiliza a função `std::sort` para ordenar a lista de jogadores em ordem alfabética
 * com base no apelido de cada jogador.
 */
void CentralDeJogos::ordenarJogadores()
{
    std::sort(jogadoresCadastrados.begin(), jogadoresCadastrados.end(),
              [](const Jogador &a, const Jogador &b) { return a.getApelido() < b.getApelido(); });
}

/**
 * @brief Lista todos os jogadores cadastrados e suas estatísticas.
 *
 * Este método ordena a lista de jogadores pelo apelido e, em seguida, exibe o apelido, o nome e as
 * estatísticas de cada jogador para todos os jogos disponíveis (Jogo da Velha, Lig4, Reversi e Batalha Naval).
 */
void CentralDeJogos::listarJogadores()
{
    ordenarJogadores();
    for (Jogador &jogador : jogadoresCadastrados)
    {
        std::cout << jogador.getApelido() << " " << jogador.getNome() << std::endl;
        jogador.mostrarEstatisticas("VELHA");
        jogador.mostrarEstatisticas("LIG4");
        jogador.mostrarEstatisticas("REVERSI");
        jogador.mostrarEstatisticas("BATALHANAVAL");
        std::cout << std::endl;
    }
    return;
}

/**
 * @brief Executa uma partida em um dos jogos disponíveis.
 *
 * Este método permite que dois jogadores (ou um jogador e a inteligência artificial) disputem uma partida
 * em um dos jogos disponíveis: Reversi (R), Lig4 (L), Jogo da Velha (V), Batalha Naval (B) ou Jogo da Velha
 * contra a AI (A).
 *
 * O método solicita o jogo escolhido e os apelidos dos jogadores. Caso o jogo escolhido seja contra a AI,
 * o segundo jogador é automaticamente definido como "AI". Se algum jogador não for encontrado, uma mensagem
 * de erro é exibida.
 */
void CentralDeJogos::executarPartida()
{
    std::string jogoEscolhido = validarEntrada();

    std::cout << "\033[2J\033[1;1H";

    std::cout << "Digite o apelido do jogador 1: ";
    std::string apelidoJogador_01 = validarEntrada();

    auto posicaoJogador_01 = std::find_if(
        jogadoresCadastrados.begin(), jogadoresCadastrados.end(),
        [&apelidoJogador_01](const Jogador &jogador) { return jogador.getApelido() == apelidoJogador_01; });

    if (jogoEscolhido == "A")
    {
        auto posicaoJogador_02 = std::find_if(jogadoresCadastrados.begin(), jogadoresCadastrados.end(),
                                              [&](const Jogador &jogador) { return jogador.getApelido() == "AI"; });

        Ai.Jogar(*posicaoJogador_01, *posicaoJogador_02);
        return;
    }

    std::cout << "Digite o apelido do jogador 2: ";
    std::string apelidoJogador_02 = validarEntrada();

    auto posicaoJogador_02 = std::find_if(
        jogadoresCadastrados.begin(), jogadoresCadastrados.end(),
        [&apelidoJogador_02](const Jogador &jogador) { return jogador.getApelido() == apelidoJogador_02; });

    if (posicaoJogador_01 == jogadoresCadastrados.end() or posicaoJogador_02 == jogadoresCadastrados.end())
    {
        std::cout << "ERRO: Jogador inexistente!" << std::endl;
        return;
    }

    if (jogoEscolhido == "R")
    {
        reversi.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else if (jogoEscolhido == "L")
    {
        lig4.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else if (jogoEscolhido == "V")
    {
        velha.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else if (jogoEscolhido == "B")
    {
        batalha.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else
    {
        std::cout << "ERRO: Insira o formato adequado [R|L|V|B|A], exemplo para jogar reversi: R" << std::endl;
    }
}
