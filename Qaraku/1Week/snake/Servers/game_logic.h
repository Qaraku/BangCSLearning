#include "sys_logic.h"

void init_snake()
{
    snake.len = 2;
    snake.x = COLS / 2 * 2;
    snake.y = ROWS / 2;
    face[snake.y][snake.x] = HEAD;
    body[0].x = snake.x + 1;
    body[0].y = snake.y;
    body[1].x = snake.x + 2;
    body[1].y = snake.y;
    for (int i = 0; i < snake.len; i++)
    {
        face[body[i].y][body[i].x] = BODY;
    }
}

void move_snake(int arg)
{
    switch (arg)
    {
    case UP:
        if (face[snake.y - 1][snake.x] != WALL)
        {
            snake.y--;
        }
        break;
    case DOWN:
        if (face[snake.y + 1][snake.x] != WALL)
        {
            snake.y++;
        }
        break;
    case LEFT:
        if (face[snake.y][snake.x - 1] != WALL)
        {
            snake.x--;
        }
        break;
    case RIGHT:
        if (face[snake.y][snake.x + 1] != WALL)
        {
            snake.x++;
        }
        break;
    }
}
void RandFOOD()
{
    int i, j;
    do
    {
        // 随机生成食物的横纵坐标
        i = rand() % ROWS;
        j = rand() % COLS;
    } while (face[i][j] != KONG); // 确保生成食物的位置为空，若不为空则重新生成
    face[i][j * 2] = FOOD;        // 将食物位置进行标记
    color(12);                    // 颜色设置为红色
    gotoxy(j * 2, i);             // 光标跳转到生成的随机位置处
    printf("❤");                  // 打印食物
}

void update_snake()
{
    face[snake.y][snake.x] = HEAD;
}

void init_face()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                face[i][j] = WALL;
            }
        }
    }
}
