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


# Dia 3 — Melhorias finais e sistema completo (4h)

## Objetivos
- Adicionar menu principal
- Implementar reinício de nível
- Criar sistema de ranking
- Adicionar múltiplos níveis
- Melhorar a IA do inimigo
- Melhorar a apresentação visual

## Trabalho realizado

### Controlos
Foram adicionados novos controlos para melhorar a jogabilidade.

Durante o jogo:

W A S D        mover  
Setas          mover  
R              reiniciar nível  
Q              voltar ao menu  

---

### Menu principal
Foi implementado um menu inicial com as opções:
- Novo jogo
- Ranking
- Sair

O jogador pode navegar pelo menu antes de iniciar a campanha.

---

### Reinício de nível
Foi implementada a funcionalidade de reinício rápido do nível atual.

Ao pressionar a tecla R:
- O jogador volta à posição inicial
- O inimigo reinicia a posição
- O mapa é restaurado

---

### Sistema de ranking
Foi criado um sistema simples de pontuações.

As pontuações ficam guardadas em:
- data/ranking.txt

Funcionalidades:
- Guardar pontuações
- Ler pontuações guardadas
- Mostrar ranking no menu

---

### Múltiplos níveis
O jogo passou a ter vários níveis.

Características:
- Progressão automática
- Dificuldade crescente
- Final da campanha no nível 5

---

### IA melhorada
A inteligência artificial do inimigo foi melhorada utilizando BFS (Breadth-First Search).

Funcionalidades da IA:
- Procura do caminho mais curto até ao jogador
- Tentativas de interceção
- Previsão simples da direção da saída

O inimigo tornou-se mais eficiente e desafiante.

---

### Melhorias visuais
Foi implementado o sistema final de cores no terminal.

Mapeamento de cores:
- Parede   -> Azul      -> ██
- Jogador  -> Amarelo   -> ██
- Inimigo  -> Vermelho  -> ██
- Saída    -> Verde     -> ██
- Moldura  -> Branco    -> ██
- Caminho  -> vazio

As cores utilizam códigos ANSI para melhorar a aparência do jogo.

---

### Compatibilidade do terminal
Foi identificado que alguns terminais do VS Code podem não apresentar corretamente:
- Unicode
- ANSI
- Cores

Recomendação:
- Utilizar Windows Terminal
- Ou configurar o VS Code para usar PowerShell moderno

---

### GitHub
- Novos commits realizados
- Atualização completa do projeto
- Organização adicional dos ficheiros
- Atualização do LOG.md

---

## Dificuldades
- Implementação da IA BFS
- Gestão de múltiplos níveis
- Compatibilidade entre terminais
- Leitura e escrita do ranking em ficheiros

## Conclusão
O projeto **EscapeGrid** evoluiu para uma versão muito mais completa.

Funcionalidades implementadas:
- Menu principal
- Sistema de ranking
- Reinício de nível
- Campanha com múltiplos níveis
- IA baseada em BFS
- Interface colorida no terminal
- Estrutura modular organizada

O projeto encontra-se funcional e preparado para futuras melhorias.

# Melhorias futuras possíveis

## Sistema de jogo
- Pausa com tecla P
- Power-ups
- Sistema de vidas
- Vários inimigos
- Campo de visão
- Geração procedural de mapas
- Boss final
- Sons com Beep
- Guardado automático
- Animações de transição

## Melhorias de IA
- Utilização de algoritmo A*
- Estados de patrulha/perseguição/interceção
- Memória dos movimentos do jogador
- Dificuldade dinâmica

## Melhorias visuais
- Menus mais avançados
- Logo ANSI Art
- HUD com tempo e pontuação
- Caixa de mensagens
- Efeitos visuais

## Organização do projeto
- README profissional
- Comentários académicos
- Arquitetura mais limpa e modular


========================================================================================================================================================================================================================================

# LOG mais Organizado (Final)
# LOG.md — EscapeGrid

## Projeto: EscapeGrid

## Linguagem: C (C11)

## Tipo: Jogo de labirinto com IA e estética Neonpunk

---

# Dia 1 — Definição do projeto e arquitetura (4h)

## Objetivos

* Definir o tema, estética e mecânicas do jogo
* Planear a estrutura modular do projeto em C
* Criar os ficheiros de cabeçalho (.h)
* Definir constantes globais e enumerações
* Criar o Makefile para compilação automática

## Trabalho realizado

### Definição do projeto

Foi definido o projeto EscapeGrid, um jogo de labirinto em terminal para Windows com estética Neonpunk inspirada no Pac-Man.

