# Tabletop Renderer (por @pl1an)


## Oque é?
É uma UI básica feita para renderizar jogos simples, no estilo de GO, Reversi e Ligue 4.


## Capacidades
- Registra perfis de jogadores (onde salvar os perfis em questão fica a cargo de uma implementação posterior)
- Registra "scores" para cada perfil e cada jogo (onde serão salvos dependerá de uma integração posterior)
- Componentes para gerar um menu simples com fotos e descrições dos jogos
- O tabuleiro e a dificuldade do oponente (caso o oponente não seja outro jogador) podem ser customizados no menu
- Fornece uma tela de resultado (vitória, derrota ou empate) com botões para retornar a seleção de usuário ou jogar novamente


## Limitações
- Suporta apenas jogos com dois tipos de peça diferentes
- Jogos com inputs mais complicados (ex: certas peças não podem ser colocadas em certas casas no tabuleiro em x situações) requerem implementação adicional
- É apenas uma UI. Apesar de ter exemplos de jogos, não implementa nenhuma lógica para os jogos
- O local de armazenamento dos dados de cada perfil e seus "scores" não foi implementado.


## Como rodar?
1- Instale o package managaer NPM na sua máquina
2- Abra um terminal no diretório UI.
2- Digite ```npm install``` e pressione enter
3- No mesmo terminal, digite ```npm run dev```
4- Copie o link resultante e cole-o em um navegador de sua escolha

IMPORTANTE: não feche a janela do terminal enquanto estiver usando a UI

