#include <stdlib.h>
#include <string.h>

#include "../include/enemy.h"
#include "../include/maze.h"

typedef struct {
    int x;
    int y;
} Node;

static int insideBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < MAZE_WIDTH && y < MAZE_HEIGHT;
}

Position predictPlayerTarget(Game *game) {
    Position predicted = game->player;
    int roll_val = rand() % 100;

    if (roll_val < game->aiPredictionBias) {
        if (game->exitPos.x > predicted.x && predicted.x + 1 < MAZE_WIDTH) {
            predicted.x += 1;
        } else if (game->exitPos.x < predicted.x && predicted.x - 1 >= 0) {
            predicted.x -= 1;
        }

        if (game->exitPos.y > predicted.y && predicted.y + 1 < MAZE_HEIGHT) {
            predicted.y += 1;
        } else if (game->exitPos.y < predicted.y && predicted.y - 1 >= 0) {
            predicted.y -= 1;
        }

        if (!isWalkable(game, predicted.x, predicted.y)) {
            predicted = game->player;
        }
    }

    return predicted;
}

Position getNextEnemyMoveBFS(Game *game) {
    int visited[MAZE_HEIGHT][MAZE_WIDTH];
    Position parent[MAZE_HEIGHT][MAZE_WIDTH];
    Node queue_vals[MAZE_WIDTH * MAZE_HEIGHT];
    int front_idx = 0;
    int back_idx = 0;
    int row_idx = 0;
    int col_idx = 0;
    int dirs[4][2] = {
        { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 }
    };

    Position target = predictPlayerTarget(game);
    Position fallback = game->enemy;

    for (row_idx = 0; row_idx < MAZE_HEIGHT; row_idx++) {
        for (col_idx = 0; col_idx < MAZE_WIDTH; col_idx++) {
            visited[row_idx][col_idx] = 0;
            parent[row_idx][col_idx].x = -1;
            parent[row_idx][col_idx].y = -1;
        }
    }

    queue_vals[back_idx].x = game->enemy.x;
    queue_vals[back_idx].y = game->enemy.y;
    back_idx++;
    visited[game->enemy.y][game->enemy.x] = 1;

    while (front_idx < back_idx) {
        Node current = queue_vals[front_idx];
        front_idx++;

        if (current.x == target.x && current.y == target.y) {
            Position step = target;
            while (!(parent[step.y][step.x].x == game->enemy.x && parent[step.y][step.x].y == game->enemy.y)) {
                Position prev = parent[step.y][step.x];
                if (prev.x == -1 || prev.y == -1) {
                    return fallback;
                }
                step = prev;
            }
            return step;
        }

        for (row_idx = 0; row_idx < 4; row_idx++) {
            int nx_val = current.x + dirs[row_idx][0];
            int ny_val = current.y + dirs[row_idx][1];

            if (insideBounds(nx_val, ny_val) && !visited[ny_val][nx_val] && isWalkable(game, nx_val, ny_val)) {
                visited[ny_val][nx_val] = 1;
                parent[ny_val][nx_val].x = current.x;
                parent[ny_val][nx_val].y = current.y;
                queue_vals[back_idx].x = nx_val;
                queue_vals[back_idx].y = ny_val;
                back_idx++;
            }
        }
    }

    return fallback;
}

void moveEnemy(Game *game) {
    Position nextMove = getNextEnemyMoveBFS(game);

    if (nextMove.x == game->enemy.x && nextMove.y == game->enemy.y) {
        int dirs[4][2] = {
            { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 }
        };
        int order[4] = { 0, 1, 2, 3 };
        int idx_vals = 0;

        for (idx_vals = 0; idx_vals < 4; idx_vals++) {
            int j_val = rand() % 4;
            int temp_val = order[idx_vals];
            order[idx_vals] = order[j_val];
            order[j_val] = temp_val;
        }

        for (idx_vals = 0; idx_vals < 4; idx_vals++) {
            int nx_val = game->enemy.x + dirs[order[idx_vals]][0];
            int ny_val = game->enemy.y + dirs[order[idx_vals]][1];
            if (isWalkable(game, nx_val, ny_val)) {
                game->enemy.x = nx_val;
                game->enemy.y = ny_val;
                return;
            }
        }
    } else {
        game->enemy.x = nextMove.x;
        game->enemy.y = nextMove.y;
    }
}