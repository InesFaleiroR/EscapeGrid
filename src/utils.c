#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

void enableANSI(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  m = 0;
    GetConsoleMode(h, &m);
    SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void hideCursor(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(h, &ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(h, &ci);
}

void showCursor(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(h, &ci);
    ci.bVisible = TRUE;
    SetConsoleCursorInfo(h, &ci);
}

void setupConsole(void) {
    SetConsoleOutputCP(65001);
    enableANSI();
    hideCursor();
    printf("\x1b[2J\x1b[H");
}

void sleepMs(int ms) { Sleep((DWORD)ms); }

int randomOdd(int minVal, int maxVal) {
    int n = minVal + rand() % (maxVal - minVal + 1);
    if (n % 2 == 0) n = (n < maxVal) ? n + 1 : n - 1;
    return n;
}

void trimNewline(char *s) {
    int l = (int)strlen(s);
    if (l > 0 && s[l - 1] == '\n') s[l - 1] = '\0';
}