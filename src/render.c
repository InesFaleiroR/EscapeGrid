#include <stdio.h>

#include "../include/render.h"
#include "../include/ranking.h"
#include "../include/timer.h"

/* ══════════════════════════════════════════════════════════
   PALETA NEONPUNK
   ══════════════════════════════════════════════════════════ */
#define C_RESET   "\x1b[0m"
#define C_BLUE    "\x1b[1;94m"
#define C_YELLOW  "\x1b[1;93m"
#define C_RED     "\x1b[1;91m"
#define C_GREEN   "\x1b[1;92m"
#define C_CYAN    "\x1b[1;96m"
#define C_MAGENTA "\x1b[1;95m"
#define C_WHITE   "\x1b[97m"
#define C_DIM     "\x1b[2m"

/* ══════════════════════════════════════════════════════════
   GLYPHS DE PERSONAGENS/ELEMENTOS  (2 colunas cada)
   ══════════════════════════════════════════════════════════ */
#define GLYPH_PLAYER   C_YELLOW  "\u25D3 " C_RESET  /* ◓   Pac-Man amarelo neon   */
#define GLYPH_ENEMY    C_RED     "\u25A6 " C_RESET  /* ▦   Fantasma vermelho      */
#define GLYPH_NPC      C_MAGENTA "\u2591\u2591" C_RESET /* ░░ Bruma magenta       */
#define GLYPH_KEY      C_GREEN   "\u2666\u2666" C_RESET /* ♦♦ Cristais verdes     */
#define GLYPH_DOOR     C_CYAN    "\u25EB " C_RESET  /* ◫   Portal ciano           */
#define GLYPH_DOOR_LK  C_RED     "\u25EB " C_RESET  /* ◫   Portal bloqueado       */
#define GLYPH_POWERUP  C_GREEN   "\u00B7 " C_RESET  /* ·   Power-up verde         */
#define GLYPH_FOG      C_DIM     "\u2592\u2592" C_RESET /* ▒▒ Névoa               */
#define GLYPH_EMPTY    "  "                          /* escuridão do corredor      */

/* ── Blocos de parede (borda sólida) ─── */
#define GLYPH_BORDER   C_BLUE "\u2588\u2588" C_RESET  /* ██ borda exterior */

/* ══════════════════════════════════════════════════════════
   RENDERIZAÇÃO DE PAREDES CONTEXTUAIS
   Cada célula de parede usa o bloco que melhor descreve a
   sua relação com os vizinhos — criando o efeito de paredes
   finas e obstáculos isolados estilo labirinto retro.

   Blocos disponíveis (2 colunas = duplicados para preencher):
     ■  U+25A0  obstáculo isolado / pastilha grande
     ▀  U+2580  meia-célula superior
     ▄  U+2584  meia-célula inferior
     ▌  U+258C  meia-célula esquerda
     ▐  U+2590  meia-célula direita
     █  U+2588  bloco completo (interiores densos)
   ══════════════════════════════════════════════════════════ */
