# LOG.md — EscapeGrid

## Projeto: EscapeGrid
## Linguagem: C
## Tipo: Jogo de labirinto com IA

---

# Dia 1 — Definição do projeto e preparação (4h)

## Objetivos
- Definir o tema do projeto
- Criar repositório no GitHub
- Pesquisar conceitos necessários
- Criar estrutura inicial do projeto
- Iniciar o LOG.md

## Trabalho realizado

### Definição do projeto
Foi definido o projeto **EscapeGrid**, um jogo em C baseado num labirinto em matriz 2D.  
O jogador controla um personagem que deve chegar à saída enquanto evita um inimigo com IA.

Elementos definidos:
- Jogador: @
- Saída: E
- Inimigo: X
- Caminho livre: .
- Paredes : ═ ║ ╔ ╗ ╚ ╝

### GitHub
- Criado repositório EscapeGrid
- Estrutura inicial adicionada
- Primeiro commit realizado

### Pesquisa
- Matrizes em C
- Game loop básico
- Input de teclado (WASD)
- Lógica básica de IA em jogos

## Dificuldades
- Ainda não existe implementação, apenas definição e pesquisa

## Conclusão
Projeto bem definido e pronto para desenvolvimento da base do jogo.

# Dia 2 — Base do jogo (4h)

## Objetivos
- Criar o esqueleto funcional do jogo
- Implementar a base jogável no terminal
- Organizar o código de forma modular

## Trabalho realizado

### Estrutura do jogo
Foi implementado o **game loop principal**, responsável por controlar o fluxo do jogo.

O ciclo foi dividido em:
- Inicialização do jogo (`initGame`)
- Atualização do estado (`gameLoop`)
- Renderização no terminal (`drawGame`)

O código foi distribuído por vários ficheiros para melhor organização.

---

### Mapa em matriz
Foi criado um labirinto simples utilizando uma **matriz 2D**.

Elementos implementados:
- Caminhos livres (`.`)
- Paredes (`#`)
- Jogador (`@`)
- Saída (`E`)

O mapa é apresentado diretamente no terminal através de ciclos `for`.

---

### Movimento do jogador
Foi implementado o sistema de movimento com teclas **WASD**.

Funcionalidades:
- Cálculo da nova posição do jogador
- Verificação de colisão com paredes
- Atualização da posição apenas se o movimento for válido

---

### GitHub
- Código organizado em múltiplos ficheiros:
  - `main.c`
  - `game.c`
  - `player.c`
  - `maze.c`
  - `enemy.c`
- Commit do progresso realizado
- Atualização do ficheiro `LOG.md`

---

## Dificuldades
- Erros de compilação ao tentar compilar apenas um ficheiro (`main.c`)
- Problemas ao navegar entre diretórios no terminal (PowerShell)
- Compreensão inicial do funcionamento do Makefile

## Conclusão
Foi criada uma base funcional do jogo **EscapeGrid**, já com:
- Estrutura modular
- Renderização no terminal
- Movimento do jogador com colisões

O projeto encontra-se pronto para evolução com:
- Inteligência artificial do inimigo
- Geração dinâmica de labirintos
- Melhorias visuais