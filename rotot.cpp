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
        game_end(pos.X, pos.Y);
    }
    void moveTo(int x, int y)
    {
        if (!can_goto(x, y)) return;
        delete_cursor();
        pos.X = x;
        pos.Y = y;
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
    bool can_goto(int x, int y)
    {
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

int dx[] = { 1, -2, 1, 0 };
int dy[] = { 0, 0, 1, -2 };

void bfs(cursor& cur, time_t st)
{
    queue<pair<int, int>> q;
    bool visit[100][100] = { 0 };
    q.push({ start.X, start.Y });

    while (!q.empty())
    {

        int x = q.front().first;
        int y = q.front().second;
        cur.moveTo(x, y);
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            x += dx[i];
            y += dy[i];
            if (cur.can_goto(x, y) && !visit[y][x])
            {
                visit[y][x] = 1;
                q.push({ x, y });
            }
        }
        Sleep(50);
        cur.print_time(clock() - st);
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

    cur.move(0, 0);
    bfs(cur, clock());
}
