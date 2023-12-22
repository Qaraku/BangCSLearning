#include "game_logic.h"
void print_snake()
{
    gotoxy(snake.x * 2 - 1, snake.y);
    color(5);
    printf(" ☯"); // ●
    for (int i = 0; i < snake.len; i++)
    {
        gotoxy(body[i].x * 2 - 1, body[i].y);
        color(i);
        printf(" ☯");
    }
}

void print_wall()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (face[i][j] == WALL && (i == 0 || i == ROWS))
            {
                printf("■ ");
            }
            else if (face[i][j] == WALL)
            {
                printf("■ ");
            }
            else
            {
                printf("  ");
            }
        }
    }
}
void print_food(int *p)
{
    int i = *p;
    int j = *(p + 1);
    free(p);
    color(12);        // 颜色设置为红色
    gotoxy(j * 2, i); // 光标跳转到生成的随机位置处
    printf("❤ ");     // 打印食物
}