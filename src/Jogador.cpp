#include "Jogador.hpp"

Jogador::Jogador(const std::string& apelido, const std::string& nome)
    : apelido(apelido), nome(nome) {}

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