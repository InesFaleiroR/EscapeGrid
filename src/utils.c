#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

void enableANSI(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD console_mode = 0;
    GetConsoleMode(hOut, &console_mode);
    console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, console_mode);
}

void hideCursor(void) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console_handle, &cursor_info);
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(console_handle, &cursor_info);
}

void showCursor(void) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console_handle, &cursor_info);
    cursor_info.bVisible = TRUE;
    SetConsoleCursorInfo(console_handle, &cursor_info);
}

void setupConsole(void) {
    SetConsoleOutputCP(65001);
    enableANSI();
    hideCursor();
    printf("\x1b[2J\x1b[H");
}

void sleepMs(int ms_val) {
    Sleep(ms_val);
}

int randomOdd(int minVal, int maxVal) {
    int number_val = minVal + (rand() % (maxVal - minVal + 1));
    if (number_val % 2 == 0) {
        if (number_val < maxVal) {
            number_val++;
        } else {
            number_val--;
        }
    }
    return number_val;
}

void trimNewline(char *text) {
    int len_val = (int)strlen(text);
    if (len_val > 0 && text[len_val - 1] == '\n') {
        text[len_val - 1] = '\0';
    }
}