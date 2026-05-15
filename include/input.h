#ifndef INPUT_H
#define INPUT_H

#include "game.h"

void processMenuInput(Game *game);
void processDifficultyInput(Game *game);
void processGameInput(Game *game);
void processPauseInput(Game *game);
void waitForAnyKey(void);

#endif