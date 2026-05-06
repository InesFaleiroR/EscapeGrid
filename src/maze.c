#include <stdlib.h>
#include "../include/game.h"

void generateMaze(Game *g) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                // Definir cantos e bordas com códigos simples
                if (i == 0 && j == 0) g->grid[i][j] = '1';
                else if (i == 0 && j == WIDTH-1) g->grid[i][j] = '2';
                else if (i == HEIGHT-1 && j == 0) g->grid[i][j] = '3';
                else if (i == HEIGHT-1 && j == WIDTH-1) g->grid[i][j] = '4';
                else if (i == 0 || i == HEIGHT-1) g->grid[i][j] = '-';
                else g->grid[i][j] = '|';
            } else {
                g->grid[i][j] = (rand() % 10 < 2) ? '#' : ' '; // 20% de obstáculos
            }
        }
    }
    g->player = (Position){1, 1};
    g->enemy  = (Position){WIDTH-2, HEIGHT-2};
    g->exit   = (Position){WIDTH-2, 1};
}
