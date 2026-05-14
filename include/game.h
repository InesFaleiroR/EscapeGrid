#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define MAZE_WIDTH  39
#define MAZE_HEIGHT 23
#define MAX_NAME_LEN 32
#define MAX_RANKS 10

typedef enum {
    CELL_WALL = '#',
    CELL_PATH = ' ',
    CELL_EXIT = 'E'
} CellType;

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_VICTORY,
    STATE_GAMEOVER,
    STATE_RANKING,
    STATE_QUIT
} GameState;

typedef enum {
    DIFFICULTY_EASY = 1,
    DIFFICULTY_MEDIUM = 2,
    DIFFICULTY_HARD = 3
} Difficulty;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    char name[MAX_NAME_LEN];
    int score;
    int level;
    int difficulty;
} RankEntry;

typedef struct {
    char maze[MAZE_HEIGHT][MAZE_WIDTH];
    Position player;
    Position enemy;
    Position exitPos;

    int running;
    int level;
    int score;
    int timeLimit;
    int timeRemaining;
    int enemyMoveDelay;
    int enemyTick;
    int aiPredictionBias;
    int fogEnabled;

    Difficulty difficulty;
    GameState state;

    char playerName[MAX_NAME_LEN];

    clock_t levelStartClock;
} Game;

void initGame(Game *game);
void setupNewRun(Game *game, const char *name, Difficulty diff);
void setupLevel(Game *game);
void nextLevel(Game *game);
void resetCurrentLevel(Game *game);
void endGame(Game *game, int victory);
void showMenu(Game *game);

#endif