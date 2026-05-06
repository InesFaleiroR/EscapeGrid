#include <stdlib.h>
#include "game.h"

void generateMaze(Game *g) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            // paredes nas bordas
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                g->grid[i][j] = '#';
            else {
                // aleatório
                g->grid[i][j] = (rand() % 100 < 20) ? '#' : '.';
            }
        }
    }

    // posições iniciais
    g->player = (Position){1,1};
    g->enemy = (Position){WIDTH - 2, HEIGHT - 2};
    g->exit = (Position){WIDTH - 3, HEIGHT - 3};

    // garantir que estão livres
    g->grid[1][1] = '.';
}