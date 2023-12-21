#include "snake.h"
// #define ROWS 40
// #define COLS 80

struct Snake
{
    int len;
    int x;
    int y;
} snake;
struct Snake_Body
{
    int x;
    int y;
} body[ROWS * COLS]; // 一维数组

int formatConsole()
{
    char chCmd[32];
    system("color 0a");
    system("title 贪吃蛇");
    sprintf(chCmd, "mode con cols=%d lines=%d", COLS, ROWS);
    system(chCmd);
}
void init_face()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                face[i][j] = Wall;
            }
        }
    }
}
void print_wall()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (face[i][j] == Wall)
            {
                printf("■");
            }
            else if (face[i][j] == HEAD)
            {
                printf("●");
            }
            else if (face[i][j] == BODY)
            {
                printf("○");
            }
            else if (face[i][j] == Food)
            {
                printf("◆");
            }
            else
            {
                printf(" ");
            }
        }
    }
}
void init_snake()
{
    snake.len = 2;
    snake.x = COLS / 2;
    snake.y = ROWS / 2;
    face[snake.y][snake.x] = HEAD;
    body[0].x = snake.x + 1;
    body[0].y = snake.y;
    body[1].x = snake.x + 2;
    body[1].y = snake.y;
    for (int n = 1; n <= snake.len; n++)
    {
        face[snake.y][snake.x + n] = BODY;
    }
}
int main()
{
    int key = 0;
    int p;
    init_face();
    init_snake();
    print_wall();
    formatConsole();
    do
    {
        key = getchar();
        print_wall();
        Sleep(50);
        system("cls");
        continue;
    } while (key != Esc);

    system("pause");
}