#include "Jogador.hpp"

Jogador::Jogador(const std::string& apelido, const std::string& nome)
    : apelido(apelido), nome(nome) {}

void Jogador::registrarVitoria(const std::string& Jogo) {}

void Jogador::registrarEmpate(const std::string& Jogo) {}

void Jogador::registrarDerrota(const std::string& Jogo) {}

Estatisticas Jogador::getEstatisticas(const std::string& Jogo) const {}