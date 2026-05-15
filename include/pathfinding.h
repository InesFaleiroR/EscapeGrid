#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "game.h"

/* Retorna 1 se existe caminho entre from e to no labirinto atual. */
int pathExists(Game *game, Position from, Position to);

/* BFS completo: devolve o primeiro passo de enemy em direção a target. */
Position bfsNextStep(Game *game, Position from, Position target);

#endif