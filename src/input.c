#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "../include/input.h"
#include "../include/maze.h"
#include "../include/enemy.h"
#include "../include/powerups.h"
#include "../include/render.h"
#include "../include/utils.h"

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_LEFT  75
#define KEY_RIGHT 77

static void movePlayer(Game *game, int dx, int dy) {
    int nx = game->player.x + dx;
    int ny = game->player.y + dy;

    if (!isWalkable(game, nx, ny)) return;
    if (game->maze[ny][nx] == CELL_EXIT && game->keyRequired && !game->hasKey) return;

    game->player.x = nx;
    game->player.y = ny;

    if (game->npcActive && nx == game->npcPos.x && ny == game->npcPos.y)
        game->npcTalked = 1;

    collectPowerUp(game);

    if (game->keyRequired && !game->hasKey && game->maze[ny][nx] == CELL_KEY) {
        game->hasKey = 1;
        game->maze[ny][nx] = CELL_PATH;
        game->score += 30;
    }

    if (game->player.x == game->exitPos.x && game->player.y == game->exitPos.y) {
        if (game->level >= 5) endGame(game, 1);
        else                  nextLevel(game);
        return;
    }

    if (game->slowEnemyTicks > 0) {
        game->slowEnemyTicks--;
    } else {
        game->enemyTick++;
        if (game->enemyTick >= game->enemyMoveDelay) {
            moveEnemy(game);
            game->enemyTick = 0;
        }
    }

    if (game->player.x == game->enemy.x && game->player.y == game->enemy.y)
        endGame(game, 0);
}

void processMenuInput(Game *game) {
    char option[16];

    if (game->state == STATE_VICTORY || game->state == STATE_GAMEOVER) {
        _getch(); game->state = STATE_MENU; return;
    }
    if (game->state == STATE_RANKING) {
        waitForAnyKey(); game->state = STATE_MENU; return;
    }

    fgets(option, sizeof(option), stdin);
    if (option[0] == '1') {
        char playerName[MAX_NAME_LEN];
        printf("\n\x1b[1;96m  Nome do jogador: \x1b[0m");
        fflush(stdout);
        fgets(playerName, sizeof(playerName), stdin);
        playerName[strcspn(playerName, "\n")] = '\0';
        if (playerName[0] == '\0') strcpy(playerName, "PLAYER");
        strncpy(game->playerName, playerName, MAX_NAME_LEN - 1);
        game->playerName[MAX_NAME_LEN - 1] = '\0';
        game->state = STATE_DIFFICULTY;
    } else if (option[0] == '2') {
        game->state = STATE_RANKING;
    } else {
        game->state = STATE_QUIT;
    }
}

void processDifficultyInput(Game *game) {
    char option[16];
    Difficulty diff = DIFFICULTY_MEDIUM;
    fgets(option, sizeof(option), stdin);
    if (option[0] == '1') diff = DIFFICULTY_EASY;
    else if (option[0] == '3') diff = DIFFICULTY_HARD;
    setupNewRun(game, game->playerName, diff);
    game->state = STATE_PLAYING;
}

void processGameInput(Game *game) {
    int key;
    if (!_kbhit()) { sleepMs(20); return; }
    key = _getch();
    if (key == 0 || key == 224) {
        int ext = _getch();
        switch (ext) {
            case KEY_UP:    movePlayer(game,  0, -1); break;
            case KEY_DOWN:  movePlayer(game,  0,  1); break;
            case KEY_LEFT:  movePlayer(game, -1,  0); break;
            case KEY_RIGHT: movePlayer(game,  1,  0); break;
        }
        return;
    }
    switch (key) {
        case 'w': case 'W': movePlayer(game,  0, -1); break;
        case 's': case 'S': movePlayer(game,  0,  1); break;
        case 'a': case 'A': movePlayer(game, -1,  0); break;
        case 'd': case 'D': movePlayer(game,  1,  0); break;
        case 'p': case 'P': game->state = STATE_PAUSED; break;
        case 'q': case 'Q': game->state = STATE_MENU;   break;
        case 'r': case 'R': resetCurrentLevel(game);     break;
    }
}

void processPauseInput(Game *game) {
    int key;
    if (!_kbhit()) { sleepMs(50); return; }
    key = _getch();
    switch (key) {
        case 'p': case 'P': game->state = STATE_PLAYING; break;
        case 'q': case 'Q': game->state = STATE_MENU;    break;
    }
}

void waitForAnyKey(void) { _getch(); }