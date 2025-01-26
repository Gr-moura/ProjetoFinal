#include <CentralDeJogos.hpp>

/*
    O construtor carrega os dados armazenados no arquivo "DadosJogadoresCadastrados.txt"
    e incializa a lista de jogadores respectivamente, cada um com suas próprias estatísticas.
*/
CentralDeJogos::CentralDeJogos() {
    std::ifstream DadosJogadoresCadastrados("data/DadosJogadoresCadastrados.txt");
    if (!DadosJogadoresCadastrados.is_open()) {
        std::cerr << "ERRO! Nao foi possivel abrir o arquivo de dados. Os dados não foram carregados." << std::endl;
        return;
    }

    std::string nome, apelido;
    int vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDaVelha;
    int vitoriasLig4, derrotasLig4, empatesLig4;
    int vitoriasReversi, derrotasReversi, empatesReversi;
    // int vitoriasJogo3, derrotasJogo3, empatesJogo3;

    while (DadosJogadoresCadastrados >> nome >> apelido 
           >> vitoriasJogoDaVelha >> derrotasJogoDaVelha >> empatesJogoDaVelha 
           >> vitoriasLig4 >> derrotasLig4 >> empatesLig4
           >> vitoriasReversi >> derrotasReversi >> empatesReversi) {

        Jogador jogador(apelido, nome,
        vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDaVelha,
        vitoriasLig4, derrotasLig4, empatesLig4,
        vitoriasReversi, derrotasReversi, empatesReversi);
        jogadoresCadastrados.push_back(jogador);
    }

    DadosJogadoresCadastrados.close();
}
 

/*
    O destrutor escreve no arquivo os jogadores cadastrados ao final da execução, atualizando as informações dos jogadores
    de acordo com as opções escolhidas pelo usuário;
*/
CentralDeJogos::~CentralDeJogos() {
    std::ofstream DadosJogadoresCadastrados("../data/DadosJogadoresCadastrados.txt");
    if (!DadosJogadoresCadastrados.is_open()) {
        std::cerr << "ERRO! Nao foi possivel abrir o arquivo de dados. Os dados não foram carregados." << std::endl;
        return;
    }

    for (Jogador &jogador : jogadoresCadastrados) {
        DadosJogadoresCadastrados << jogador.getNome() << " " << jogador.getApelido() << " " 
        << jogador.getVitorias("VELHA") << " " << jogador.getDerrotas("VELHA") << " " << jogador.getEmpates("VELHA") << " "
        << jogador.getVitorias("LIG4") << " " << jogador.getDerrotas("LIG4") << " " << jogador.getEmpates("LIG4") << " "
        << jogador.getVitorias("REVERSI") << " " << jogador.getDerrotas("REVERSI") << " " << jogador.getEmpates("REVERSI") << std::endl;
    }

    DadosJogadoresCadastrados.close();  
}

/*
    validarEntrada() é um método que avalia se a entrada desejada é coerente, e caso seja, retorna a entrada.
    Se ela não for coerente, será feito um looping até que a entrada correta seja inserida;
*/
std::string CentralDeJogos::validarEntrada() {
    std::string entrada;
    while (not (std::cin >> entrada)) {
        std::cout << "ERRO, tipo de dado invalido. Por favor insira uma string." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    return entrada;
}

/*
    buscarJogador() é um método que verifica se um jogador já existe no sistema da Central de Jogos, caso exista
    o método retorna verdadeiro;
*/
bool CentralDeJogos::buscarJogador(std::string &apelido) {
    for (Jogador &jogador : jogadoresCadastrados) {
        if (jogador.getApelido() == apelido) 
            return true;
    }
    return false;
}

/*
    cadastrarJogador() é um método que cadastra o jogador no sistema da central de jogos, incializando com seu nome e apelido;
*/
void CentralDeJogos::cadastrarJogador(std::string &apelido, std::string &nome) {
    if (buscarJogador(apelido))
        std::cout << "ERRO: o jogador já existe no sistema!" << std::endl;
    else {
        Jogador novoJogador(apelido, nome);
        jogadoresCadastrados.push_back(novoJogador);
        std::cout << "Jogador " << apelido << " cadastrado com sucesso!" << std::endl;
    }
}

/*
    removerJogador() é um método que remove o jogador no sistema da central de jogos;
*/
void CentralDeJogos::removerJogador(std::string &apelido) {
    auto posicaoNoVetor = std::find_if(jogadoresCadastrados.begin(), jogadoresCadastrados.end(), 
                           [&apelido](const Jogador& jogador) {
                               return jogador.getApelido() == apelido;
                           });

    if (posicaoNoVetor != jogadoresCadastrados.end()) {
        jogadoresCadastrados.erase(posicaoNoVetor);
        std::cout << "Jogador  " << apelido << " removido com sucesso!" << std::endl;
    }
    else {
        std::cout << "ERRO: Jogador inexistente" << std::endl;
    }
}


/*
    ordenarJogadores() é um método que ordena o vetor de jogadores cadastrados com base na ordem alfabética de seus apelidos
*/
void CentralDeJogos::ordenarJogadores() {
    std::sort(jogadoresCadastrados.begin(), jogadoresCadastrados.end(), 
              [](const Jogador& a, const Jogador& b) {
                  return a.getApelido() < b.getApelido();
              });
}


/*
    listaJogadores() é um método que lista todos os jogadores cadastrados na lista de jogadores cadastrados no sistema; 
*/
void CentralDeJogos::listarJogadores() {
    ordenarJogadores();
    for (Jogador &jogador : jogadoresCadastrados) {
        std::cout << jogador.getApelido() << " " << jogador.getNome() << std::endl;
        jogador.mostrarEstatisticas("VELHA");
        jogador.mostrarEstatisticas("LIG4");
        jogador.mostrarEstatisticas("REVERSI");
        std::cout << std::endl;
    }
    return;
}

/*
    executarPartida() é o método que gerencia a execução de partidas dos jogos, lendo uma entrada do usuário,
    com o respectivo jogo e jogadores e executa a partida, registrando a partida nos jogadores selecionados;
*/
void CentralDeJogos::executarPartida() {
    std::string jogoEscolhido = validarEntrada();

    std::cout << "Digite o apelido do jogador 1: ";
    std::string apelidoJogador_01 = validarEntrada();

    std::cout << "Digite o apelido do jogador 2: ";
    std::string apelidoJogador_02 = validarEntrada();

    auto posicaoJogador_01 = std::find_if(jogadoresCadastrados.begin(), jogadoresCadastrados.end(), 
                           [&apelidoJogador_01](const Jogador& jogador) {
                               return jogador.getApelido() == apelidoJogador_01;
                           });

    auto posicaoJogador_02 = std::find_if(jogadoresCadastrados.begin(), jogadoresCadastrados.end(), 
                           [&apelidoJogador_02](const Jogador& jogador) {
                               return jogador.getApelido() == apelidoJogador_02;
                           });

    if (posicaoJogador_01 == jogadoresCadastrados.end() or posicaoJogador_02 == jogadoresCadastrados.end()) {
        std::cout << "ERRO: Jogador inexistente!" << std::endl;
        return;
    }

    if (jogoEscolhido == "R") {
        reversi.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else if (jogoEscolhido == "L") {
        lig4.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else if (jogoEscolhido == "V") {
        std::cout << "entrou";
        velha.Jogar(*posicaoJogador_01, *posicaoJogador_02);
    }
    else { 
        std::cout << "ERRO: Insira o formato adequado [R|L|V], exemplo para jogar reversi: R" << std::endl;
    }
}
