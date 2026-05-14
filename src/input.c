#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "../include/input.h"
#include "../include/maze.h"
#include "../include/enemy.h"
#include "../include/render.h"
#include "../include/utils.h"

static void readPlayerName(char *nameBuffer, int maxLen) {
    char temp_name[128];
    printf("Nome do jogador: ");
    fgets(temp_name, sizeof(temp_name), stdin);

    if (temp_name[0] == '\n' || temp_name[0] == '\0') {
        strncpy(nameBuffer, "PLAYER", maxLen - 1);
        nameBuffer[maxLen - 1] = '\0';
        return;
    }

    {
        int len_val = (int)strlen(temp_name);
        if (len_val > 0 && temp_name[len_val - 1] == '\n') {
            temp_name[len_val - 1] = '\0';
        }
    }

    strncpy(nameBuffer, temp_name, maxLen - 1);
    nameBuffer[maxLen - 1] = '\0';
}

static Difficulty readDifficulty(void) {
    char diff_val[16];
    int option_val = 2;

    printf("Dificuldade 1-Fácil 2-Médio 3-Difícil: ");
    fgets(diff_val, sizeof(diff_val), stdin);
    sscanf(diff_val, "%d", &option_val);

    if (option_val < 1 || option_val > 3) {
        option_val = 2;
    }

    return (Difficulty)option_val;
}

static void tryMovePlayer(Game *game, int dx_val, int dy_val) {
    int nx_val = game->player.x + dx_val;
    int ny_val = game->player.y + dy_val;

    if (isWalkable(game, nx_val, ny_val)) {
        game->player.x = nx_val;
        game->player.y = ny_val;
    }

    if (game->player.x == game->exitPos.x && game->player.y == game->exitPos.y) {
        if (game->level >= 5) {
            endGame(game, 1);
            return;
        }
        nextLevel(game);
        return;
    }

    game->enemyTick++;
    if (game->enemyTick >= game->enemyMoveDelay) {
        moveEnemy(game);
        game->enemyTick = 0;
    }

    if (game->player.x == game->enemy.x && game->player.y == game->enemy.y) {
        endGame(game, 0);
    }
}

void waitForAnyKey(void) {
    _getch();
}

void processMenuInput(Game *game) {
    if (game->state == STATE_MENU) {
        char option_text[16];
        char player_name[MAX_NAME_LEN];

        fgets(option_text, sizeof(option_text), stdin);

        if (option_text[0] == '1') {
            readPlayerName(player_name, MAX_NAME_LEN);
            setupNewRun(game, player_name, readDifficulty());
        } else if (option_text[0] == '2') {
            game->state = STATE_RANKING;
        } else {
            game->state = STATE_QUIT;
        }
        return;
    }

    if (game->state == STATE_VICTORY || game->state == STATE_GAMEOVER) {
        char option_text[16];
        fgets(option_text, sizeof(option_text), stdin);

        if (option_text[0] == '1') {
            game->state = STATE_MENU;
        } else if (option_text[0] == '2') {
            game->state = STATE_RANKING;
        } else {
            game->state = STATE_QUIT;
        }
        return;
    }

    if (game->state == STATE_RANKING) {
        waitForAnyKey();
        game->state = STATE_MENU;
    }
}

void processGameInput(Game *game) {
    int key_val = 0;

    if (!_kbhit()) {
        sleepMs(30);
        moveEnemy(game);
        if (game->player.x == game->enemy.x && game->player.y == game->enemy.y) {
            endGame(game, 0);
        }
        return;
    }

    key_val = _getch();

    if (key_val == 0 || key_val == 224) {
        key_val = _getch();
        if (key_val == 72) {
            tryMovePlayer(game, 0, -1);
        } else if (key_val == 80) {
            tryMovePlayer(game, 0, 1);
        } else if (key_val == 75) {
            tryMovePlayer(game, -1, 0);
        } else if (key_val == 77) {
            tryMovePlayer(game, 1, 0);
        }
        return;
    }

    if (key_val == 'w' || key_val == 'W') {
        tryMovePlayer(game, 0, -1);
    } else if (key_val == 's' || key_val == 'S') {
        tryMovePlayer(game, 0, 1);
    } else if (key_val == 'a' || key_val == 'A') {
        tryMovePlayer(game, -1, 0);
    } else if (key_val == 'd' || key_val == 'D') {
        tryMovePlayer(game, 1, 0);
    } else if (key_val == 'r' || key_val == 'R') {
        resetCurrentLevel(game);
    } else if (key_val == 'q' || key_val == 'Q') {
        game->state = STATE_MENU;
    }

    if (game->player.x == game->enemy.x && game->player.y == game->enemy.y) {
        endGame(game, 0);
    }
}
