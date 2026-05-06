# =========================
# EscapeGrid - Makefile Final (MSYS2)
# =========================

# Nome do executável
TARGET = EscapeGrid.exe

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Ficheiros fonte
SRCS = src/main.c \
       src/game.c \
       src/player.c \
       src/enemy.c \
       src/maze.c

# Objetos gerados automaticamente
OBJS = $(SRCS:.c=.o)

# =========================
# REGRAS PRINCIPAIS
# =========================

all: $(TARGET)

# Link final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compilação dos .c para .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# LIMPEZA (MSYS2 COMPATÍVEL)
# =========================
clean:
	rm -f src/*.o EscapeGrid.exe 2>/dev/null || true

# =========================
# EXECUÇÃO
# =========================
run: all
	./$(TARGET)

# =========================
# REBUILD COMPLETO
# =========================
rebuild: clean all