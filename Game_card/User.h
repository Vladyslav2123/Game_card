#pragma once

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "Enums.h"
#include "Menu.h"

using namespace std;

struct User {
    string login;
    string password;
    //Data fields...
    int game_count;
    int win_game;
    int lost_game;
    int nobody_win;
};

int Registration_User(User& user);

// Save user data to file
void saveUser(const User& user);
// Load user data from file
void loadUser(User& user);
// Check user exist (file with data
bool userExists(const User& user);
//Registration
User registerNewUser();
//Authorization
User loginUser();