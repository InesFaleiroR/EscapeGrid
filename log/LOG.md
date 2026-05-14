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