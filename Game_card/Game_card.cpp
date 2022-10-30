﻿#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <string.h>
#include "Menu.h"
#include "Struct_card.h"
#include "User.h"

using namespace std;

void Shuffle(Game_card& deck, int& size) { //Перемішування карт
    srand(time(NULL));
    int x, shuffled = 1000;
    for (int i = 0; i < shuffled; i++) {
        for (int i = 0; i < size; i++) {
            x = rand() % size;
            swap((&deck)[i], (&deck)[x]);
        }
    }
}

void MoveCard(Game_card*& Move_to, Game_card*& Move_from, int& size_to, int& size_from, int pos) { // Переміщення карт з одного масиву в інший масив
    int how = 1;
    Game_card* arr_to = new Game_card[size_to + how];
    Game_card* arr_from = new Game_card[size_from - how];

    for (int i = 0; i < size_to; i++) {
        arr_to[i] = Move_to[i];
    }
        arr_to[size_to] = Move_from[pos];
        
        for (int i = 0; i < pos; i++) {
            arr_from[i] = Move_from[i];
        }
        for (int i = pos; i < size_from - how; i++) {
            arr_from[i] = Move_from[i + how];
        }

    size_to += how;
    size_from -= how;

    delete[]Move_from;
    delete[]Move_to;

    Move_to = arr_to;
    Move_from = arr_from;
    SetColor(WHITE,BLACK);
}

void print(const Game_card & ptr, int& value, short width, short height, bool active = false) {  // друкування передньої частини карти
    int size_small = width + 5;  //ширина
    int size_height = 5 + height;  //висота
    for (int i = width; i < size_small; i++) {
        for (int j = height; j < size_height; j++) {
            
            SetColor((&ptr)[value].color, active ? BLUE_FADE : WHITE);

            if (i == width && j == height || j == height && i == size_small - 1 || i == width && j == size_height - 1 || i == size_small - 1 && j == size_height - 1) {
                SetCursorPosition(i, j);
                wcout << (&ptr)[value].suit;
            }
            else if (i == (width + 2) && j == (height + 2)) {
                SetCursorPosition(i, j);
                if ((&ptr)[value].card == 'A') {
                    wcout << 10;
                }
                else
                    wcout << (&ptr)[value].card;
            }
            else {
                SetCursorPosition(i, j);
                if (i == (width + 3) && (&ptr)[value].card == 'A' && j == (height + 2))
                {
                    continue;
                }
                wcout << " ";
            }
        }
    }
    SetColor(WHITE, BLACK);
}

int choise(Game_card *&card, int &size) { // вибір карти ігроком
    int key;
    int activeOption = 0;
    int x = 0, y = 1;
    int i = 0;

    while (true){
        x = 0;
        key = getKey();
        if (key != -1) {
            switch (key) {
            case LEFT_ARROW:
                if (activeOption > 0) {
                    activeOption--;
                }
                for ( i = 0; i < size+1; i++) {
                    if (i < size){
                        print(*card, i, x, y, activeOption == i);
                        x += 9;
                    }
                    else {
                        SetCursorPosition(x,y);
                        setMenuRowColor(activeOption == i);
                        wcout << "END";
                    }
                }
                break;
            case RIGHT_ARROW:
                if (activeOption < size) {
                    activeOption++;
                }
                for ( i = 0; i < size+1; i++) {
                    if (i < size) {
                        print(*card, i, x, y, activeOption == i);
                        x += 9;
                    }
                    else {
                        SetCursorPosition(x, y);
                        setMenuRowColor(activeOption == i);
                        wcout << "END";
                    }
                }
                break;
            case ENTER:
                return activeOption;
            default:
                break;
            }
        }
    }
    SetColor(WHITE, BLACK);
}

bool Min_trump(Game_card*& bot, Game_card*& players, Game_card* trump, int& size_bot, int& size_player) { // Знаходження найменшого козиря, хто буде ходити
    int min_bot = 10;
    int min_player = 10;
    int c = 0, v = 0;
    bool good = true;
    for (int i = 0; i < size_player; i++) {
        if (players[i].suit == trump[0].suit && players[i].value < min_player) {
            min_player = players[i].value;
            c++;
        }
    }
    if (c == 0) {
        min_player = 0;
    }
    for (int i = 0; i < size_bot; i++) {
        if (bot[i].suit == trump[0].suit && bot[i].value < min_bot) {
            min_bot = bot[i].value;
            v++;
        }
    }
    if (v == 0) {
        min_bot = 0;
    }
    if (c > 0 && v > 0) {
        good = (min_player <= min_bot);
    }
    else if (c > 0 || v > 0) {
        if (c > 0) {
            good = true;
        }
        else {
            good = false;
        }
    }
    return good;
}

