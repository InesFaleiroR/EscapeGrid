#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void clearScreen(void);
void moveCursorTop(void);
void renderMenu(void);
void renderGame(Game *game);
void renderVictory(Game *game);
void renderGameOver(Game *game);
void renderRankingScreen(void);

#endif