O jogador controla uma personagem num labirinto gerado proceduralmente e deve chegar à saída enquanto evita um inimigo com inteligência artificial.

### Elementos visuais definidos

* Jogador → ◓ (Amarelo)
* Inimigo → ▦ (Vermelho)
* NPC → ░░ (Magenta)
* Chave → ♦♦ (Verde)
* Porta → ◫ (Ciano)
* Power-up → ★ (Branco)
* Parede → █ ■ ▀ ▄ ▌ ▐ (Azul)

### Estrutura modular

EscapeGrid/

include/

* game.h
* enemy.h
* input.h
* maze.h
* pathfinding.h
* powerups.h
* ranking.h
* render.h
* timer.h
* utils.h

src/

* main.c
* game.c
* maze.c
* enemy.c
* pathfinding.c
* render.c
* input.c
* powerups.c
* ranking.c
* timer.c
* utils.c

### Estruturas e tipos principais

Position

* Estrutura responsável pelas coordenadas do labirinto.

GameState

* STATE_MENU
* STATE_DIFFICULTY
* STATE_PLAYING
* STATE_PAUSED
* STATE_GAME_OVER
* STATE_WIN
* STATE_RANKING

CellType

* CELL_EMPTY
* CELL_WALL
* CELL_EXIT
* CELL_KEY
* CELL_POWERUP
* CELL_NPC

Difficulty

* EASY
* MEDIUM
* HARD

Game
Estrutura principal contendo:

* Labirinto
* Posições do jogador, inimigo e NPC
* Flags de estado
* Pontuação
* Temporizador
* Sistema de power-ups

### Makefile

Foram criadas as seguintes tarefas:

* make
* make all
* make run
* make clean

Flags utilizadas:
-Wall -Wextra -std=c11 -Iinclude

### GitHub

* Repositório criado
* Estrutura inicial enviada
* Primeiro commit realizado

### Dificuldades

* Planeamento da arquitetura do jogo
* Organização das estruturas de dados

### Conclusão

Projeto totalmente definido e preparado para implementação das mecânicas principais.

---

# Dia 2 — Motor de jogo e mecânicas base (4h)

## Objetivos

* Implementar geração procedural de labirintos
* Criar o game loop
* Implementar movimento do jogador
* Criar renderização no terminal
* Desenvolver sistema de dificuldade

## Trabalho realizado

### Geração procedural de labirintos (maze.c)

Foi implementado o algoritmo Recursive Backtracker (DFS) para gerar labirintos solucionáveis.

Processo:

* Inicialização da grelha
* DFS recursivo
* Colocação da saída
* Verificação de solvabilidade com BFS

### Elementos do mapa

* Chave em Médio e Difícil
* NPC em Fácil e Médio
* Power-ups espalhados aleatoriamente

### Máquina de estados (main.c)

Estados implementados:

* STATE_MENU
* STATE_DIFFICULTY
* STATE_PLAYING
* STATE_PAUSED
* STATE_GAME_OVER
* STATE_WIN
* STATE_RANKING

### Movimento do jogador (input.c)

Controlos:

* WASD
* Setas direcionais
* P → pausa
* Q → sair

Sistema de colisões:

* Parede bloqueia
* Chave recolhida
* Power-up ativado
* Inimigo provoca derrota
* NPC ativa diálogo

### Sistema de dificuldade (game.c)

Fácil:

* Sem névoa
* NPC ativo
* Mais tempo

Médio:

* Chave obrigatória
* Tempo moderado

Difícil:

* Névoa de guerra
* Inimigo rápido
* Menos tempo

### Temporizador (timer.c)

Sistema criado com:

* time_t
* difftime()

Quando o tempo chega a zero:

* STATE_GAME_OVER

### Utilitários Windows (utils.c)

Configuração:

* UTF-8
* ANSI
* Cursor oculto
* Sleep wrapper

### GitHub

* Commits por módulo
* Atualização do LOG.md

### Dificuldades

* Garantir solvabilidade do labirinto
* Gestão do timing sem bloquear input
* Compilação no PowerShell

### Conclusão

Motor de jogo totalmente funcional com:

* Labirintos procedurais
* Movimento completo
* Sistema de dificuldade
* Game loop operacional

---

# Dia 3 — Sistemas avançados, IA e visual Neonpunk (4h + 2h)

## Objetivos

* Implementar IA com BFS
* Criar renderização contextual
* Adicionar névoa de guerra
* Criar ranking persistente
* Implementar power-ups
* Corrigir avisos do compilador

## Trabalho realizado

### Pathfinding BFS (pathfinding.c)

pathExists()

* Verifica existência de caminho.

bfsNextStep()