void Print_desk(Game_card*& deck, Game_card*& bot, Game_card*& players, int& size_bot, int& size_player, int& size_deck, Game_card* trump){ // Друкування частини дошки
    int size_trump = 0;
    int x = 0, y = 1;
    SetColor(WHITE, BLACK);
    SetCursorPosition(55, 15);
    wcout << "Number of card: " << size_deck;
    SetCursorPosition(0, 0);
    wcout << "Player's card:" << endl;
    SetCursorPosition(60, 8);
    print(*trump, size_trump, 60, 8);
    x = 0;
    y = 1;

    for (int i = 0; i < size_player; i++) {
        print(*players, i, x, y);
        x += 9;
    }

    SetCursorPosition(0, 22);
    wcout << "Bot's card: " << endl;
    SetColor(WHITE, BLACK);
}

void Player_game(Game_card*& deck, Game_card*& bot, Game_card*& players, int& size_bot, int& size_player, int& size_deck, Game_card* trump) { // ХІД ІГРОКА
    int number_of_card = 0;
    int value_delete = 1;
    int select = 0;
    int min = 0;
    int min_card = 0;
    int size_trump = 0;
    int size_table = 0;
    int size_table_bot = 0;
    int push_card = 1;
    int position = 0;
    bool contin = true;
    int x = 0, y = 1, i = 0;

    do {
    new_start:
        Game_card* table_player = new Game_card[value_delete];
        Game_card* table_bot = new Game_card[value_delete];
        if (size_player == 0 || size_bot == 0) {
            goto end;
        }
        do {
            do {
            repit:
                system("cls");
                Print_desk(deck, bot, players, size_bot, size_player, size_deck, trump);
                x = 0;
                y = 8;

                for (int i = 0; i < size_table; i++) {
                    print(*table_player, i, x, y);
                    x += 9;
                }
                
                number_of_card = choise(players, size_player);  // вибір карти ігроком
                
                if (number_of_card > (size_player-1)) {
                    SetColor(WHITE, BLACK);
                    goto play;
                }

                for (i = 0; i < size_table; i++) {
                    if (players[number_of_card].value != table_player[i].value) { // перевірка, яку карту викинув ігрок на стіл, чи карта того ж рангу
                        SetColor(WHITE, BLACK);
                        goto repit;
                    }
                }
                x = 0;
                y = 8;
                MoveCard(table_player, players, size_table, size_player, number_of_card);
                for (int i = 0; i < size_table; i++) {
                    print(*table_player, i, x, y);
                    x += 9;
                }
                SetColor(WHITE, BLACK);
            } while (size_player != 0);
        } while (!(size_player != -1));

    play:
        if (size_table == 0) {
            SetColor(WHITE, BLACK);
            goto repit;
        }
        if (size_player != 0 || size_bot != 0) {
            SetColor(WHITE, BLACK);
            SetCursorPosition(1, 14);  // Відбивання бота
            wcout << "Bot move!";
            
            for ( i = 0; i < size_table; i++) {
                for (int k = 0; k < size_bot; k++) {
                    if (bot[k].suit == table_player[i].suit && bot[k].value > table_player[i].value) { // перевірка на наявність простої карти
                        min = k;
                        min_card = bot[k].value;
                        for (int r = k; r < size_bot; r++) {
                            if (bot[r].suit == table_player[i].suit && min_card >= bot[r].value && bot[r].value > table_player[i].value) { // вибір найменшої карти серед простих
                                min = r;
                                min_card = bot[r].value;
                            }
                        }
                        MoveCard(table_bot, bot, size_table_bot, size_bot, min);
                        break;
                    }
                }
                if (i == size_table_bot) {
                    for (int l = 0; l < size_bot; l++) {
                        if (bot[l].suit == trump[0].suit && table_player[i].suit != trump[0].suit) { // перевірка на наявність козирної карти
                            min = l;
                            min_card = bot[l].value;
                            for (int f = l; f < size_bot; f++) {
                                if (bot[f].suit == trump[0].suit && min_card >= bot[f].value) // вибір найменшої карти серед козирних
                                {
                                    min = f;
                                    min_card = bot[f].value;
                                }
                            }
                            MoveCard(table_bot, bot, size_table_bot, size_bot, min);
                            break;
                        }
                        else if (bot[l].suit == trump[0].suit && table_player[i].suit == trump[0].suit && bot[l].value > table_player[i].value) { // перевірка козирної карти відовідно до козирної
                            min = l;
                            min_card = bot[l].value;
                            for (int d = l; d < size_bot; d++) {
                                if (bot[d].suit == trump[0].suit && min_card >= bot[d].value) // вибір карти серед козирних
                                {
                                    min = d;
                                    min_card = bot[d].value;
                                }
                            }
                            MoveCard(table_bot, bot, size_table_bot, size_bot, min);
                            break;
                        }
                    }
                }
                if (i == size_table_bot) { // Перевірка, чи відбита карта 
                    break;
                }
            }

            if (size_table_bot == size_table) { //Перевірка, на кількість відбитих карт 
                Print_desk(deck, bot, players, size_bot, size_player, size_deck, trump);
                x = 0;
                y = 23;
                SetCursorPosition(x, y);
                for (int i = 0; i < size_bot; i++) {
                    print(*bot, i, x, y);
                    x += 9;
                }
                x = 0;
                int p = 0;
                for (i = 0; i < size_table; i++) {
                    y = 8;
                    print(*table_player, i, x, y);
                    x += 9;
                    y = 15;
                    print(*table_bot, i, p, y);
                    p += 9;
                }
                system("pause");
                goto end;
            }
            SetCursorPosition(1, 16);
            wcout << "Bot take.";
            system("pause");
            
            while (size_table != 0 || size_table_bot != 0) {  // переміщення карт з дошки до карт бота
                MoveCard(bot, table_player, size_bot, size_table, position);
                if (size_table_bot != 0) {
                    MoveCard(bot, table_bot, size_bot, size_table_bot, position);
                }
            }
            while (size_player < 6 && size_deck > 0) {
                MoveCard(players, deck, size_player, size_deck, position);
            }
            while (size_bot < 6 && size_deck > 0) {
                MoveCard(bot, deck, size_bot, size_deck, position);
            }
            
            delete[]table_player;
            delete[]table_bot;
            size_table = 0;
            size_table_bot = 0;
            SetColor(WHITE, BLACK);
            goto new_start;  // бот взяв карти, перехід до ходу ігрока
        }

    end:  // бот відбив карти ігрока, кінець ходу ігрока
        while (size_player < 6 && size_deck > 0) {  
            MoveCard(players, deck, size_player, size_deck, position);
        }
        while (size_bot < 6 && size_deck > 0) {
            MoveCard(bot, deck, size_bot, size_deck, position);
        }
        delete[]table_player;
        delete[]table_bot;
        size_table = 0;
        size_table_bot = 0;

        contin = true;
    } while (!contin);
    _getch();
}

