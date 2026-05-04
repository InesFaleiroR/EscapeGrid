# projeto-final-c_EscapeGrid

## Descrição do Projeto

EscapeGrid é um jogo em C baseado numa grelha (matriz 2D), onde o jogador deve atravessar um labirinto até à saída enquanto evita um inimigo controlado por inteligência artificial.

O jogo foi desenvolvido com foco em:
- estruturas de dados (matrizes)
- lógica de jogos em terminal
- IA simples baseada em regras
- organização modular de código em C

---

## Objetivo do Jogo

O jogador controla o símbolo `@` e deve chegar ao objetivo `E` antes de ser apanhado pelo inimigo `X`.

---

## Símbolos do Jogo

- `@` → Jogador
- `E` → Saída
- `X` → Inimigo
- `.` → Caminho livre
- `═ ║ ╔ ╗ ╚ ╝` → Paredes

---

## Funcionalidades

- Movimento do jogador com WASD
- Colisão com paredes
- Labirinto em matriz 2D
- Inimigo com IA simples
- Diferentes níveis de dificuldade:
  - Fácil (movimento aleatório)
  - Médio (perseguição simples)
  - Difícil (perseguição otimizada)
- Sistema de game loop
- Estrutura modular em vários ficheiros

---

## Estrutura do Projeto

```text
EscapeGrid/
│
├── src/
│   ├── main.c  # ponto de entrada do programa
│   ├── game.c  # lógica principal do jogo (loop, estados)
│   ├── game.h  # declarações globais do jogo
│   │
│   ├── player.c # lógica do jogador (movimento, colisões)
│   ├── enemy.c  # IA do inimigo (fácil, médio, difícil)
│   ├── maze.c   # geração e manipulação do labirinto
│
├── include/
│   ├── game.h   # headers principais (separa interface do código)
│
├── assets/
│   ├── maps/   # mapas pré-definidos
│
├── logs/
│   ├── LOG.md   # registo de desenvolvimento
│
├── build/       # ficheiros compilados (opcional)
│
├── README.md   # descrição do projeto
├── Makefile    # compilação automática
│
└── .gitignore     # ficheiros a ignorar no GitHub
