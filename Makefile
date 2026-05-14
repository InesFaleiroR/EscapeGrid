CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude
SRC=src/main.c src/game.c src/maze.c src/enemy.c src/render.c src/input.c src/timer.c src/utils.c src/ranking.c
OUT=EscapeGrid.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)