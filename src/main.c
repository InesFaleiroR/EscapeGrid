#include <stdio.h>
#include <windows.h>
#include "../include/game.h"

int main() {
    // Configura o terminal para aceitar caracteres especiais (UTF-8)
    SetConsoleOutputCP(65001);
    system("cls"); // Limpa o lixo do compilador

    Game game;
    initGame(&game);
    gameLoop(&game);

    printf("\nJogo Terminado. Obrigado por jogar!\n");
    return 0;
}