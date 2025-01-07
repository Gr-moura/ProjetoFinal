#include "Jogador.hpp"

Jogador::Jogador(const std::string& apelido, const std::string& nome)
    : apelido(apelido), nome(nome) {}

void Jogador::registrarVitoria(const std::string& Jogo) {
  estatisticasPorJogo.at(Jogo).registrarVitoria();
}

void Jogador::registrarEmpate(const std::string& Jogo) {
  estatisticasPorJogo.at(Jogo).registrarEmpate();
}

void Jogador::registrarDerrota(const std::string& Jogo) {
  estatisticasPorJogo.at(Jogo).registrarDerrota();
}

std::string Jogador::getApelido() const { return apelido; }

std::string Jogador::getNome() const { return nome; }

void Jogador::mostrarEstatisticas(const std::string& Jogo) const {
  std::cout << Jogo << " ";
  estatisticasPorJogo.at(Jogo).mostrarEstatisticas();
}