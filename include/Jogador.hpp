#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Estatisticas.hpp"

class Jogador
{
  private:
    std::string apelido;
    std::string nome;
    std::unordered_map<std::string, Estatisticas> estatisticasPorJogo;

  public:
    Jogador(const std::string &apelido, const std::string &nome);
    Jogador(const std::string &apelido, const std::string &nome, int vitoriasJogoDaVelha, int derrotasJogoDaVelha,
            int empatesJogoDavelha, int vitoriasLig4, int derrotasLig4, int empatesLig4, int vitoriasReversi,
            int derrotasReversi, int empatesReversi, int vitoriasBatalhaNaval, int derrotasBatalhaNaval,
            int empatesBatalhaNaval);

    void registrarVitoria(const std::string &nomeJogo);
    void registrarDerrota(const std::string &nomeJogo);
    void registrarEmpate(const std::string &nomeJogo);

    std::string getApelido() const;
    std::string getNome() const;
    int getVitorias(std::string jogo);
    int getDerrotas(std::string jogo);
    int getEmpates(std::string jogo);

    void mostrarEstatisticas(const std::string &nomeJogo) const;
};

#endif