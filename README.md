﻿<h1 align="center"> Карткова гра "Дурень" </a> 
<h3 align="center"> Виконав студент навчального закладу КА "ШАГ" </h3>
<h3 align="center"> Vladyslav Seheda </h3>

<br><br>
___
> Консольна гра на одного гравця, написана на мові програмування С++.
___

# <h3 align="center"> Меню </h3>

1. [Правила гри.](#правила-гри)
2. [Опис гри.](#опис-гри)
3. [Процес гри.](#процес-гри)
    - [Система облікових записів.](#Система-облікових-записів)
        - [Створення облікового запису.](#Створення-облікового-запису)
        - [Вхід під створеним обліковим записом.](#Вхід-під-створеним-обліковим-записом)
    - [Перемішування карт.](#Перемішування-карт)
    - [Початок гри.](#Початок-гри)
        - [Роздача карт.](#Роздача-карт)
        - [Хід гравця.](#Хід-гравця)
        - [Хід бота.](#Хід-бота)
        - [Відбивання карт ботом.](#Відбивання-карт-ботом)
    - [Вивід карт.](#Вивід-карт)
4. [Завершення гри.](#Завершення-гри)
5. [Висновок.](#Висновок)

## ***Правила гри.***
«Дурень» — популярна стратегічна картярська гра для 2—6 гравців, поширена на території колишнього СРСР.
<br> У грі використовується колода з 36 карт і беруть участь від двох до шести гравців. Кожному роздається по 6 карт, 
остання карта відкривається і її масть визначає козир для даної гри, решта колоди кладеться зверху так, щоб козирну 
карту було видно всім.
<br> У грі є нічия: коли за ігровим столом залишається двоє гравців, гравець, що ходить кидає карти противнику так, 
щоб противник відбив усі карти і в обох гравців не залишається карт — тоді в грі оголошується нічия.
Ціль гри — позбутися всіх карт. Останній гравець, у якого залишилися карти, залишається в «дурнях». 
<br> У першій здачі першим ходить гравець із молодшим козирем. Хід робиться завжди ліворуч, і 
складається з викладання однієї або більше карт, і спроби гравця, під якого ходять, їх покрити або старшою картою 
тієї ж масті, або картою козирної масті, якщо карта, що криється, сама є козирною — у такому випадку її можна покрити 
тільки старшим козирем.

## Опис гри.
* У грі використовується:
    + *Колода карт = 36 карт*
    + *Карти ігрока = 6 карт*
    + *Карти бота = 6 карт*
    + *Масть = стандарт 4, один постійний козир*
    + *Козир = остання карта*
    + *Пріоритет (ранг) карт в колоді (від меншого до більшого значення): 6, 7, 8, 9, 10, J, Q, K, T.*
___
[Вверх](#-меню-)
___
## Процес гри.

### Система облікових записів.
   * _Створення облікового запису._
   * _Вхід під створеним обліковим записом._
   * _Вихід._
   ___
   [Вверх](#-меню-)
   ___
#### _Створення облікового запису._

```<>
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

```
![Фото](/SIGN_UP.png)

> В цьому пункті виконується створення нового користувача.

![Фото](/SIGN_UP1.png)

#### _Вхід під створеним обліковим записом._
![Фото](/SIGN_IN.gif)
___
 [Вверх](#-меню-)
 ___

### Перемішування карт

```С++
void Shuffle (Game_card& deck, int& size) {
    srand(time(NULL));
    int x, shuffled = 1000;
    for (int i = 0; i < shuffled; i++) {
        for (int i = 0; i < size; i++) {
            x = rand() % size;
            swap((&deck)[i], (&deck)[x]);
        }
    }
}
```
___
[Вверх](#-меню-)
___
### Початок гри

#### Роздача карт

Після перемішування колоди, роздаються карти. Кожному по 6 карт.
___
> Це робиться за допомогою функції: 
___
```С++
void MoveCard(Game_card*& Move_to, Game_card*& Move_from, int& size_to, int& size_from, int pos) {
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
```
Після чого, за допомогою функції вибору найменшого козиря, гру починає той, у кого в руках козир найменшого рангу.<br>
___
[Вверх](#-меню-)
___

#### Хід гравця
Гравець розміщує на столі будь-яку з наявних у нього карт, або (при бажанні і при наявності) кілька карт однакового значення (після вибору карт, гравець повинен натиснути "END"),
а бот-гравець повинен або обіграти його, або взяти. Щоб обіграти (синонім - прикривати) карту, потрібно покласти на неї старшу карту
такої ж масті або козиря, якщо розміщена карта не є козирем. Якщо розміщена карта - це козир, то обіграти її можна тільки старшим козирем.
Після того, як бот побив карту, хід переходить до нього. А карти викидаються у відбій.<br>
Якщо бот не може обіграти одну або кілька карт, він бере їх і пропускає хід. 

___
> Вибір карти виконується такою функцією:
___

```<
int choise(Game_card *&card, int &size) { 
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

```
![Фото](/Move.gif)

___
[Вверх](#-меню-)
___
#### Хід бота
Хід починається з вибору простої карти, після чого робиться перевірка, чи бот має карту такого ж рангу.
Якщо знаходить, тоді він викидує стільки скільки має однакових карт по ранзі.

```<language>
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
```
___
[Вверх](#-меню-)
___

#### Відбивання карт ботом
Процес починається з перевірки першої карти(якшо їх більше одної), якшо бот має карту для відбивання,йде перехід
до наступної перевірки,де знаходиться найменша карта відповідної масті і тільки тоді карта викидається на дошку, 
і йде перевірка другої карти. Якшо бот не має чим відбити першу карту (відповідно другу і т.д.), якшо вона проста,
перевіряється чи є козирна карта, якшо вона є, переходимо до перевірки знаходження найменшої козирної карти. Якшо після 
цих перевірок бот не має чим відбитися, перевірка закінчується і бот забирає карти з дошки.

> Фрагмент коду:
```<language>
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
                       if (bot[f].suit == trump[0].suit && min_card >= bot[f].value){ // вибір найменшої карти серед козирних
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
```
___
[Вверх](#-меню-)
___

### Вивід карт
- Карта складається з:
    - Символу (ранг)
    - Масті
    - Значення
    - Колір

Виводиться (малюється) карта за допомогою такої функції. Ця функція шаблонна, за допомогою неї також виводиться сорочка карт бота.
```<language>
template <class T>
void print(const T &ptr, int &value, short width, short height, bool active = false) {  // друкування передньої частини карти
    int size_small = width + 5;  //ширина
    int size_height = 5 + height;  //висота
    for (int i = width; i < size_small; i++) {
        for (int j = height; j < size_height; j++) {
            
            SetColor((&ptr)[value].color, active ? GREEN : WHITE);

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

```
___
[Вверх](#-меню-)
___

## Завершення гри
Після того, як в колоді не залишилося карт, гра продовжується з рештою карт під рукою за тими ж правилами 
(крім того, що забираються карти з колоди), поки всі гравці, крім хіба що одного, не використають всі свої карти.
Цей гравець, що залишився з картами, вважається невдахою (дурнем). 
  - Гра завершується при таких умовах:
    - Перемога гравця.
    - Перемога бота.
    - Нічия.

Всі дані записуються в статистику, яку можна подивитися через меню гри.

## Висновок
Починаючи навчатися в КА"ШАГ" я не думав, що програмування буде таким складним водночас таким цікавим.
Дякую викладачеві за надані знання, для завершення цієї курсової роботи. 

___
[Вверх](#-меню-)
___
