#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <utility>
#include <queue>
using namespace std;

constexpr int U = 72;
constexpr int D = 80;
constexpr int L = 75;
constexpr int R = 77;

string graph[] = {
    "1111111111111111111111111111e1",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "101111111111111111111111111111",
    "100000000000000000000000000001",
    "1s1111111111111111111111111111"
};

int h = sizeof(graph) / sizeof(graph[0]);
int w = graph[0].length();

int dx[] = { 1, -2, 1, 0 };
int dy[] = { 0, 0, 1, -2 };

bool visit[100][100];

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
    void remove(int x, int y)
    {
        gotoxy(x, y);
        cout << "  ";
    }
    void moveto(int x, int y)
    {
        if (!can_goto(x, y)) return;
        gotoxy(x, y);
        cout << "■";
        game_end(x, y);
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
    bool can_goto(int x, int y)
    {
        return x >= 0 && y >= 0 && x < w&& y < h&& graph[y][x] != '1' && !visit[y][x];
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

void dfs(cursor& cur, int x, int y, time_t st)
{
    cur.print_time(clock() - st);
    Sleep(10);
    cur.moveto(x, y);
    visit[y][x] = true;

    for (int i = 0; i < 4; i++)
    {
        x += dx[i];
        y += dy[i];
        if (cur.can_goto(x, y))
        {
            dfs(cur, x, y, st);
            Sleep(10);
            cur.print_time(clock() - st);
            cur.remove(x, y);
        }
    }
}

int main()
{
    system("mode con lines=30 cols=60");

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

    initGraph();

    cursor cur(start);
    cur.hide_cursor();

    time_t st = clock();

    dfs(cur, start.X, start.Y, st);
}
