#include "JogoDaVelha.hpp"

JogoDaVelha::JogoDaVelha(){
  tabuleiro.resize(3, std::vector<char>(3, ' '));
}

JogoDaVelha::JogoDaVelha(int tamanhoTabuleiro){
  tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro, ' '));
}

void JogoDaVelha::inciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) {
  if (turno) {
    std::cout << "Bem Vindo ao Jogo da velha! O jogador " <<
    Jogador1.getApelido() << " comecara a partida!" <<
    std::endl;
  }
  else {
    std::cout << "Bem Vindo ao Jogo da velha! O jogador " <<
    Jogador2.getApelido() << "comecara a partida!" <<
    std::endl;
  }
}

std::pair<int, int> JogoDaVelha::lerJogada() {
  std::cout << "Insira a posicao que deseja marcar no tabuleiro, linha e coluna respectivamente." <<
  std::endl;
  int linha, coluna;
  bool entradaValida = false;
  while (not (entradaValida)){
    while (not (std::cin >> linha >> coluna)) {
      std::cout << "ERRO, tipo de dado invalido. Por favor insira dois inteiros." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }

    if (linha-1 < static_cast<int>(tabuleiro.size()) and
    linha-1 >= 0 and
    coluna-1 < static_cast<int>(tabuleiro[0].size()) and
    coluna-1 >= 0) {
      if (tabuleiro[linha - 1][coluna - 1] == ' ') {
        std::pair<int, int> jogada = {linha - 1, coluna - 1};
        entradaValida = true;
        return jogada;
      }
      else {
        std::cout << "ERRO!  A posicao escolhida ja esta ocupada. Insira uma posicao valida!"
        << std::endl;
      }          
    }
    else {
      std::cout << "ERRO! A posicao escolhida nao esta dentro dos limites do tabuleiro. Escolha uma opcao valida!"
      << std::endl;
    }
      
  }    
}

void JogoDaVelha::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) {
  if (turno)
    tabuleiro[jogada.first][jogada.second] = 'X';
  else
    tabuleiro[jogada.first][jogada.second] = 'O';
}

bool JogoDaVelha::checarDiagonal(std::vector<std::pair<int, int>> &movimentos) {
  int n = static_cast<int>(tabuleiro.size());
  int contadorMainDiagonal = 0; 
  int contadorAntiDiagonal = 0;

  for (int i = 0; i < n; i++) {
    if (std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, i)) != movimentos.end()) 
      contadorMainDiagonal++;
  }

  if (contadorMainDiagonal == n) 
    return true;

  for (int i = 0; i < n; i++) {
    if (std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, n - 1 - i)) != movimentos.end())
      contadorAntiDiagonal++;
  }

  if (contadorAntiDiagonal == n)
    return true;

  return false;
}

bool JogoDaVelha::checarColunas(std::vector<std::pair<int, int>> &movimentos) {
  for (int j = 0; j < static_cast<int>(tabuleiro.size()); j++) {
    bool colunaCompleta = true;
    for (int i = 0; i < static_cast<int>(tabuleiro[0].size()); i++) {
      auto it =
          std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, j));
      if (it == movimentos.end()) {
        colunaCompleta = false;
        break;
      }
    }
    if (colunaCompleta) {
      return true;
      std::cout << "COLUNA" << std::endl;
    }
  }
  return false;
}

bool JogoDaVelha::checarLinhas(std::vector<std::pair<int, int>> &movimentos) {
  for (int i = 0; i < static_cast<int>(tabuleiro.size()); i++) {
    bool linhaCompleta = true;
    for (int j = 0; j < static_cast<int>(tabuleiro.size()); j++) {
      auto it =
          std::find(movimentos.begin(), movimentos.end(), std::make_pair(i, j));
      if (it == movimentos.end()) {
        linhaCompleta = false;
        break;
      }
    }
    if (linhaCompleta) {
      return true;
      std::cout << "LINHA" << std::endl;
    }
  }
  return false;
}

bool JogoDaVelha::checarVencedor(std::vector<std::pair<int, int>> &movimentos) {
  if (!movimentos.empty()) {
    if (checarDiagonal(movimentos) or
        checarColunas(movimentos) or
        checarLinhas(movimentos))
      return true;
  }
  return false;
}