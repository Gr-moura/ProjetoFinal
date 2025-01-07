#include "Jogos.hpp"

#include "Jogador.hpp"

Jogos::~Jogos() {}

std::string Jogos::gerarDivisoriaTabuleiro(
    std::vector<std::vector<char>>& tabuleiro) {
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

void Jogos::mostrarTabuleiro(std::vector<std::vector<char>>& tabuleiro) {
  for (int i = 0; i < tabuleiro.size(); i++) {
    for (int j = 0; j < tabuleiro[i].size(); j++) {
      if (j > 0) {
        std::cout << "| " << tabuleiro[i][j] << " ";
      } else {
        std::cout << " " << tabuleiro[i][j] << " ";
      }
    }
    if (i < tabuleiro.size() - 1) {
      std::cout << gerarDivisoriaTabuleiro(tabuleiro);
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
  std::vector<std::pair<int, int>> movimentosJogador1;
  std::vector<std::pair<int, int>> movimentosJogador2;

  if (turno) {
    std::cout << "O jogador " << Jogador1.getApelido() << " comecara o jogo!"
              << std::endl;
  } else {
    std::cout << "O jogador 2 comecara o jogo!" << std::endl;
  }

  while (1) {
    int linha, coluna, count = 0;
    if (turno) {  // a partir da 5 rodada checar vencedor
      std::cout << "Turno de " << Jogador1.getApelido() << std::endl;
      while (1) {
        std::cin >> linha >> coluna;
        if (checarJogada(linha, coluna, tabuleiro)) {
          tabuleiro[linha][coluna] = 'X';
          movimentosJogador1.push_back(std::make_pair(linha, coluna));
          mostrarTabuleiro(tabuleiro);
          if (count >= 5) {
            if (checarVencedor(movimentosJogador1, tabuleiro.size())) {
              std::cout << Jogador1.getApelido() << "ganhou o Jogo!"
                        << std::endl;
              break;
            }
          }
        } else {
          std::cout << "ERRO: Jogada Inválida." << std::endl;
        }
      }
      turno = true;
    } else {
      std::cout << "Turno de " << Jogador2.getApelido() << std::endl;
      while (1) {
        std::cin >> linha >> coluna;
        if (checarJogada(linha, coluna, tabuleiro)) {
          tabuleiro[linha][coluna] = 'O';
          movimentosJogador2.push_back(std::make_pair(linha, coluna));
          mostrarTabuleiro(tabuleiro);
          if (count >= 5) {
            if (checarVencedor(movimentosJogador2, tabuleiro.size())) {
              std::cout << Jogador2.getApelido() << "ganhou o Jogo!"
                        << std::endl;
              break;
            }
          }
        } else {
          std::cout << "ERRO: Jogada Inválida." << std::endl;
        }
      }
      turno = true;
    }
  }
}

bool Jogos::checarJogada(int linha, int coluna,
                         std::vector<std::vector<char>>& tabuleiro) {
  if (!tabuleiro.empty()) {
    if (tabuleiro[linha][coluna] != ' ') {
      return false;
    }
  }
  return true;
}
// remover dependencies do makefile