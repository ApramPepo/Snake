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
}

void draw(void)
{

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