#include "Lig4.hpp"

Lig4::Lig4(int tamanhoTabuleiro) {
  tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro + 1, ' '));
}

Lig4::Lig4(){
  tabuleiro.resize(7, std::vector<char>(6, ' '));
}

void Lig4::inciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) {
  if (turno) {
    std::cout << "Bem Vindo ao Ligue 4! O jogador " <<
    Jogador1.getApelido() << " comecara a partida!" <<
    std::endl;
  }
  else {
    std::cout << "Bem Vindo ao Ligue 4! O jogador " <<
    Jogador2.getApelido() << "comecara a partida!" <<
    std::endl;
  }
}

std::pair<int, int> Lig4::lerJogada() {
  std::cout << "Insira a coluna que deseja insirir a peca no tabuleiro." <<
  std::endl;
  int coluna;
  bool entradaValida = false;
  while (not (entradaValida)){
    while (not (std::cin >> coluna)) {
      std::cout << "ERRO, tipo de dado invalido. Por favor um inteiro." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }

    if (checarPosicaoValida(0, coluna - 1)) {
      for (int i = static_cast<int>(tabuleiro.size()) - 1; i >= 0; i--) {
        if (tabuleiro[i][coluna-1] != ' ')
          continue;
        else {
          std::pair<int, int> jogada = {i, coluna - 1};
          entradaValida = true;
          return jogada;
        }
      }
      std::cout << "ERRO! A coluna escolhida esta cheia!"
      << std::endl;
    }
    else {
      std::cout << "ERRO! A posicao escolhida nao esta dentro dos limites do tabuleiro. Escolha uma opcao valida!"
      << std::endl;
    }
      
  }    
}

bool Lig4::checarDiagonal(std::vector<std::pair<int, int>> &jogadas) {
  int numeroLinhasTabuleiro = static_cast<int>(tabuleiro.size());
  int numeroColunasTabuleiro = static_cast<int>(tabuleiro[0].size());
  int contadorMainDiagonal = 0; 
  int contadorAntiDiagonal = 0;

  std::pair<int, int> ultimaJogada = jogadas[jogadas.size() - 1];

  // Precisamo checar a útima jogada, que está localizada ao final do array de Jogadas,
  // caso o contador de Diagonais Main ou Anti atinja 4, retornar true,
  // caso contrário falso.
  // comparar a última jogada com todas as anteriores, assim não precisamos comparar todas as jogadas de uma vez;


  // Comparando os proximos 3 termos na diagonal a direita inferior
  for (int i = ultimaJogada.first + 1, j = ultimaJogada.second + 1, contadorDeIteracoes = 0;
      contadorDeIteracoes < 3; i++, j++, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, j)) {
      // Checar se o jogador fez essa jogada, caso positivo contador main++;
    }
    else {
      // Break, pois a posicao nao existe, nao faz sentido continuar o loop.
    }
  }
  
}

bool Lig4::checarVencedor(std::vector<std::pair<int, int>> &jogadas) {
  if (!jogadas.empty()) {
    if (checarDiagonal(jogadas) or
        checarColunas(jogadas) or
        checarLinhas(jogadas))
      return true;
  }
  return false;
}