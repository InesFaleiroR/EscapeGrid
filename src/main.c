#include <stdio.h>
#include "game.h"

int main() {
    Game game;

    initGame(&game);
    gameLoop(&game);

    return 0;
}