static void printWallCell(const Game *game, int x, int y) {
    /* vizinhos que também são paredes */
    int t = (y > 0)             && (game->maze[y-1][x] == CELL_WALL);
    int b = (y < MAZE_HEIGHT-1) && (game->maze[y+1][x] == CELL_WALL);
    int l = (x > 0)             && (game->maze[y][x-1] == CELL_WALL);
    int r = (x < MAZE_WIDTH-1)  && (game->maze[y][x+1] == CELL_WALL);
    int n = t + b + l + r;

    printf(C_BLUE);

    if (n == 0) {
        /* ■   – obstáculo isolado (sem vizinhos) */
        printf("\u25A0 ");

    } else if (n >= 3 || (t && b && l && r)) {
        /* ██  – interior denso / cruzamento */
        printf("\u2588\u2588");

    } else if (t && b && !l && !r) {
        /* ▌▐  – passagem vertical (parede separa corredores H) */
        printf("\u258C\u2590");

    } else if (!t && !b && l && r) {
        /* ▀▄  – passagem horizontal (parede separa corredores V) */
        printf("\u2580\u2584");

    } else if (!t && b && !l && !r) {
        /* ▄▄  – cápsula superior (corredor acima) */
        printf("\u2584\u2584");

    } else if (t && !b && !l && !r) {
        /* ▀▀  – cápsula inferior (corredor abaixo) */
        printf("\u2580\u2580");

    } else if (!t && !b && !l && r) {
        /* ▌   – borda esquerda (corredor à esquerda) */
        printf("\u258C ");

    } else if (!t && !b && l && !r) {
        /* ▐   – borda direita (corredor à direita) */
        printf("\u2590 ");

    } else if (!t && b && l && !r) {
        /* ▀▄  – canto superior-esquerdo */
        printf("\u2580\u2584");

    } else if (!t && b && !l && r) {
        /* ▄▄  – canto superior-direito */
        printf("\u2584\u2584");

    } else if (t && !b && l && !r) {
        /* ▀▀  – canto inferior-esquerdo */
        printf("\u2580\u2580");

    } else if (t && !b && !l && r) {
        /* ▌▐  – canto inferior-direito */
        printf("\u258C\u2590");

    } else {
        /* ██  – fallback sólido */
        printf("\u2588\u2588");
    }

    printf(C_RESET);
}

/* ══════════════════════════════════════════════════════════
   UTILITÁRIOS
   ══════════════════════════════════════════════════════════ */
void clearScreen(void) {
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
}

static void moveCursor(int row, int col) {
    printf("\x1b[%d;%dH", row, col);
}

/* ══════════════════════════════════════════════════════════
   MENU PRINCIPAL
   ══════════════════════════════════════════════════════════ */
void renderMenu(void) {
    clearScreen();

    printf(C_CYAN
        "\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550"
        "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550"
        "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550"
        "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\n"
        "\u2551" C_YELLOW
        "       \u25D3  E S C A P E G R I D  \u25D3       " C_CYAN
        "\u2551\n"
        "\u2551" C_MAGENTA
        "            N E O N P U N K             " C_CYAN
        "\u2551\n"
        "\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550"
        "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550"
        "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550"
        "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\n"
        C_RESET "\n");

    printf("  " C_GREEN  "[ 1 ]" C_WHITE " Novo Jogo\n" C_RESET);
    printf("  " C_YELLOW "[ 2 ]" C_WHITE " Ranking\n"   C_RESET);
    printf("  " C_RED    "[ 3 ]" C_WHITE " Sair\n\n"    C_RESET);

    printf(C_DIM "  WASD / Setas \u2502 Q menu \u2502 P pausa\n" C_RESET "\n");

    printf(C_CYAN "  Escolha: " C_RESET);
    fflush(stdout);
}

/* ══════════════════════════════════════════════════════════
   ECRÃ DE SELECÇÃO DE DIFICULDADE
   ══════════════════════════════════════════════════════════ */
void renderDifficultyScreen(void) {
    clearScreen();

    printf(C_CYAN
        "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2513\n"
        "\u2503" C_YELLOW
        "        ESCOLHA A DIFICULDADE         " C_CYAN
        "\u2503\n"
        "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u251B\n"
        C_RESET "\n");

    printf("  " C_GREEN  "[ 1 ]" C_WHITE " F\u00e1cil   "
           C_DIM "– labirinto aberto, inimigo lento, NPC presente\n" C_RESET);
    printf("  " C_YELLOW "[ 2 ]" C_WHITE " M\u00e9dio   "
           C_DIM "– chave obrigat\u00f3ria, inimigo moderado\n"       C_RESET);
    printf("  " C_RED    "[ 3 ]" C_WHITE " Dif\u00edcil "
           C_DIM "– n\u00e9voa, inimigo r\u00e1pido e preditivo\n\n"  C_RESET);

    printf(C_CYAN "  Escolha: " C_RESET);
    fflush(stdout);
}

/* ══════════════════════════════════════════════════════════
   HUD
   ══════════════════════════════════════════════════════════ */
