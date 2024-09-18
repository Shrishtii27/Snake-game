#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

int height = 25;
int width = 100;
int gameover = 0, counter, gameover2 = 0, choice, counter2;
int lflag = 0, rflag = 0, uflag = 0, dflag = 0;
int lflag2 = 0, rflag2 = 0, uflag2 = 0, dflag2 = 0;
short fcount;

class snake {
public:
    int x, y, fx, fy, x2, y2;
    int choice;
    char playername[50], playername2[50];

    class node {
    public:
        int nx, ny;
        node* next;
        node* back;
    };

    node* head = NULL;
    node* head2 = NULL;

    void gotoxy(int x, int y) {
        COORD pos = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void textcolor(int k) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
    }

    void name_and_score() {
        gotoxy(101, 0);
        textcolor(10);
        cout << playername << "'s SCORE = " << counter * 100;
        if (choice == 2) {
            gotoxy(101, 2);
            cout << playername2 << "'s SCORE = " << counter2 * 100;
            gotoxy(117, 6);
            cout << "  ";
            gotoxy(117, 6);
            cout << fcount;
        }
    }

    void window() {
        textcolor(choice == 1 ? 10 : 1);
        for (int i = 0; i <= width; i++) {
            gotoxy(i, 0); cout << "*";
            gotoxy(i, height); cout << "*";
        }
        for (int i = 0; i <= height; i++) {
            gotoxy(0, i); cout << "*";
            gotoxy(width, i); cout << "*";
        }
    }

    void setup() {
        counter = 0;
        gameover = 0;
        window();
        resetflag();
        name_and_score();
        head = new node;
        head->nx = width / 2;
        head->ny = height / 2;
        head->next = NULL;
        head->back = NULL;
        x = width / 2;
        y = height / 2;
        generate_fruit();
    }

    void setup2() {
        resetflag2();
        gameover2 = 0;
        counter2 = 0;
        fcount = 25;
        head2 = new node;
        head2->nx = width / 2 + 5;
        head2->ny = height / 2 + 5;
        head2->next = NULL;
        head2->back = NULL;
        x2 = width / 2 + 5;
        y2 = height / 2 + 5;
    }

    void drawlist(node* h, int k) {
        textcolor(k);
        node* ptr = h;
        while (ptr != NULL) {
            gotoxy(ptr->nx, ptr->ny);
            cout << "@";
            ptr = ptr->next;
        }
    }

    void destroylist(node* h) {
        node* ptr = h;
        while (ptr != NULL) {
            gotoxy(ptr->nx, ptr->ny);
            cout << " ";
            ptr = ptr->next;
        }
    }

    void draw() {
        drawlist(head, 2);
        drawlist(head2, 5);
        gotoxy(fx, fy);
        textcolor(10);
        cout << "*";
        Sleep(120);
        destroylist(head);
        destroylist(head2);
    }

    void resetflag() {
        uflag = dflag = lflag = rflag = 0;
    }

    void resetflag2() {
        uflag2 = dflag2 = lflag2 = rflag2 = 0;
    }

    void play() {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case 72: if (!dflag) { resetflag(); uflag = 1; } break; // up arrow
            case 80: if (!uflag) { resetflag(); dflag = 1; } break; // down arrow
            case 75: if (!rflag) { resetflag(); lflag = 1; } break; // left arrow
            case 77: if (!lflag) { resetflag(); rflag = 1; } break; // right arrow
            case 'w': if (!dflag2) { resetflag2(); uflag2 = 1; } break; // player 2 up
            case 's': if (!uflag2) { resetflag2(); dflag2 = 1; } break; // player 2 down
            case 'a': if (!rflag2) { resetflag2(); lflag2 = 1; } break; // player 2 left
            case 'd': if (!lflag2) { resetflag2(); rflag2 = 1; } break; // player 2 right
            default: break;
            }
        }
    }

    void generate_fruit() {
        do {
            fx = rand() % width;
        } while (fx == 0 || fx == width);
        do {
            fy = rand() % height;
        } while (fy == 0 || fy == height);
    }

    void run() {
        if (uflag) y--;
        else if (dflag) y++;
        else if (lflag) x--;
        else if (rflag) x++;

        if (uflag2) y2--;
        else if (dflag2) y2++;
        else if (lflag2) x2--;
        else if (rflag2) x2++;
    }

    void checkup() {
        if (choice == 1) {
            if (x == width || x == 0 || y == height || y == 0) gameover = 1;
        }
        node* h = head->next;
        while (h != NULL) {
            if (x == h->nx && y == h->ny) {
                gameover = 1;
                break;
            }
            h = h->next;
        }
        if (x == fx && y == fy) {
            node* t = new node;
            t->next = NULL;
            t->back = NULL;
            node* ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = t;
            t->back = ptr;
            generate_fruit();
            counter++;
            name_and_score();
        }
    }

    void checkup2() {
        if (x2 == width || x2 == 0 || y2 == height || y2 == 0) gameover2 = 1;
        node* h = head2->next;
        while (h != NULL) {
            if (x2 == h->nx && y2 == h->ny) {
                gameover2 = 1;
                break;
            }
            h = h->next;
        }
        if (x2 == fx && y2 == fy) {
            node* t = new node;
            t->next = NULL;
            t->back = NULL;
            node* ptr = head2;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = t;
            t->back = ptr;
            generate_fruit();
            counter2++;
            name_and_score();
        }
    }

    char end_game() {
        char c;
        gotoxy(width / 2 - 5, height / 2 - 4);
        cout << "GAME OVER\n";
        textcolor(10);
        cout << playername << " You Scored : " << counter * 100;
        if (choice == 2) {
            cout << playername2 << " You Scored : " << counter2 * 100;
            textcolor(4);
            cout << (gameover ? playername : playername2) << " has lost !";
        }
        textcolor(6);
        cout << "Want To Play Again? (Y/N): ";
        cin >> c;
        system("cls");
        return c;
    }

    void game1() {
        char ch;
        setup();
        do {
            window();
            while (!gameover) {
                draw();
                play();
                run();
                checkup();
            }
            ch = end_game();
        } while (ch == 'y' || ch == 'Y');
    }

    void game2() {
        char ch;
        setup2();
        setup();
        do {
            window();
            while (!gameover && !gameover2) {
                draw();
                play();
                run();
                checkup();
                checkup2();
            }
            ch = end_game();
        } while (ch == 'y' || ch == 'Y');
    }

    void welcome() {
        textcolor(10);
        gotoxy(width / 2 - 20, height / 2 - 4);
        cout << "Welcome To The Snake Game";
        cout << "Press any key to continue... ";
        _getch();
        system("cls");
        textcolor(12);
        cout << "Select An Option" << endl;
        cout << "1. Single Player" << endl;
        cout << "2. Multiplayer" << endl;
        cout << "Choose: ";
        cin >> choice;
        system("cls");
        cout << "Enter Player Name: ";
        cin >> playername;
        if (choice == 2) {
            cout << "Enter Player 2 Name: ";
            cin >> playername2;
        }
        system("cls");
    }
};

int main() {
    snake game;
    game.welcome();
    if (game.choice == 1) game.game1();
    else if (game.choice == 2) game.game2();
    return 0;
}

