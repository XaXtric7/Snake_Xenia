#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction dir;
bool gameOver;
const int height = 20;
const int width = 20;
int headX, headY, fruitX, fruitY, score;
int tailx[100], taily[100];
int tail_length;

void setup();
void draw();
void input();
void logic();

int main()
{
    char start;
    cout << "\t-----------------------------------------" << endl;
    cout << "\t \t    |* SNAKE XENIA *|" << endl;
    cout << "\t-----------------------------------------" << endl;
    cout << "\tUp='W', Left='A', Down='S', Right='D' " << endl;
    cout << "\tPress 's' to start the game : ";
    cin >> start;

    if (start == 's')
    {
        setup();
        while (!gameOver)
        {
            draw();
            input();
            logic();
            Sleep(30);
            system("cls");
        }
        cout << "\t\t*****************" << endl;
        cout << "\t\t* GAME OVER!:'( *" << endl;
        cout << "\t\t*****************" << endl;
        cout << "\t\t Your Score : " << score << endl;
    }

    return 0;
}

void setup()
{
    gameOver = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
    system("cls");
    // Upper Border
    cout << "\t\t";
    for (int i = 0; i < width - 8; i++)
    {
        cout << "||";
    }
    cout << endl;

    // Snake, fruit, space, and side borders
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // left border
            if (j == 0)
            {
                cout << "\t\t||";
            }
            // Snake Head
            if (i == headY && j == headX)
            {
                cout << "O";
            }
            // fruit
            else if (i == fruitY && j == fruitX)
            {
                cout << "*";
            }
            // Space, Snake Tail
            else
            {
                bool print = false;
                // tail
                for (int k = 0; k < tail_length; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                // space
                if (!print)
                {
                    cout << " ";
                }
            }
            // right border
            if (j == width - 1)
            {
                cout << "||";
            }
        }
        cout << endl;
    }
    // Lower Border
    cout << "\t\t";
    for (int i = 0; i < width - 8; i++)
    {
        cout << "||";
    }
    cout << endl;
    cout << "\t\t\t Score : " << score << endl;
}

void input()
{
    if (_kbhit())
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        default:
            break;
        }
}

void logic()
{
    // tail logic
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = headX;
    taily[0] = headY;
    for (int i = 1; i < tail_length; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    // Direction logic
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    // touch wall;
    if (headX >= width)
    {
        headX = 0;
    }
    else if (headX < 0)
    {
        headX = width - 1;
    }
    if (headY >= height)
    {
        headY = 0;
    }
    else if (headY < 0)
    {
        headY = height - 1;
    }

    // Snake bites itself
    for (int i = 0; i < tail_length; i++)
    {
        if (tailx[i] == headX && taily[i] == headY)
        {
            gameOver = true;
        }
    }

    // Snake eats the fruit
    if (headX == fruitX && headY == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tail_length++;
    }
}