* Calcula o próximo movimento ótimo do inimigo.

### Inteligência artificial (enemy.c)

Estratégias:

* Perseguição direta
* Previsão do movimento do jogador

Sistema de velocidade:

* Movimento controlado por ticks
* Power-up desacelera inimigo

### Power-ups (powerups.c)

Sistema implementado:

* Colocação automática
* Efeito de lentidão
* Duração temporária

HUD apresenta:
[SLOW N]

### NPC

Funcionalidades:

* Dá dicas ao jogador
* Interação automática
* Apenas em Fácil e Médio

Mensagem:
"A saída está no canto inferior direito!"

### Sistema de ranking (ranking.c)

Ficheiro:
data/ranking.txt

Funções:

* loadRanking()
* saveRanking()
* insertRanking()

Formato:
nome;pontuacao;nivel;dificuldade

### Renderização Neonpunk (render.c)

Sistema de paredes contextuais:

* █
* ■
* ▀
* ▄
* ▌
* ▐

### Névoa de guerra

No modo Difícil:

* Apenas área próxima do jogador é visível
* Raio de visão = 4

### HUD

Informações:

* Dificuldade
* Nível
* Pontuação
* Tempo
* Estado da chave
* Power-up ativo

### Ecrãs implementados

* Menu principal
* Seleção de dificuldade
* Pausa
* Vitória
* Game Over
* Ranking

### Correção de aviso GCC

Problema:
-Wmisleading-indentation

Solução:
Adição de chavetas para remover ambiguidades.

### GitHub

* Commits organizados
* Atualização final do LOG.md

### Dificuldades

* Implementação do BFS
* Renderização contextual
* Névoa de guerra
* Sistema de ficheiros

### Conclusão

O projeto EscapeGrid ficou completo e funcional com:

* Labirintos procedurais
* IA com BFS
* Névoa de guerra
* Chave obrigatória
* NPC interativo
* Power-ups
* Sistema de ranking
* HUD completo
* Renderização Neonpunk
* Máquina de estados completa

---

# Melhorias futuras possíveis

## Sistema de jogo

* Sons com Beep()
* Sistema de vidas
* Múltiplos inimigos
* Boss final
* Guardado automático
* Animações entre níveis

## Melhorias de IA

* Algoritmo A*
* Estados de patrulha
* Memória do jogador
* Dificuldade dinâmica

## Melhorias visuais

* Logo ANSI Art avançado
* Efeito flicker Neonpunk
* Animação da porta
* Caixa de diálogo estilizada

## Organização do projeto

* README profissional
* Comentários académicos
* Testes unitários
* Suporte a múltiplas resoluções de terminal


---


## 1. Extrair o ficheiro .zip

Não é recomendado compilar ou executar ficheiros diretamente dentro da pasta compactada.

### Passos:

* Clicar com o botão direito no ficheiro `.zip`
* Selecionar:

  * **Extrair Tudo...**
* Escolher a pasta de destino
* Confirmar a extração

Exemplo:

* Área de Trabalho

---

## 2. Abrir o terminal na pasta correta

Depois de extrair os ficheiros, abrir o terminal e navegar até à pasta do projeto.

### MSYS2 MINGW64

```bash
cd "/c/Users/SeuNome/Desktop/EscapeGrid"
```

### PowerShell

```powershell
cd "C:\Users\SeuNome\Desktop\EscapeGrid"
```

Substituir:

```text
Nome_Da_Pasta_Extraida
```

pelo nome real da pasta criada após a extração.

---

## 3. Limpar ficheiros antigos (opcional)

Para evitar conflitos com executáveis antigos ou ficheiros temporários.

### MSYS2

```bash
mingw32-make clean
```

### PowerShell

Caso o `make` não esteja configurado:

* apagar manualmente:

```text
EscapeGrid.exe
```

---

## 4. Compilar o projeto

Compilar todos os ficheiros `.c` e gerar o executável atualizado.

### MSYS2

```bash
mingw32-make
```

O Makefile compila automaticamente:

* game.c
* maze.c
* render.c
* enemy.c
* pathfinding.c
* powerups.c
* ranking.c
* timer.c
* input.c
* utils.c
* main.c

---

## 5. Executar o jogo

Após compilação sem erros:

### MSYS2

```bash
./EscapeGrid.exe
```

### PowerShell

```powershell
.\EscapeGrid.exe
```

---

## Notas importantes

Caso existam erros:

* verificar se todos os ficheiros `.c` e `.h` estão presentes
* confirmar se o Makefile está atualizado
* garantir que o terminal está na pasta correta
* verificar se o GCC/MINGW64 está instalado

---