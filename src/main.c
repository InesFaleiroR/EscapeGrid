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
        switch (game.state) {
            case STATE_MENU:
                renderMenu();
                processMenuInput(&game);
                break;
            case STATE_DIFFICULTY:
                renderDifficultyScreen();
                processDifficultyInput(&game);
                break;
            case STATE_PLAYING:
                renderGame(&game);
                processGameInput(&game);
                break;
            case STATE_PAUSED:
                renderPauseScreen(&game);
                processPauseInput(&game);
                break;
            case STATE_VICTORY:
                renderVictory(&game);
                processMenuInput(&game);
                break;
            case STATE_GAMEOVER:
                renderGameOver(&game);
                processMenuInput(&game);
                break;
            case STATE_RANKING:
                renderRankingScreen();
                processMenuInput(&game);
                break;
            default:
                break;
        }
    }

    showCursor();
    clearScreen();
    return 0;
}