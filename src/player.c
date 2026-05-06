#include "../include/game.h"

void movePlayer(Game *g, char input) {
    Position next = g->player;
    if (input == 'w') next.y--;
    if (input == 's') next.y++;
    if (input == 'a') next.x--;
    if (input == 'd') next.x++;

    // Verifica se não é parede (qualquer coisa diferente de espaço ou saída é parede)
    char target = g->grid[next.y][next.x];
    if (target == ' ' || next.x == g->exit.x && next.y == g->exit.y) {
        g->player = next;
    }
}
