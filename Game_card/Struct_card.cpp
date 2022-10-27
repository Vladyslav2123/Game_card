#include "Struct_card.h"
#include "Enums.h"

Game_card* Desk() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    Game_card* desk = new Game_card[36];
    desk[0] = { '6', L'\u2660',1 , BLACK};
    //TODO add color
    desk[1] = { '7', L'\u2660',2, BLACK };
    desk[2] = { '8', L'\u2660',3, BLACK };
    desk[3] = { '9', L'\u2660',4, BLACK };
    desk[4] = { 'A', L'\u2660',5, BLACK };
    desk[5] = { 'J', L'\u2660',6, BLACK };
    desk[6] = { 'Q', L'\u2660',7, BLACK };
    desk[7] = { 'K', L'\u2660',8, BLACK };
    desk[8] = { 'T', L'\u2660',9, BLACK };

    desk[9] = { '6', L'\u2663',1, BLACK };
    desk[10] = { '7', L'\u2663',2, BLACK };
    desk[11] = { '8', L'\u2663',3, BLACK };
    desk[12] = { '9', L'\u2663',4, BLACK };
    desk[13] = { 'A', L'\u2663',5, BLACK };
    desk[14] = { 'J', L'\u2663',6, BLACK };
    desk[15] = { 'Q', L'\u2663',7, BLACK };
    desk[16] = { 'K', L'\u2663',8, BLACK };
    desk[17] = { 'T', L'\u2663',9, BLACK };

    desk[18] = { '6', L'\u2665',1, RED };
    desk[19] = { '7', L'\u2665',2, RED };
    desk[20] = { '8', L'\u2665',3, RED };
    desk[21] = { '9', L'\u2665',4, RED };
    desk[22] = { 'A', L'\u2665',5, RED };
    desk[23] = { 'J', L'\u2665',6, RED };
    desk[24] = { 'Q', L'\u2665',7, RED };
    desk[25] = { 'K', L'\u2665',8, RED };
    desk[26] = { 'T', L'\u2665',9, RED };

    desk[27] = { '6', L'\u2666',1, RED };
    desk[28] = { '7', L'\u2666',2, RED };
    desk[29] = { '8', L'\u2666',3, RED };
    desk[30] = { '9', L'\u2666',4, RED };
    desk[31] = { 'A', L'\u2666',5, RED };
    desk[32] = { 'J', L'\u2666',6, RED };
    desk[33] = { 'Q', L'\u2666',7, RED };
    desk[34] = { 'K', L'\u2666',8, RED };
    desk[35] = { 'T', L'\u2666',9, RED };

    return desk;
}
