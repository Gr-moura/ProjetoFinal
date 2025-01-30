# UI


## Objetivo
O objetivo da UI do projeto é melhorar a experiância do usuárioa ao interagir com o código em c++.  
O código em c++ pode ser tanto rodado usando a UI como diretamente no terminal. Para executar o código com a UI, siga as instruções disponóveis mais a frente.  


## Solução
A solução usada para desenvolver a UI foi o REACT. Usando código em javascript, desenvolvemos uma interface gráfica para o projeto que pode ser executada diretamente em qualquer navegador.  
Podemos dividir, de uma forma geral, a UI entre telas e componentes.  

### O worflow REACT
O react trabalha usando html, css, e javascript para criar páginas web.  
O diferencial que o usa do REACT proporciona é a capacidade de criar "componentes": Funções que podem ser chamadas como tags html. A criação de componentes proporciona uma facilidade imensa em criar partes reutilizáveis para o site.  
Além disso, o REACT proporciona diversos outros beneficios, como a renderização condicional (usando "state variables" é possível re-renderizar apenas as partes do site que sofreram mudanças, melhorando o desempenho da aplicação) e as routes (forma de navegar entre as páginas do site sem ter que recarregar a janela).

### Telas
#### Seleção de jogadores (PlayerSelection)
A tela inicial da UI é a seleção de jogadores. Nela, você pode criar, selecionar e deletar jogadores.  
Essa tela usa o "Local Storage" do navegador para guardar os dados dos jogadores e mostrá-los na tela (vitórias, derrotas e empates).  
#### Seleção de jogos (Menu)
Após a seleção de jogadores, uma tela para escolher os jogos é apresentada. Nessa tela, os jogadores também tem acesso a uma descrição de cada jogo.  
Além disso é possível escolher a dificuldade da IA, caso o jogador 2 escolhido seja um bot.  
#### Tabuleiro (Board)
Essa tela renderiza de forma dinâmica um tabuleiro para cada jogo. Além disso, nela são chamadas as implementações das regras de cada jogo para verificar vitórias ou derrotas.  
A tela controla a verificação de vitória e derrota, as jogadas (tanto do jogador como da IA), e as regras de cada jogo.  
A verificação de vitória, derrota e as regras foram implementadas em C++ e conectadas à tela depois de serem compiladas em WASM (WebAssembly).
#### Outras telas (DebugMenu)
Por fim, a UI contém algumas telas que foram usadas para testar o código durante a fase de desenvolvimento, e não são acessíveis ao usuário.  


## Problemas encontrados durante o desenvolvimento
- Arquivos locais não podem ser modificados: Como a UI é executada diretamente no navegador como um site, modificar arquivos locais é impossível. Devido à medidas de segurança implementadas nos navegadores e no próprio REACT, modificar o arquivo de texto local usado para armazenar jogadores depois de cada partida é uma falha de segurança grave, pois seria equivalente a permitir que um site modifique arquivos em seu computador. Logo, a solução encontrada foi usar o "Local Storage": Dados em formato JSON que ficam armazenados diretamente no navegador do usuário, e podem ser acessados e modificados facilmente pelo site que os armazenou.
- Integração direta com o código em C++: 


## Como rodar?
1- Instale o package managaer NPM na sua máquina  
2- Abra um terminal no diretório UI  
2- Digite ```npm install``` e pressione enter  
3- No mesmo terminal, digite ```npm run dev```  
4- Copie o link resultante e cole-o em um navegador de sua escolha  
  
IMPORTANTE: não feche a janela do terminal enquanto estiver usando a UI  
