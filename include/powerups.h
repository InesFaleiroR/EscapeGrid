#ifndef POWERUPS_H
#define POWERUPS_H

#include "game.h"

/* Coloca power-ups aleatórios no labirinto. */
void generatePowerUps(Game *game);

/* Chamado após cada passo do jogador – recolhe power-up se existir. */
void collectPowerUp(Game *game);

#endif