#include <stdlib.h>
#include "game.h"

void moveEnemy(Game *g) {
    int dx = 0, dy = 0;

    // IA média: aproxima-se do jogador
    if (g->enemy.x < g->player.x) dx = 1;
    else if (g->enemy.x > g->player.x) dx = -1;

    if (g->enemy.y < g->player.y) dy = 1;
    else if (g->enemy.y > g->player.y) dy = -1;

    int newX = g->enemy.x + dx;
    int newY = g->enemy.y + dy;

    if (g->grid[newY][newX] != '#') {
        g->enemy.x = newX;
        g->enemy.y = newY;
    }
}