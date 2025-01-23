#include "Jogos.hpp"
#include "Jogador.hpp"

Jogos::~Jogos() {}

std::string Jogos::gerarDivisoriaTabuleiro(){
  std::string divisor;
  divisor.push_back('\n');

  if (!tabuleiro.empty()) {
    int numCols = tabuleiro[0].size();
    for (int i = 0; i < numCols * 4 - 1; i++) {
      divisor.push_back('-');
    }
  }

  divisor.push_back('\n');
  return divisor;
}

void Jogos::mostrarTabuleiro() {
  for (int i = 0; i < tabuleiro.size(); i++) {
    for (int j = 0; j < tabuleiro[i].size(); j++) {
      if (j > 0) {
        std::cout << "| " << tabuleiro[i][j] << " ";
      } else {
        std::cout << " " << tabuleiro[i][j] << " ";
      }
    }
    if (i < tabuleiro.size() - 1) {
      std::cout << gerarDivisoriaTabuleiro();
    }
  }
  std::cout << std::endl;
}

bool Jogos::sorteio() {
  srand(std::time(0));
  bool sorteio = std::rand() % 2;
  return sorteio;
}

void Jogos::Jogar(Jogador& Jogador1, Jogador& Jogador2) {
  bool turno = sorteio();
  bool jogoEmAndamento = true;
  std::vector<std::pair<int, int>> movimentosJogador1;
  std::vector<std::pair<int, int>> movimentosJogador2;

  if (turno)
    std::cout << "O jogador " << Jogador1.getApelido() << " começará o jogo!" << std::endl;
  else
    std::cout << "O jogador " << Jogador2.getApelido() << "começará o jogo!" << std::endl;

  while (1) {
    int linha, coluna, count = 0;

    if (turno) {  // a partir da 5 rodada checar vencedor
      std::cout << "Turno de " << Jogador1.getApelido() << "!" << std::endl
      << "Insira a posição que deseja fazer a jogada. O primeiro número para linha, e o segundo para coluna."
      << std::endl;

      do {
        while (!(std::cin >> linha >> coluna)) {
          std::cout << "Tipo de dado inválido. Por favor insira dois inteiros, separados por um espaço!" << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }

        if (checarJogada(linha - 1, coluna - 1)) {
          tabuleiro[linha][coluna] = 'X';
          movimentosJogador1.push_back(std::make_pair(linha, coluna));
          mostrarTabuleiro();
          
          if (count >= 5) {
            if (checarVencedor(movimentosJogador1)) {
              std::cout << Jogador1.getApelido() << "ganhou o Jogo!"
                        << std::endl;
              jogoEmAndamento = false;
            }
          }
        }
    
      } while (jogoEmAndamento);
      turno = true;
    }
    else {
      std::cout << "Turno de " << Jogador2.getApelido() << "!" << std::endl;

      do {
        while (!(std::cin >> linha >> coluna)) {
          std::cout << "Tipo de dado inválido. Por favor insira dois inteiros, separados por um espaço!" << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }

        if (checarJogada(linha, coluna)) {
          tabuleiro[linha][coluna] = 'O';
          movimentosJogador2.push_back(std::make_pair(linha, coluna));
          mostrarTabuleiro();

          if (count >= 5) {
            if (checarVencedor(movimentosJogador2)) {
              std::cout << Jogador2.getApelido() << "ganhou o Jogo!"
                        << std::endl;
              jogoEmAndamento = false;
            }
          }
        }
      } while (jogoEmAndamento);
      turno = true;
    }
  }
}

bool Jogos::checarJogada(int linha, int coluna) {
  if (linha >= 0 and linha <= tabuleiro.size() and
      coluna >= 0 and coluna <= tabuleiro[0].size()) {

    if (tabuleiro[linha][coluna] != ' '){
      std::cout << "ERRO, Jogada inválida! A posição escolhida já foi ocupada!" << std::endl;
      return false;
    }
    else
      return  true;
  }
  else{
    std::cout << "ERRO, Jogada inválida! A posição escolhida é além dos limites do tabuleiro!" << std::endl;
    return false;
  }
}
// remover dependencies do makefile