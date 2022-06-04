#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>
using namespace std;

constexpr int U = 72;
constexpr int D = 80;
constexpr int L = 75;
constexpr int R = 77;

string graph[] = {
    "1111111111111111111111111111e1",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "100000000000000000000000000001",
    "1s1111111111111111111111111111"
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
        if (graph[pos.Y][pos.X] == 'e')
            exit(0);
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
        gotoxy(w / 2 - 3, h + 5); cout << "현재시간 : " << (double)t / 1000;
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
    system("pause");
    system("pause");
}
