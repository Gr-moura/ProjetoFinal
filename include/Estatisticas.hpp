#ifndef ESTATISTICAS_HPP
#define ESTATISITICAS_HPP

#include <vector>

class Estatisticas {
 private:
  int vitorias;
  int derrotas;
  int empates;
  std::vector<char> historico;

 public:
  Estatisticas();
  Estatisticas(int vitorias, int derrotas, int empates);
  
  void registrarVitoria();
  void registrarDerrota();
  void registrarEmpate();

  int getVitorias() const;
  int getDerrotas() const;
  int getEmpates() const;
  std::vector<char> getHistorico() const;
  void mostrarEstatisticas() const;
};

#endif