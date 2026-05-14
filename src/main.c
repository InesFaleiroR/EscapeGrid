#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/game.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/ranking.h"

int main(void) {
    srand((unsigned int)time(NULL));
    setupConsole();
    ensureRankingFile();

    Game game;
    initGame(&game);

    while (game.state != STATE_QUIT) {
        if (game.state == STATE_MENU) {
            renderMenu();
            processMenuInput(&game);
        } else if (game.state == STATE_PLAYING) {
            renderGame(&game);
            processGameInput(&game);
        } else if (game.state == STATE_VICTORY) {
            renderVictory(&game);
            processMenuInput(&game);
        } else if (game.state == STATE_GAMEOVER) {
            renderGameOver(&game);
            processMenuInput(&game);
        } else if (game.state == STATE_RANKING) {
            renderRankingScreen();
            processMenuInput(&game);
        }
    }

    showCursor();
    clearScreen();
    return 0;
}