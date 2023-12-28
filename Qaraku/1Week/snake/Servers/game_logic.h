#include "sys_logic.h"

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

void init_snake()
{
    snake.len = 2;
    snake.x = COLS / 2;
    snake.y = ROWS / 2;
    // face[snake.y][snake.x] = HEAD;
    body[0].x = snake.x + 1;
    body[0].y = snake.y;
    body[1].x = snake.x + 2;
    body[1].y = snake.y;
}

void update_snake()
{
    // print操作上
    gotoxy(body[snake.len - 1].x * 2 - 1, body[snake.len - 1].y);
    printf("  ");
    // face[snake.y][snake.x] = HEAD;
    for (int i = snake.len - 1; i > 0; i--)
    {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }
    // snake.len += 1;
}
void move_snake(int arg)
{

    switch (arg)
    {
    case UP:
        if (face[snake.y - 1][snake.x] != WALL)
        {
            update_snake();
            body[0].x = snake.x;
            body[0].y = snake.y;
            snake.y--;
        }
        break;
    case DOWN:
        if (face[snake.y + 1][snake.x] != WALL)
        {
            update_snake();
            body[0].x = snake.x;
            body[0].y = snake.y;
            snake.y++;
        }
        break;
    case LEFT:
        if (face[snake.y][snake.x - 1] != WALL)
        {
            update_snake();
            body[0].x = snake.x;
            body[0].y = snake.y;
            snake.x--;
        }
        break;
    case RIGHT:
        if (face[snake.y][snake.x + 1] != WALL)
        {
            update_snake();
            body[0].x = snake.x;
            body[0].y = snake.y;
            snake.x++;
        }
        break;
    }
}

void RandFOOD()
{

    int x, y;

    do
    {
        // 随机生成食物的横纵坐标
        x = rand() % ROWS;
        y = rand() % COLS;
    } while (face[x][y] != KONG); // 确保生成食物的位置为空，若不为空则重新生成
    face[x][y] = FOOD;            // 将食物位置进行标记
    food.x = x;
    food.y = y;
    food.exist = 1;
}

int Judge_Sfood()
{
    if (snake.x == food.x && snake.y == food.y)
    {
        face[food.x][food.y] = KONG;
        food.exist = 0;
        snake.len++;
        update_snake();

        return 1;
    }
    else
    {
        return 0;
    }
}