#include <string.h>
#include <time.h>

#include "../include/game.h"
#include "../include/maze.h"
#include "../include/powerups.h"
#include "../include/ranking.h"

static void applyDifficulty(Game *game) {
    game->fogEnabled       = 0;
    game->fogRadius        = 0;
    game->keyRequired      = 0;
    game->npcActive        = 0;
    game->extraWallChance  = 0;
    game->extraPathChance  = 0;
    game->aiPredictionBias = 0;

    switch (game->difficulty) {
        case DIFFICULTY_EASY:
            game->enemyMoveDelay  = 5;
            game->timeLimit       = 180;
            game->fogRadius       = 0;
            game->extraPathChance = 30;
            game->npcActive       = 1;
            break;
        case DIFFICULTY_MEDIUM:
            game->enemyMoveDelay   = 3;
            game->timeLimit        = 100;
            game->extraPathChance  = 0;
            game->keyRequired      = 1;
            game->npcActive        = 1;
            game->aiPredictionBias = 1;
            break;
        case DIFFICULTY_HARD:
            game->enemyMoveDelay   = 1;
            game->timeLimit        = 70;
            game->fogEnabled       = 1;
            game->fogRadius        = 4;
            game->extraWallChance  = 8;
            game->keyRequired      = 1;
            game->npcActive        = 0;
            game->aiPredictionBias = 3;
            break;
    }
    if (game->timeLimit < 30) game->timeLimit = 30;
}

void initGame(Game *game) {
    memset(game, 0, sizeof(Game));
    game->state = STATE_MENU;
    strcpy(game->playerName, "PLAYER");
}

void setupNewRun(Game *game, const char *name, Difficulty diff) {
    strncpy(game->playerName, name, MAX_NAME_LEN - 1);
    game->playerName[MAX_NAME_LEN - 1] = '\0';
    game->difficulty = diff;
    game->score      = 0;
    game->level      = 1;
    setupLevel(game);
    game->state = STATE_PLAYING;
}

void setupLevel(Game *game) {
    applyDifficulty(game);
    generateMaze(game);
    generatePowerUps(game);
    game->timeRemaining  = game->timeLimit;
    game->levelStartTime = time(NULL);
    game->enemyTick      = 0;
    game->slowEnemyTicks = 0;
}

void nextLevel(Game *game) {
    game->score += 100 + (game->timeRemaining * 2) + (game->level * 20);
    game->level++;
    setupLevel(game);
}

void resetCurrentLevel(Game *game) {
    setupLevel(game);
}

void endGame(Game *game, int victory) {
    RankEntry entry;
    strncpy(entry.name, game->playerName, MAX_NAME_LEN - 1);
    entry.name[MAX_NAME_LEN - 1] = '\0';
    entry.score      = game->score;
    entry.level      = game->level;
    entry.difficulty = (int)game->difficulty;
    insertRanking(&entry);
    game->state = victory ? STATE_VICTORY : STATE_GAMEOVER;
}