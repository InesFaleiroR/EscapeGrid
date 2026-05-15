#include <stdlib.h>
#include "../include/powerups.h"
#include "../include/maze.h"

void generatePowerUps(Game *game) {
    int count = 0, attempts = 0, i;
    int total = (game->difficulty == DIFFICULTY_EASY)   ? 3 :
                (game->difficulty == DIFFICULTY_MEDIUM) ? 2 : 1;

    for (i = 0; i < MAX_POWERUPS; i++)
        game->powerups[i].active = 0;

    while (count < total && attempts < 500) {
        int rx = 1 + rand() % (MAZE_WIDTH  - 2);
        int ry = 1 + rand() % (MAZE_HEIGHT - 2);
        attempts++;

        if (game->maze[ry][rx] != CELL_PATH)                continue;
        if (rx == game->player.x  && ry == game->player.y)  continue;
        if (rx == game->enemy.x   && ry == game->enemy.y)   continue;
        if (rx == game->exitPos.x && ry == game->exitPos.y) continue;
        if (game->keyRequired &&
            rx == game->keyPos.x  && ry == game->keyPos.y)  continue;

        game->powerups[count].pos.x  = rx;
        game->powerups[count].pos.y  = ry;
        game->powerups[count].active = 1;
        game->maze[ry][rx] = CELL_POWERUP;
        count++;
    }
    game->slowEnemyTicks = 0;
}

void collectPowerUp(Game *game) {
    int i, px = game->player.x, py = game->player.y;

    for (i = 0; i < MAX_POWERUPS; i++) {
        if (!game->powerups[i].active)      continue;
        if (game->powerups[i].pos.x != px)  continue;
        if (game->powerups[i].pos.y != py)  continue;

        game->powerups[i].active = 0;
        game->maze[py][px]       = CELL_PATH;
        game->score             += 20;
        game->slowEnemyTicks    += 8;
        break;
    }
}