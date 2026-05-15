#include <string.h>
#include "../include/pathfinding.h"
#include "../include/maze.h"

static const int DX[4] = {  0,  0, -1,  1 };
static const int DY[4] = { -1,  1,  0,  0 };

int pathExists(Game *game, Position from, Position to) {
    char visited[MAZE_HEIGHT][MAZE_WIDTH];
    int  qx[MAZE_HEIGHT * MAZE_WIDTH];
    int  qy[MAZE_HEIGHT * MAZE_WIDTH];
    int  front = 0, back = 0, i, cx, cy, nx, ny;

    memset(visited, 0, sizeof(visited));
    qx[back] = from.x; qy[back] = from.y; back++;
    visited[from.y][from.x] = 1;

    while (front < back) {
        cx = qx[front]; cy = qy[front]; front++;
        if (cx == to.x && cy == to.y) return 1;
        for (i = 0; i < 4; i++) {
            nx = cx + DX[i]; ny = cy + DY[i];
            if (nx >= 0 && nx < MAZE_WIDTH  &&
                ny >= 0 && ny < MAZE_HEIGHT &&
                !visited[ny][nx]             &&
                game->maze[ny][nx] != CELL_WALL) {
                visited[ny][nx] = 1;
                qx[back] = nx; qy[back] = ny; back++;
            }
        }
    }
    return 0;
}

Position bfsNextStep(Game *game, Position from, Position target) {
    char     visited[MAZE_HEIGHT][MAZE_WIDTH];
    Position parent[MAZE_HEIGHT][MAZE_WIDTH];
    int      qx[MAZE_HEIGHT * MAZE_WIDTH];
    int      qy[MAZE_HEIGHT * MAZE_WIDTH];
    int      front = 0, back = 0, i, cx, cy, nx, ny;

    memset(visited, 0, sizeof(visited));
    for (cy = 0; cy < MAZE_HEIGHT; cy++)
        for (cx = 0; cx < MAZE_WIDTH; cx++)
            parent[cy][cx].x = parent[cy][cx].y = -1;

    qx[back] = from.x; qy[back] = from.y; back++;
    visited[from.y][from.x] = 1;

    while (front < back) {
        cx = qx[front]; cy = qy[front]; front++;

        if (cx == target.x && cy == target.y) {
            Position step = target;
            while (!(parent[step.y][step.x].x == from.x &&
                     parent[step.y][step.x].y == from.y)) {
                Position prev = parent[step.y][step.x];
                if (prev.x == -1) return from;
                step = prev;
            }
            return step;
        }

        for (i = 0; i < 4; i++) {
            nx = cx + DX[i]; ny = cy + DY[i];
            if (nx >= 0 && nx < MAZE_WIDTH  &&
                ny >= 0 && ny < MAZE_HEIGHT &&
                !visited[ny][nx]             &&
                game->maze[ny][nx] != CELL_WALL) {
                visited[ny][nx]  = 1;
                parent[ny][nx].x = cx;
                parent[ny][nx].y = cy;
                qx[back] = nx; qy[back] = ny; back++;
            }
        }
    }
    return from;
}