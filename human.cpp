#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

constexpr int U = 72;
constexpr int D = 80;
constexpr int L = 75;
constexpr int R = 77;

string graph[] = {
    "111111111111111111111111111111111111111111111e11111",
    "100010000010001010100010100000000010100010001000001",
    "101011111011111010101010111111111010111011101111101",
    "101000100000000010001000100000001010001000101000101",
    "101110111111111111101111101111101111101111101010101",
    "100010100010000000101000100000100010001000101010101",
    "111010101010111110111010111011111010111010101010101",
    "100010001000100000100010100010000010100010101010001",
    "101111111111101110101110101110111010101110101011111",
    "100010001000001000101010101010100010001010100010001",
    "111010101011111011101010101010111111111010101110101",
    "101010101010000000101010000010000000000010100010101",
    "101011101011111110101011111111101011111011111011101",
    "100010001000001000100000001000101010001000001000101",
    "101110111111101011111110111010111010111111101110101",
    "100010000010001000000010100010000010001000001010001",
    "111011101010111110111110101111111110101011111011101",
    "100010001010100010100000101000001000101010000010001",
    "101110111110101011101111101011111011101011101010111",
    "101000000010001010001000001000000000100000001010001",
    "101011111011111010111011111111111111111111101111101",
    "101010000000101000101000000010000000001000101000001",
    "101110111110101111101111111010111111101010111011111",
    "100000100000000000000000001000000000100010000000001",
    "1s1111111111111111111111111111111111111111111111111",
};

int h = sizeof(graph) / sizeof(graph[0]);
int w = graph[0].length();

class cursor {
public:
    COORD pos;
    cursor(COORD start)
    {
        pos.X = start.X;
        pos.Y = start.Y;
    }
    void gotoxy(short x, short y)
    {
        COORD position = { x << 1, y };
        auto std = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(std, position);
    }
    void delete_cursor()
    {
        gotoxy(pos.X, pos.Y);
        cout << "  ";
    }
    void move(int x, int y)
    {
        if (!can_go(x, -y)) return;
        delete_cursor();
        pos.X += x;
        pos.Y -= y;
        gotoxy(pos.X, pos.Y);
        cout << "■";
        game_end(pos.X, pos.Y);
    }
    void game_end(int x, int y)
    {
        if (graph[y][x] == 'e')
        {
            gotoxy(0, h + 10);
            system("pause");
            system("pause");
            exit(0);
        }
    }
    void hide_cursor()
    {
        CONSOLE_CURSOR_INFO cci;
        cci.dwSize = 100;
        cci.bVisible = false;

        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    }
    bool can_go(int x, int y)
    {
        x += pos.X;
        y += pos.Y;
        return x >= 0 && y >= 0 && x < w&& y < h&& graph[y][x] != '1';
    }
    void print_time(double t)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(w / 2 - 3, h + 5); cout << "Time : " << (double)t / 1000;
        hide_cursor();
    }
};

COORD start = { -1, -1 };

void initGraph()
{
    int x = 0, y = 0;

    for (string s : graph)
    {
        for (char c : s)
        {
            switch (c)
            {
            case '0': cout << "  "; break;
            case '1': cout << "■"; break;
            case 'e': cout << "▣"; break;
            case 's':
                start.X = x;
                start.Y = y;
                cout << "  ";
            } x++;
        }
        cout << '\n'; y++; x = 0;
    }
    if (start.X == -1) exit(0);
}

int main()
{
    system("mode con lines=36 cols=105");

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

    initGraph();

    cursor cur(start);
    cur.hide_cursor();

    cur.move(0, 0);

    time_t start = clock();

    while (1)
    {
        if (_kbhit() && _getch() == 224)
        {
            switch (_getch())
            {
            case U: cur.move(0, 1); break;
            case R: cur.move(1, 0); break;
            case D: cur.move(0, -1); break;
            case L: cur.move(-1, 0); break;
            }
        }
        cur.print_time(clock() - start);
    }
}
