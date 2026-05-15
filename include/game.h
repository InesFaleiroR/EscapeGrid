#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <stdbool.h>
#include <time.h>

/* ── Dimensões do labirinto ────────────────────────────── */
#define MAZE_WIDTH  39
#define MAZE_HEIGHT 23

/* ── Limites gerais ────────────────────────────────────── */
#define MAX_NAME_LEN  32
#define MAX_RANKS     10
#define MAX_POWERUPS   5

/* ── Células do labirinto ──────────────────────────────── */
typedef enum {
    CELL_WALL    = '#',
    CELL_PATH    = ' ',
    CELL_EXIT    = 'E',
    CELL_POWERUP = 'P',
    CELL_KEY     = 'K',
    CELL_NPC     = 'N'
} CellType;

/* ── Estados do jogo ───────────────────────────────────── */
typedef enum {
    STATE_MENU,
    STATE_DIFFICULTY,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_VICTORY,
    STATE_GAMEOVER,
    STATE_RANKING,
    STATE_QUIT
} GameState;

/* ── Níveis de dificuldade ─────────────────────────────── */
typedef enum {
    DIFFICULTY_EASY   = 1,
    DIFFICULTY_MEDIUM = 2,
    DIFFICULTY_HARD   = 3
} Difficulty;

/* ── Posição 2-D ───────────────────────────────────────── */
typedef struct { int x; int y; } Position;

/* ── Entrada de ranking ────────────────────────────────── */
typedef struct {
    char name[MAX_NAME_LEN];
    int  score;
    int  level;
    int  difficulty;
} RankEntry;

/* ── Power-up ──────────────────────────────────────────── */
typedef struct {
    Position pos;
    int      active;
} PowerUp;

/* ── Estado completo do jogo ───────────────────────────── */
typedef struct {
    char maze[MAZE_HEIGHT][MAZE_WIDTH];

    Position player;
    Position enemy;
    Position exitPos;
    Position npcPos;
    Position keyPos;

    PowerUp  powerups[MAX_POWERUPS];

    int running;
    int level;
    int score;

    int timeLimit;
    int timeRemaining;

    int enemyMoveDelay;     /* passos do jogador entre cada movimento do inimigo */
    int enemyTick;
    int aiPredictionBias;   /* 0 = reactivo  /  >0 = preditivo (hard) */

    int fogEnabled;         /* 1 = névoa ativa (hard) */
    int fogRadius;          /* raio de visibilidade em células */

    int hasKey;             /* 1 = jogador apanhou a chave */
    int keyRequired;        /* 1 = é necessária chave para sair (medium+) */

    int npcActive;          /* 1 = NPC presente no nível */
    int npcTalked;          /* 1 = jogador já interagiu com o NPC */

    int extraWallChance;    /* 0-100: % de paredes extra adicionadas após geração */
    int extraPathChance;    /* 0-100: % de paredes removidas após geração */

    int slowEnemyTicks;     /* ticks restantes em que inimigo não move */

    Difficulty difficulty;
    GameState  state;

    char   playerName[MAX_NAME_LEN];
    time_t levelStartTime;
} Game;

/* ── Protótipos ────────────────────────────────────────── */
void initGame(Game *game);
void setupNewRun(Game *game, const char *name, Difficulty diff);
void setupLevel(Game *game);
void nextLevel(Game *game);
void resetCurrentLevel(Game *game);
void endGame(Game *game, int victory);

#endif