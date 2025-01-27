#include "Jogos.hpp"
#include "Jogador.hpp"

Jogos::~Jogos() {}

std::string Jogos::gerarDivisoriaTabuleiro(){
  std::string divisor;
  divisor.push_back('\n');

  if (!tabuleiro.empty()) {
    int numCols = static_cast<int>((tabuleiro.size()));
    for (int i = 0; i < numCols * 4 - 1; i++) {
      divisor.push_back('-');
    }
  }

  divisor.push_back('\n');
  return divisor;
}

void Jogos::mostrarTabuleiro() {
  for (int i = 0; i < static_cast<int>(tabuleiro.size()); i++) {
    for (int j = 0; j < static_cast<int>(tabuleiro[i].size()); j++) {
      if (j > 0) {
        std::cout << "| " << tabuleiro[i][j] << " ";
      } else {
        std::cout << " " << tabuleiro[i][j] << " ";
      }
    }
    if (i < static_cast<int>(tabuleiro.size()) - 1) {
      std::cout << gerarDivisoriaTabuleiro();
    }
  }
  std::cout << std::endl;
}

void Jogos::limparTabuleiro() {
  for (auto &linha : tabuleiro) {
    for (auto &coluna : linha) {
      coluna = ' ';
    }
  }
  return;
}

void Jogos::marcarTabuleiro(std::pair<int, int> &jogada, bool &turno) {
  if (turno)
    tabuleiro[jogada.first][jogada.second] = 'X';
  else
    tabuleiro[jogada.first][jogada.second] = 'O';
}

void Jogos::iniciarTurno(Jogador &Jogador) {
  std::cout << "Turno de " << Jogador.getApelido() << "!" << std::endl;
}

bool Jogos::sorteio() {
  srand(std::time(0));
  bool sorteio = std::rand() % 2;
  return sorteio;
}

bool Jogos::checarJogadaExistente(std::vector<std::pair<int, int>> &jogadas, int linha, int coluna) {
  std::pair<int, int> jogada = {linha , coluna};
  if (std::find(jogadas.begin(), jogadas.end(), jogada) != jogadas.end())
    return  true;
  else
    return false;
}

bool Jogos::checarPosicaoValida(int linha, int coluna) {
  if (linha < static_cast<int>(tabuleiro.size()) and
  linha >= 0 and
  coluna < static_cast<int>(tabuleiro[0].size()) and
  coluna >= 0) {
    return true;  
  }
  else
    return false;
}

void Jogos::Jogar(Jogador &Jogador1, Jogador &Jogador2) {  
  bool jogoEmAndamento = true;
  bool turno = sorteio();
  int contadorTurnos = 0;
  std::vector<std::pair<int, int>> movimentosJogador1;
  std::vector<std::pair<int, int>> movimentosJogador2;

  std::pair<int, int> jogada;
  iniciarPartida(Jogador1, Jogador2, turno);

  while (jogoEmAndamento) {
    contadorTurnos++;
    if (turno) {
      iniciarTurno(Jogador1); //jogadorX no reversi
      jogada = lerJogada();
      
      marcarTabuleiro(jogada, turno);
      mostrarTabuleiro();

      movimentosJogador1.push_back(jogada);
      if (checarVencedor(movimentosJogador1, Jogador1, Jogador2, turno)){
        std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!"
        << std::endl;
        jogoEmAndamento = false;
        limparTabuleiro();
        return;
      }
      turno = not turno;
    }
    else {
      iniciarTurno(Jogador2); //jogadorO no reversi
      jogada = lerJogada();
      
      marcarTabuleiro(jogada, turno);
      mostrarTabuleiro();

      movimentosJogador2.push_back(jogada);
      if (checarVencedor(movimentosJogador2, Jogador2, Jogador1, turno)){
        jogoEmAndamento = false;
        std::cout << "O jogador " << Jogador2.getApelido() << " ganhou o jogo!"
        << std::endl;
        limparTabuleiro();
        return;
      }
      turno = not turno;
    }
    if (checarEmpate(contadorTurnos, Jogador1, Jogador2)) {
      jogoEmAndamento = false;
      limparTabuleiro();
      return;
    }
  }
  
}


void Jogos::JogarReversi(Jogador &Jogador1, Jogador &Jogador2) {  
  bool jogoEmAndamento = true;
  bool turno = sorteio();
  int contadorTurnos = 0;
  std::vector<std::pair<int, int>> movimentosJogador1;
  std::vector<std::pair<int, int>> movimentosJogador2;

  std::pair<int, int> jogada;
  iniciarPartida(Jogador1, Jogador2, turno);

  while (jogoEmAndamento) {
    contadorTurnos++;
    if (turno) {
      iniciarTurno(Jogador1); //jogadorX no reversi
      jogada = lerJogadaReversi(turno);
      
      marcarTabuleiro(jogada, turno);
      mostrarTabuleiro();

      movimentosJogador1.push_back(jogada);
      if (checarVencedor(movimentosJogador1, Jogador1, Jogador2, turno)){
        std::cout << "O jogador " << Jogador1.getApelido() << " ganhou o jogo!"
        << std::endl;
        jogoEmAndamento = false;
        limparTabuleiro();
        return;
      }
      turno = not turno;
    }
    else {
      iniciarTurno(Jogador2); //jogadorO no reversi
      jogada = lerJogadaReversi(turno);
      
      marcarTabuleiro(jogada, turno);
      mostrarTabuleiro();

      movimentosJogador2.push_back(jogada);
      if (checarVencedor(movimentosJogador2, Jogador2, Jogador1, turno)){
        jogoEmAndamento = false;
        std::cout << "O jogador " << Jogador2.getApelido() << " ganhou o jogo!"
        << std::endl;
        limparTabuleiro();
        return;
      }
      turno = not turno;
    }
    if (checarEmpate(contadorTurnos, Jogador1, Jogador2)) {
      jogoEmAndamento = false;
      limparTabuleiro();
      return;
    }
  }
  
}

// remover dependencies do makefile