int GoSimpleBot(Game_card *&bot, int & size_bot, Game_card* trump) { // Функція вибору простої карти бота
    int min = 0;
    int min_card = 0;
    for (int k = 0; k < size_bot; k++) {
        if (bot[k].suit != trump[0].suit) {
            min = k;
            min_card = bot[k].value;
            for (int j = k; j < size_bot; j++) {
                if (bot[j].suit != trump[0].suit && min_card >= bot[j].value) {
                    min_card = bot[j].value;
                    min = j;
                }
            }
            break;
        }
    }
    return min;
}

int GoTrumpBot(Game_card*& bot, int& size_bot, Game_card* trump) { // Функція вибору козирної карти бота
    int min = 0;
    int min_card = 0;
    for (int i = 0; i < size_bot; i++) {
        if (bot[i].suit == trump[0].suit) {
            min = i;
            min_card = bot[i].value;
            for (int j = i; j < size_bot; j++) {
                if (bot[j].suit == trump[0].suit && min_card >= bot[j].value) {
                    min = j;
                    min_card = bot[j].value;
                }
            }
            break;
        }
    }
    return min;
}

void Bot_game(Game_card*& deck, Game_card*& bot, Game_card*& player, int& size_bot, int& size_player, int& size_deck, Game_card* trump) {  // ХІД БОТА
    int number_of_card = 0;
    int size_trump = 0;
    int answer = 0;
    int value_delete = 1;
    int size_table = 0;
    int size_table_bot = 0;
    int s = 0;
    int min = 0;
    int x = 0;
    int y = 0;
    bool contin = true;
    do {
        start_game:
        system("cls");
        Game_card* table_player = new Game_card[value_delete];
        Game_card* table_bot = new Game_card[value_delete];
        if (size_bot == 0 && size_deck == 0) {
            goto end_game;
        }
        Print_desk(deck, bot, player, size_bot, size_player, size_deck, trump);
        SetCursorPosition(15, 7);
        wcout << "Bot move!";
        
        for (int i = 0; i < size_bot; i++) { //Вибір ботом простої карти,якою ходити
            if (bot[i].suit != trump[0].suit) {
                min = GoSimpleBot(bot, size_bot, trump);
                MoveCard(table_bot, bot, size_table_bot, size_bot, min); // визов функції
                for (int k = 0; k < size_bot; k++) {  // перевірка, чи бот має ще одну карту такого рангу
                    for (int j = 0; j < size_table_bot; j++) {
                        if (bot[k].value == table_bot[j].value) {
                            MoveCard(table_bot, bot, size_table_bot, size_bot, k);
                        }
                    }
                }
                if (size_bot == 1 && size_table_bot == 1 && bot[size_trump].card == 'T')
                {
                    swap(bot[size_trump], table_bot[size_trump]);
                }
                goto end;
            }
        }

        min = GoTrumpBot(bot, size_bot, trump);//Вибір ботом козирної карти,якою ходити
        MoveCard(table_bot, bot, size_table_bot, size_bot, min);

        if (size_bot == 1 && size_table_bot == 1 && bot[size_trump].card == 'T' && bot[size_trump].suit == trump[size_trump].suit)
        {
            swap(bot[size_trump], table_bot[size_trump]);
        }

    end: // початок вибору карти ігроком
        do {
        system("cls");
        contin = true;
        Print_desk(deck, bot, player, size_bot, size_player, size_deck, trump);
        x = 0;
        for (int i = 0; i < size_table_bot; i++) {
            print(*table_bot, i, x, 8);
            x += 9;
        }

        x = 0;
        for (int i = 0; i < size_table; i++) {
            print(*table_player, i, x, 15);
            x += 9;
        }

        number_of_card = choise(player, size_player); // вибір карти ігроком

        if (number_of_card > (size_player - 1)) { // якщо ігрок не має чим відбитися, то натискаючи END переходимо до пункту взяття карт
            SetColor(WHITE, BLACK);
            goto take;
        }

        for (int i = 0; i < size_table_bot; i++) { // перевірка чи карта ігрока може побити карту бота
            if (i == size_table) {
                if (player[number_of_card].suit == table_bot[i].suit && player[number_of_card].value > table_bot[i].value) {
                    MoveCard(table_player, player, size_table, size_player, number_of_card);
                    break;
                }
                else if (player[number_of_card].suit == trump[size_trump].suit && table_bot[i].suit != trump[size_trump].suit) {
                    MoveCard(table_player, player, size_table, size_player, number_of_card);
                    break;
                }
            }
        }

        if (size_table != size_table_bot) {
            contin = false;
        }
            SetColor(WHITE, BLACK);
        } while (!contin);

        Print_desk(deck, bot, player, size_bot, size_player, size_deck, trump);
            SetCursorPosition(15, 14);
            wcout << "Your move! ";
            SetCursorPosition(0, 22);
            wcout << "Bot's card: " << endl;
            x = 0;
            for (int i = 0; i < size_bot; i++) {
                print(*bot, i, x, 23);
                x += 9;
            }

            x = 0;
            for (int i = 0; i < size_table; i++) {
                print(*table_player, i, x, 15);
                x += 9;
            }
            while (size_player < 6 && size_deck > 0) {
                MoveCard(player, deck, size_player, size_deck, size_trump);
            }
            while (size_bot < 6 && size_deck > 0) {
                MoveCard(bot, deck, size_bot, size_deck, size_trump);
            }
            system("pause");
            goto end_game;
        
        take:
        SetCursorPosition(15, 15);
        wcout << "You take card: ";
        system("pause");
        while (size_table != 0 || size_table_bot != 0) {
            MoveCard(player, table_bot, size_player, size_table_bot, size_trump);
            if (size_table != 0) {
                MoveCard(player, table_player, size_player, size_table, size_trump);
            }
        }
        while (size_player < 6 && size_deck > 0) {
            MoveCard(player, deck, size_player, size_deck, size_trump);
        }
        while (size_bot < 6 && size_deck > 0) {
            MoveCard(bot, deck, size_bot, size_deck, size_trump);
        }


        delete[]table_player;
        delete[]table_bot;
        size_table = 0;
        size_table_bot = 0;
        goto start_game; // Якшо ігрок взяв карти, перехід до нового ходу бота

    end_game: // кінець ходу бота
        delete[]table_player;
        delete[]table_bot;
        size_table = 0;
        size_table_bot = 0;
        contin = true;
    } while (!contin);
}

