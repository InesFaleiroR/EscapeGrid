#include <stdlib.h>

#include "../include/enemy.h"
#include "../include/maze.h"
#include "../include/pathfinding.h"

Position predictPlayerTarget(Game *game) {
    Position predicted = game->player;
    int roll = rand() % 100;
    int bias = game->aiPredictionBias * 25;

    if (roll < bias) {
        if (game->exitPos.x > predicted.x && predicted.x + 1 < MAZE_WIDTH)
            predicted.x++;
        else if (game->exitPos.x < predicted.x && predicted.x - 1 >= 0)
            predicted.x--;
        if (game->exitPos.y > predicted.y && predicted.y + 1 < MAZE_HEIGHT)
            predicted.y++;
        else if (game->exitPos.y < predicted.y && predicted.y - 1 >= 0)
            predicted.y--;
        if (!isWalkable(game, predicted.x, predicted.y))
            predicted = game->player;
    }
    return predicted;
}

void moveEnemy(Game *game) {
    Position target   = predictPlayerTarget(game);
    Position nextStep = bfsNextStep(game, game->enemy, target);

    if (nextStep.x == game->enemy.x && nextStep.y == game->enemy.y) {
        int dirs[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
        int order[4] = { 0,1,2,3 }, i, j, tmp;
        for (i = 0; i < 4; i++) {
            j = rand() % 4; tmp = order[i]; order[i] = order[j]; order[j] = tmp;
        }
        for (i = 0; i < 4; i++) {
            int nx = game->enemy.x + dirs[order[i]][0];
            int ny = game->enemy.y + dirs[order[i]][1];
            if (isWalkable(game, nx, ny)) {
                game->enemy.x = nx; game->enemy.y = ny; return;
            }
        }
        return;
    }
    game->enemy.x = nextStep.x;
    game->enemy.y = nextStep.y;
}