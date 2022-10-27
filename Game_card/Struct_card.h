#pragma once
#pragma once

#include <iostream>
#include <io.h>
#include <fcntl.h>

struct Game_card {
    char card;
    wchar_t suit;
    int value;
};

Game_card* Desk() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    Game_card* desk = new Game_card[36];
    desk[0] = { '6', L'\u2660',1 };
    desk[1] = { '7', L'\u2660',2 };
    desk[2] = { '8', L'\u2660',3 };
    desk[3] = { '9', L'\u2660',4 };
    desk[4] = { 'A', L'\u2660',5 };
    desk[5] = { 'J', L'\u2660',6 };
    desk[6] = { 'Q', L'\u2660',7 };
    desk[7] = { 'K', L'\u2660',8 };
    desk[8] = { 'T', L'\u2660',9 };

    desk[9] = { '6', L'\u2663',1 };
    desk[10] = { '7', L'\u2663',2 };
    desk[11] = { '8', L'\u2663',3 };
    desk[12] = { '9', L'\u2663',4 };
    desk[13] = { 'A', L'\u2663',5 };
    desk[14] = { 'J', L'\u2663',6 };
    desk[15] = { 'Q', L'\u2663',7 };
    desk[16] = { 'K', L'\u2663',8 };
    desk[17] = { 'T', L'\u2663',9 };

    desk[18] = { '6', L'\u2665',1 };
    desk[19] = { '7', L'\u2665',2 };
    desk[20] = { '8', L'\u2665',3 };
    desk[21] = { '9', L'\u2665',4 };
    desk[22] = { 'A', L'\u2665',5 };
    desk[23] = { 'J', L'\u2665',6 };
    desk[24] = { 'Q', L'\u2665',7 };
    desk[25] = { 'K', L'\u2665',8 };
    desk[26] = { 'T', L'\u2665',9 };

    desk[27] = { '6', L'\u2666',1 };
    desk[28] = { '7', L'\u2666',2 };
    desk[29] = { '8', L'\u2666',3 };
    desk[30] = { '9', L'\u2666',4 };
    desk[31] = { 'A', L'\u2666',5 };
    desk[32] = { 'J', L'\u2666',6 };
    desk[33] = { 'Q', L'\u2666',7 };
    desk[34] = { 'K', L'\u2666',8 };
    desk[35] = { 'T', L'\u2666',9 };

    return desk;
}
