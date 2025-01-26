#include "Lig4.hpp"

Lig4::Lig4(int tamanhoTabuleiro) {
  tabuleiro.resize(tamanhoTabuleiro, std::vector<char>(tamanhoTabuleiro + 1, ' '));
}

Lig4::Lig4(){
  tabuleiro.resize(7, std::vector<char>(6, ' '));
}

void Lig4::iniciarPartida(Jogador &Jogador1, Jogador &Jogador2, bool &turno) {
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
  mostrarTabuleiro();
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
  return {0, 0};    
}

bool Lig4::checarDiagonal(std::vector<std::pair<int, int>> &jogadas) {
  int contadorMainDiagonal = 0; 
  int contadorAntiDiagonal = 0;

  std::pair<int, int> ultimaJogada = jogadas[jogadas.size() - 1];

  for (int i = ultimaJogada.first + 1, j = ultimaJogada.second + 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; i++, j++, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, j)) {
      if (checarJogadaExistente(jogadas, i, j))
        contadorMainDiagonal++;
      else
        break;
    }
    else
      break;
  }

  for (int i = ultimaJogada.first - 1, j = ultimaJogada.second - 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; i--, j--, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, j)) {
      if (checarJogadaExistente(jogadas, i, j))
        contadorMainDiagonal++;
      else
        break;
    }
    else
      break;
  }

  for (int i = ultimaJogada.first + 1, j = ultimaJogada.second - 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; i++, j--, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, j)) {
      if (checarJogadaExistente(jogadas, i, j))
        contadorAntiDiagonal++;
      else
        break;
    }
    else
      break;
  }

  for (int i = ultimaJogada.first - 1, j = ultimaJogada.second + 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; i--, j++, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, j)) {
      if (checarJogadaExistente(jogadas, i, j))
        contadorAntiDiagonal++;
      else
        break;
    }
    else
      break;
  }
  
  if (contadorMainDiagonal  >= 3 or contadorAntiDiagonal >= 3)
    return true;
  else
    return false;
}

bool Lig4::checarLinhas(std::vector<std::pair<int, int>> &jogadas) {
  int contadorLinhas = 0;

  std::pair<int, int> ultimaJogada = jogadas[jogadas.size() - 1];

  // Checar os próximos três elementos à direita.
  for (int j = ultimaJogada.second + 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; j++, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(ultimaJogada.first, j)) {
      if (checarJogadaExistente(jogadas, ultimaJogada.first, j))
        contadorLinhas++;
      else
        break;
    }
    else
      break;
  }

  // Checar os próximos três elementos à esquerda.
  for (int j = ultimaJogada.second - 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; j--, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(ultimaJogada.first, j)) {
      if (checarJogadaExistente(jogadas, ultimaJogada.first, j))
        contadorLinhas++;
      else
        break;
    }
    else
      break;
  }

  if (contadorLinhas >= 3)
    return true;
  else
    return false;
}

bool Lig4::checarColunas(std::vector<std::pair<int, int>> &jogadas) {
  int contadorColunas = 0;

  std::pair<int, int> ultimaJogada = jogadas[jogadas.size() - 1];

  // Checar as próximas três casas acima.
  for (int i = ultimaJogada.first + 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; i++, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, ultimaJogada.second)) {
      if (checarJogadaExistente(jogadas, i, ultimaJogada.second))
        contadorColunas++;
      else
        break;
    }
    else
      break;
  }

  // Checar as próximas três casas abaixo.
  for (int i = ultimaJogada.first - 1, contadorDeIteracoes = 0;
  contadorDeIteracoes < 3; i--, contadorDeIteracoes++) {
    
    if (checarPosicaoValida(i, ultimaJogada.second)) {
      if (checarJogadaExistente(jogadas, i, ultimaJogada.second))
        contadorColunas++;
      else
        break;
    }
    else
      break;
  }
  if (contadorColunas >= 3)
    return true;
  else
    return false; 
}

bool Lig4::checarVencedor(std::vector<std::pair<int, int>> &jogadas, Jogador &vencedor, Jogador &perdedor, bool turno) {
  if (!jogadas.empty()) {
    if (checarDiagonal(jogadas) or
        checarLinhas(jogadas) or
        checarColunas(jogadas)) {
          vencedor.registrarVitoria("LIG4");
          perdedor.registrarDerrota("LIG4");
          return true;
        }
  }
  return false;
}

bool Lig4::checarEmpate(int numeroJogadas, Jogador &jogador_01, Jogador &jogador_02) {
  if (numeroJogadas >= (static_cast<int>(tabuleiro.size() * tabuleiro[0].size()))) {
    std::cout << "O jogo finalizou com um EMPATE. Ninguem ganhou!"
    << std::endl;
    jogador_01.registrarEmpate("LIG4");
    jogador_02.registrarEmpate("LIG4");
    return true;
  }
  else
    return false;
}



