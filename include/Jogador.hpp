#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Estatisticas.hpp"

class Jogador {
 private:
  std::string apelido;
  std::string nome;
  std::unordered_map<std::string, Estatisticas> estatisticasPorJogo;

 public:
  Jogador(const std::string &apelido, const std::string &nome);

  void registrarVitoria(const std::string &nomeJogo);
  void registrarDerrota(const std::string &nomeJogo);
  void registrarEmpate(const std::string &nomeJogo);

  std::string getApelido() const;
  std::string getNome() const;
  void mostrarEstatisticas(const std::string &nomeJogo) const;
};

#endif