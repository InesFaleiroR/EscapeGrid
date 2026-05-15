#ifndef MAZE_H
#define MAZE_H

#include "game.h"

void generateMaze(Game *game);
void carveMaze(Game *game, int x, int y);
int  isWalkable(Game *game, int x, int y);

#endif