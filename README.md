# ProjetoFinal

## Sobre o Projeto

Este projeto foi desenvolvido em C++ e tem como objetivo a criação de um sistema confiável para gerenciar uma plataforma de jogos, similar a um videogame. O sistema deve ser capaz de armazenar informações sobre jogadores, como número de vitórias, derrotas e empates em diferentes jogos. Além disso, os dados dos jogadores devem ser persistidos entre execuções do programa.

Inicialmente, o sistema foi projetado para suportar pelo menos três jogos:

- Jogo da Velha
- Ligue 4
- Reversi

---

## Visão Geral da Solução

A solução foi implementada de forma modular e organizada, utilizando classes para estruturar os diferentes componentes do sistema. O núcleo do projeto é a classe `CentralDeJogos`, responsável pela gerência dos jogos e dos jogadores cadastrados. Essa classe contém os seguintes elementos principais:

### Estrutura de Dados

- **Lista de jogadores cadastrados**: Representada por objetos da classe `Jogador`, armazenando nome, apelido e estatísticas individuais.
- **Estatísticas por jogo**: Cada jogador mantém um `std::map<std::string, Estatisticas>`, onde a chave é o nome do jogo e o valor é um objeto da classe `Estatisticas`, que registra o número de vitórias, derrotas e empates.
- **Objetos de jogos**: A `CentralDeJogos` contém instâncias das classes `JogoDaVelha`, `Ligue4`, `Reversi`, `BatalhaNaval` e `JogoDaVelhaIA`, permitindo a execução e manipulação das partidas.

### Persistência de Dados

Para garantir a persistência das informações entre execuções, o sistema utiliza um arquivo de armazenamento localizado em `data/`:

- **No construtor da classe `CentralDeJogos`**: O arquivo de save é lido, e os dados dos jogadores são carregados na memória.
- **No destrutor da classe `CentralDeJogos`**: O estado atual dos jogadores é salvo no arquivo `DadosJogadoresCadastrados`, garantindo que as informações sejam preservadas para futuras execuções.

⚠️ **Importante**: O terminal deve estar aberto no diretório raiz do projeto ao executar o programa. Caso contrário, podem ocorrer erros na recuperação dos dados salvos.

---

## Arquitetura dos Jogos

Os jogos foram desenvolvidos utilizando um modelo de herança baseado em uma classe abstrata chamada `Jogos`. Essa classe contém:

- **Tabuleiro**: Representado como um atributo compartilhado entre os jogos.
- **Métodos auxiliares**: Funções utilitárias para manipulação do tabuleiro e regras de jogo.
- **Métodos puramente virtuais**: Definições obrigatórias para todas as classes filhas, garantindo que cada jogo implemente suas próprias regras e comportamento.

O principal método dessa classe é `Jogar()`, que gerencia a execução de uma partida. Esse método é redefinido e, quando necessário, sobrecarregado nas classes derivadas para atender às regras específicas de cada jogo.

---

## Recursos Extras Implementados

Além dos requisitos básicos do projeto, foram desenvolvidas funcionalidades adicionais para aumentar a complexidade e aprimorar a experiência do usuário. Os recursos extras incluem:

- **Batalha Naval**: Implementação do clássico jogo de estratégia, seguindo regras tradicionais.
- **Jogo da Velha com IA**: Um modo single-player onde o usuário pode desafiar uma inteligência artificial.
- **Interface Gráfica (UI)**: Desenvolvimento de uma interface gráfica para facilitar a interação com os jogos.

---

## Principais Desafios

Durante o desenvolvimento do projeto, enfrentamos diversos desafios técnicos e organizacionais, incluindo:

- **Implementação da Inteligência Artificial**: A criação da IA para o Jogo da Velha exigiu o desenvolvimento de um algoritmo capaz de tomar decisões estratégicas em tempo real.
- **Desenvolvimento do Reversi**: A complexidade das regras e das mecânicas de jogo tornou a implementação mais desafiadora do que o esperado.
- **Trabalho Colaborativo com Git**: A colaboração simultânea entre os membros da equipe exigiu um controle eficiente de versionamento e resolução de conflitos no código.
- **Integração da Interface Gráfica**: A adaptação do código-base para uma versão com UI apresentou dificuldades na comunicação entre os módulos gráficos e o núcleo do projeto.

No final, a interface gráfica resultou em uma implementação paralela do sistema principal em C++, com pequenas variações em relação ao código-fonte original. Como a integração da IA com a UI não foi completamente bem-sucedida, recomenda-se a utilização prioritária da versão executável do projeto principal localizada em `/bin/ProjetoFinal`.

Mais detalhes sobre a implementação da IA, da interface gráfica e do jogo Batalha Naval podem ser encontrados na documentação e no arquivo `README.md` da UI, localizado no diretório `/UI`.

---



## Instruções de Compilação

1. **Garanta que o terminal esteja aberto no diretório raiz do projeto** (`ProjetoFinal`). Isso é fundamental para o correto carregamento do arquivo de save dos jogadores.
   
   Exemplo de caminho esperado no Windows:
   ```
   C:\...\...\ProjetoFinal>
   ```

2. **Execute os seguintes comandos conforme o sistema operacional:**

   **Para Linux/macOS:**
   ```sh
   make clean
   make
   ```
   
   **Para Windows (com MinGW instalado):**
   ```sh
   mingw32-make clean
   mingw32-make
   ```
   
   **Explicação dos comandos:**
   - `make clean` ou `mingw32-make clean`: Remove arquivos temporários e binários antigos, garantindo uma recompilação limpa.
   - `make` ou `mingw32-make`: Compila o projeto conforme as regras definidas no `Makefile`, gerando o executável final na pasta `bin/`.

---

## Executando o Projeto

Após a compilação bem-sucedida, o executável estará localizado na pasta `bin`. Para rodar o programa, utilize o seguinte comando no terminal:

```sh
./bin/ProjetoFinal
```

No Windows, caso esteja usando o CMD, utilize:
```sh
bin\ProjetoFinal.exe
```

Certifique-se de manter o terminal aberto na pasta `ProjetoFinal` antes de executar o comando.

---

## Observações Importantes

- **Estrutura do diretório:** O projeto depende de arquivos de configuração e saves armazenados na pasta raiz. Alterar a localização do executável e do diretório em que o terminal está aberto pode impedir o carregamento correto desses arquivos.
- **Compatibilidade:** Testado em Windows 10/11, Ubuntu 20.04+ e macOS Monterey+.
- **Erros na compilação:** Se ocorrerem erros, verifique se o `make` está corretamente instalado e se o compilador suporta C++11.

---

Caso tenha dúvidas ou precise de suporte, consulte a documentação do Makefile ou entre em contato com o grupo desenvolvedor.

