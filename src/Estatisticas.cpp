#include "Estatisticas.hpp"

#include <iostream>

Estatisticas::Estatisticas() : vitorias(0), derrotas(0), empates(0) {}

Estatisticas::Estatisticas(int vitorias, int derrotas, int empates) :
vitorias(vitorias), derrotas(derrotas), empates(empates) {}

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

int Estatisticas::getVitorias() const{ 
  return vitorias;
}
int Estatisticas::getDerrotas() const{
  return derrotas;
}
int Estatisticas::getEmpates() const{
  return empates;
}
std::vector<char> Estatisticas::getHistorico() const{
  return historico;
}
void Estatisticas::mostrarEstatisticas() const{
  std::cout << "- V: <" << getVitorias() << "> D: <" << getDerrotas() << ">" << " E: <" << getEmpates() << "> " << std::endl;
}