#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Enums.h"
using namespace std;

void ConsoleCursorVisible() {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    structCursorInfo.dwSize = 99;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
}

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
        SetColor(BLACK, BLUE_FADE);
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
                SetColor(BLUE_FADE, WHITE);
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

int Registration_User(User& user) {
    int registr = 0;
    bool userexist = false;

    while (registr != 2) {
        registr = startLOG();
        system("cls");
        switch (registr) {
        case 0:
            user = registerNewUser();
            saveUser(user);
            userexist = true;
            break;
        case 1:
            user = loginUser();
            userexist = true;
            break;
        case 2:
            return registr;
        default:
            break;
        }
        if (userexist) {
            system("cls");
            break;
        }
    }
}

// Save user data to file
void saveUser(const User& user) {
    ofstream file(user.login + ".txt");
    file << user.login << endl;
    file << user.password << endl;
    file << user.game_count << " ";
    file << user.win_game << " ";
    file << user.lost_game << " ";
    file << user.nobody_win << " ";
    file.close();
}

// Load user data from file
void loadUser(User& user) {
    ifstream file(user.login + ".txt");
    getline(file, user.login);
    getline(file, user.password);
    file >> user.game_count;
    file >> user.win_game;
    file >> user.lost_game;
    file >> user.nobody_win;
    file.close();
}

// Check user exist (file with data
bool userExists(const User& user) {
    ifstream file(user.login + ".txt");
    return file.good();
}

//Registration
User registerNewUser() {
    User user;
    user.game_count = 0;
    user.win_game = 0;
    user.lost_game = 0;
    user.nobody_win = 0;
    string confirmPassword;
    while (true) {
        wcout << "Register new user" << endl;
        wcout << "Login: ";
        getline(cin, user.login);
        wcout << "Password: ";
        SetColor(WHITE, WHITE);
        getline(cin, user.password);
        SetColor(WHITE, BLACK);
        wcout << "Confirm : ";
        SetColor(WHITE, WHITE);
        getline(cin, confirmPassword);
        SetColor(WHITE, BLACK);
        SetColor(RED, BLACK);
        bool valid = true;

        if (user.login.size() < 5) {
            wcout << "Login must be more than 5 symbols" << endl;
            valid = false;
        }
        if (user.password.size() < 5) {
            wcout << "Password must be more than 5 symbols" << endl;
            valid = false;
        }
        if (user.password != confirmPassword) {
            wcout << "Passwords not equal" << endl;
            valid = false;
        }
        if (userExists(user)) {
            wcout << "user already exists" << endl;
            valid = false;
        }
        SetColor(WHITE, BLACK);
        if (valid) {
            break;
        }
        else {
            system("pause");
            int key = _getch();
            if (key == ESC) {
                exit(0);
            }
        }
        system("cls");
    }
    return user;
}

//Authorization
User loginUser() {
    User user;
    string password;
    while (true) {
        wcout << "Login user" << endl;
        wcout << "Login: ";
        getline(cin, user.login);
        wcout << "Password: ";
        SetColor(WHITE, WHITE);
        getline(cin, password);
        SetColor(WHITE, BLACK);
        SetColor(RED, BLACK);
        bool valid = true;
        if (user.login.size() < 5) {
            wcout << "Login invalid" << endl;
            valid = false;
        }
        if (valid && !userExists(user)) {
            wcout << "User not exists" << endl;
            valid = false;
        }
        else {
            loadUser(user);
        }
        if (valid && user.password != password) {
            wcout << "Invalid password" << endl;
            valid = false;
        }
        SetColor(WHITE, BLACK);
        if (valid) {
            break;
        }
        else {
            system("pause");
            int key = _getch();
            if (key == ESC) {
                exit(0);
            }
        }
        system("cls");
    }
    return user;
}