static void renderHUD(Game *game) {
    const char *diffStr[]   = { "", "FACIL", "MEDIO", "DIFICIL" };
    const char *diffColor[] = { "", C_GREEN, C_YELLOW, C_RED };
    int d = (int)game->difficulty;
    if (d < 1 || d > 3) d = 2;

    printf(C_CYAN "\u2554\u2550\u2550 " C_RESET);
    printf("%s%-7s" C_RESET, diffColor[d], diffStr[d]);
    printf(C_CYAN " \u2550\u2550 " C_RESET);
    printf(C_WHITE "N\u00edvel " C_YELLOW "%2d" C_RESET, game->level);
    printf(C_CYAN " \u2550\u2550 " C_RESET);
    printf(C_WHITE "Pontos " C_GREEN "%5d" C_RESET, game->score);
    printf(C_CYAN " \u2550\u2550 " C_RESET);

    if (game->timeRemaining <= 15)
        printf(C_RED "\u23f1 %3ds" C_RESET, game->timeRemaining);
    else
        printf(C_WHITE "\u23f1 " C_CYAN "%3ds" C_RESET, game->timeRemaining);

    if (game->keyRequired) {
        if (game->hasKey)
            printf(C_GREEN " [\u2666 CHAVE \u2713]" C_RESET);
        else
            printf(C_RED   " [\u2666 CHAVE \u2717]" C_RESET);
    }

    if (game->slowEnemyTicks > 0)
        printf(C_MAGENTA " [SLOW %d]" C_RESET, game->slowEnemyTicks);

    printf(C_CYAN " \u2557\n" C_RESET);
}

/* ══════════════════════════════════════════════════════════
   JOGO EM CURSO
   ══════════════════════════════════════════════════════════ */
void renderGame(Game *game) {
    int x, y;

    updateTimer(game);
    if (game->state != STATE_PLAYING) return;

    moveCursor(1, 1);
    renderHUD(game);

    /* borda superior */
    for (x = 0; x < MAZE_WIDTH + 2; x++) printf(GLYPH_BORDER);
    printf("\n");

    for (y = 0; y < MAZE_HEIGHT; y++) {
        printf(GLYPH_BORDER);  /* borda esquerda */

        for (x = 0; x < MAZE_WIDTH; x++) {

            /* ── Névoa ─────────────────────────────── */
            if (game->fogEnabled && game->fogRadius > 0) {
                int ddx  = game->player.x - x;
                int ddy  = game->player.y - y;
                int dist = (ddx < 0 ? -ddx : ddx) + (ddy < 0 ? -ddy : ddy);
                if (dist > game->fogRadius) {
                    printf(GLYPH_FOG);
                    continue;
                }
            }

            /* ── Personagens (prioridade sobre células) */
            if (x == game->player.x && y == game->player.y) {
                printf(GLYPH_PLAYER); continue;
            }
            if (x == game->enemy.x && y == game->enemy.y) {
                printf(GLYPH_ENEMY); continue;
            }
            if (game->npcActive &&
                x == game->npcPos.x && y == game->npcPos.y) {
                printf(GLYPH_NPC); continue;
            }

            /* ── Células do labirinto ─────────────── */
            switch (game->maze[y][x]) {
                case CELL_WALL:
                    printWallCell(game, x, y);
                    break;
                case CELL_EXIT:
                   if (game->keyRequired && !game->hasKey) {
                       printf(GLYPH_DOOR_LK);
                    } else {
                       printf(GLYPH_DOOR);
                    }
                    break;
                case CELL_KEY:
                    printf(GLYPH_KEY);
                    break;
                case CELL_POWERUP:
                    printf(GLYPH_POWERUP);
                    break;
                case CELL_NPC:
                    printf(GLYPH_NPC);
                    break;
                default:
                    printf(GLYPH_EMPTY);
                    break;
            }
        }

        printf(GLYPH_BORDER "\n");  /* borda direita */
    }

    /* borda inferior */
    for (x = 0; x < MAZE_WIDTH + 2; x++) printf(GLYPH_BORDER);
    printf("\n");

    /* legenda */
    printf(C_DIM
        "  WASD/Setas: mover  \u2502  Q: menu  \u2502  P: pausa  \u2502  R: reiniciar\n"
        C_RESET);

    /* mensagem NPC */
    if (game->npcActive && game->npcTalked)
        printf(C_MAGENTA
            "  NPC: \"A sa\u00edda est\u00e1 no canto inferior direito!\"\n"
            C_RESET);
    else
        printf("\n");

    fflush(stdout);
}

