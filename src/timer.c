#include <time.h>
#include "../include/timer.h"

void updateTimer(Game *game) {
    time_t now     = time(NULL);
    int    elapsed = (int)difftime(now, game->levelStartTime);
    game->timeRemaining = game->timeLimit - elapsed;
    if (game->timeRemaining <= 0) {
        game->timeRemaining = 0;
        endGame(game, 0);
    }
}