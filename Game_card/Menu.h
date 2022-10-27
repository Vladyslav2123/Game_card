#pragma once

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <ctime>

void ConsoleCursorVisible(bool show, short size);

enum ConsoleColor {
    GRAY = 8, BLUE, GREEN,
    TEAL, RED, PINK,
    YELLOW, WHITE,
    BLACK = 0, BLUE_FADE, GREEN_FADE,
    TEAL_FADE, RED_FADE, PINK_FADE,
    YELLOW_FADE, WHITE_FADE,
};
enum Keys {
    ESC = 27, ARROW_START = 224, ENTER = 13,
    UP_ARROW = 72, DOWN_ARROW = 80, LEFT_ARROW = 75, RIGHT_ARROW = 77
};
int getKey();

void SetColor(ConsoleColor text, ConsoleColor background = BLACK);

void SetColor(short text, short background = BLACK);

void ResetColor();

void SetCursorPosition(short x, short y);

void setMenuRowColor(const bool isActive);

void drawFrame(short height, short width);

void drawMenu(const int& activeOption);

void drawregistration(const int& activeOption);

int startMenu();

int startLOG();