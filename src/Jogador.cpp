#include "Jogador.hpp"
#include <iostream>

Jogador::Jogador(const std::string &apelido, const std::string &nome) : apelido(apelido), nome(nome)
{
    estatisticasPorJogo["VELHA"] = Estatisticas();
    estatisticasPorJogo["LIG4"] = Estatisticas();
    estatisticasPorJogo["REVERSI"] = Estatisticas();
    estatisticasPorJogo["BATALHANAVAL"] = Estatisticas();
}

Jogador::Jogador(const std::string &apelido, const std::string &nome, const int vitoriasJogoDaVelha,
                 const int derrotasJogoDaVelha, const int empatesJogoDavelha, const int vitoriasLig4,
                 const int derrotasLig4, const int empatesLig4, const int vitoriasReversi, const int derrotasReversi,
                 const int empatesReversi, const int vitoriasBatalhaNaval, const int derrotasBatalhaNaval,
                 const int empatesBatalhaNaval) : apelido(apelido), nome(nome)
{
    estatisticasPorJogo["VELHA"] = Estatisticas(vitoriasJogoDaVelha, derrotasJogoDaVelha, empatesJogoDavelha);
    estatisticasPorJogo["LIG4"] = Estatisticas(vitoriasLig4, derrotasLig4, empatesLig4);
    estatisticasPorJogo["REVERSI"] = Estatisticas(vitoriasReversi, derrotasReversi, empatesReversi);
    estatisticasPorJogo["BATALHANAVAL"] = Estatisticas(vitoriasBatalhaNaval, derrotasBatalhaNaval, empatesBatalhaNaval);
}

void Jogador::registrarVitoria(const std::string &nomeJogo)
{
    estatisticasPorJogo.at(nomeJogo).registrarVitoria();
}

void Jogador::registrarEmpate(const std::string &nomeJogo)
{
    estatisticasPorJogo.at(nomeJogo).registrarEmpate();
}

void Jogador::registrarDerrota(const std::string &nomeJogo)
{
    estatisticasPorJogo.at(nomeJogo).registrarDerrota();
}

std::string Jogador::getApelido() const
{
    return apelido;
}

std::string Jogador::getNome() const
{
    return nome;
}

int Jogador::getVitorias(std::string jogo)
{
    return estatisticasPorJogo[jogo].getVitorias();
}

int Jogador::getDerrotas(std::string jogo)
{
    return estatisticasPorJogo[jogo].getDerrotas();
}

int Jogador::getEmpates(std::string jogo)
{
    return estatisticasPorJogo[jogo].getEmpates();
}

void Jogador::mostrarEstatisticas(const std::string &nomeJogo) const
{
    std::cout << nomeJogo << " ";
    estatisticasPorJogo.at(nomeJogo).mostrarEstatisticas();
}