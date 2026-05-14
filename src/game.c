#include <stdio.h>
#include <string.h>

#include "../include/game.h"
#include "../include/maze.h"
#include "../include/ranking.h"

static void applyDifficulty(Game *game) {
    if (game->difficulty == DIFFICULTY_EASY) {
        game->enemyMoveDelay = 3;
        game->aiPredictionBias = 20;
        game->timeLimit = 90 - ((game->level - 1) * 5);
    } else if (game->difficulty == DIFFICULTY_MEDIUM) {
        game->enemyMoveDelay = 2;
        game->aiPredictionBias = 45;
        game->timeLimit = 75 - ((game->level - 1) * 5);
    } else {
        game->enemyMoveDelay = 1;
        game->aiPredictionBias = 70;
        game->timeLimit = 60 - ((game->level - 1) * 4);
    }

    if (game->timeLimit < 25) {
        game->timeLimit = 25;
    }
}

void initGame(Game *game) {
    memset(game, 0, sizeof(Game));
    game->running = 1;
    game->state = STATE_MENU;
    game->difficulty = DIFFICULTY_MEDIUM;
    game->level = 1;
    game->score = 0;
    strcpy(game->playerName, "PLAYER");
}

void setupNewRun(Game *game, const char *name, Difficulty diff) {
    memset(game->maze, '#', sizeof(game->maze));
    game->difficulty = diff;
    game->level = 1;
    game->score = 0;
    game->enemyTick = 0;
    game->fogEnabled = 0;
    strncpy(game->playerName, name, MAX_NAME_LEN - 1);
    game->playerName[MAX_NAME_LEN - 1] = '\0';
    setupLevel(game);
    game->state = STATE_PLAYING;
}

void setupLevel(Game *game) {
    applyDifficulty(game);
    generateMaze(game);
    game->timeRemaining = game->timeLimit;
    game->levelStartClock = clock();
    game->enemyTick = 0;
}

void nextLevel(Game *game) {
    game->score += 100 + (game->timeRemaining * 2) + (game->level * 20);
    game->level++;
    setupLevel(game);
}

void resetCurrentLevel(Game *game) {
    setupLevel(game);
    game->state = STATE_PLAYING;
}

void endGame(Game *game, int victory) {
    if (victory) {
        RankEntry entry;
        strncpy(entry.name, game->playerName, MAX_NAME_LEN - 1);
        entry.name[MAX_NAME_LEN - 1] = '\0';
        entry.score = game->score;
        entry.level = game->level;
        entry.difficulty = game->difficulty;
        insertRanking(&entry);
        game->state = STATE_VICTORY;
    } else {
        RankEntry entry;
        strncpy(entry.name, game->playerName, MAX_NAME_LEN - 1);
        entry.name[MAX_NAME_LEN - 1] = '\0';
        entry.score = game->score;
        entry.level = game->level;
        entry.difficulty = game->difficulty;
        insertRanking(&entry);
        game->state = STATE_GAMEOVER;
    }
}

void showMenu(Game *game) {
    game->state = STATE_MENU;
}