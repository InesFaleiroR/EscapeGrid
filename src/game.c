#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../include/game.h"

void initGame(Game *g) {
    g->running = 1;
    g->difficulty = EASY;
    generateMaze(g);
}

void drawGame(Game *g) {
    // Reset do cursor para o topo (evita o piscar do ecrã)
    printf("\033[H"); 

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == g->player.y && j == g->player.x) printf("P");
            else if (i == g->enemy.y && j == g->enemy.x) printf("E");
            else if (i == g->exit.y && j == g->exit.x) printf("X");
            else {
                char c = g->grid[i][j];
                // Se o terminal não suportar os símbolos, usa ASCII simples:
                if (c == '1') printf("+"); // Canto superior esq
                else if (c == '2') printf("+"); // Canto superior dir
                else if (c == '3') printf("+"); // Canto inferior esq
                else if (c == '4') printf("+"); // Canto inferior dir
                else if (c == '-') printf("-"); // Parede horizontal
                else if (c == '|') printf("|"); // Parede vertical
                else if (c == '#') printf("#"); // Obstáculo
                else printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n(Use WASD para mover, Q para sair)\n");
}

void gameLoop(Game *g) {
    while (g->running) {
        drawGame(g);
        if (_kbhit()) {
            char input = _getch();
            if (input == 'q') g->running = 0;
            movePlayer(g, input);
            moveEnemy(g);
        }
        // Condição de vitória
        if (g->player.x == g->exit.x && g->player.y == g->exit.y) {
            drawGame(g);
            printf("\nPARABÉNS! Escapaste da Grid!\n");
            g->running = 0;
        }
    }
}
