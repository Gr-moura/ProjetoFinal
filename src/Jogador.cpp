#include "Jogador.hpp"
#include <iostream>

Jogador::Jogador(const std::string& apelido, const std::string& nome)
    : apelido(apelido), nome(nome) {}

Jogador::Jogador(const std::string &apelido, const std::string &nome,
          const int vitoriasJogoDaVelha, const int derrotasJogoDaVelha, const int empatesJogoDavelha,
          const int vitoriasLig4, const int derrotasLig4, const int empatesLig4,
          const int vitoriasReversi, const int derrotasReversi, const int empatesReversi
  ) : apelido(apelido), nome(nome){
  estatisticasPorJogo["Velha"] = Estatisticas(vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDavelha);
  estatisticasPorJogo["Lig4"] = Estatisticas(vitoriasLig4, derrotasLig4, empatesLig4);
  estatisticasPorJogo["Reversi"] = Estatisticas(vitoriasReversi, derrotasReversi, empatesReversi);
}

void Jogador::registrarVitoria(const std::string& nomeJogo) {
  estatisticasPorJogo.at(nomeJogo).registrarVitoria();
}

void Jogador::registrarEmpate(const std::string& nomeJogo) {
  estatisticasPorJogo.at(nomeJogo).registrarEmpate();
}

void Jogador::registrarDerrota(const std::string& nomeJogo) {
  estatisticasPorJogo.at(nomeJogo).registrarDerrota();
}

std::string Jogador::getApelido() const { return apelido; }

std::string Jogador::getNome() const { return nome; }

void Jogador::mostrarEstatisticas(const std::string& nomeJogo) const {
  std::cout << nomeJogo << " ";
  estatisticasPorJogo.at(nomeJogo).mostrarEstatisticas();
}