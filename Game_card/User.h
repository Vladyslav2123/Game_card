#pragma once

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

struct User {
    string login;
    string password;
    //Data fields...
    int game_count;
    int win_count;
};

// Save user data to file
void saveUser(const User& user) {
    ofstream file(user.login + ".txt");
    file << user.login << endl;
    file << user.password << endl;
    file << user.game_count << " ";
    file << user.win_count << " ";
    file.close();
}
// Load user data from file
void loadUser(User& user) {
    ifstream file(user.login + ".txt");
    getline(file, user.login);
    getline(file, user.password);
    file >> user.game_count;
    file >> user.win_count;
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
    user.win_count = 0;
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