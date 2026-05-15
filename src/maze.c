#include <stdlib.h>
#include <string.h>

#include "../include/maze.h"
#include "../include/pathfinding.h"

static int carveDirs[4][2] = { {0,-2},{0,2},{-2,0},{2,0} };

static void shuffle(int order[4]) {
    int i, j, tmp;
    for (i = 0; i < 4; i++) order[i] = i;
    for (i = 3; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = order[i]; order[i] = order[j]; order[j] = tmp;
    }
}

void carveMaze(Game *game, int x, int y) {
    int order[4], i, dir, nx, ny;
    game->maze[y][x] = CELL_PATH;
    shuffle(order);
    for (i = 0; i < 4; i++) {
        dir = order[i];
        nx  = x + carveDirs[dir][0];
        ny  = y + carveDirs[dir][1];
        if (nx > 0 && ny > 0 && nx < MAZE_WIDTH-1 && ny < MAZE_HEIGHT-1
            && game->maze[ny][nx] == CELL_WALL) {
            game->maze[y + carveDirs[dir][1]/2]
                      [x + carveDirs[dir][0]/2] = CELL_PATH;
            carveMaze(game, nx, ny);
        }
    }
}

int isWalkable(Game *game, int x, int y) {
    if (x < 0 || y < 0 || x >= MAZE_WIDTH || y >= MAZE_HEIGHT) return 0;
    return game->maze[y][x] != CELL_WALL;
}

static Position randomPath(Game *game) {
    Position p;
    do {
        p.x = 1 + rand() % (MAZE_WIDTH  - 2);
        p.y = 1 + rand() % (MAZE_HEIGHT - 2);
    } while (game->maze[p.y][p.x] != CELL_PATH);
    return p;
}

static void openExtraPaths(Game *game, int chance) {
    int y, x;
    if (chance <= 0) return;
    for (y = 2; y < MAZE_HEIGHT-2; y += 2)
        for (x = 2; x < MAZE_WIDTH-2; x += 2)
            if (game->maze[y][x] == CELL_WALL && (rand() % 100) < chance)
                game->maze[y][x] = CELL_PATH;
    for (y = 1; y < MAZE_HEIGHT-1; y++)
        for (x = 1; x < MAZE_WIDTH-1; x++)
            if (game->maze[y][x] == CELL_WALL && (rand() % 100) < (chance/2))
                game->maze[y][x] = CELL_PATH;
}

static void addExtraWalls(Game *game, int chance) {
    int y, x;
    if (chance <= 0) return;
    for (y = 2; y < MAZE_HEIGHT-2; y++)
        for (x = 2; x < MAZE_WIDTH-2; x++)
            if (game->maze[y][x] == CELL_PATH && (rand() % 100) < chance)
                game->maze[y][x] = CELL_WALL;
}

void generateMaze(Game *game) {
    int valid = 0, y, x;

    while (!valid) {
        /* 1. Inicializar tudo a parede */
        for (y = 0; y < MAZE_HEIGHT; y++)
            for (x = 0; x < MAZE_WIDTH; x++)
                game->maze[y][x] = CELL_WALL;

        /* 2. Escavar labirinto perfeito DFS */
        carveMaze(game, 1, 1);

        /* 3. Abrir caminhos extra (fácil) */
        if (game->extraPathChance > 0)
            openExtraPaths(game, game->extraPathChance);

        /* 4. Posições fixas */
        game->player.x = 1; game->player.y = 1;
        game->maze[1][1] = CELL_PATH;
        game->exitPos.x = MAZE_WIDTH-2; game->exitPos.y = MAZE_HEIGHT-2;
        game->maze[game->exitPos.y][game->exitPos.x] = CELL_EXIT;
        game->enemy.x = MAZE_WIDTH-4; game->enemy.y = 1;
        game->maze[game->enemy.y][game->enemy.x] = CELL_PATH;

        /* 5. Paredes extra (difícil) */
        if (game->extraWallChance > 0) {
            char sp = game->maze[game->player.y][game->player.x];
            char se = game->maze[game->exitPos.y][game->exitPos.x];
            char sn = game->maze[game->enemy.y][game->enemy.x];
            addExtraWalls(game, game->extraWallChance);
            game->maze[game->player.y][game->player.x]   = sp;
            game->maze[game->exitPos.y][game->exitPos.x] = se;
            game->maze[game->enemy.y][game->enemy.x]     = sn;
        }

        /* 6. Chave (médio e difícil) */
        if (game->keyRequired) {
            game->keyPos = randomPath(game);
            while ((game->keyPos.x == game->player.x  && game->keyPos.y == game->player.y)  ||
                   (game->keyPos.x == game->exitPos.x && game->keyPos.y == game->exitPos.y) ||
                   (game->keyPos.x == game->enemy.x   && game->keyPos.y == game->enemy.y))
                game->keyPos = randomPath(game);
            game->maze[game->keyPos.y][game->keyPos.x] = CELL_KEY;
            game->hasKey = 0;
        }

        /* 7. NPC (fácil e médio) */
        if (game->npcActive) {
            game->npcPos = randomPath(game);
            while ((game->npcPos.x == game->player.x  && game->npcPos.y == game->player.y)  ||
                   (game->npcPos.x == game->exitPos.x && game->npcPos.y == game->exitPos.y) ||
                   (game->npcPos.x == game->enemy.x   && game->npcPos.y == game->enemy.y)   ||
                   (game->keyRequired &&
                    game->npcPos.x == game->keyPos.x  && game->npcPos.y == game->keyPos.y))
                game->npcPos = randomPath(game);
            game->maze[game->npcPos.y][game->npcPos.x] = CELL_NPC;
            game->npcTalked = 0;
        }

        /* 8. Verificar solubilidade via BFS */
        {
            Position pFrom = game->player;
            Position pTo   = game->exitPos;
            valid = pathExists(game, pFrom, pTo);
            if (valid && game->keyRequired)
                valid = pathExists(game, pFrom, game->keyPos) &&
                        pathExists(game, game->keyPos, pTo);
        }
    }
}