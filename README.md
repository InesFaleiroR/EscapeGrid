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

# Big Update
## Estrutura do projeto NOVO
  ✖✔ ☑ ☒  ❌ ✅ ✔️   ● ○ ☐ ■ □★ ☆
EscapeGrid/
├── .vscode/
│   ├── tasks.json  ✅*New
│   └── launch.json ✅*New
├── include/
│   ├── game.h      ✅
│   ├── maze.h      ✅*New
│   ├── enemy.h     ✅*New
│   ├── render.h    ✅*New
│   ├── input.h     ✅*New
│   ├── timer.h     ✅*New
│   ├── utils.h     ✅*New
│   └── ranking.h   ✅*New
├── src/
│   ├── main.c      ✅
│   ├── game.c      ✅
│   ├── maze.c      ✅
│   ├── enemy.c     ✅
│   ├── render.c    ✅*New
│   ├── input.c     ✅*New
│   ├── timer.c     ✅*New
│   ├── utils.c     ✅*New
│   └── ranking.c   ✅*New
├── data/
│   └── ranking.txt ✅*New
└── Makefile


### Controlos
Durante o jogo:
W A S D        mover
Setas          mover
R              reiniciar nível
Q              voltar ao menu

## EscapeGrid: Labirinto Inteligente — Jogo Completo em C para Terminal

Este projeto é um jogo de terminal desenvolvido em C, inspirado no estilo PACMAN, com geração procedural de labirintos, IA adaptativa com pathfinding BFS, temporizador, sistema de ranking local, múltiplos níveis e gráficos Unicode coloridos via sequências ANSI. Foi concebido para compilar e correr no Visual Studio Code com terminal Windows (PowerShell, cmd.exe ou Windows Terminal no Windows 10/11).

---

## Visão Geral do Projeto

O **EscapeGrid Premium** é uma evolução profissional e modular de um jogo de labirinto para terminal. O jogador navega por labirintos gerados aleatoriamente, evitando um inimigo com IA inteligente, dentro de um tempo limitado. O objetivo é alcançar a saída verde antes que o tempo acabe ou o inimigo o apanhe.

---

## Funcionalidades Principais

- **Labirinto gerado aleatoriamente** com algoritmo DFS recursivo — cada partida é única
- **IA do inimigo melhorada com BFS** — o inimigo encontra caminhos reais até ao jogador e tenta prever a sua direção
- **3 níveis de dificuldade** (Fácil, Médio, Difícil) que afetam velocidade da IA, tempo disponível e agressividade de previsão
- **5 níveis progressivos** — a campanha termina ao completar o nível 5
- **Menu inicial** com opções de novo jogo, ranking e sair
- **Reinício rápido** com a tecla R durante a partida
- **Ranking local** guardado em ficheiro (`data/ranking.txt`) com os 10 melhores resultados
- **Gráficos Unicode** com blocos `██` coloridos via sequências ANSI
- **Temporizador** que diminui a cada nível, aumentando a pressão
- **Controlos** por WASD ou setas direcionais

---

## Mapeamento Visual

| Elemento |   Cor   |  Código ANSI |     Glifo    |
|----------|---------|--------------|--------------|
| Parede   |   Azul  |  `\x1b[94m`  |     `██`     |
| Jogador  | Amarelo | `\x1b[1;93m` |     `██`     |
| Inimigo  |Vermelho | `\x1b[1;91m` |     `██`     |
| Saída    |  Verde  | `\x1b[1;92m` |     `██`     |
| Moldura  | Branco  |  `\x1b[97m`  |     `██`     |
| Caminho  |    -    |   (sem cor)  | espaço vazio |

---

## Estrutura Modular do Projeto

O código está dividido em 9 módulos fonte e 8 cabeçalhos, organizados profissionalmente:

- **main.c** — ciclo principal e gestão de estados (menu, jogo, vitória, derrota, ranking)
- **game.c** — inicialização, configuração de dificuldade, transição de níveis
- **maze.c** — geração procedural do labirinto com DFS recursivo
- **enemy.c** — IA com BFS completo e previsão adaptativa da posição do jogador
- **render.c** — desenho do labirinto, HUD, ecrãs de vitória/derrota com cores ANSI
- **input.c** — leitura de teclas (WASD, setas, R para reiniciar, Q para menu)
- **timer.c** — controlo do tempo restante por nível
- **utils.c** — configuração da consola Windows (UTF-8, ANSI, cursor)
- **ranking.c** — persistência de pontuações em ficheiro com ordenação

---

## Dificuldades e Progressão

| Nível de Dificuldade |       Velocidade IA        | Tempo Inicial | Bias de Previsão |
|----------------------|----------------------------|---------------|------------------|
| Fácil                | Lenta (cada 3 movimentos)  |      90s      |      20%         |
| Médio                | Normal (cada 2 movimentos) |      75s      |      45%         |
| Difícil              | Rápida (cada movimento)    |      60s      |      70%         |

O tempo diminui em cada nível progressivo, com um mínimo de 25 segundos nos níveis finais.

---

## Como Compilar e Jogar

A compilação requer `gcc` (MinGW/TDM-GCC) e faz-se com um único comando no terminal do VS Code:

```
gcc -Wall -Wextra -std=c11 src/*.c -Iinclude -o EscapeGrid.exe
.\EscapeGrid.exe
```

O jogo abre com um menu onde o jogador introduz o nome, escolhe a dificuldade e começa imediatamente a jogar.

---

## Resumo

O EscapeGrid Premium é um projeto completo, profissional e pronto a entregar, que combina geração procedural, inteligência artificial com BFS, persistência de dados, interface colorida em Unicode e uma estrutura de código modular. A experiência de jogo escala em dificuldade ao longo de 5 níveis, com um inimigo cada vez mais inteligente e menos tempo disponível — oferecendo uma combinação de estratégia, reflexos e diversão diretamente no terminal.