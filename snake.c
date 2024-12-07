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

}

void logic(void)
{

}

int main(void)
{
    setup();

}