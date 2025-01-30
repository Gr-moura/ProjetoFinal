#include "Estatisticas.hpp"

#include <iostream>

Estatisticas::Estatisticas() : vitorias(0), derrotas(0), empates(0) {}

Estatisticas::Estatisticas(int vitorias, int derrotas, int empates) :
    vitorias(vitorias), derrotas(derrotas), empates(empates)
{
}

void Estatisticas::registrarVitoria()
{
    vitorias++;
}

void Estatisticas::registrarDerrota()
{
    derrotas++;
}

void Estatisticas::registrarEmpate()
{
    empates++;
}

int Estatisticas::getVitorias() const
{
    return vitorias;
}

int Estatisticas::getDerrotas() const
{
    return derrotas;
}

int Estatisticas::getEmpates() const
{
    return empates;
}

void Estatisticas::mostrarEstatisticas() const
{
    std::cout << "- V: <" << getVitorias() << "> D: <" << getDerrotas() << ">" << " E: <" << getEmpates() << "> "
              << std::endl;
}