#include <stdio.h>

#include "../include/render.h"
#include "../include/ranking.h"
#include "../include/timer.h"

#define C_RESET   "\x1b[0m"
#define C_BLUE    "\x1b[94m"
#define C_WHITE   "\x1b[97m"
#define C_YELLOW  "\x1b[1;93m"
#define C_RED     "\x1b[1;91m"
#define C_GREEN   "\x1b[1;92m"
#define C_CYAN    "\x1b[96m"
#define C_MAGENTA "\x1b[95m"

#define GLYPH_BLOCK "██"
#define GLYPH_EMPTY "  "

void clearScreen(void) {
    printf("\x1b[2J\x1b[H");
}

void moveCursorTop(void) {
    printf("\x1b[H");
}

void renderMenu(void) {
    clearScreen();
    printf(C_CYAN "╔══════════════════════════════════════════════════════╗\n" C_RESET);
    printf(C_CYAN "║" C_RESET "             ESCAPEGRID PREMIUM  " C_CYAN "║\n" C_RESET);
    printf(C_CYAN "╠══════════════════════════════════════════════════════╣\n" C_RESET);
    printf(C_CYAN "║" C_RESET "  1. Novo Jogo                   " C_CYAN "║\n" C_RESET);
    printf(C_CYAN "║" C_RESET "  2. Ver Ranking                 " C_CYAN "║\n" C_RESET);
    printf(C_CYAN "║" C_RESET "  3. Sair                        " C_CYAN "║\n" C_RESET);
    printf(C_CYAN "╠══════════════════════════════════════════════════════╣\n" C_RESET);
    printf(C_CYAN "║" C_RESET "  Controlos                      " C_CYAN "║\n" C_RESET);
    printf(C_CYAN "║" C_RESET "  WASD ou setas para mover       " C_CYAN "║\n" C_RESET);
    printf(C_CYAN "║" C_RESET "  R reinicia nível | Q volta menu" C_CYAN "║\n" C_RESET);
    printf(C_CYAN "╚══════════════════════════════════════════════════════╝\n" C_RESET);
    printf("\nEscolha uma opção: ");
}

static void printHud(Game *game) {
    const char *diffText = "MEDIUM";
    if (game->difficulty == DIFFICULTY_EASY) {
        diffText = "EASY";
    } else if (game->difficulty == DIFFICULTY_HARD) {
        diffText = "HARD";
    }

    printf(C_WHITE "Jogador: " C_YELLOW "%s" C_RESET, game->playerName);
    printf(C_WHITE "   Nível: " C_CYAN "%d" C_RESET, game->level);
    printf(C_WHITE "   Score: " C_GREEN "%d" C_RESET, game->score);
    printf(C_WHITE "   Tempo: " C_RED "%d" C_RESET, game->timeRemaining);
    printf(C_WHITE "   Dificuldade: " C_MAGENTA "%s\n" C_RESET, diffText);

    printf(C_WHITE "Objetivo: chega à " C_GREEN "saída" C_WHITE " e evita o " C_RED "inimigo" C_WHITE ".\n" C_RESET);
    printf(C_WHITE "Teclas: WASD/setas | R reiniciar nível | Q menu\n\n" C_RESET);
}

void renderGame(Game *game) {
    int row_idx = 0;
    int col_idx = 0;

    updateTimer(game);
    moveCursorTop();
    printHud(game);

    for (row_idx = 0; row_idx < MAZE_HEIGHT + 2; row_idx++) {
        for (col_idx = 0; col_idx < MAZE_WIDTH + 2; col_idx++) {
            if (row_idx == 0 || row_idx == MAZE_HEIGHT + 1 || col_idx == 0 || col_idx == MAZE_WIDTH + 1) {
                printf(C_WHITE GLYPH_BLOCK C_RESET);
                continue;
            }

            {
                int mx_val = col_idx - 1;
                int my_val = row_idx - 1;

                if (game->player.x == mx_val && game->player.y == my_val) {
                    printf(C_YELLOW GLYPH_BLOCK C_RESET);
                } else if (game->enemy.x == mx_val && game->enemy.y == my_val) {
                    printf(C_RED GLYPH_BLOCK C_RESET);
                } else if (game->exitPos.x == mx_val && game->exitPos.y == my_val) {
                    printf(C_GREEN GLYPH_BLOCK C_RESET);
                } else if (game->maze[my_val][mx_val] == CELL_WALL) {
                    printf(C_BLUE GLYPH_BLOCK C_RESET);
                } else {
                    printf(GLYPH_EMPTY);
                }
            }
        }
        printf("\n");
    }
}

void renderVictory(Game *game) {
    clearScreen();
    printf(C_GREEN "╔════════════════════════════════════╗\n" C_RESET);
    printf(C_GREEN "║         VITÓRIA ESCAPASTE          ║\n" C_RESET);
    printf(C_GREEN "╚════════════════════════════════════╝\n\n" C_RESET);
    printf("Jogador: %s\n", game->playerName);
    printf("Pontuação: %d\n", game->score);
    printf("Nível alcançado: %d\n\n", game->level);
    printf("1. Voltar ao menu\n");
    printf("2. Ver ranking\n");
    printf("3. Sair\n");
    printf("\nEscolha: ");
}

void renderGameOver(Game *game) {
    clearScreen();
    printf(C_RED "╔════════════════════════════════════╗\n" C_RESET);
    printf(C_RED "║            GAME OVER               ║\n" C_RESET);
    printf(C_RED "╚════════════════════════════════════╝\n\n" C_RESET);
    printf("Jogador: %s\n", game->playerName);
    printf("Pontuação: %d\n", game->score);
    printf("Nível alcançado: %d\n\n", game->level);
    printf("1. Voltar ao menu\n");
    printf("2. Ver ranking\n");
    printf("3. Sair\n");
    printf("\nEscolha: ");
}

void renderRankingScreen(void) {
    clearScreen();
    printf(C_CYAN "╔════════════════════ RANKING ════════════════════╗\n" C_RESET);
    printf(C_CYAN "╚═════════════════════════════════════════════════╝\n\n" C_RESET);
    printRankingTable();
    printf("\nPrima qualquer tecla para voltar ao menu...");
}