# UI


## Objetivo
O objetivo da UI do projeto é melhorar a experiência do usuário ao interagir com o código em C++.  
O código em C++ pode ser tanto rodado usando a UI como diretamente no terminal. Isso decorre do fato de que a integração foi feita usando arquivos WASM (pré-compilados a partir dos arquivos C++ modificados). Ou seja, de certa forma é como se o projeto com a UI seja um executável separado do projeto sem a UI.  
Para executar o código com a UI, siga as instruções disponóveis mais a frente.  


## Solução
A solução usada para desenvolver a UI foi o REACT. Usando código em javascript, desenvolvemos uma interface gráfica para o projeto que pode ser executada diretamente em qualquer navegador.  
Podemos dividir, de uma forma geral, a UI entre telas e componentes.  

### O worflow REACT
O react trabalha usando html, CSS, e JavaScript para criar páginas web.  
O diferencial que o usa do REACT proporciona é a capacidade de criar "componentes": Funções que podem ser chamadas como tags html. A criação de componentes proporciona uma facilidade imensa em criar partes reutilizáveis para o site.  
Além disso, o REACT proporciona diversos outros beneficios, como a renderização condicional (usando "state variables" é possível re-renderizar apenas as partes do site que sofreram mudanças, melhorando o desempenho da aplicação) e as "routes" (forma de navegar entre as páginas do site sem ter que recarregar a janela).

### Telas
- #### Seleção de jogadores (PlayerSelection):
  A tela inicial da UI é a seleção de jogadores. Nela, você pode criar, selecionar e deletar jogadores.  
  Essa tela usa o "Local Storage" do navegador para guardar os dados dos jogadores e mostrá-los na tela (vitórias, derrotas e empates).  
- #### Seleção de jogos (Menu):
  Após a seleção de jogadores, uma tela para escolher os jogos é apresentada. Nessa tela, os jogadores também tem acesso a uma descrição de cada jogo.  
  Além disso é possível escolher a dificuldade da IA, caso o jogador 2 escolhido seja um bot.  
- #### Tabuleiro (Board):
  Essa tela renderiza de forma dinâmica um tabuleiro para cada jogo. Além disso, nela são chamadas as implementações das regras de cada jogo para verificar vitórias ou derrotas.  
  A tela controla a verificação de vitória e derrota, as jogadas (tanto do jogador como da IA), e as regras de cada jogo.  
  A verificação de vitória, derrota e as regras foram implementadas em C++ e conectadas à tela depois de serem compiladas em WASM (WebAssembly).
- #### Outras telas (DebugMenu):
  Por fim, a UI contém algumas telas que foram usadas para testar o código durante a fase de desenvolvimento, e não são acessíveis ao usuário.  

### Componentes
- #### Casa do tabuleiro (BoardCell):
  Componente usado na renderização do tabuleiro durante os jogos. Exibi uma "casa" circular que pode estar vazia, ou colorida em verde ou vermelho.  
  É capaz de guardar qual jogador clicou nele, e de executar uma função personalizada quando clicado.  
- #### Banner de jogo (MenuBanner):
  Um banner que registra uma imagem, um nome e uma descrição de um jogo.  
  Tem um botão que executa uma função personalizada, e várias animações inclusas.  
- #### Banner de jogador (PlayerBanner):
  Um banner que mostra um apelido, um nome, e uma pontuação em vários jogos.  
  É capaz de executar uma função personalizada quando clicado, e tem vários parâmetros que permitem customizações adicionais (como playerType="nameless" que esconde o nome do jogador).  
- #### Seletor (Selector):
  Um seletor que usa setas para circular entre seus conteúdos. Cada contéudo selecionado atualiza uma variável de "state" customizável.  
  Cada contúdo do seletor é um objeto, que contém um nome (mostrado ao usuário), um valor (usado no código e guardado na variável de "state") e um "index" (referente a ordem que os conteúdos aparecerão no seletor).  
- #### "Overlay" de vitória (WinOverlay):
  Um "overlay" semi-transparente que aparece sobre o tabuleiro quando um jogo acaba.  
  Exibe o nome do vencedor (ou "Empate") e duas opções: Voltar à tela de seleção de jogadores ou jogar novamente.
- #### Outros componentes (dropdown):
  Alguns outros componentes foram uasdos apenas nas telas não acessíveis para o usuário.


## Problemas encontrados durante o desenvolvimento
- #### Arquivos locais não podem ser modificados: 
  Como a UI é executada diretamente no navegador como um site, modificar arquivos locais é impossível, devido à medidas de segurança implementadas nos navegadores e no próprio REACT. Modificar o arquivo de texto local usado para armazenar jogadores depois de cada partida é uma falha de segurança grave, pois seria equivalente a permitir que um site modifique arquivos em seu computador.  
  Logo, a solução encontrada foi usar o "Local Storage": Dados em formato JSON que ficam armazenados diretamente no navegador do usuário, e podem ser acessados e modificados facilmente pelo site que os armazenou.  
  
- #### Integração direta com o código em C++:
  Integrar o código do REACT com o código em C++ se provou uma dificuldade maior do que o esperado.  
  Isso decorre do fato de que o C++ é uma linguagem feita para ser compilada para computadores. E todos os compildares mais conhecidos (como o G++) compilam C++ em arquivos feitos para ser executados em sistemas operacionais, diferentemente do JavaScript e do REACT, que são compilados com o objetivo de serem executados em navegadores.  
  Logo a solução encontrada foi pré-compilar os arquivos de C++ em WebAssembly (WASM) usando o Emscripten. Após a compilação em arquivos WASM, os códigos em c++ poderiam ser chamadas pelo site e integrados com a UI.  
  
- #### WebAssembly e VITE: 
  O Vite é uma "build tool" moderna usada para testar o site durante o desenvolvimento. Ele possibilita que um servidor local aja como "Host" para o site, fazendo que não seja necessário pagar para manter um site na rede apenas para executá-lo, e foi uma ferramenta essencial durante o desenvolvimento da UI para este projeto.  
  Além de possibilitar a execução do projeto, ele também é dinâmico e altera o site à medida que a "codebase" é modificada de forma quase instantânea. Entretanto, ele não possui suporte para os "wrappers" em javascript (não possuit suporte para "ES Modules" e WASM) gerados pelo Emscripten.  
  Assim, foi necessário lidar diretamente com os arquivos WASM, o que gerou várias restrições na integração do C++ com o REACT. A principal delas é que passar qualquer variável mais complexa que um inteiro é extremamente difícil, forçando uma refatoração das funções que iriam ser integradas com a UI.  


## Como executar o projeto com a UI?
1- Instale o package managaer NPM na sua máquina.  
2- Abra um terminal no diretório base desse repositório.  
3- Digite ```cd UI``` e pressione enter.  
2- Digite ```npm install``` e pressione enter.  
3- No mesmo terminal, digite ```npm run dev``` e pressione enter.  
4- Copie o link resultante e cole-o em um navegador de sua escolha.  
  
**IMPORTANTE:** não feche a janela do terminal enquanto estiver usando a UI  