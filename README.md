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
- `═ ║ ╔ ╗ ╚ ╝` → Paredes apelativas

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

### EscapeGrid — Labirinto Inteligente

Bem-vindo ao universo desafiante de "EscapeGrid", um jogo de labirinto 2D desenvolvido em C que combina estratégia, lógica e inteligência artificial! O teu objetivo? Guiar o jogador (`@`) até à saída (`E`), enquanto escapas de um inimigo (`X`) implacável e navegas por um labirinto cheio de obstáculos e surpresas.

---

### Estrutura do Projeto

O projeto foi cuidadosamente organizado para garantir clareza e escalabilidade. Aqui está a estrutura do teu próximo sucesso:

```text
0809_LAB_FINAL/
│
├── EscapeGrid/
│   ├── src/
│   │   ├── main.c       # O coração do jogo
│   │   ├── game.c       # Lógica principal e loop do jogo
│   │   ├── player.c     # Movimentos e interações do jogador
│   │   ├── enemy.c      # Inteligência artificial do inimigo
│   │   ├── maze.c       # Geração e gestão do labirinto
│   │
│   ├── include/
│   │   ├── game.h       # Cabeçalhos para modularidade
│   │
│   ├── assets/
│   │   ├── maps/        # Mapas pré-definidos do labirinto
│   │
│   ├── logs/
│   │   ├── LOG.md       # Diário de desenvolvimento
│   │
│   ├── build/           # Ficheiros compilados (opcional)
│   │
│   ├── README.md        # Descrição detalhada do projeto
│   ├── Makefile         # Automatização da compilação
│   └── .gitignore       # Ficheiros a ignorar no repositório Git
```

---

### O que já foi feito?

#### LOG.md:
O diário de bordo do projeto **EscapeGrid** já está em ação! Aqui registamos o progresso, desafios e conquistas. Até agora:

- Dia 1:
  - Definimos o conceito do jogo: um labirinto 2D com IA.  
  - Criámos a estrutura inicial do projeto.  
  - Fizemos o primeiro commit no GitHub.  
  - Realizámos pesquisas sobre matrizes, lógica de jogos em terminal, input de teclado e IA simples.

---

### .gitignore:
Para manter o repositório limpo e organizado, foram configuradas as exclusões no ficheiro `.gitignore`. Ficheiros desnecessários como objetos compilados (`*.o`, `*.exe`), pastas temporárias (`build/`, `.vscode/`, `.idea/`) e logs locais estão devidamente ignorados.

---

### Makefile:
A magia da compilação automatizada está garantida com o nosso **Makefile**. Aqui estão os comandos principais:

- `make` ou `make all`: Compila o jogo e cria o executável `EscapeGrid`.  
- `make clean`: Remove todos os ficheiros compilados, deixando o projeto limpo.  
- `make rebuild`: Limpa tudo e recompila do zero.  
- `make run`: Executa o jogo diretamente após a compilação.  

---

### Sobre o Jogo

"EscapeGrid" é mais do que um simples jogo de labirinto. É uma experiência estratégica onde cada decisão conta! Aqui estão as principais funcionalidades que te esperam:

- Movimento intuitivo: Controla o jogador (`@`) com as teclas WASD.  
- Desafios reais: Enfrenta colisões com paredes e evita o inimigo (`X`), que fica mais esperto a cada nível.  
- IA adaptativa:** Escolhe entre três níveis de dificuldade para o inimigo:
  - Fácil: Movimentos aleatórios.
  - Médio: Perseguição simples.
  - Difícil: Estratégia otimizada para te apanhar!  
- Labirintos dinâmicos: Explora mapas pré-definidos ou cria os teus próprios desafios!  

---

### Próximos Passos

Com uma base sólida já estabelecida, os próximos passos incluem implementar a lógica do jogo, criar mapas desafiantes e refinar a IA para tornar o inimigo ainda mais inteligente (e assustador!).

---

### Conclusão

O projeto "EscapeGrid" está a ganhar forma rapidamente, com uma estrutura modular robusta, ferramentas de automação eficientes e uma visão clara do que queremos alcançar. Agora é hora de dar vida ao labirinto e transformar este conceito numa experiência emocionante para os jogadores.