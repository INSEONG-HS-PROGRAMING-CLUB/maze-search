#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>
using namespace std;

constexpr int U = 72;
constexpr int D = 80;
constexpr int L = 75;
constexpr int R = 77;

class cursor {
public:
    COORD pos;
    cursor(int x, int y)
    {
        pos.X = x << 1;
        pos.Y = y;
    }
    void gotoxy(int x, int y) {
        cout << "  ";
        pos.X += x << 1;
        pos.Y += y;
        auto std = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(std, pos);
        cout << "■";
    }
    void hide_cursor() {

        CONSOLE_CURSOR_INFO cci;
        cci.dwSize = true;
        cci.bVisible = false;

        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    }
};

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
}
