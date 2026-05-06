#ifndef GAME_H
#define GAME_H

#define WIDTH 20
#define HEIGHT 10

typedef struct {
    int x;
    int y;
} Position;

typedef enum { EASY, MEDIUM, HARD } Difficulty;

typedef struct {
    char grid[HEIGHT][WIDTH];
    Position player;
    Position enemy;
    Position exit;
    int running;
    Difficulty difficulty;
} Game;

// Protótipos das funções
void initGame(Game *g);
void gameLoop(Game *g);
void drawGame(Game *g);
void generateMaze(Game *g);
void movePlayer(Game *g, char input);
void moveEnemy(Game *g);

#endif
