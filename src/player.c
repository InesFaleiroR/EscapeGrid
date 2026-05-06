#include "game.h"

void movePlayer(Game *g, char input) {
    int newX = g->player.x;
    int newY = g->player.y;

    if (input == 'w') newY--;
    if (input == 's') newY++;
    if (input == 'a') newX--;
    if (input == 'd') newX++;

    // colisão
    if (g->grid[newY][newX] != '#') {
        g->player.x = newX;
        g->player.y = newY;
    }
}