void Game(Game_card*& deck, Game_card*& bot, Game_card*& players, int& size_bot, int& size_player, int& size_deck, Game_card* trump, User& user) { // Хід ігри
    int position = 0;
    int push_card = 0;
    int delet = 1;
    const int t = 1;

    while (size_player < 6 && size_deck > 0) { // Роздача карт ігроку
        MoveCard(players, deck, size_player, size_deck, position);
    }
    while (size_bot < 6 && size_deck > 0) {
        MoveCard(bot, deck, size_bot, size_deck, position); // Роздача карт боту
    }
    
    bool good = Min_trump(bot, players, trump, size_bot, size_player); // Функція вибору , хто ходить першим

    if (good) {
        do {
            Player_game(deck, bot, players, size_bot, size_player, size_deck, trump);
            if (size_player == 0 || size_bot == 0) {
                break;
            }
            Bot_game(deck, bot, players, size_bot, size_player, size_deck, trump);
            if (size_player == 0 || size_bot == 0) {
                break;
            }
        } while (size_bot > 0 && size_player > 0);
    }
    else {
        do {
            Bot_game(deck, bot, players, size_bot, size_player, size_deck, trump);
            if (size_player == 0 || size_bot == 0) {
                break;
            }
            Player_game(deck, bot, players,  size_bot, size_player, size_deck, trump);
            if (size_player == 0 || size_bot == 0) {
                break;
            }
        } while (size_bot > 0 && size_player > 0);
    }

    if (size_player == 0 && size_bot > 0) { // Перемога ігрока
        system("cls");
        user.win_count++;
        SetCursorPosition(5, 5);
        wcout << "You WIN! " << endl;
        system("pause");
        _getch();
    }
    else if (size_bot == 0 && size_player > 0) { // Перемога бота
        system("cls");
        SetCursorPosition(5, 5);
        wcout << "Bot WIN! " << endl;
        system("pause");
        _getch();
    }
    else if (size_bot == 0 && size_player == 0) { // Нічия
        system("cls");
        SetCursorPosition(5, 5);
        wcout << "Nobody's WIN! " << endl;
        system("pause");
        _getch();
    }
}

