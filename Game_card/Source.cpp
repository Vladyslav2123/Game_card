#include <Windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
}

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

int getKey() {
    if (_kbhit()) {
        return _getch();
    }
    return -1;
};

void SetColor(ConsoleColor text, ConsoleColor background = BLACK) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (short)text | ((short)background << 4));
}

void SetColor(short text, short background = BLACK) {
    SetColor((ConsoleColor)text, (ConsoleColor)background);
}

void ResetColor() {
    SetColor(WHITE, BLACK);
}

void SetCursorPosition(short x, short y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setMenuRowColor(const bool isActive) {
    if (isActive) {
        SetColor(BLACK, GREEN_FADE);
    }
    else {
        SetColor(RED, WHITE);
    }
}

void drawFrame(short height, short width) {
    for (short y = 8; y < height; y++) {
        for (short x = 32; x < width; x++) {
            if (x == 32 || y == 8 || x == width - 1 || y == height - 1) {
                SetCursorPosition(x, y);
                SetColor(RED, WHITE);
                wcout << "*";
            }
        }
    }
    SetColor(WHITE, BLACK);
}

void drawMenu(const int& activeOption) {
    short x = 35;
    short y = 10;
    SetCursorPosition(x, y++);
    setMenuRowColor(activeOption == 0);
    wcout << "Start game";
    SetCursorPosition(x, y++);
    setMenuRowColor(activeOption == 1);
    wcout << "Options";
    SetCursorPosition(x, y);
    setMenuRowColor(activeOption == 2);
    wcout << "Exit";
    SetColor(WHITE, BLACK);
}

void drawregistration(const int& activeOption) {
    short x = 35;
    short y = 10;
    SetCursorPosition(x, y++);
    setMenuRowColor(activeOption == 0);
    wcout << "SIGN UP";
    SetCursorPosition(x, y++);
    setMenuRowColor(activeOption == 1);
    wcout << "SIGN IN";
    SetCursorPosition(x, y);
    setMenuRowColor(activeOption == 2);
    wcout << "EXIT";
    SetColor(WHITE, BLACK);
}

int startMenu() {
    system("cls");
    int key;
    int activeOption = 0;
    drawMenu(activeOption);
    drawFrame(15, 47);
    while (true)
    {
        key = getKey();
        if (key != -1) {
            switch (key) {
            case UP_ARROW:
                if (activeOption > 0) {
                    activeOption--;
                }
                drawMenu(activeOption);
                break;
            case DOWN_ARROW:
                if (activeOption < 2) {
                    activeOption++;
                }
                drawMenu(activeOption);
                break;
            case ENTER:
                system("cls");
                return activeOption;
            default:
                break;
            }
        }
        Sleep(50);
    }
}

int startLOG() {
    system("cls");
    int key;
    int activeOption = 0;
    drawregistration(activeOption);
    drawFrame(15, 47);
    while (true)
    {
        key = getKey();
        if (key != -1) {
            switch (key) {
            case UP_ARROW:
                if (activeOption > 0) {
                    activeOption--;
                }
                drawregistration(activeOption);
                break;
            case DOWN_ARROW:
                if (activeOption < 2) {
                    activeOption++;
                }
                drawregistration(activeOption);
                break;
            case ENTER:
                system("cls");
                return activeOption;
            default:
                break;
            }
        }
    }
}