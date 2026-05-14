#include <stdlib.h>
#include <string.h>

#include "../include/maze.h"
#include "../include/utils.h"

static const int dirX[4] = { 0, 0, -2, 2 };
static const int dirY[4] = { -2, 2, 0, 0 };

static void shuffleDirections(int order[4]) {
    int idx_vals = 0;
    for (idx_vals = 0; idx_vals < 4; idx_vals++) {
        order[idx_vals] = idx_vals;
    }

    for (idx_vals = 0; idx_vals < 4; idx_vals++) {
        int j_val = rand() % 4;
        int temp_val = order[idx_vals];
        order[idx_vals] = order[j_val];
        order[j_val] = temp_val;
    }
}

void carveMaze(Game *game, int x, int y) {
    int order[4];
    int idx_vals = 0;

    game->maze[y][x] = CELL_PATH;
    shuffleDirections(order);

    for (idx_vals = 0; idx_vals < 4; idx_vals++) {
        int direction = order[idx_vals];
        int nx_val = x + dirX[direction];
        int ny_val = y + dirY[direction];

        if (nx_val > 0 && nx_val < MAZE_WIDTH - 1 && ny_val > 0 && ny_val < MAZE_HEIGHT - 1) {
            if (game->maze[ny_val][nx_val] == CELL_WALL) {
                game->maze[y + dirY[direction] / 2][x + dirX[direction] / 2] = CELL_PATH;
                carveMaze(game, nx_val, ny_val);
            }
        }
    }
}

int isWalkable(Game *game, int x, int y) {
    if (x < 0 || y < 0 || x >= MAZE_WIDTH || y >= MAZE_HEIGHT) {
        return 0;
    }

    return game->maze[y][x] != CELL_WALL;
}

void generateMaze(Game *game) {
    int row_idx = 0;
    int col_idx = 0;

    for (row_idx = 0; row_idx < MAZE_HEIGHT; row_idx++) {
        for (col_idx = 0; col_idx < MAZE_WIDTH; col_idx++) {
            game->maze[row_idx][col_idx] = CELL_WALL;
        }
    }

    carveMaze(game, 1, 1);

    game->player.x = 1;
    game->player.y = 1;

    game->exitPos.x = MAZE_WIDTH - 2;
    game->exitPos.y = MAZE_HEIGHT - 2;

    if (game->exitPos.x % 2 == 0) {
        game->exitPos.x--;
    }

    if (game->exitPos.y % 2 == 0) {
        game->exitPos.y--;
    }

    game->maze[game->exitPos.y][game->exitPos.x] = CELL_EXIT;

    game->enemy.x = MAZE_WIDTH - 2;
    game->enemy.y = 1;

    if (!isWalkable(game, game->enemy.x, game->enemy.y)) {
        game->enemy.x = MAZE_WIDTH - 4;
        game->enemy.y = 1;
    }

    game->maze[game->enemy.y][game->enemy.x] = CELL_PATH;
}