#include <time.h>

#include "../include/timer.h"

void updateTimer(Game *game) {
    clock_t current_clock = clock();
    int elapsed_seconds = (int)((current_clock - game->levelStartClock) / CLOCKS_PER_SEC);
    game->timeRemaining = game->timeLimit - elapsed_seconds;

    if (game->timeRemaining <= 0) {
        game->timeRemaining = 0;
        endGame(game, 0);
    }
}