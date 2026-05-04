# Nome do executável
TARGET = EscapeGrid

# Compilador
CC = gcc

# Flags de compilação (warnings + debug básico)
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Ficheiros fonte
SRCS = src/main.c \
       src/game.c \
       src/player.c \
       src/enemy.c \
       src/maze.c

# Ficheiros objeto (gera automaticamente a partir dos .c)
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(TARGET)

# Criar executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilar ficheiros .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar ficheiros compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilar tudo do zero
rebuild: clean all

# Executar o jogo
run: $(TARGET)
	./$(TARGET)