void PrintUser(const User& user) { // Друкування даних про користувача
    const char* str = user.login.c_str();
    wcout << "Name     : " << str << endl;
    wcout << "Games    : " << user.game_count << endl;
    wcout << "Win games: " << user.win_count << endl;
}

int main() {
    ConsoleCursorVisible(false,100);
    srand(time(NULL));
    int SIZE = 0;
    int size_p = 0;
    int size_b = 0;
    const int t = 1;
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    User user;
    int menuOption = 0;
    
    //int registr = Registration_User(user); // Меню регістрації, входу

    //if (registr == 2) {
    //    return 0;
    //}

    do {
        SIZE = 36;
        size_p = 0;
        size_b = 0;
        menuOption = startMenu();
        Game_card* desk = new Game_card[SIZE];
        Game_card* player = new Game_card[size_p];
        Game_card* bot = new Game_card[size_b];
        Game_card trump[t] = { 0 };

        switch (menuOption) {
        case 0:
            desk = Desk();
            Shuffle(*desk, SIZE);
            trump[0] = desk[SIZE - 1];

            user.game_count++;
            saveUser(user);
            Game(desk, bot, player, size_b, size_p, SIZE, trump, user);
            
            delete[]desk;
            delete[]player;
            delete[]bot;
            break;
        case 1:
            PrintUser(user);
            system("pause");
            _getch();
        case 2:
            wcout << "Good Bye!";
        }
    } while (menuOption != 2);

    _getch();

    return 0;
}