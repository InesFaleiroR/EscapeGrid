#ifndef GAME_H
#define GAME_H

#define WIDTH 20
#define HEIGHT 10

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    char grid[HEIGHT][WIDTH];
    Position player;
    Position enemy;
    Position exit;
    int running;
} Game;

// game.c
void initGame(Game *g);
void gameLoop(Game *g);
void drawGame(Game *g);

// maze.c
void generateMaze(Game *g);

// player.c
void movePlayer(Game *g, char input);

// enemy.c
void moveEnemy(Game *g);

#endif