/* ══════════════════════════════════════════════════════════
   PAUSA
   ══════════════════════════════════════════════════════════ */
void renderPauseScreen(Game *game) {
    (void)game;
    clearScreen();
    printf(C_CYAN
        "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2513\n"
        "\u2503" C_YELLOW "                PAUSA         " C_CYAN "\u2503\n"
        "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u251B\n\n"
        C_RESET);
    printf("  " C_GREEN "[ P ]" C_WHITE " Retomar\n"          C_RESET);
    printf("  " C_RED   "[ Q ]" C_WHITE " Voltar ao menu\n\n" C_RESET);
    fflush(stdout);
}

/* ══════════════════════════════════════════════════════════
   VITÓRIA
   ══════════════════════════════════════════════════════════ */
void renderVictory(Game *game) {
    clearScreen();
    printf(C_GREEN
        "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2513\n"
        "\u2503" C_YELLOW
        "      \u2756 VITOR\u00cdA! PARAB\u00c9NS! \u2756      "
        C_GREEN "\u2503\n"
        "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u251B\n\n"
        C_RESET);

    printf(C_WHITE "  Jogador : " C_YELLOW "%s\n" C_RESET, game->playerName);
    printf(C_WHITE "  Pontos  : " C_GREEN  "%d\n" C_RESET, game->score);
    printf(C_WHITE "  N\u00edvel   : " C_CYAN   "%d\n" C_RESET, game->level);
    printf("\n" C_DIM "  Prima qualquer tecla para voltar ao menu...\n" C_RESET);
    fflush(stdout);
}

/* ══════════════════════════════════════════════════════════
   GAME OVER
   ══════════════════════════════════════════════════════════ */
void renderGameOver(Game *game) {
    clearScreen();
    printf(C_RED
        "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2513\n"
        "\u2503" C_RED
        "           \u2716  GAME OVER  \u2716           "
        C_RED "\u2503\n"
        "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u251B\n\n"
        C_RESET);

    printf(C_WHITE "  Jogador : " C_YELLOW "%s\n" C_RESET, game->playerName);
    printf(C_WHITE "  Pontos  : " C_GREEN  "%d\n" C_RESET, game->score);
    printf(C_WHITE "  N\u00edvel   : " C_CYAN   "%d\n" C_RESET, game->level);
    printf("\n" C_DIM "  Prima qualquer tecla para voltar ao menu...\n" C_RESET);
    fflush(stdout);
}

/* ══════════════════════════════════════════════════════════
   RANKING  (alinhamento de tabela preservado)
   ══════════════════════════════════════════════════════════ */
void renderRankingScreen(void) {
    clearScreen();

    printf(C_YELLOW
        "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2513\n"
        "\u2503" C_YELLOW
        "           \u2605  TOP PLAYERS  \u2605           "
        C_YELLOW "\u2503\n"
        "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501"
        "\u2501\u2501\u2501\u2501\u251B\n\n"
        C_RESET);

    /* cabeçalho da tabela */
    printf(C_CYAN "  %-4s %-18s %-10s %-8s %-8s\n" C_RESET,
           "POS", "NOME", "SCORE", "NIVEL", "DIFIC");
    printf(C_DIM
        "  \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500"
        "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500"
        "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500"
        "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500"
        "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\n"
        C_RESET);

    printRankingTable();

    printf("\n" C_DIM "  Prima qualquer tecla para voltar ao menu...\n" C_RESET);
    fflush(stdout);
}