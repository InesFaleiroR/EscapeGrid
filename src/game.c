#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void initGame(Game *g) {
    g->running = 1;
    generateMaze(g);
}

void drawGame(Game *g) {
    system("clear"); // Linux/Mac

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == g->player.y && j == g->player.x)
                printf("@");
            else if (i == g->enemy.y && j == g->enemy.x)
                printf("X");
            else if (i == g->exit.y && j == g->exit.x)
                printf("E");
            else
                printf("%c", g->grid[i][j]);
        }
        printf("\n");
    }
}

void gameLoop(Game *g) {
    char input;

    while (g->running) {
        drawGame(g);

        printf("Move (WASD): ");
        scanf(" %c", &input);

        movePlayer(g, input);
        moveEnemy(g);

        // vitória
        if (g->player.x == g->exit.x && g->player.y == g->exit.y) {
            printf("Ganhou!\n");
            break;
        }

        // derrota
        if (g->player.x == g->enemy.x && g->player.y == g->enemy.y) {
            printf("(Foste apanhado!\n");
            break;
        }
    }
}