#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Estatisticas.hpp"
#include "JogoDaVelha.hpp"
#include "Jogos.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

class Jogador {
 private:
  std::string apelido;
  std::string nome;
  std::unordered_map<std::string, Estatisticas> estatisticasPorJogo;

 public:
  Jogador(const std::string&, const std::string&);
  
  void registrarVitoria(const std::string&);
  void registrarDerrota(const std::string&);
  void registrarEmpate(const std::string&);

  Estatisticas getEstatisticas(const std::string&) const;
};

#endif