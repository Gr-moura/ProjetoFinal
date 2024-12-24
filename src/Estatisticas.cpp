#include "Estatisticas.hpp"

#include <iostream>

void Estatisticas::registrarVitoria() {
  vitorias++;
  historico.push_back('V');
}
void Estatisticas::registrarDerrota() {
  derrotas++;
  historico.push_back('D');
}
void Estatisticas::registrarEmpate() {
  empates++;
  historico.push_back('E');
}

int Estatisticas::getVitorias() { return vitorias; }
int Estatisticas::getDerrotas() { return derrotas; }
int Estatisticas::getEmpates() { return empates; }
std::vector<char> Estatisticas::getHistorico() const { return historico; }
void Estatisticas::mostrarEstatisticas() {
  std::cout << "- V: <" << getVitorias() << "> D: <" << getDerrotas() << ">" << std::endl;
}