#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROWS 40
#define COLS 80

#define KONG 0
#define Snake 1
#define Food 2
#define Wall 3

#define Escape 27
#define Space 32
#define Tab 9
#define Enter 13
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

void print_screen(void);
void print_snake(void);
void print_food(void);
void print_wall(void);
void move_snake(void);
void judgeFunc(int x, int y);
void update_screen(void);
void print_start(void);

int face[ROWS][COLS];
void print_start()
{
    printf("Welcome to Snake!\n");
    printf("Press any key to start.\n");
}
void print_screen()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                printf("#");
                face[i][j] = Wall;
            }
            else
            {
                printf(" ");
                face[i][j] = KONG;
            }
        }
    }
}

int main()
{
    system("mode con cols=40 lines=20");
    print_screen();
    system("pause");
    return 0;
}