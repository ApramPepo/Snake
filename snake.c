#include <curses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define Width 40
#define height 40

int gameover;
int x, y, fruitX, fruitY, score;
int tailx[100], taily[100];
int tail;

enum direction {stop = 0, left, right, up, down};
enum direction dir;

void setup(void)
{
    gameover = 0;
    dir = stop;
    x = Width / 2;
    y = height / 2;
    srand(time(0));
    fruitX = rand() &Width;
    fruitY = rand() &height;
    score = 0;
}

void draw(void)
{
    system("clear");
    for(int i = 0; i < Width +2; i++)
    {
        printf("#");
    }
    printf("\n");
    for (int a = 0; a < height; a++)
    {
        for (int j = 0; j < Width; j++)
        {
            if (j==0)
            {
                printf("#");
            }
            if (a == y && j == x)
            {
                printf("x");
            }
            else if (a == fruitY && j == fruitX)
            {
                printf("8");
            }
            else {
                int print = 0;
                for (int m = 0; m < tail; m++)
                {
                    if (tailx[m] == j && taily[m] == a)
                    {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print) printf(" ");
            }
            if (j ==Width - 1)
            {
                printf("#");
            }

        }
        printf("\n");
    }
    for (int i = 0; i < Width + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    printf("Score:%d\n", score);
}

void function(void)
{
    struct termios old_tio, new_tio;
    unsigned char ch;

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    if (read(STDIN_FILENO, &ch, 1) == 1)
    {
        switch (tolower(ch))
        {
        case 'w':
        dir = up;
            break;
        case 's':
        dir = down;
            break;
        case 'd':
        dir = right;
            break;
        case 'a':
        dir = left;
            break;
        case 'k':
        gameover = 1;
            break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void logic(void)
{
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;

    for (int i = 1; i <tail; i++)
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case up:
        y--;
        break;

        case down:
        y++;
        break;
        
        case left:
        x--;
        break;

        case right:
        x++;
        break;
    }
    if (x >= Width)
    {
        x = 0;
    }
    else if ( x < 0)
    {
        x = Width - 1;
    }

    if (x >= Width)
    {
        y = 0;
    }
    else if (y < 0) 
    {
        y = height - 1;
    }

    for(int i = 0; i < tail; i++)
    {
        if(tailx[i] == x && taily[i] == y)
        {
            gameover = 1;
        }
    }
    if (x == fruitX && y == fruitY)
    {
        score += 50;
        fruitX = rand() % Width;
        fruitY = rand() % height;
        tail++;
    }
    
}

int main(void)
{
    setup();
    while (!gameover)
    {
        draw();
        function();
        logic();
        usleep(1000);
    }
    return 0;
}