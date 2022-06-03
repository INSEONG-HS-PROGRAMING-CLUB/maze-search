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
    "111111111111111111111111111101",
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
    "101111111111111111111111111111"
};

int h = sizeof(graph) / sizeof(graph[0]);
int w = graph[0].length();

class cursor {
public:
    COORD pos;
    cursor(int x, int y)
    {
        pos.X = x << 1;
        pos.Y = y;
    }
    void delete_cursor()
    {
        auto std = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(std, pos);
        cout << "  ";
    }
    void gotoxy(int x, int y)
    {
        if (!can_go(x, -y)) return;
        delete_cursor();
        pos.X += x << 1;
        pos.Y += -y;
        auto std = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(std, pos);
        cout << "■";
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
        x += pos.X + x;
        y += pos.Y;
        return (x >> 1) < w && y < h && (x >> 1) >= 0 && y >= 0 && graph[y][x >> 1] == '0';
    }
};

void initGraph()
{
    for (string s : graph)
    {
        for (char c : s)
        {
            if (c - '0')
                cout << "■";
            else
                cout << "  ";
        }
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);

    initGraph();

    cursor cur(1, 18);
    cur.hide_cursor();

    cur.gotoxy(0, 0);

    while (1)
    {
        if (_kbhit() && _getch() == 224)
        {
            switch (_getch())
            {
            case U: cur.gotoxy(0, 1); break;
            case R: cur.gotoxy(1, 0); break;
            case D: cur.gotoxy(0, -1); break;
            case L: cur.gotoxy(-1, 0); break;
            }
        }
    }
}
