#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

void setupConsole(void);
void enableANSI(void);
void hideCursor(void);
void showCursor(void);
void sleepMs(int ms);
int randomOdd(int min, int max);
void trimNewline(char *text);

#endif