<h1 align="center"> Карткова гра "Дурень" </a> 
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
    - [Перемішування карт.](#Перемішування-карт)

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
[Вверх](#Меню)
___
## Процес гри.

### Система облікових записів.
   * _Створення облікового запису._
   * _Вхід під створеним обліковим записом._
   * _Вихід._
   ___
   [Вверх](#Меню)
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
 [Вверх](#Меню)
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
[Вверх](#Меню)
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
[Вверх](#Меню)
___

#### Хід гравця
Гравець розміщує на столі будь-яку з наявних у нього карт, або (при бажанні і при наявності) кілька карт однакового значення (після вибору карт, ігрок повинен натиснути "END"),
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
[Вверх](#Меню)
___



Після того, як в колоді не залишилося карт, гра продовжується з рештою карт під рукою за тими ж правилами (крім того, що забирають 
карти з колоди), поки всі гравці, крім хіба що одного, не використають всі свої карти. Цей гравець, що залишився з картами, 
вважається невдахою (дурнем). 
