#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void clearScreen(void);
void renderMenu(void);
void renderDifficultyScreen(void);
void renderGame(Game *game);
void renderPauseScreen(Game *game);
void renderVictory(Game *game);
void renderGameOver(Game *game);
void renderRankingScreen(void);

#endif