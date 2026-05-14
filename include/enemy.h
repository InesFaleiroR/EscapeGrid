#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"

void moveEnemy(Game *game);
Position getNextEnemyMoveBFS(Game *game);
Position predictPlayerTarget(Game *game);

#endif