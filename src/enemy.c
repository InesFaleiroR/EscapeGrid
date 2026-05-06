#include "../include/game.h"

void moveEnemy(Game *g) {
    if (g->enemy.x < g->player.x) g->enemy.x++;
    else if (g->enemy.x > g->player.x) g->enemy.x--;
    
    if (g->enemy.y < g->player.y) g->enemy.y++;
    else if (g->enemy.y > g->player.y) g->enemy.y--;
}
