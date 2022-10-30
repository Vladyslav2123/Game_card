#pragma once

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <ctime>
#include "Enums.h"

void ConsoleCursorVisible();
int getKey();

void SetColor(ConsoleColor text, ConsoleColor background);

void SetColor(short text, short background);

void ResetColor();

void SetCursorPosition(short x, short y);

void setMenuRowColor(const bool isActive);

void drawFrame(short height, short width);

void drawMenu(const int& activeOption);

void drawregistration(const int& activeOption);

int startMenu();

int startLOG();

