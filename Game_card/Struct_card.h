#pragma once
#include "Enums.h"

#include <iostream>
#include <io.h>
#include <fcntl.h>

struct Game_card {
    char card;
    wchar_t suit;
    int value;
    short color;
};

Game_card* Desk();

struct Shirt_card {
    char card ;
    wchar_t suit ;
    short color ;
};